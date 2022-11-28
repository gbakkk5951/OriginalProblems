
### 1. 考察知识：
递推/组合数



### 2. 优秀代码
作者: 胡皓明
滚动数组+直接递推法
dp[i][j]表示m = i, n = j时的答案
dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
为了节省空间，我们只保存本次的i和上一次的i-1故二维数组的第一维只需要2，用i的奇偶来回使用数组

**一**

```C++
#include <cstdio>
#define MOD 998244353
int f[2][2010], n, m;
int mod(long long v)
{
	return v > MOD ? v - MOD : v;
}
int main() 
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		f[1][i] = 1;
	for(int i = 2; i <= m; i++)
	{
		f[i & 1][1] = i;
		for(int j = 2; j <= n; j++)
			f[i & 1][j] = mod(1ll * f[!(i & 1)][j] + f[i & 1][j - 1]);
	}
	printf("%d\n", f[m & 1][n]);
	return 0;
}
```
**二**
作者：张浩宇
组合数解法，递推求组合数

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 998244353;
const int mxn = 4e3 + 10;
int com[mxn][mxn / 2];
// answer = com[(m - 1) + (n + 1) - 1][n];
int main() {
    int n, m;
    cin >> n >> m;
    int from = m - 1 + n + 1 - 1;
    int choose = n;
    for (int i = 0; i <= from; ++i) {
        com[i][0] = 1;
        for (int j = 1; j <= i && j <= choose; ++j) {
            com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
            com[i][j] -= com[i][j] >= p ? p : 0;
        }
    }
    cout << com[from][choose];
}
```

**三**
作者：张浩宇
组合数解法，阶乘+乘法逆元解法
费马小定理+快速幂求乘法逆元


```C++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 998244353;
const int mxn = 1e7 + 10;
int fr[mxn];//阶乘的逆元
// answer = k * com[(m - 1) + (n + 1) - 1 + 1][n + 1] + c * com[(m - 1) + (n + 1) - 1][n];
ll fastpower(ll base, ll pow) {
	ll ret = 1;
	while (pow) {
		if (pow & 1) ret = ret * base % p;
		if (pow >>= 1) base = base * base % p;
	}
	return ret;
}
int main() {
    int n, m;
    cin >> n >> m;
    int from = m - 1 + ( n + 1) - 1;
    int choose = n;
	ll tmp = 1;
	for (int i = from - choose + 1; i <= from; ++i) tmp = tmp * i % p;
	fr[0] = 1;
	fr[choose] = choose;
	for (int i = choose - 1; i >= 1; --i) fr[i] = fr[i + 1] * (ll)i % p;//倒着的阶乘
	ll rev = fastpower(fr[1], p - 2);//(choose + 1)!的逆元
	ll t = 1, a;
	for (int i = choose; i >= 1; --i) {
		a = fr[i];
		fr[i] = rev * t % p;
		t = a;
	}
    cout << fr[choose] * tmp % p;
}
```