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
	lld ans, mul;
	char c[6][6];
	void dfs(int x, int y) {
		if (x == n + 1) {
			int i, j;
			for (i = 1; i <= n; i++) {
				for (j = 2; j <= n; j++) {
					if (c[i][j] != c[i][j - 1]) break;
				}
				if (j == n + 1) break;
				for (j = 2; j <= n; j++) {
					if (c[j][i] != c[j - 1][i]) break;
				}
				if (j == n + 1) break;
			}
			if (i == n + 1) {
				ans = (ans + mul) % MOD;
			}
			return;
		}
		int nx = x, ny = y + 1;
		if (ny == n + 1) ++nx, ny = 1;
		for (int i = 1; i <= m; i++) {
			if (rate[x][y][i] == 0) continue;
			lld lst = mul;
			c[x][y] = i;
			mul = mul * rate[x][y][i] % MOD;
			dfs(nx, ny);
			mul = lst;
		}
	}
	_Main() {
		read(n); read(m);
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
				}
			}
		}
		mul = 1;
		dfs(1, 1);
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
