#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int N = 200010, T = 200010, S = 2000010;

char s[S], s1[S];
queue<int> q;
int head[T], nxt[T], to[T], cnt;
int n, tr[T][26], fail[T], tot = 1, match[N], siz[T];

void dfs(int u)
{
    int i, v;
    for (i = head[u]; i; i = nxt[i])
    {
        v = to[i];
        dfs(v);
        siz[u] += siz[v];
    }
}

void add(int u, int v)
{
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}
int main()
{
    freopen("sugar.in", "r", stdin);
    freopen("sugar.out", "w", stdout);
    int i, j, u;

    scanf("%d", &n);
    scanf("%s", s1);
    for (i = 1; i <= n; ++i)
    {
        scanf("%s", s);
        for (u = 1, j = 0; s[j]; ++j)
        {
            int c = s[j] - '0';
            if (!tr[u][c])
                tr[u][c] = ++tot;
            u = tr[u][c];
        }
        match[i] = u;
    }

    tr[0][0] = 1;
    tr[0][1] = 1;
    q.push(1);

    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (i = 0; i <= 1; ++i)
        {
            if (tr[u][i])
            {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            }
            else
                tr[u][i] = tr[fail[u]][i];
        }
    }

    for (u = 1, i = 0; s1[i]; ++i)
    {
        u = tr[u][s1[i] - '0'];
        ++siz[u];
    }

    for (i = 2; i <= tot; ++i)
        add(fail[i], i);

    dfs(1);

    for (i = 1; i <= n; ++i)
        printf("%d\n", siz[match[i]]);

    return 0;
}
