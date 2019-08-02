// QAQ 并查集写炸了，只好每次暴力重构 
#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

inline int read() {
	int re = 0; char in = getchar();
	while (!isdigit(in)) in = getchar();
	while (isdigit(in)) re = re * 10 + in - '0', in = getchar();
	return re;
}

struct Edge {
	int u, v, w;
};

#define M 200005
#define N 100005

int n, m, ans, tak;
int fa[N];
bool vs[M];
Edge e[M];

bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int kru() {
	int re = 0;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++) {
		if (i != tak) {
			int u = e[i].u, v = e[i].v, fu = find(u), fv = find(v);
			if (fu != fv) {
				fa[fu] = fa[fv];
				re += e[i].w;
				vs[i] = true;
			}
		}
	}
	return re;
}

int main() {
	freopen("selfless.in", "r", stdin);
	freopen("selfless.out", "w", stdout);
	
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		e[i].u = read(), e[i].v = read(), e[i].w = read();
		
	sort(e+1, e+m+1, cmp);
	int fir = kru(), mx = 0x3f3f3f3f;
	//printf("%d\n", ans);
	
	int p;
	for (int i = 1; i <= n; i++) {
		if (!vs[i] && e[i].w > e[p].w) {
			tak = p;
			int re = kru();
			if (re - fir < mx && re - fir > 0)
				ans = re;
			vs[i] = false;
		}
		else
			p = i;
	}
	
	printf("%d\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
