#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
int nxt[N], vis[N], inCyc[N];
int ans = 0;

void dfs(int cur, int tag)
{
    if (vis[cur] == tag)
        inCyc[cur] = 1;
    else if (!vis[cur])
        vis[cur] = tag, dfs(nxt[cur], tag);
}

void calcAns(int cur)
{
    if (vis[cur])
        return;
    vis[cur] = 1;
    ++ans;
    calcAns(nxt[cur]);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &nxt[i]);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i, i);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
        if (inCyc[i] && !vis[i])
            calcAns(i);
    printf("%d\n", ans);
    return 0;
}
