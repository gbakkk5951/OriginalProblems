
### 1. 考察知识：

拓扑排序

已经完成的科技可以直接删掉

重边不需要删除

你只需要更改还剩的依赖条数，不需要去删除

### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
typedef long long lld;
vector<int> whodependme[maxn];//依赖我的科技的列表
lld depmax[maxn] /* 依赖的科技中完成时间最靠后的科技的完成时间 */, ans;
int t[maxn];
int dep_count[maxn];//依赖数量
int n, m;
int got_count;//完成数量
void dfs(int nd) {
	++got_count;
	dep_count[nd] = -1;//-1表示研究完成
	ans = max(ans, depmax[nd] + t[nd]);
	for (auto i : whodependme[nd]) {//枚举元素，语法不一定要学
		depmax[i] = max(depmax[i], depmax[nd] + t[nd]);
		if (--dep_count[i] == 0) {//我是最后一个依赖
			dfs(i);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t[i]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		if (t[u] != -1 && t[v] != -1) {//至少一方已完成时，则不需要添加关系
			dep_count[u]++;//依赖数量
			whodependme[v].push_back(u);
		}
	}
	for (int i = 1; i <= n; ++i) {//这是一个拓扑排序的过程
		if (t[i] == -1) {
			++got_count;
		} else if (dep_count[i] == 0) {//没有依赖，可以研究
			dfs(i);//开始研究
		}
	}
	if (got_count != n) {
		printf("bad idea");
	} else {
		printf("%lld", ans);
	}
	return 0;
}


```
