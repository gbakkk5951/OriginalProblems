#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;
const long long MAXN = 400005, MAXM = 900005, INF = 2147483647000000;
struct edge
{
    long long u, v, d, next;
} G[MAXN << 1], A[MAXM << 1];
long long tot = 0, head[MAXN], foo[MAXN][19], mmax[MAXN][19], mmin[MAXN][19], dep[MAXN], n, CNT, ANS = INF, m, Father[MAXN];
bool B[MAXM << 1];

inline void read(long long &x)
{
    x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = x * 10 + (ch ^ 48), ch = getchar();
}

void dfs0(long long u, long long fa)
{
    foo[u][0] = fa;
    for (long long i = head[u]; i; i = G[i].next)
    {
        long long v = G[i].v;
        if (v != fa)
        {
            dep[v] = dep[u] + 1ll;
            mmax[v][0] = G[i].d;
            mmin[v][0] = -INF;
            dfs0(v, u);
        }
    }
}

inline void Work()
{
    for (long long i = 1; i <= 18; ++i)
    {
        for (long long j = 1; j <= n; ++j)
        {
            foo[j][i] = foo[foo[j][i - 1]][i - 1];
            mmax[j][i] = max(mmax[j][i - 1], mmax[foo[j][i - 1]][i - 1]);
            mmin[j][i] = max(mmin[j][i - 1], mmin[foo[j][i - 1]][i - 1]);
            if (mmax[j][i - 1] > mmax[foo[j][i - 1]][i - 1])
            {
                mmin[j][i] = max(mmin[j][i], mmax[foo[j][i - 1]][i - 1]);
            }
            else if (mmax[j][i - 1] < mmax[foo[j][i - 1]][i - 1])
            {
                mmin[j][i] = max(mmin[j][i], mmax[j][i - 1]);
            }
        }
    }
}

inline long long LCA(long long x, long long y)
{
    if  (dep[x] < dep[y])
        {
            swap(x, y);
        }
    for (long long i = 18; i >= 0; --i)
    {
        if  (dep[foo[x][i]] >= dep[y])
            {
                x = foo[x][i];
            }
    }
    if (x != y)
    {
        for (long long i = 18; i >= 0; --i)
        {
            if (foo[x][i] ^ foo[y][i])
            {
                x = foo[x][i], y = foo[y][i];
            }
        }
        return foo[x][0];
    }
    else
    {
        return x;
    }
}

inline long long fmax(long long u, long long v, long long maxx)
{
    long long ANS = -INF;
    for (long long i = 18; i >= 0; --i)
    {
        if  (dep[foo[u][i]] >= dep[v])
            {
                if (maxx != mmax[u][i])
                {
                    ANS = max(ANS, mmax[u][i]);
                }
                else
                {
                    ANS = max(ANS, mmin[u][i]);
                }
                u = foo[u][i];
            }
    }
    return ANS;
}

inline void add_edge(long long u, long long v, long long d)
{
    G[++tot].u = u, G[tot].v = v, G[tot].d = d, G[tot].next = head[u], head[u] = tot;
    G[++tot].u = v, G[tot].v = u, G[tot].d = d, G[tot].next = head[v], head[v] = tot;
}

inline bool cmp(edge x, edge y)
{
    return x.d < y.d;
}

inline long long getfa(long long x)
{
    return (x == Father[x]) ? x : Father[x] = getfa(Father[x]);
}

int main()
{
	freopen("selfless.in", "r", stdin);
    freopen("selfless.out", "w", stdout);
    read(n), read(m);
    for (long long i = 1; i <= m; ++i)
    {
        read(A[i].u), read(A[i].v), read(A[i].d);
    }
    sort(A + 1, A + m + 1, cmp);
    for (long long i = 1; i <= n; ++i)
    {
        Father[i] = i;
    }
    for (long long i = 1; i <= m; ++i)
    {
        long long Father_u = getfa(A[i].u), Father_v = getfa(A[i].v);
        if (Father_u != Father_v)
        {
            CNT += A[i].d;
            Father[Father_u] = Father_v;
            add_edge(A[i].u, A[i].v, A[i].d);
            B[i] = true;
        }
    }
    mmin[1][0] = -INF;
    dep[1] = 1;
    dfs0(1, -1);
    Work();
    for (long long i = 1; i <= m; ++i)
    {
        if (!B[i])
        {
            long long u = A[i].u, v = A[i].v, d = A[i].d, lca = LCA(u, v), maxu = fmax(u, lca, d), maxv = fmax(v, lca, d);
            ANS = min(ANS, CNT - max(maxu, maxv) + d);
        }
    }
    printf("%lld", ANS);
    return 0;
}