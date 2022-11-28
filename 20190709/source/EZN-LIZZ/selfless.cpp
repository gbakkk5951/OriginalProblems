#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;
struct edge
{
    int frm, nxt, to, val;
} ed[maxm];
int vis[maxn], hd[maxn], nxt[maxn], cnct[maxn], used[maxm], dis[maxn], a[maxn], nowcost[maxn];
int cnt, sum, ans, minadd = maxn;
int val[maxm], mind = maxn;
void add(int x, int y, int z)
{
    ed[++cnt].to = y;
    ed[cnt].frm = x;
    ed[cnt].nxt = hd[x];
    ed[cnt].val = z;
    hd[x] = cnt;
    val[cnt] = z;
}
void kruskal()
{
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<int> q;
    q.push(1);
    dis[ed[1].frm] = 0;
    cnct[1] = 1;
    while (!q.empty())
    {
        int t = q.top();
        q.pop();
        for (int i = hd[t]; i; i = ed[i].nxt)
        {
            int u = ed[i].frm, v = ed[i].to;
            if (!used[i])
            {
                if (dis[u] + ed[i].val < dis[v])
                {
                    if (cnct[v])
                        minadd = min(minadd, nowcost[v] - ed[i].val);
                    else
                        cnct[v] = 1;
                    dis[v] = dis[u] + ed[i].val;
                    used[i] = 1;
                    sum -= nowcost[v];
                    sum += nowcost[v] = ed[i].val;
                }
            }
        }
    }
}
signed main()
{
    freopen("selfless.in", "r", stdin);
    freopen("selfless.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    kruskal();
    sort(val + 1, val + 1 + cnt);
    for (int i = 2; i <= cnt; i++)
        mind = min(mind, max(1, val[i] - val[i - 1]));
    printf("%d\n", sum + mind); //TODO:骗分效率need more UPPER↑ 预期得分 10
    return 0;
}
/*
3 5
1 2 3
1 2 5
2 3 4
2 3 9
1 3 3


7
*/