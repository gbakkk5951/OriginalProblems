
### 1. 考察知识：搜索（当然也可以用递推）

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
枚举进货方案里有什么，
为了防止{3, 4}和{4, 3}被重复统计
要求被加入的物品的价格单调不降（也可以单调不增）

322ms，大概是一般搜索中最快的

由于X <= 80时，答案其实是在998244353以内的，所以其实不用 long long 也不用取模

```c++
#include <bits/stdc++.h>
using namespace std;
int ans;
int x;	
void search(int i, int rem) { // i表示当前要被选的物品的价格，rem表示剩余钱数
	if (i + 1 < rem) search(i + 1, rem); //尝试选下一种物品
	ans += rem -= i; // rem -= i选了当前物品， ans += 表示将{{恰为当前进货组合不再选其他物品}的那种方案}对答案的贡献加到答案中
	if (rem > i) search(i, rem); //尝试继续选
}//这里用了 > < 却没有用 >= 和 <= 是因为当剩余钱数为0的方案，对答案没有影响，故可以省略
int main() {
	cin >> x;
	ans = x; //不进货
	if (x) search(1, x); //特判 x == 0
	cout << ans;
	return 0;
}

```


**二**
作者：朱宇博
该代码会超时，因为比如在X=7时，
{3, 3}方案会枚举为
{0, 0, 3 * 2, 0, 0, 0, 0}
而显然后面的四个0不应当被枚举，
在不能选择更多的情况下应当果断剪枝掉以该方案为基础的计算

```C++
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int X;
int ans = 0;
void dfs(int depth, int currentAns)
{
	if (currentAns > X) return;
	if (depth == X + 1)
	{
		if (currentAns <= X) ans += X - currentAns;
		return;
	}

	int up = (X - currentAns) / depth;
  for (int i = 0; i <= up; i++)
    dfs(depth + 1, currentAns + i * depth);
}

int main()
{
  scanf("%d", &X);
  dfs(1, 0);
  printf("%d", ans);
  return 0;
}
```

**三**
作者：朱宇博
比我的更好理解，但是由于无法尾递归优化，导致跑得比较慢
```C++
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int X;
int ans = 0;
void dfs(int depth, int currentAns)
{
    if (depth == X + 1 || depth + currentAns > X) {ans += X - currentAns; return;} 
  for (int t = currentAns; t <= X; t += depth)
    dfs(depth + 1, t);
}

int main()
{
  scanf("%d", &X);
  dfs(1, 0);
  printf("%d", ans);
  return 0;
}
```
**四**
作者:张浩宇
递推版本
空间复杂度O( $$ n^2 $$)
时间复杂度O( $$ n^2logn $$)
```C++
#include <bits/stdc++.h>
using namespace std;
int dp[81][81]; // dp[i][j]表示最大值 <= i, 和 == j的方案数
int main()
{  
    int x;
    cin >> x;
    dp[0][0] = 1;
    for (int i = 1; i <= x; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j < x; ++j) {// dp[...][x]用不到
            dp[i][j] = dp[i - 1][j]; //不选价格为i的物品
            for (int k = j - i; k >= 0; k -= i) {//枚举选了几个i
                dp[i][j] += dp[i - 1][k];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < x; ++i) { 
        ans += dp[x][i] * (x - i);
    }
    cout << ans;
    return 0;
}
```

**五**
作者:徐沐杰
优秀的写法，只用了O($$ n^2 $$)的空间和O( $$ n^2 $$ )的时间
利用同最大值之间的关系，避免了枚举选了几个最大值
```c++
#include<cstdio>
const int mod = 998244353;
int X, f[85][85];
int main() {
	scanf("%d", &X);
	f[0][0] = 1;
	for (int i = 1; i <= X; i++)
		for (int j = 0; j <= X; j++)
			if (j >= i) f[i][j] = (f[i - 1][j] + f[i][j - i]) % mod;
			else f[i][j] = f[i - 1][j];
	int ans = 0;
	for (int i = 0; i <= X; i++) ans = (ans + (f[X][i] * 1ll * (X - i)) % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
```

**六**

作者:赵烜呈
极其优秀的写法，只用了O(n)的空间和O( $$ n^2 $$ )的时间，modd可以省略
```c++
#include<cstdio>
#define modd 998244353
int num[85], ans;//num[a]和为a的方案
int n;
int main()
{
	int i, j, k;
	scanf("%d" ,&n);
	num[0] = 1;
	for(i = 1; i <= n; i++)
		for(j = i; j <= n; j++) //将最大值 <= i - 1, 和 == j的方案数 更新为 最大值 <= i, 和 == j的方案数
			num[j] = (num[j] + num[j - i])%modd;
	for(i = 0; i <= n; i++) ans = (ans + (n - i) * num[i] % modd) % modd;
	printf("%d" ,ans);
	return 0;
}
```
**七**
作者：郑逸云
记忆化搜索，和递推类似
```C++
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, ans[85][85];
int solve(int deep, int res)
{
  if (deep == n + 1)
    return res;
  if (ans[deep][res] != -1)
    return ans[deep][res];
  int now = 0;
  ans[deep][res] = 0;
  for (int i = 0; i <= n && (res - i * deep >= 0); i++)
  {
    ans[deep][res] += solve(deep + 1, res - i * deep);
    if (ans[deep][res] >= mod)
      ans[deep][res] -= mod;
    if (now >= mod)
      now -= mod;
  }
  return ans[deep][res];
}
int main()
{
  memset(ans, -1, sizeof(ans));
  cin >> n;
  if (n == 0)
  {
    cout << 0;
    return 0;
  }
  solve(1, n);
  cout << ans[1][n];
  return 0;
}
```

**八**
作者：缪天顺
该解法不是课程内容，不需要掌握
[五边形数和整数拆分](https://blog.csdn.net/qq_33229466/article/details/80359560)
```c++
#pragma warning(disable: 4996)
#include <iostream>
const long long BIG = 998244353;
using namespace std;

int main()
{
	int list1[100] = {};
	for (int k = -7; k <= 7; ++k)
		list1[k * (3 * k - 1) / 2] += (k & 1) ? -1 : 1;
	long long list2[100] = {1};
	for (int i = 1; i <= 80; ++i)
		for (int j = 0; j < i; ++j) {
			list2[i] -= list2[j] * list1[i - j];
		}
	int x;
	scanf("%d", &x);
	long long res = 0;
	for (int i = 0; i < x; ++i) {
		res += list2[i] * (x - i);
	}
	printf("%d", res % BIG);
}
```