#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100010;
const int maxm = 200010;
const int inf = 0x3f3f3f3f;
int n, m, head[maxn], to[maxn << 1], nxt[maxn << 1], val[maxn << 1], tot = 1;
int tree_sum = 0, ans = 0x3f3f3f3f;
int depth[maxn], fa[maxn][16], max1[maxn][16], max2[maxn][16];
bool tree[maxn];

struct edge
{
	int from, to, val;
	
	bool operator < (const edge &rhs) const
	{
		return val < rhs.val;
	}
}e[maxm];

class union_find_set
{
	private:
		int fa[maxn];
		
	public:
		inline void Init(int bound)
		{
			for (int i = 1; i <= bound; ++i) fa[i] = i;
		}
		
		int Find(int x)
		{
			return x == fa[x] ? x : fa[x] = Find(fa[x]);	
		}
		
		inline bool Merge(int x, int y)
		{
			int fx = Find(x), fy = Find(y);
			if (fx == fy) return false;
			fa[fx] = fy;
			return true;
		}
}S;

inline void file()
{
	freopen("selfless.in", "r", stdin);
	freopen("selfless.out", "w", stdout);
}

inline void add_edge(int u, int v, int w)
{
	to[++tot] = v;
	val[tot] = w;
	nxt[tot] = head[u];
	head[u] = tot;
}

void dfs_init(int u, int pre)
{
	fa[u][0] = pre;
	depth[u] = depth[pre] + 1;
	for (int c = head[u]; c; c = nxt[c])
	{
		if (to[c] != pre)
		{
			max1[to[c]][0] = val[c];
			max2[to[c]][0] = -inf;
		 	dfs_init(to[c], u);
		}
	}
}

inline void update(int &x, int &y, int a, int b)
{
	x = max(x, a);
	y = max(y, b);
	if (x > a) y = max(y, a);
	else if (x < a) y = max(y, x);
}

inline void multi_init()
{
	for (int i = 15; i >= 0; --i)
	{
		for (int u = 1; u <= n; ++u)
		{
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
			update(max1[u][i], max2[u][i], 
			max1[fa[u][i - 1]][i - 1], max2[fa[u][i - 1]][i - 1]);
		}
	}
}

inline int lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 15; i >= 0; --i)
	{
		if (depth[fa[x][i]] >= depth[y]) x = fa[x][i];
	}
	if (x == y) return x;
	for (int i = 15; i >= 0; --i)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

inline int query(int x, int y, int value)
{
	int res = 0;
	for (int i = 15; i >= 0; --i)
	{
		if (depth[fa[x][i]] >= depth[y])
		{
			if (value != max1[x][i]) res = max(res, max1[x][i]);
			else res = max(res, max2[x][i]);
		}
	}
	return res;
}

int main()
{
	file();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].val);
	sort(e + 1, e + m + 1);
	S.Init(n);
	for (int i = 1, cnt = 0; i <= m; ++i)
	{
		if (!S.Merge(e[i].from, e[i].to)) continue;
		++cnt;
		add_edge(e[i].from, e[i].to, e[i].val);
		add_edge(e[i].to, e[i].from, e[i].val);
		tree_sum += e[i].val;
		tree[i] = true;
		if (cnt == n - 1) break;
	}
	dfs_init(1, 0);
	multi_init();
	for (int i = 1; i <= m; ++i)
	{
		if (tree[i]) continue;
		int p = lca(e[i].from, e[i].to);
		int dis = max(query(e[i].from, p, e[i].val), 
					query(e[i].to, p, e[i].val));
		ans = min(ans, tree_sum - dis + e[i].val);
	}
	printf("%d", ans);
	return 0;
}
