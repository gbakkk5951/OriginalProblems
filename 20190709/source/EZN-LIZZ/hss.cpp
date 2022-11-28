#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 5;
char str[maxn];
int ans, n, m, suc, lft, rht;
void pp(int frm, int ed)
{
    int sum = 0;
    stack<int> st;
    for (int i = frm; i <= ed; i++)
    {
        if (str[i] == 'S')
            sum++;
        if (str[i] == 's')
            st.push(str[i]);
        if (str[i] == 'h')
        {
            if (!st.empty())
            {
                st.pop();
                sum += 2;
            }
            else
            {
                rht = 1;
                ans = max(ans, sum);
                return;
            }
        }
    }
    if (!st.empty())
    {
        return;
        lft = 1;
    }
    else
    {
        lft = rht = 0;
        suc = 1;
        ans = max(ans, sum);
    }
}
signed main()
{
    freopen("hss.in", "r", stdin);
    freopen("hss.out", "w", stdout);
    cin.tie(0);
    cin >> n >> m;
    int l = 1e6 + 1, r = 1e6 + n;
    for (int i = l; i <= r; i++)
        cin >> str[i];
    for (int i = l; i <= r; i++)
    {
        if (lft)
            if (str[i - 1] != 's')
                continue;
        if (rht)
            if (str[i - 1] != 'h')
                continue;
        if (suc)
        {
            suc = lft = rht = 0;
            break;
        }
        pp(i, r);
    }
    printf("%d\n", ans);
    while (m--)
    {
        int opt;
        char ch;
        cin >> opt >> ch;
        if (opt == 1)
        {
            str[--l] = ch;
            for (int i = l; i <= r; i++)
            {

                if (lft)
                    if (str[i - 1] != 's')
                        continue;
                if (rht)
                    if (str[i - 1] != 'h')
                        continue;
                if (suc)
                {
                    suc = lft = rht = 0;
                    break;
                }
                pp(i, r);
            }
        }
        else
        {
            str[++r] = ch;
            for (int i = l; i <= r; i++)
            {

                if (lft)
                    if (str[i - 1] != 's')
                        continue;
                if (rht)
                    if (str[i - 1] != 'h')
                        continue;
                if (suc)
                {
                    suc = lft = rht = 0;
                    break;
                }
                pp(i, r);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/* 
6 3
S s s s h h
2 h
1 h
1 s


4
7
7
9
*/