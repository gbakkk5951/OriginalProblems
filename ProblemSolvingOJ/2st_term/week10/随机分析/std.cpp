#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int mod = 998244353;
const int maxn = 301;
int rev, n;
lld quickpow(lld base, lld index) {
	lld ret = 1;
	while (index) {
		if (index & 1) ret = ret * base % mod;
		if (index >>= 1) base = base * base % mod;
	}
	return ret;
}
int dp[maxn][maxn];// i used j time arrived at k; can be O(n) but not necessary
int a;
int ans[maxn];
int main() {
	cin >> n;
	rev = quickpow(n, mod - 2); 
	for (int i = 1, a; i <= n; ++i) {
		cin >> a;
		memset(dp[0], 0, sizeof(dp[0]));
		dp[0][i] = 1;
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				dp[j][k] = (dp[j - 1][k] * (n - 1LL) % mod * rev + dp[j - 1][j] * (lld)rev) % mod;
			}
			dp[j][j] = rev;
		}
		for (int k = 1; k <= n; ++k) {
			ans[k] = (ans[k] + dp[n][k] * (lld)a) % mod;
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " ";
	}
	return 0;
}
