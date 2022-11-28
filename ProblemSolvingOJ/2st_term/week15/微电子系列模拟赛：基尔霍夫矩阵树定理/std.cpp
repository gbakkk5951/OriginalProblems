#include <bits/stdc++.h>
using namespace std;
template <typename type>
void read(type &a) {
    int t, f = 0;
    while (!isdigit(t = getchar())) {
        f |= t == '-';
    }
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
    a = f ? -a : a;
}
template <typename type>
void write(type a) {
    char out[35];
    int index = 35;
    out[--index] = 0;
    out[--index] = ' ';
    if (a < 0) {
        putchar('-');
        a = -a;
    }
    if (a) {
        do {
            out[--index] = a % 10 + '0';
        } while(a /= 10);
    } else {
        out[--index] = '0';
    }
    do {
        putchar(out[index]);
    } while(out[++index]);
}
const int maxn = 1e6 + 10;
int position[maxn];
int pre[maxn];
int in[maxn];
int n;
int post[maxn];
void get(int l, int r) {
	static int index = 0;
	if (l > r) return;
	int cho = l;
	int now = pre[++index];
	int p = position[now];
//	assert(l <= p && p <= r);
	get(l, p - 1);
	get(p + 1, r);
	write(now);
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(pre[i]);
	}
	for (int i = 1; i <= n; ++i) {
		read(in[i]);
		position[in[i]] = i;
	}
	get(1, n);
	return 0;
}
