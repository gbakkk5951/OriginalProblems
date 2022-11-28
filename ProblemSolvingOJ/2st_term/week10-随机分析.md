
### 1. 考察知识：
对一个概率不均匀的洗牌算法的分析

两种方案
1.算出i到j的概率，然后与数值相乘得到期望
2.直接用期望进行运算，复杂度更低

### 2. 优秀代码
**一**
作者：张浩宇

算出概率后乘数值

```c++
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
		for (int j = 1; j <= n; ++j) {//j轮移动后a[i]被移动到k的概率
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

```

**二**
作者：胡皓明
非常敏捷
直接用期望来计算
只需要O(n^2)

```C++
#include <cstdio>
#define MOD 998244353
int n;
long long invn, a[310][310];
long long fp(long long b, long long p, long long m)
{
	long long ans = 1;
	while(p)
	{
		if(p & 1)
			ans = ans * b % m;	
		b = b * b % m;
		p /= 2;
	}
	return ans;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i][0]);
	invn = fp(n, MOD - 2, MOD);
	long long n_but_one = (n-1) * invn % MOD;
	for(int i = 1; i <= n; i++)
	{
		long long Ei = 0;
		for(int j = 1; j <= n; j++)
		{
			Ei = (Ei + a[j][i-1] * invn % MOD) % MOD;
			if(i != j)
			{
				a[j][i] = (a[i][i-1] * invn % MOD + a[j][i-1] * n_but_one % MOD)% MOD;
			}
		}
		a[i][i] = Ei;
	}
	for(int i = 1; i <= n; i++)
		printf("%lld ", a[i][n]);
	return 0;
}
```