
### 1. 考察知识：

组合数/乘法逆元/快速幂（或线性逆元）/求和式的转化/更节省性能的组合数计算


### 2. 优秀代码
**一**
作者：缪天顺
运行十分敏捷，71ms
```C++
#include <iostream>
using namespace std;
const int MOD = 998244353;
typedef long long ll;


inline ll powr(long long x, ll y) {
	long long res = 1;
	while (y) {
		if (y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}


inline ll inv(ll x) {
	return powr(x, MOD - 2);
}


inline ll comb(int x, int y) {
	ll res = 1;
	ll temp = 1;
	for (int i = 1; i <= x; ++i) {
		res = (res * (i + y) % MOD) % MOD;
		temp = (temp * i) % MOD;
    }
    res = (res * inv(temp) % MOD) % MOD;
	return res;
}

int main()
{
	int n, m, k, c;
	scanf("%d%d%d%d", &n, &m, &k, &c);
	ll temp1 = comb(n, m - 1);
	ll temp2 = (((temp1 * (m + n) % MOD) % MOD) * inv(n + 1) % MOD) % MOD;
	printf("%d", (c * temp1 % MOD + k * temp2 % MOD) % MOD);
}

```
**二**
作者：张浩宇

组合数法
推导见题目提示
思路是用 从1到x_1对1求和 来表示 x_1
然后拆成 c * (n个求和嵌套对1求和) + k * (n+1个求和嵌套对1求和)

更一般化的计算见[某不科学的超数列求和2](https://github.com/gbakkk5951/OriginalProblems/tree/master/高考系列试题/数学/求和/某不科学的超数列求和2)
完整论文部份描述了完整的步骤（虽然没写代码）


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 998244353;
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
    int n, m, k, c;
    cin >> n >> m >> k >> c;
    int from = m - 1 +( n + 1) - 1;
    int choose = n;
	ll tmp = 1;
	for (int i = from - choose + 1; i <= from; ++i) tmp = tmp * i % p;
	ll rev = 1;
	for (int i = 2; i <= choose + 1; ++i) rev = rev * i % p;
	rev = fastpower(rev, p - 2);
    cout << (rev * (tmp * (from + 1) % p) % p * k 
			+ rev * (choose + 1) % p * tmp % p * c) % p;
}



```
