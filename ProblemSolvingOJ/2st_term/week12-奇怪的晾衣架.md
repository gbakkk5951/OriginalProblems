
### 1. 考察知识：

其实就是给你一个 左child，右brother&sister 的二叉树，

要你输出其还原为多叉树后bfs的结果

对每个高度存一个vector

然后以恰当顺序遍历即可

一个点是根结点，当且仅当，其不是任意一个结点的child结点


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n;
int l[maxn], r[maxn];
int child[maxn];
vector<int> id[maxn];

void dfs(int x, int h) {
	if (x) {
		id[h].push_back(x);
		dfs(l[x], h + 1);
		dfs(r[x], h);
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
		child[l[i]] = 1;
		child[r[i]] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		if (child[i] == 0) {
			dfs(i, 1);
		}
	}
	for (int i = 1; id[i].size(); ++i) {
		for (auto j : id[i]) {//对id[i] (一个vector<int>类型的对象)的 **元素** 进行遍历
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}


```
