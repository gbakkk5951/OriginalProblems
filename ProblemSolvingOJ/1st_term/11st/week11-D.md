
### 1. 考察知识：搜索？、图论基础

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
性质：从某个点出发不断移动到指向的点，必然会遇到环
整个结构是若干个（可能是1个）rho型结构（可能退化为环）组成，

要注意的点：自环也是环
如果大量重复访问大量的结点，会超时

为了更好理解各种算法，你可以画几个rho型图

比如
5
2
3
4
5
3
你的算法应当可以在以其他顺序对该结构进行标号时仍然有正确的结果


```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 10;
int vis[MXN], d[MXN], stk[MXN], instk[MXN];
int top;
int n;
int main() {
	int ans = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> d[i];
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		int nd = i;
		while (!vis[nd]) {//vis表示是否被访问过，instk == 0表示在本轮中没有访问过，否则表示其在栈中的下标
			vis[nd] = 1; 
			stk[instk[nd] = ++top] = nd;//将本轮访问到的结点加入栈中，
			nd = d[nd];
		}
		if (instk[nd]) {//找到环
			ans += top - instk[nd] + 1;
		}
		while (top) {//清空
			instk[stk[top--]] = 0;
		}
	}
	cout << ans;
	return 0;
}
```

**二**
作者：陈荣锴

```C++
#include <cstdio>
int n, g[100003], vis[100003], ans;
void dfs(int x, int d)
{
    vis[x] = d;
    if (vis[g[x]] > 0)
        ans += d - vis[g[x]] + 1;
    if (vis[g[x]] == 0)
        dfs(g[x], d + 1);
    vis[x] = -1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &g[i]);
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0)
            dfs(i, 1);
    printf("%d", ans);
    return 0;
}

```
**三**
作者：刘博悦

```C++
#include <stdio.h>

int vhash[100001], a[100001], ans;
int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int count = 1;
    for (int i = 1; i <= n; i++) {
        int countnow = count;//本轮开始的编号
        int now = i;
        while (!vhash[now]) {
            vhash[now] = count;
            count++;
            now = a[now];
        }
        if (vhash[now] >= countnow) {
            ans += count - vhash[now];
        }
    }
    printf("%d", ans);
    return 0;
}

```


**四**
作者：邓振霄
利用dfs先找到每一个环上的一个点，标记为在环上（每个环恰有一个点被标记）
最后从每一个被标记的点出发，
计算环的长度

```C++
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
int nxt[N], vis[N], inCyc[N];
int ans = 0;

void dfs(int cur, int tag)
{
    if (vis[cur] == tag)
        inCyc[cur] = 1;
    else if (!vis[cur])
        vis[cur] = tag, dfs(nxt[cur], tag);
}

void calcAns(int cur)
{
    if (vis[cur])
        return;
    vis[cur] = 1;
    ++ans;
    calcAns(nxt[cur]);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &nxt[i]);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i, i);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
        if (inCyc[i])
            calcAns(i);
    printf("%d\n", ans);
    return 0;
}
```

**五**
作者：缪天顺

```c++
#pragma warning(disable: 4996)
#include <iostream>
#include <algorithm>
using namespace std;
const int NUM = 1e5 + 100;
int list[NUM] = {}, list2[NUM] = {};

int main()
{
	int N, *pt1 = list, *pt2 = list2, *temp;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &list[i]);
	for (int a = 0; a <= 20; ++a) {
		for (int i = 1; i <= N; ++i)
			pt2[i] = pt1[pt1[i]];
		temp = pt1;
		pt1 = pt2;
		pt2 = temp;
	}
    //进行21次倍增，循环结束后，list保存的值是移动 2的21次方 次后的目的地，这样必然不存在不在环上的结点。
    //又由于环上不同的点移动相同次数后，仍然是不同的，所以list中不同的数个个数即为环上结点的个数
	int count = 0;
	sort(list, list + N + 1);
	for (int i = 0; i < N; ++i) //统计有多少个不同的目的地，因为list[0] == 0所以不用特别+1
		if (list[i + 1] > list[i]) ++count; 
	printf("%d", count);
}
```