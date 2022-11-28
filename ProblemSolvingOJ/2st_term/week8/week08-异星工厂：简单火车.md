
### 1. 考察知识：

对于正的权，最小生成树

对于负的权，一定要加入

n=1时，可以不加，但负权的一定要加


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1e6 + 10;
int n, m;
int p[maxn];//p[i] = 0 表示i的代表元是i自己
int getp(int nd) {//找到代表元
	return p[nd] ? p[nd] = getp(p[nd]) : nd;//路径压缩
}
lld ans;//记得long long
struct Edge {
	int a, b, v;
	bool operator < (const Edge &b) const {//重载小于运算符
		return v < b.v;
	}
}edge[maxn * 2];
int edge_index;
int main() {
	scanf("%d%d", &n, &m);
	int a, b, v;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &v);
		if (v <= 0) {//非正，直接加
			ans += v;
			v = 0;
			a = getp(a);
			b = getp(b);
			if (a != b) {
				p[a] = b;
			}
		} else {
			edge[++edge_index] = (Edge) {a, b, v};
		}
	}
	sort(edge + 1, edge + edge_index + 1);//kruskal
	for (int i = 1; i <= edge_index; ++i) {
		a = getp(edge[i].a);
		b = getp(edge[i].b);
		if (a != b) {
			p[a] = b;
			ans += edge[i].v;
		}
	}
	int parent = getp(1);
	int flag = 1;
	for (int i = 2; i <= n; ++i) {
		if (getp(i) != parent) {
			flag = 0;
			break;
		}
	}
	if (flag) {
		printf("%lld", ans);
	} else {
		printf("bad idea");
	}
	return 0;
}


```
