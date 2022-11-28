#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e6 + 5;
int c[MAXN][2], val[MAXN], fail[MAXN], cnt;
queue<int> q;
struct ANS
{
    int num, pos;
    bool operator<(ANS x)
    {
        return x.num == num ? pos < x.pos : num < x.num;
    }
} Ans[MAXN];
void insert(string s, int num)
{
    int len = s.length();
    int now = 0;
    for (register int i = 0; i < len; ++i)
    {
        int v = s[i] - '0';
        if (!c[now][v])
            c[now][v] = ++cnt;
        now = c[now][v];
    }
    val[now] = num;
}
void build()
{
    for (register int i = 0; i < 2; ++i)
        if (c[0][i])
            fail[c[0][i]] = 0, q.push(c[0][i]);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (register int i = 0; i < 2; ++i)
            if (c[u][i])
                fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
            else
                c[u][i] = c[fail[u]][i];
    }
}
int query(char *s)
{
    int len = strlen(s);
    int now = 0, ans = 0;
    for (register int i = 0; i < len; ++i)
    {
        now = c[now][s[i] - '0'];
        for (register int t = now; t; t = fail[t])
            Ans[val[t]].num++;
    }
    return ans;
}
int n;
char S[MAXN];
string s[100001];
int main()
{
#ifdef lky233
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#else
    freopen("sugar.in", "r", stdin);
    freopen("sugar.out", "w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", S);
    for (register int i = 1; i <= n; ++i)
    {
        cin>>s[i];
        insert(s[i], i);
        Ans[i].num = 0;
        Ans[i].pos = i;
    }
    build();
    int ans = 0;
    ans = query(S);
    sort(ans + 1, ans + n + 1);
    for (register int i = 1; i <= n; i++)
    {
        cerr << Ans[i].num << " " << s[Ans[i].pos] << endl;
    }
    printf("%d", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
