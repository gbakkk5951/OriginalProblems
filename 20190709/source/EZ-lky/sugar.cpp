#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXL = 5e6 + 7;
struct Tree
{
    int fail;
    int vis[2];
    int end;
} AC[MAXL];
int cnt = 0;
struct Result
{
    int num;
    int pos;
} Ans[MAXN];
string s[MAXN];
int Len[MAXN];
int ff[MAXL];
bool operator<(Result a, Result b)
{
    return s[a.pos].length() == s[b.pos].length() ? a.num > b.num : s[a.pos].length() < s[b.pos].length();
}
inline void Build(string s, int Num)
{
    int l = Len[Num];
    int now = 0;
    for (int i = 0; i < l; ++i)
    {
        if (AC[now].vis[s[i] - '0'] == 0)
        {
            AC[now].vis[s[i] - '0'] = ++cnt;
        }
        now = AC[now].vis[s[i] - '0'];
    }
    AC[now].end = Num;
}
void Get_fail()
{
    queue<int> Q;
    for (int i = 0; i < 2; ++i)
    {
        if (AC[0].vis[i] != 0)
        {
            AC[AC[0].vis[i]].fail = 0;
            Q.push(AC[0].vis[i]);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 2; ++i)
        {
            if (AC[u].vis[i] != 0)
            {
                AC[AC[u].vis[i]].fail = AC[AC[u].fail].vis[i];
                Q.push(AC[u].vis[i]);
            }
            else
                AC[u].vis[i] = AC[AC[u].fail].vis[i];
        }
    }
}
void AC_Query(string s)
{
    int l = s.length();
    int now = 0;
    for (int i = 0; i < l; ++i)
    {
        now = AC[now].vis[s[i] - '0'];
        for (int t = now; t; t = AC[t].fail)
        {
            Ans[AC[t].end].num++;
            ff[i + 1] = max(ff[i + 1], AC[t].end); //ohhh记录第几个串出现位置！！！;
        }
    }
}
int n;

int f[MAXL];
int main()
{
#ifdef lky233
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#else
    freopen("sugar.in", "r", stdin);
    freopen("sugar.out", "w", stdout);
#endif
    cin >> n;
    cin >> s[0];
    Len[0] = s[0].length();
    for (register int i = 1; i <= n; i++)
    {
        cin >> s[i];
        Ans[i].num = 0;
        Ans[i].pos = i;
        Len[i] = s[i].length();
        Build(s[i], i);
    }
    Get_fail();
    AC_Query(s[0]);
    // sort(&Ans[1], &Ans[n + 1]);
    // for(register int i = 1; i <= Len[0]; i++)
    //     cerr<<ff[i]<<endl;
    // for (register int i = 1; i <= Len[0]; i++)
    // ans += ff[i];
    for (register int i = 1; i <= Len[0]; ++i)
    {
        f[i] = max(f[i - 1],f[i - Len[ff[i]]] + 1);
        // cerr<<f[i]<<" ";
        // cerr<<(i - Len[ff[i]])<<endl;
    }
    printf("%d\n", f[Len[0]]);
    return 0;
}