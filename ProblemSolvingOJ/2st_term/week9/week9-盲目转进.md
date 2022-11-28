
### 1. 考察知识：
快速幂，递推

我们不考虑优化，考虑原本的递推数组
dp[i][x][y] 表示经历了i轮后没有走过障碍且到了(x, y)的概率
我们随机向上下左右走
那么
dp[i + 1][x + 1][y] += dp[i][x][y] / 4
dp[i + 1][x - 1][y] += dp[i][x][y] / 4
dp[i + 1][x][y - 1] += dp[i][x][y] / 4
dp[i + 1][x][y + 1] += dp[i][x][y] / 4
当然如果是障碍，则要为0
我们更改下视角
我们不以从某一点向外来更新，
而是以从四周走来的方式来更新
则
dp[i + 1][x][y] = dp[i][x - 1][y] + dp[i][x + 1][y] + dp[i][x][y - 1] + dp[i][x][y + 1] 
当然如果是障碍，则要为0
我们发现dp[i]只依赖dp[i-1]的数据
所以可以滚动数组
我们可以构造映射，用1维数组来模拟动态长宽的二维乃至三维数组
我们发现递推数组的 / 4的数量一致，所以可以提出来，单独除
由于等概率出现在每个格子处，所以还需要 / (n*m)

### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
lld mod = 7LL << 50 | 1;
lld mod2 = mod << 1;
lld fastpower(lld base, lld index) { // assert -phi(mod) <= index < phi(mod) 快速幂
	lld ret = 1;
	index += index < 0 ? mod - 1 : 0;
	while (index) {
		if (index & 1) ret = ret * (__int128)base % mod;
		if (index >>= 1) base = base * (__int128)base % mod;
	}
	return ret;
}
int main() {//坐标映射方式为f(x, y, 0或1) = x * (m + 2) + y * 2 + (0或1) 
	int n, m, K;
	scanf("%d%d%d", &n, &m, &K);
	long long *arr = (long long *) malloc(sizeof(long long) * (n + 2) * (m + 2) * 2);
	int dx[] = {+2, -2, - (m + 2) * 2, (m + 2) * 2};//上下左右坐标变化
	char *s = (char *) malloc(sizeof(char) * (m + 2) * (n + 2)); 
	int index = 0;
	memset(arr, 0, sizeof(long long) * (n + 2) * (m + 2) * 2);//necessary
	for (int i = 1; i <= n; ++i) {
		int x = i * (m + 2) << 1;
		scanf("%s", s + (x >> 1) + 1);
		for (int j = 1; j <= m; ++j) {
			x += 2;
			arr[x] = s[x >> 1] -= '0';//根据地图赋值递推数组的初值
		}
	}
	long long tmp;
	for (int I = 1; I <= K; ++I) {//走的步数
		index ^= 1;//index是0或1,用来模拟滚动数组
		for (int i = 1; i <= n; ++i) {//横坐标
			int x = i * (m + 2) * 2 | index;
			for (int j = 1; j <= m; ++j) {//纵坐标
				x += 2;
				if (s[x >> 1]) {//道路, 如果你判的不是原地图而是递推数组，则可能在一个孤立的道路上出问题
					tmp = arr[x + dx[0] ^ 1];
					for (int k = 1; k < 4; ++k) {//4个方向走来
						tmp += arr[x + dx[k] ^ 1];
					}
					arr[x] = tmp;//用一个临时变量来暂存或许可以加速,不必要
				}
			}
		}
	}
	__int128 ans = 0;;
	for (int i = 1; i <= n; ++i) {//统计答案
		int x = i * (m + 2) << 1 | index;
		for (int j = 1; j <= m; ++j) {
			x += 2;
			ans += arr[x];
		}
	}
	ans %= mod;
	ans = ans * fastpower(n * m, -1) % mod * (__int128)fastpower(4, -K) % mod;// 除以(n * m * 4的k次方)
	printf("%lld", (lld)ans);
	return 0;
}


```
