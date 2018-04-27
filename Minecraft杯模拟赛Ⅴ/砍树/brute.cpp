using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
const int DST = 0, NXT = 1;
const int MXN = 500050;
typedef pair<int, int> pr;

struct SegTree {
	int n;
	int tag[MXN];
	pr node[MXN];
	inline void clear() {//init时顺便clear 
	}

	void change(int nd, int nl, int nr, int l, int r, int v) {
		for (int i = l; i <= r; i++) {
			node[i].first += v;
		}
	}
	inline pr query() {
		pr ans = (pr){-500, -500};
		for (int i = 1; i <= n; i++) {
			ans = max(ans, node[i]);
		}
		return ans;
	}
	void init(int nd, int nl, int nr, int arr[]) {
		for (int i = 1; i <= n; i++) {
			node[i].first = arr[i];
			node[i].second = i;
		}
	}
}tree;

struct _Main {
	int head[MXN], edge[MXN << 1][2];
	int size[MXN];// 除了size和dfn下标全用dfn
	int dfn[MXN], dep[MXN], vis[MXN], f[MXN], l[MXN], r[MXN];
	int idx;
	int n, m;
	void dfs(int nd, int fa) {
		dfn[nd] = ++idx;
		size[nd] = 1;
		dep[dfn[nd]] = dep[dfn[fa]] + 1;
		f[dfn[nd]] = dfn[fa];
		l[dfn[nd]] = idx;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd);
				size[nd] += size[t];
			}
		}
		r[dfn[nd]] = idx;
	}
	int eidx;
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	int ansidx;
	pr ans[MXN];
	void calc(int root) {
		int len = 0, n, sum = 0;
		memset(vis + 1, 0, (tree.n) * sizeof(int));
		idx = 0;
		dfs(root, 0);
		n = size[root];
		tree.clear();
		tree.n = n;
		tree.init(1, 1, n, dep);
		pr tmp;
		while (sum < n) {
			tmp = tree.query();
			int nd = tmp.second;
			len = max(len, tmp.first);
			while (!vis[nd]) {
				vis[nd] = 1;
				tree.change(1, 1, n, l[nd], r[nd], -1);
				nd = f[nd];
			}
			sum += tmp.first;
			ans[++ansidx] = (pr){tmp.first, len};
		}
		
	}
	_Main() {
		int n, m;
		int u, v;
		read(n); read(m);
		for (int i = 1; i <= m; i++) {
			read(u); read(v);
			add(u, v); add(v, u);
		}
		vis[0] = 1;
		for (int i = 1; i <= n; i++) {
			if (!size[i]) {
				calc(i);
			}
		}
		sort(ans + 1, ans + ansidx + 1);
		int tcnt = 0, ncnt = 0;
		printf("%d\n", ansidx);
		for (int i = ansidx; i >= 1; i--) {
			ncnt += ans[i].first;
			tcnt += ans[i].second == ans[i].first;
			printf("%d %d\n", ncnt, tcnt);
		}
	}
template <typename Type>	
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
	}
}timber;
}
