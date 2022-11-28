#include <bits/stdc++.h>
using namespace std;
int s[1010], sum[1010], m[1010];

int Strlen(int start)
{
    int lenth = 0;
    // cout << "start=" << start << endl;
    for (int i = start; s[i] != 0; i++)
    {
        lenth++;
        // cout << "s[i]" << i << "=" << s[i] << endl;
    }
    return lenth;
}
void Strcpy(int begin1, int len1, int begin2)
{
    for (int i = begin1; i <= begin1 + len1; i++)
    {
        s[begin2] = s[i];
        // cout << "copy s[i]" << begin2 << "=" << s[begin2] << endl;
        begin2++;
    }
}
int main()
{
    int n, k = 0, T, opt, x, y, v, c, x0, y0, x1, y1, len1, len2, len;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m[i]; j++)
        {
            cin >> s[k];
            k++;
        }
    }
    sum[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + m[i - 1];
    }
    cin >> T;
    while (T--)
    {
        cin >> opt;
        if (opt == 0)
        {
            cin >> x >> y >> v >> c;
            if (c == 0)
            {
                cout << "true" << endl;
            }
            else if ((sum[x] + y + c) > sum[n] || sum[x] + y < 0)
            {
                cout << "overflow" << endl;
            }
            else if ((sum[x] + y + c) > sum[x + 1] || y < 0)
            {
                cout << "w";
                for (int j = sum[x] + y; j < sum[x] + y + c; j++)
                {
                    s[j] = v;
                }
                cout << "true" << endl;
            }
            else
            {
                for (int j = sum[x] + y; j < sum[x] + y + c; j++)
                {
                    s[j] = v;
                }
                cout << "true" << endl;
            }
        }
        if (opt == 1)
        {
            cin >> x0 >> y0 >> x1 >> y1;
            if (sum[x0] + y0 > sum[n] - 1 || sum[x1] + y1 > sum[n] - 1 || sum[x0] + y0 < 0 || sum[x1] + y1 < 0)
            {
                cout << "overflow" << endl;
            }
            else
            {
                len1 = Strlen(sum[x0] + y0);
                // printf("len1=%d\n", len1);
                if (sum[x1] + y1 + len1 >= sum[n] || sum[x0] + y0 + len1 >= sum[n])
                {
                    // cout << "len1" <<  len1;
                    cout << "overflow" << endl;
                }
                else if (min(sum[x0] + y0, sum[x1] + y1) + len1 >= max(sum[x0] + y0, sum[x1] + y1))
                {
                    cout << "overwrite" << endl;
                }
                else if (y1 < 0 || y1 < 0 || sum[x0] + y0 + len1 >= sum[x0 + 1] || sum[x1] + y1 + len1 >= sum[x1 + 1])
                {
                    cout << "w";
                    Strcpy(sum[x0] + y0, len1, sum[x1] + y1);
                    cout << "true" << endl;
                }
                else
                {
                    Strcpy(sum[x0] + y0, len1, sum[x1] + y1);
                    cout << "true" << endl;
                }
            }
        }
        else if (opt == 2)
        {
            cin >> x >> y;
            if (sum[x] + y >= sum[n] || sum[x] + y < 0)
            {
                cout << "overflow" << endl;
                continue;
            }
            len = Strlen(sum[x] + y);
            // cout << "len=" << len << endl;
            if (sum[x] + y + len >= sum[n])
            {
                cout << "overflow" << endl;
            }
            else if (y < 0 || sum[x] + y + len >= sum[x + 1])
            {
                cout << "w" << len << endl;
            }
            else
                cout << len << endl;
        }
    }
    return 0;
}
