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
inline int lb(int a) {
	return a & (-a);
}
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
const lld MOD = 1e9 + 7;
const int MXP = 257;
struct _Main {
	lld pow[MXP + 1];
	lld dp[65];
	lld mul(lld a, lld b) {
		return a * b % MOD;
	}
	lld brute(int n) {
		lld brt = 0;
		for (int j = 0; j < n; j++) {
			for (int k = j + 1; k <= n; k++) {
				int val = j ^ k;
				while (val) {
					++brt;
					val -= lb(val);
				}
			}
		} 
		return brt % MOD;
	}
	lld solve(lld n) {
		int l[65], ln = 0;
		int now = 0, x;
		while ((1 << now) < (n ^ (1 << now))) ++now;
		lld ret = 0;
		while (now >= 0) {
			if ((1 << now) & n) {
				ret = (ret + dp[now]) % MOD;
				for (int i = 0; i < ln; i++) {
					x = l[i] - now;
					ret = (ret + pow[x - 1] * x % MOD * pow[now]) % MOD;
					ret = (ret + pow[x + 2 * now - 1] * now) % MOD;
				}
				l[ln++] = now;
			}
			--now;
		}
		return ret;
	}
	_Main() {
		pow[0] = 1;
		for (int i = 1; i <= MXP; i++) {
			pow[i] = (pow[i - 1] << 1) % MOD;
		} 
		dp[0] = 0; dp[1] = 1;
		for (int i = 2; i <= 14; i++) {
			dp[i] = pow[2 * i - 2] + (i - 1) * pow[2 * i - 3];
			dp[i] += dp[i - 1] << 1;
			dp[i] %= MOD;
		}
		int Tn, n;
		read(Tn);
		for (int T = 1; T <= Tn; T++) {
			read(n);
			printf("Case #%d: %lld\n", T, solve(n + 1));
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
