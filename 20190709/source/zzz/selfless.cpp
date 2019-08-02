#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;

const int N = 100005;
const int M = 300005;
int f[N], n, m;
struct node {
	int x, y, w;
	bool operator < (const node &i) const{
		return w < i.w;
	}
}e[M];

int get(int x) {
	if (x == f[x]) return x;
	return f[x] = get(f[x]);
}

int read(void) {
	int x = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}

int h[N], ne[N<<1], w[N<<1];
int to[N<<1], tot;
void add(int x,int y,int z) {
	ne[++tot] = h[x], w[tot] = z;
	to[tot] = y, h[x] = tot;
}

bool b[M];

ll cnt = 0;

void kruskal() {
	sort(e + 1, e + m + 1);
	for (int i = 1;i <= m; i++) {
		int fx = get(e[i].x), fy = get(e[i].y);
		if (fx == fy) continue;
		b[i] = true, cnt += e[i].w;
		add(e[i].x, e[i].y, e[i].w);
		add(e[i].y, e[i].x, e[i].w);
		f[f[fx]] = fy;
	}
}

ll depth[N], max1[N][25], max2[N][25];
int father[N][25];

void dfs(int x,int fa) {

	for (int i = h[x]; i; i = ne[i]) {
		int y = to[i];
		if (y == fa) continue;	
		depth[y] = depth[x] + 1;
		father[y][0] = x;
		max1[y][0] = w[i];
		max2[y][0] =  -200000000;
		for (int i = 1;i <= 20; i++) {
			father[y][i] = father[father[y][i-1]][i-1];
			if (father[y][i] == 0) break;
			int m1 = max1[father[y][i-1]][i-1];
			int m2 = max2[father[y][i-1]][i-1];
			if (m1 <= max2[y][i-1]) {
				max2[y][i] = max2[y][i-1];
				max1[y][i] = max1[y][i-1];
				continue;
			}
			if (m1 < max1[y][i-1]) {
				max1[y][i] = max1[y][i-1];
				max2[y][i] = m1;
				continue;
			}
			if (m1 == max2[y][i-1]) {
				max1[y][i] = max1[y][i-1];
				max2[y][i] = max(max2[y][i-1], (ll)m2);
			}
			max1[y][i] = m1;
			max2[y][i] = max(max1[y][i-1], (ll)m2);
		}
		dfs(y, x);
	}
}

int Lca(int x,int y) {
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 20;i >= 0; i--) 
	if (depth[father[x][i]] >= depth[y]) x = father[x][i];
	if (x == y) return x;
	for (int i = 20;i >= 0; i--) {
		if (father[x][i] != father[y][i]) 
		x = father[x][i], y = father[y][i];
	}
	return father[x][0];
}


inline ll qmax(ll u,ll v,ll maxx)
{
    ll Ans = -222222222;
    for(ll i = 20;i >= 0; --i)
    {
        if(depth[father[u][i]] >= depth[v])
        {
            if(maxx != max1[u][i]) 
				Ans = max(Ans, max1[u][i]);
            else Ans = max(Ans, max2[u][i]);
            u = father[u][i];
        }
    }
    return Ans;
}

int main() {
	freopen("selfless.in", "r", stdin);
	freopen("selfless.out", "w", stdout);
	n = read(), m = read();
	for (int i = 1;i <= n; i++) f[i] = i;
	for (int i = 1;i <= m; i++) 
	e[i].x = read(), e[i].y = read(), e[i].w = read();
	kruskal();
	depth[1] = 1;
	dfs(1, 0);
	ll ans = 22222222222;
	for (int i = 1;i <= m; i++) {
		if (!b[i]) {
			int lca = Lca(e[i].x, e[i].y);
			int maxu = qmax(e[i].x, lca, e[i].w);
			int maxv = qmax(e[i].y, lca, e[i].w);
			ans = min(ans, cnt - max(maxu, maxv) + e[i].w);
		}
	}
	printf("%lld", ans);
}

