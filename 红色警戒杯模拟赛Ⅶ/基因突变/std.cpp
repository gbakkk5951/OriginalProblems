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
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const lld MOD = 1e9 + 7;
const int MXN = 2e4 + 10;
struct _Main {
	char a[MXN], b[MXN];
	int n, m, l1, l2;
	lld arr[2][59];
	lld *dp[2];
	lld pow[MXN];
	lld getdp(int len) {
		lld ans = 0;
		int bound = 0;
		int t, it = 0;
		for (int i = 1; i <= len; i++) {
			it ^= 1;
			memset(arr[it], 0, sizeof(arr[it]));
			//bound
			if (bound != -INF) {
				if (bound < 2000000) {
					bound *= m;
				}
				for (int j = 0; j < b[i]; j++) {
					t = bound + j - a[i];
					if (t >= n - 1) {
						ans += pow[len - i];
					} else
					if (t > -(n - 1)) {
						dp[it][t] = (dp[it][t] + 1) % MOD;
					}
				}
				bound += b[i] - a[i];
				if (bound <= -(n - 1)) {
					bound = -INF;
				}
			}
			//other
			for (int j = -n + 2; j <= n - 2; j++) {
				if (dp[it ^ 1][j]) {
					for (int k = 0; k < n; k++) {
						t = j * m + k - a[i];
						if (t >= n - 1) {
							ans += dp[it ^ 1][j] * pow[len - i] % MOD;
						} else
						if (t > -(n - 1)) {
							dp[it][t] = (dp[it][t] + dp[it ^ 1][j]) % MOD;
						}
					}
				}
			}
		}
		for (int i = 1; i < n - 1; i++) {
			ans += dp[it][i];
		}
		ans += bound > 0;
		return ans % MOD;
	}
	_Main() {
		read(n); read(m); read(l1); read(l2);
		pow[0] = 1;
		for (int i = 1; i <= l1 || i <= l2; i++) {
			pow[i] = pow[i - 1] * n % MOD;
		}
		char *sa = a, *sb = b;
		for (int i = 0; i < 2; i++) {
			dp[i] = arr[i] + n - 1;
		}
		if (l1 < l2) {
			sa += l2 - l1;
		} else if (l2 < l1) {
			sb += l1 - l2;
		}
		for (int i = 1; i <= l1; i++) {
			read(sa[i]);
		}
		for (int i = 1; i <= l2; i++) {
			read(sb[i]);
		}
		printf("%lld", getdp(max(l1, l2)));
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
