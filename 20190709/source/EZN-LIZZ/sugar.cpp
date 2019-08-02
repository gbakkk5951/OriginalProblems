#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 5;
char str[maxn], chuan[maxn];
bool f[maxn], vis[maxn];
int n;
struct ACauto
{
    int tot, ed[maxn], nxt[maxn], ch[maxn][2];
    void insert(char *s)
    {
        int u = 0, len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            int c = s[i] - '0';
            if (!ch[u][c])
                ch[u][c] = ++tot;
            u = ch[u][c];
        }
        ed[u]++;
    }
    void Fail()
    {
        queue<int> q;
        memset(nxt, 0, sizeof(nxt));
        for (int i = 0; i < 2; i++)
            if (ch[0][i])
                q.push(ch[0][i]);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (ed[nxt[u]])
                ed[u] = 1;
            for (int i = 0; i < 2; i++)
            {
                if (ch[u][i])
                {
                    nxt[ch[u][i]] = ch[nxt[u]][i];
                    q.push(ch[u][i]);
                }
                else
                    ch[u][i] = ch[nxt[u]][i];
            }
        }
    }
    void query(char *T)
    {
        int u = 0, n = strlen(T), res = 0, cnt = 0;
        for (int i = 0; i < n; i += cnt)
        {
            cnt = 0;
            int c = T[i] - '0';
            u = ch[u][c];
            cnt++;
            int v = nxt[u];
            while (v)
            {
                cnt++;
                v = nxt[v];
            }
            res++;
        }
        printf("%d\n", res);
        return;
    }
} AC;
signed main()
{
    freopen("sugar.in", "r", stdin);
    freopen("sugar.out", "w", stdout);
    scanf("%d", &n);
    scanf("%s", chuan);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str);
        AC.insert(str);
    }
    AC.Fail();
    AC.query(chuan);
    return 0;
}
/*
5
010101010111
010
01
11
1000
1110


6
*/