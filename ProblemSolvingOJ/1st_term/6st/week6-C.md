
### 1. 考察知识：枚举/搜索/递归/动态规划

思路如下：


### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，用了两种枚举方式
dfs1中的参数表示
要求你枚举 在 {
    已经从[1, now - 1]中选了cho个，
    并且已经选了的部份，在最终求和中的贡献为sum
}
的前提下可能的结果值，并更新全局变量ans

dfs2则

要求你计算 在 {
    已经从[1, now - 1]中选了cho个
}
的前提下，后面的部份能贡献的最大值为多少
即要求你计算，在[now, n]中选k - cho个猫，最大的对答案的贡献值

每一步，要么选now，要么不选now



```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 30;
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
int v[maxn], n, k;
lld ans = -LINF;
void dfs1(int cho = 0, int now = 1, lld sum = 0) {
	if (now == n + 1) {//now == n + 1纯粹为了压力测试，你可以{选够了就更新答案并返回，剩下的不够选直接返回}
		if (cho == k) ans = max(ans, sum);
		return;
	}
//	if (k - cho <= n - now) //剪枝，不剪也能过
		dfs1(cho, now + 1, sum); //不选 now 号猫
	lld base = 1;
	for (int i = 1; i < k - cho; ++i) {//应该不影响复杂度
		base *= 3;
	}
//	if (cho < k)//剪枝，不剪也能过
		dfs1(cho + 1, now + 1, sum + v[now] * base);//选 now 号猫
}
lld dfs2(int cho = 0, int now = 1) {
	if (now == n + 1) {
		return cho == k ? 0 : -LINF;
	}
	lld ret = -LINF;
//	if (k - cho <= n - now) //剪枝，不剪也能过
		ret = max(ret, dfs2(cho, now + 1)); //不选 now 号猫
	lld base = 1;
	for (int i = 1; i < k - cho; ++i) {//应该不影响复杂度
		base *= 3;
	}
/*	if (cho < k)*/ { //剪枝，不剪也能过
		lld tmp = dfs2(cho + 1, now + 1);//选 now 号猫
		if (tmp != -LINF) {
			ret = max(ret, tmp + base * v[now]);
		}
	}
	return ret;
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> v[i];
	dfs1();
	assert(dfs2() == ans);
	cout << ans;
	return 0;
}

```




**二**
作者：张浩宇
用了后来提示的作法，递归的定义是动态规划风格的
可以容易地转化为递推
64位编译器下long和long long表示范围相同
32位编译器下long和int表示范围相同

```C++
#include <bits/stdc++.h>
typedef long l;
l p[30], v[30];
const l inf = 0x7fffffffffffffff;
l n, k;
l calc(l begin, l remain) {//求解从begin号到第n号猫中，还需要选择remain只猫的最优解
    if (remain == 0) return 0; //（1）如果不用选了即remain == 0，那么返回值为0
    if (n - begin + 1 < remain) return -inf; //（2）如果不够选了，即(n - begin + 1) < remain, 那么不存在合法方案，应当返回一个−∞
    return std::max(calc(begin + 1, remain), calc(begin + 1, remain - 1) + p[remain - 1] * v[begin]);//（3）枚举第begin号猫要不要选，取最优
}
int main() {
    std::cin >> n >> k;
    for (l i = 1; i <= n; ++i) std::cin >> v[i];//读入优秀值
    p[0] = 1;//很重要
    for (l i = 1; i < k; ++i) p[i] = p[i - 1] * 3;//预处理3的幂次
    std::cout << calc(1, k);
    return 0;
}
```
**三**
作者：黄泽方
zyb推荐的搜索风格写法
每次“尝试”后，要擦除尝试造成的“痕迹”（当然ans除外）
即恢复现场
m表示要决定 第m个被选择的猫 是哪个猫
其实从last+1开始，就通过隐式约定的方式，避免了vis[i] == 1的情况，vis数组可以删除
（如果不从last+1而是从1开始枚举，那么即便你continue，也是要耗费时间的，最终导致超时TLE）
如果用返回值或者参数来传递sum，而不是全局变量，那么就不需要恢复sum
另外 last 其实不需要恢复

```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 25 + 5;
int n, k, last, j, l;
long long sum = 0;
long long ans = -0x3f3f3f3f3f3f3f3f;
int val[N], vis[N];
long long product[25];//这是有问题的，在main中，用到了product[k], k最大是25,所以这里最少写26,或者更好的直接使用N
void solve(int *a, int m)
{
    if (m == k + 1)
    {
        if (sum > ans)
        {
            ans = sum;
        }
        return;
    }
    for (int i = last + 1; i <= n; i++)
    {
        if (vis[i] == 1)
            continue;
        val[m] = i;
        vis[i] = 1;
        last = i;
        sum += (a[val[m]] * product[m]);
        solve(a, m + 1);
        sum -= (a[val[m]] * product[m]);
        vis[i] = 0;
        last = 0;
    }
}
int main()
{
    cin >> n >> k;
    int a[N];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    product[k] = 1;//这里
    for (int i = k - 1; i > 0; i--)
    {
        product[i] = 3 * product[i + 1];
    }
    solve(a, 1);
    cout << ans;
    return 0;
}
```

zhy修改后的版本
```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 25 + 5;
int n, k;
long long ans = -0x3f3f3f3f3f3f3f3f;
long long product[N];//如果这里改成25,交上去会挂
void solve(int *a, int m, int last, long long sum)
{
    if (m == k + 1)
    {
        if (sum > ans)
        {
            ans = sum;
        }
        return;
    }
    for (int i = last + 1; i <= n; i++)
    {
        solve(a, m + 1, i, sum + a[i] * product[m]);
    }
}
int main()
{
    cin >> n >> k;
    int a[N];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    product[k] = 1;
    for (int i = k - 1; i > 0; i--)
    {
        product[i] = 3 * product[i + 1];
    }
    solve(a, 1, 0, 0);
    cout << ans;
    return 0;
}
```


**四**
作者：张浩宇
动态规划写法，将解法二改成了递推形式。
```c++
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 30;
lld base[maxn]; // 3的幂次
lld dp[maxn][maxn];// dp[i][j]表示从前i个猫中选了j个的最大贡献值
int main() {
	cin >> n >> k;
    base[0] = 1;
    for (int i = 1; i < k; ++i) base[i] = base[i - 1] * 3;
    memset(dp, 192, sizeof(dp));//设置为-inf，这样设置的负无穷两个相加不会溢出
	dp[0][0] = 0;
	for (int i = 1, v; i <= n; ++i) {
	    cin >> v;
	    dp[i][0] = 0;
	    for (int j = 1; j <= k; ++j) { // j > i的部份答案一定为-inf，也可以 j <= min(i, k) 来减少计算量，进一步可以预先算出min(i, k)
	        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + base[k - j] * v);
	    }
	}
	cout << dp[n][k];
	return 0;
}

```