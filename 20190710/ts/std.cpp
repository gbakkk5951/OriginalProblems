using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
#include <cassert>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef long double Lf;
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 5e5 + 10;
struct _Main {
	int tp;
	int sum[MXN][2];
	int f[MXN], r[MXN], h[MXN];
	int getfa(int nd) {
		if (f[nd]) {
			int ret = getfa(f[nd]);
			r[nd] ^= r[f[nd]];
			return f[nd] = ret;
		} else {
			return nd;
		}
	}
	void merge(int fa, int fb, char re) {
		if (h[fa] > h[fb]) {
			swap(fa, fb);
		} else {
			h[fb] += h[fa] == h[fb];
		}
		tp -= max(sum[fa][0], sum[fa][1]);
		tp -= max(sum[fb][0], sum[fb][1]);
		sum[fb][0] += sum[fa][0 ^ re];
		sum[fb][1] += sum[fa][1 ^ re];
		f[fa] = fb;
		r[fa] = re;
		tp += max(sum[fb][0], sum[fb][1]);
	}
	_Main() {
		int n, Qn;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			sum[i][0] = 1;
		}
		tp = n;
		for (int Q = 1; Q <= Qn; Q++) {
			int a, b, fa, fb;
			read(a); read(b);
			fa = getfa(a), fb = getfa(b);
			if (fa == fb) {
				if (r[a] == r[b]) {
					printf("0 %d\n", tp);
				} else {
					printf("1 %d\n", tp);
				}
			} else {
				merge(fa, fb, r[a] ^ r[b] ^ 1);
				printf("1 %d\n", tp);
			}
		}
		
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
