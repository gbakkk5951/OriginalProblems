#include <bits/stdc++.h>
using namespace std;
long long ans;
int arr[4000005];
queue<int> q;
int main()
{
    int n, m;
    bool flag = 0;
    int zero = 0, one = 0;
    cin >> n >> m;
    getchar();
    int idx = 0;
    for (int i = 1; i <= m; i++)
    {
        char ch;
        ch = getchar();

        if (ch == '1' && flag != 0)
            one++, idx++, arr[idx] = 1;
        else if (ch == '0')
            zero++, idx++, arr[idx] = 0, flag = 1;
    }
    int emptynum = n, z = 0;
    int right = 0;
    bool rightflag = 0, flagr = 0;
    for (int i = 1; i <= m; i++)
    {
        if (arr[i] == 0 && z < one)
        {
            if (emptynum > 0)
                q.push(2), emptynum--;
            else
                q.push(4);
            zero--;
            z++;
        }
        else if (arr[i] == 1 && !q.empty())
        {
            int temptop = q.front();
            ans += q.front();
            q.pop();
            if (rightflag == 1 && q.front() == 2)
                flagr = 1;
            if ((q.front() == 2 && (temptop == 2 || flagr == 1) && emptynum < n - 1) || q.empty() == 1)
            {
                emptynum++;
                flagr = 0, rightflag = 0;
            }
            if (temptop == 2 && q.front() == 4 && emptynum > 0)
            {
                rightflag = 1;
            }
            else if (temptop == 2 && q.front() == 4 && emptynum == 0)
            {
                emptynum++;
            }
        }
    }

    cout << ans;
    return 0;
}
