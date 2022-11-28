#include<bits/stdc++.h>
using namespace std;
int n, cnt, re;
string s, ss;
queue<int> q;
int aa[5000010], f[5000010];
struct AC{
    int fail, ch[2], sum, len;
} ac[5000010];
void insert(string s, int x){
    int len = s.length();
    int p = 0;
    for (int i = 0; i < len; i++){
        if (!ac[p].ch[s[i] - '0'])
            ac[p].ch[s[i] - '0'] = ++cnt, ac[cnt].len = ac[p].len + 1;
        p = ac[p].ch[s[i] - '0'];
    }
    aa[p] = x;
    ac[p].sum = 1;
}
int main(){
    freopen("sugar.in", "r", stdin);
    freopen("sugar.out", "w", stdout);
    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++){
        cin >> ss;
        insert(ss, i);
    }
    for (int i = 0; i < 2; i++)
        if (ac[0].ch[i])
            q.push(ac[0].ch[i]), ac[ac[0].ch[i]].fail = 0;
    while (q.size()){
        int p = q.front();
        q.pop();
        for (int i = 0; i < 2; i++)
            if (ac[p].ch[i])
                ac[ac[p].ch[i]].fail = ac[ac[p].fail].ch[i], q.push(ac[p].ch[i]);
            else
                ac[p].ch[i] = ac[ac[p].fail].ch[i];
    }
    memset(f, 0, sizeof(f));
    int len = s.length(), now = 0;
    f[now] = 0;
    for (int i = 0; i < len; i++){
        f[i] = max(f[i], f[i - 1]);
        now = ac[now].ch[s[i] - '0'];
        f[i] = max(f[i], f[i - ac[now].len] + ac[now].sum);
        for (int j = now; j; j = ac[j].fail)
            f[i] = max(f[i], f[i - ac[j].len] + ac[j].sum);
    }
    cout << f[len - 1];
}
