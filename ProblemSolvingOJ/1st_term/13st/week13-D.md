
### 1. 考察知识：格、子格
枚举一个非空子集S，然后判断S中任意两个元素的上、下确界是否在S中

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
注意，1 << 0位是取出最低位，
而输入是1到n，所以需要先-1
这种枚举集合的方法在提示中有

没必要把枚举出的元素存在数组里，然后再到数组里遍历

用时：303ms
加上被注释的部份：89ms
```c++
#include <cstdio>
int main() {
    int b[22][22];
    int ans = 0, n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &b[i][j]);
			--b[i][j];
		}
	}
	//if (!(n & 1) && n > 8) {//数据特征保证的，而不是问题保证的，你可以改成判断是否层数不超过3,这样正确性有保证，但时间依然依赖于数据
	//    ans = -1 + 4 + (n - 2) * 4 + ((1 << (n - 2)) - (n - 2) - 1);
	//} else
    for (int s = 1; s < (1 << n); ++s) {
	    for (int i = 0; i < n; i++) if (s & (1 << i)) {
	        for (int j = i + 1; j < n; j++) if (s & (1 << j)) {
	            if (!((s & (1 << b[i][j])) && (s & (1 << b[j][i])))) {
	                goto End;
	            }
	        }
	    }
	    ++ans;
	    End:;
	}
	printf("%d", ans);
	return 0;
}

```


**二**
作者：张浩宇
搜索法
用时：170ms，
加上被注释的部份，可以加速到19ms

```C++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 23;
int b[MXN][MXN];
int n;
int used[MXN];
int ans;
inline bool test(int a, int now) {
	return a >= now || used[a];
}
void dfs(int now) {//要求1到now-1之间的已经固定
	if (now == n + 1) {
		++ans;
		return;
	}
	if (!used[now]) dfs(now + 1);
	for (int j = 1; j <= n; ++j) if (used[j]) {
		if (!test(b[j][now], now) || !test(b[now][j], now)) {
			return;
		}
	}
	for (int j = 1; j < now; ++j) if (used[j]) {
		if (!used[b[now][j]]) {
			used[b[now][j]] = now;
		}
		if (!used[b[j][now]]) {
			used[b[j][now]] = now;
		}
	}
	if (used[now] == 0) used[now] = now;
	dfs(now + 1);
	for (int j = now; j <= n; ++j) if (used[j] == now) {
		used[j] = 0;
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> b[i][j];
		}
	}
//	if (!(n & 1) && n > 8) {//数据特征保证的，而不是问题保证的，你可以改成判断是否层数不超过3,这样正确性有保证，但时间依然依赖于数据
//	    ans = 4 + (n - 2) * 4 + ((1 << (n - 2)) - (n - 2) - 1);
//	} else
	dfs(1);
	cout << ans - 1;
	return 0;
}


```
**三**
作者：缪天顺
```C++
#include <cstdio>
int ans, n, mat[25][25], vis[25];
void dfs(int dep)
{
	if(dep == n + 1)
	{
		bool res = 1;
		for(int i = 1; i <= n; i++)
		{
			if(vis[i])
				for(int j = i + 1; j <= n; j++)
					if(vis[j])
					{
						if(!(vis[mat[i][j]] && vis[mat[j][i]]))
						{
							res = 0;
							goto dfs_end;
						}
					}
		}
		dfs_end:
		if(res)
			ans++;
		return;
	}
	vis[dep] = 1;
	dfs(dep + 1);
	vis[dep] = 0;
	dfs(dep + 1);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &mat[i][j]);
	ans = -1;//预先排除空的情况
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
```