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
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1e7 + 10;
const lld MOD = 1e9 + 7;
const lf e = exp(1.0);
struct _Main {
	lld A, B, C, D;
	lld f[MXN], fr[MXN], cp[MXN], dp[MXN], r[MXN];
	lld q[MXN], mx;
	/*
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		while (pow) {
			ret = (pow & 1) ? ret * base % MOD : ret;
			base = (pow >>= 1) ? base * base % MOD : base;
		}
		return ret;
	}*/
	lld com(int n, int m) {
		return f[n] * fr[m] % MOD * fr[n - m] % MOD; 
	}
	void init(int n) {
		r[0] = 0;
		dp[0] = cp[0] = f[0] = f[1] = fr[0] = fr[1] = r[1] = 1;
		dp[1] = D; cp[1] = C;
		for (int i = 2; i <= n; i++) {
			r[i] = -MOD / i * r[MOD % i] % MOD + MOD;
			f[i] = f[i - 1] * i % MOD;
			fr[i] = fr[i - 1] * r[i] % MOD;
//			fr[i] = fastpower(f[i], MOD - 2);
			cp[i] = cp[i - 1] * C % MOD;
			dp[i] = dp[i - 1] * D % MOD;
		}
	}
	_Main() {
		read(A); read(B); read(C); read(D);
		int Qn, n;
		read(Qn);
		for (int Q = 1; Q <= Qn; Q++) {
			read(q[Q]); mx = max(mx, q[Q]);
		}
		init(mx);
		for (int Q = 1; Q <= Qn; Q++) {
			lld ans = 0;
			n = q[Q];
			ans += cp[n - B + 1] % MOD;
			for (int i = 1; !(n - (i - 1) * e < B); i++) {
				for (int j = max(ceil(n - i * e - B), 0.0); !(n - j - (i - 1) * e < B); j++) {
//					printf("i = %d, j = %d\n", i, j);
					//end at f(n - i * e - j)
					if (n - i * e - (j - 1) < B) {//最后一个必须-e
						ans = (ans + com(i + j - 1, j) * cp[j] % MOD * dp[i]) % MOD;
					} else {//最后一次可1可e
						ans = (ans + com(i + j, j) * cp[j] % MOD * dp[i]) % MOD;
					}
				}
			}
			printf("%lld\n", ans * A % MOD);
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
