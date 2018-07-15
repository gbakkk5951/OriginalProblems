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
struct _Main {
	char c[20][20];
	int n;
	lld pow[405];
	int dp[2][1 << 20];
	char *count[20];
	void init() {
		for (int i = 0; i < 20; i++) {
			count[i] = (char *)new char[1 << i];
			for (int I = 0; I < 1 << i; I++) {
				for (int j = 0; j < i; j++) {
					count[i][I] += ~I >> j & 1;
				}
			}
		}
	}
	lld calccolume() {//不存在行，存在列
		memset(dp, 0, sizeof(dp));
		int it = 0;
		int *ndp, *ldp, cnt, S;
		lld p, v;
		dp[it][(1 << n) - 1] = 1;
		for (int j = 0; j < n; j++) {//算到第j行
			it ^= 1;
			ndp = dp[it];
			ldp = dp[it ^ 1];
			for (int I = j ? 0 : ((1 << n) - 1); I < 1 << n; I++) {
				if (ldp[I] == 0) {
					continue;
				}
				v = ldp[I];
				cnt = count[n][I];//count表示I后n位0的个数
				S = I;
				for (int k = 0; k < n; k++) {
					if (c[j][k]) {
						//已经钦定为黑的不能填白
						S &= ~(1 << k);
						cnt -= ~I >> k & 1;
					}
				}
				p = pow[cnt];//可以填白的方案数
				for (int s = S; s; s = S & (s - 1)) {//将那些填上白色
					ndp[I ^ s] = (ndp[I ^ s] + v * p) % MOD;
				}
				ndp[I] = (ndp[I] + v * (p - 1)) % MOD; //不能全黑
				ldp[I] = 0;
			}
		}
		return dp[it][0] % MOD;
	}
	_Main() {
		init();
		pow[0] = 1;
		for (int i = 1; i <= 400; i++) {
			pow[i] = (pow[i - 1] << 1) % MOD;
		}
		for (n = 1; n <= 15; n++) {
			lld ans = calccolume();
			for (int i = 0; i < n; i++) {
				c[i][i] = 1;
			}
			ans -= calccolume() * 2;
			for (int i = 0; i < n; i++) {
				c[i][n - i - 1] = 1;
			}
			ans += calccolume();
			memset(c, 0, sizeof(c));
			ans %= MOD;
			ans += ans < 0 ? MOD : 0;
			printf("%lld\n", ans);
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
