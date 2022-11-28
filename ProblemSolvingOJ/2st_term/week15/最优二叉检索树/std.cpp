#include <bits/stdc++.h>
using namespace std;
const int maxn = 3005;
typedef long long lld;
lld dp[maxn][maxn];
int cho[maxn][maxn];
int v[maxn];
lld sum[maxn];
lld LINF = 0x3f3f3f3f3f3f3f3fLL;
int n;
void print(int l, int r) {
	if (l > r) return;
	int nd = cho[l][r];
	printf("%d ", nd);
	print(l, nd - 1);
	print(nd + 1, r);
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
		dp[i][i] = v[i];
		cho[i][i] = i;
		sum[i] = sum[i - 1] + v[i];
	}
	for (int d = 1; d < n; ++d) {
		for (int i = 1; i <= n - d; ++i) {
			lld v = LINF, vv;
			int c = i;
			for (int j = i; j <= i + d; ++j) {
				vv = dp[i][j - 1] + dp[j + 1][i + d];
				if (vv < v) {
					c = j;
					v = vv;
				}
			}
			cho[i][i + d] = c;
			dp[i][i + d] = v + sum[i + d] - sum[i - 1];
		}
	}
	cout << dp[1][n] << endl;
	print(1, n);
	return 0;
}
