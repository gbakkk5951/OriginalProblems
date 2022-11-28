#include <cstdio>
int n, g[100003], vis[100003], ans;
void dfs(int x, int d)
{
    vis[x] = d;
    if (vis[g[x]] > 0)
        ans += d - vis[g[x]] + 1;
    if (vis[g[x]] == 0)
        dfs(g[x], d + 1);
    vis[x] = -1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &g[i]);
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0)
            dfs(i, 1);
    printf("%d", ans);
    return 0;
}
