#include <bits/stdc++.h>
#define maxp(x, y) \
    if (x < y)     \
        x = y;
#define max(x, y) x > y ? x : y;
namespace fdata
{
inline char nextchar()
{
    static const int BS = 1 << 21;
    static char buf[BS], *st, *ed;
    if (st == ed)
        ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? -1 : *st++;
}
inline int poread()
{
    int ret = 0;
    char ch;
    while (!isdigit(ch = nextchar()))
        ;

    do
        ret = ret * 10 + ch - '0';
    while (isdigit(ch = nextchar()));
    return ret;
}
} // namespace fdata
using namespace fdata;
using namespace std;
const int MAXM = 2e5 + 5;
const int MAXN = 1e5 + 5;
int n, m;
long long sum;
bool mst[MAXM];
int head[MAXN], nxt[MAXM << 1], ver[MAXM << 1], len[MAXM << 1], tot;
struct rec
{
    int x, y, z;
    inline void in()
    {
        x = poread();
        y = poread();
        z = poread();
    }
    inline bool operator<(rec x) const
    {
        return z < x.z;
    }
    inline void add()
    {
        sum += z;
        ver[++tot] = y, len[tot] = z, nxt[tot] = head[x], head[x] = tot;
        ver[++tot] = x, len[tot] = z, nxt[tot] = head[y], head[y] = tot;
    }
} edge[MAXM];

int fa[MAXN];
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

int b[MAXN], d[MAXN];
struct ST
{
    int f, m1, m2;
} st[MAXN][18];
void dfs(int u, int fa)
{
    d[u] = d[fa] + 1;
    st[u][0].f = fa;
    ST *a, *l, *r;
    for (register int &i = b[u]; ((a = &st[u][i + 1])->f = (l = &st[(r = &st[u][i])->f][i])->f); ++i)
    {
        if (l->m1 > r->m1)
        {
            a->m1 = l->m1;
            a->m2 = max(l->m2, r->m1);
        }
        else if (r->m1 > l->m1)
        {
            a->m1 = r->m1;
            a->m2 = max(r->m2, l->m1);
        }
        else
        {
            a->m1 = l->m1;
            a->m2 = max(l->m2, r->m2);
        }
    }
    for (register int i = head[u]; i; i = nxt[i])
    {
        if (ver[i] != fa)
            st[ver[i]][0].m1 = len[i], dfs(ver[i], u);
    }
}

int main()
{
#ifdef lky233
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#else
    freopen("selfless.in", "r", stdin);
    freopen("selfless.out", "w", stdout);
#endif
    ST *l, *r;
    int ans = 2147483647;
    n = poread();
    m = poread();
    for (register int i = 1; i <= m; i++)
        edge[i].in();
    for (register int i = 1; i <= n; i++)
        fa[i] = i;
    sort(edge + 1, edge + 1 + m);
    for (register int i = 1; (tot >> 1) < n - 1; i++)
    {
        int x = find(fa[edge[i].x]);
        int y = find(fa[edge[i].y]);
        if (x == y)
            continue;
        mst[i] = true;
        fa[x] = y;
        edge[i].add();
    }
    dfs(1, 0);
    for (register int i = 1; i <= m; i++)
    {
        if (mst[i])
            continue;
        int x = edge[i].x;
        int y = edge[i].y;
        int now = 0;
        int nl = edge[i].z;
        if (d[x] < d[y])
            swap(x, y);
        for (register int j = 0, k = d[x] - d[y]; k; ++j, k >>= 1)
        {
            if (k & 1)
            {
                if ((l = &st[x][j])->m1 != nl)
                {
                    maxp(now, l->m1);
                }
                else
                {
                    maxp(now, l->m2);
                }
                x = l->f;
            }
        }
        if (x == y)
            goto F;
        for (register int j = b[x]; j >= 0; --j)
        {
            if ((l = &st[x][j])->f == (r = &st[y][j])->f)
                continue;
            if (l->m1 != nl)
            {
                maxp(now, l->m1);
            }
            else
            {
                maxp(now, l->m2);
            }
            if (r->m1 != nl)
            {
                maxp(now, r->m1);
            }
            else
            {
                maxp(now, r->m2);
            }
            x = l->f;
            y = r->f;
        }
        if ((l = &st[x][0])->m1 != nl)
        {
            maxp(now, l->m1);
        }
        else
        {
            maxp(now, l->m2);
        }
        if ((r = &st[y][0])->m1 != nl)
        {
            maxp(now, r->m1);
        }
        else
        {
            maxp(now, r->m2);
        }
    F:
        if (ans > nl - now)
            ans = nl - now;
    }
    printf("%lld\n", sum + ans);
    return 0;
}