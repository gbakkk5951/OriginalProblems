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
const lld MOD = 1e9 + 7;
const int PHI = MOD - 1;
struct _Main {

	int n, m;
	lld rate[6][6][8];
	lld pi[6][8];//第i行，全为j的概率
	lld sum[6][6];//第i行，j列的颜色概率和
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		while (pow) {
			ret = (pow & 1) ? ret * base % MOD : ret;
			base = (pow >>= 1) ? base * base % MOD : base;
		}
		return ret;
	}
	lld dp[2][(1 << 15) + 10];
	void getdp() {
		int it = 1;
		lld *ldp, *ndp = dp[it];
		int MX = 1 << n * 3;
		char c[6];
		for (int I = 0; I < MX; I++) {
			ndp[I] = 1;
			int flag = 0;
			for (int i = 1; i <= n; i++) {
				c[i] = (I >> ((i - 1) * 3)) & 7;
				ndp[I] = ndp[I] * rate[1][i][c[i]] % MOD;
				if (i > 1 && c[i] != c[i - 1]) flag = 1;
			}
			if (!flag) ndp[I] = 0;
		}
		for (int i = 2; i <= n; i++) {
			it ^= 1;
			ldp = dp[it ^ 1];
			ndp = dp[it];
			for (int I = 0; I < MX; I++) {
				lld v = ldp[I];
				if (v == 0) continue;
				ldp[I] = 0;
				int S = 0;
				for (int j = 1; j <= n; j++) {
					c[j] = (I >> ((j - 1) * 3)) & 7;
					S |= (c[j] != 0) << j;
				}
				for (int s = S; ; s = S & (s - 1)) {
					int N = 0;//有哪些颜色不可能成为同行颜色。
					lld r = 1;
					for (int j = 1; j <= n; j++) {
						if (c[j] == 0) {
							r = r * sum[i][j] % MOD;
						} else
						if (s >> j & 1) {
							r = r * (sum[i][j] - rate[i][j][c[j]]) % MOD;
							N |= 1 << c[j];
						} else {
							r = r * rate[i][j][c[j]] % MOD;
							N |= ~(1 << c[j]);
						}
					}
					for (int j = 1; j <= m; j++) {
						if (~N >> j & 1) {
							r -= pi[i][j];
						}
					}
					int D = 0;
					for (int j = 1; j <= n; j++) {
						D |= (((S ^ s) >> j & 1) ? c[j] : 0) << ((j - 1) * 3);
					}
					ndp[D] = (ndp[D] + r * v) % MOD;
					if (s == 0) break;
				}
			}
		}
		
	}
	_Main() {
		read(n); read(m);
		if (n == 1 || m == 1) {
			printf("0");
			return;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				lld s = 0;
				for (int k = 1; k <= m; k++) {
					read(rate[i][j][k]);
					s += rate[i][j][k];
				}
				s = fastpower(s, PHI - 1);
				for (int k = 1; k <= m; k++) {
					rate[i][j][k] = rate[i][j][k] * s % MOD;
					sum[i][j] = (sum[i][j] + rate[i][j][k]) % MOD;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				pi[i][j] = 1;
				for (int k = 1; k <= n; k++) {
					pi[i][j] = (pi[i][j] * rate[i][k][j]) % MOD;
				}
			}
		}
		getdp();
		lld ans = dp[n & 1][0];
		ans += ans < 0 ? MOD : 0;
		printf("%lld", ans);
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
