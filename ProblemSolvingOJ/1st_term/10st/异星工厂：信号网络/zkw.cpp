#include <bits/stdc++.h>
using namespace std;
const int MXN = 700;
struct ZKW {
	char node[MXN];
	void Xor(int s, int t) {// [1, 128] [0, 255]
//		printf("Xor(%d, %d)\n", s, t);
		for (s = 256 | (s - 1), t = 256 | (t + 1); s ^ t ^ 1; s >>= 1, t >>= 1) {
			if (~s & 1) node[s ^ 1] ^= 1;
			if ( t & 1) node[t ^ 1] ^= 1;
		}
	}
	int get(int nd, int nl, int nr, int pos) {
		int x = 0;
		while (nl != nr) {
			int mid = nl + nr >> 1;
			x ^= node[nd];
			if (pos <= mid) {nd = nd << 1; nr = mid;}
			else {nd = nd << 1 | 1; nl = mid + 1; }
		}
		return x ^ node[nd];
	}
	
	int calc(int l, int r, int beg, int x = 0, int nd = 1, int nl = 0, int nr = 255) {
//		printf("calc %d %d %d %d %d %d %d\n", l, r, beg, x, nd, nl, nr);
		x ^= node[nd];
		if (nl == nr) return x << beg;
		int mid = nl + nr >> 1;
		if (l <= mid) {
			if (r > mid) {
				return calc(l, mid, beg, x, nd << 1, nl, mid) | calc(mid + 1, r, (beg + (mid - l + 1)), x, nd << 1 | 1, mid + 1, nr);
			} else {
				return calc(l, r, beg, x, nd << 1, nl, mid);
			}
		} else {
			return calc(l, r, beg, x, nd << 1 | 1, mid + 1, nr);
		}
	}
}tree;
int shift;

template <typename Type>
void read(Type &a) {
    char t, f = 1;
    while (!isdigit(t = getchar())) {
        if (t == '-') f = -1;
    }
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
    a *= f;
}
int mod;
int last;
int calc() {
	if (!mod) return last;
	mod = 0;
	/*int ret = 0;
	for (int i = 0; i < 16; ++i) ret |= tree.get(1, 0, 255, 1 + ((i + shift) & 127)) << i;
	return ret;
	*/
	int l = shift + 1;
	if (l <= 113) {
		return last = tree.calc(l, l + 15, 0);
	} else {
		return last = tree.calc(l, 128, 0) | tree.calc(1, 16 - (128 - l + 1), 128 - l + 1);
	}
}
void Xor(int l, int len) {
	l = ((l + shift) & 127) + 1;
	if (l + len - 1 <= 128) {
		tree.Xor(l, l + len - 1);
	} else {
		tree.Xor(l, 128);
		len -= 128 - l + 1;
		tree.Xor(1, len);
	}
}
int main() {
	int n, x, l, r;
	int op;
	read(n);
	while (n--) {
		read(op);
		switch(op) {
			case 1:
				read(x);
				shift += x;
				shift &= 127;
				mod = 1;
				break;
			case 2:
				printf("%X\n", calc());
				break;
			case 3:
				read(l); read(r);
				Xor(l, r - l + 1);
				mod = 1;
				break;
		}
	}
	return 0;
}
