#include <bits/stdc++.h>
using namespace std;
const int maxn = 4000000 + 10;
int n, m;
char s[maxn];
bool useful[maxn], num[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    int cntOut = 0, cntIn = 0, ans = 0;
    char c = getchar();
    for (int i = 0; i < m; i++)
    {
        s[i] = getchar();
        useful[i] = true;
        if (s[i] == '0')
            cntIn++;
        else 
        {
            if (cntOut < cntIn)
                cntOut++;
            else
                useful[i] = false;
        }
    }
    int cnt = 0, nowIn = 0, nowOut = 0;
    for (int i = 0; i < m; i++)
    {
        if (!useful[i]) continue;
        if (s[i] == '0')
        {
            nowIn++;
            if (nowIn > cntOut)
                continue;
            else
            {
                if (cnt < n) cnt++;
                else ans += 2, num[nowIn] = true;
                ans++;
            }
        }
        else 
        {
            nowOut++;
            if (!num[nowOut]) 
            {
                cnt--;
                if (num[nowOut + 1] && cnt == 0) 
                    cnt = 1, num[nowOut + 1] = false;
            }
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
