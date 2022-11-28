
### 1. 考察知识：
区间动态规划

我们用dp[l][r]表示，将l到r建成一棵二叉检索树需要的最小代价

cho[l][r]表示其根结点。

sum表示权值的前缀和

注意，循环的顺序要按照区间长度递增



### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3005;
typedef long long lld;
lld dp[maxn][maxn];//将l到r建成一棵二叉检索树需要的最小代价
int cho[maxn][maxn];//根结点
int v[maxn];
lld sum[maxn];//前缀和
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
	for (int d = 1; d < n; ++d) {//区间长度-1
		for (int i = 1; i <= n - d; ++i) {//左端点
			lld v = LINF, vv;
			int c = i;
			for (int j = i; j <= i + d; ++j) {//根结点
				vv = dp[i][j - 1] + dp[j + 1][i + d];
				if (vv < v) {
					c = j;
					v = vv;
				}
			}
			cho[i][i + d] = c;
			dp[i][i + d] = v + sum[i + d] - sum[i - 1];//sum是其左右子树深度+1,并且加入根结点的代价
		}
	}
	cout << dp[1][n] << endl;
	print(1, n);
	return 0;
}

```
