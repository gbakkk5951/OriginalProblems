#include <bits/stdc++.h>
using namespace std;
typedef __uint128_t u;
u a;
u mask[129];
u getmask(int bits) {//也可以用这个函数
	return bits == 128 ? ~(u)0 : ((u)1 << bits) - 1;
}
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
int main() {
	assert(mask[0] == getmask(0));
	for (int i = 1; i <= 128; ++i) {//有i个1的掩码
		mask[i] = mask[i - 1] << 1 | 1;
		assert(mask[i] == getmask(i));
	}
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		int op;
		read(op);
		if (op == 1) {
			int x;
			read(x);
			x = x & mask[7]; /*等价于 x = (x % 128 + 128) % 128*/
			a = a >> x | a << (mask[7] ^ x) << 1;
			/*或者
			a = a >> x | (a << (128 - x));
			a = a >> x ^ a << (mask[7] ^ x) << 1;
			a = a >> x ^ a << (127 - x) << 1;
			但不能是
			a = a >> x ^ (a << (128 - x));
			因为x == 0时会挂(此时a << 128 等价于 a << 0)
			
			优先级：先算位移，再异或,或
			*/
		} else
		if (op == 2) {
			printf("%X\n", (int)(a & mask[16]));
		} else
		if (op == 3) {
			int l, r;
			read(l); read(r);
			++r;
			a ^= mask[r] ^ mask[l];
		} else {
			cerr << "Wrong op" << endl;
		}
	}
	return 0;
}
