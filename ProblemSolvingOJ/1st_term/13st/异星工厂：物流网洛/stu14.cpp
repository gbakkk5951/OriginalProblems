#include <bits/stdc++.h>
using namespace std;
int R[50][50], order[55][55] = {0};
int t, n, flag, cnt;
int testTran()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (j != i && R[i][j])
                for (int k = 0; k < n; k++)
                    if (R[j][k] && !R[i][k])
                        return 0;
    return 1;
}
void testEqual(int a, int b)
{
    for (int i = 0; i < n; i++)
        if (R[a][i] != R[b][i] || R[i][a] != R[i][b])
        {
            flag = 0;
            return;
        }
}
void testSup(int a, int b)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (R[a][i] == 1 && R[b][i] == 1)
            if (i != a && i != b)
                cnt++;
    if (cnt > 1)
        testEqual(a, b);
}
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        flag = 1;
        for (int i = 0; i < n; i++)
        {
            cnt = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> R[i][j];
                if (R[i][j])
                    cnt++;
            }
            order[cnt][++order[cnt][0]] = i;
            if (!R[i][i])
                flag = 0;
        }
        if (flag && testTran() && order[n][0])
        {
            if (order[1][0] > 1)
                for (int i = 1; i < order[1][0]; i++)
                    for (int j = i + 1; j <= order[1][0]; j++)
                        testEqual(order[1][i], order[1][j]);
            if (order[n][0] > 1)
                for (int i = 1; i < order[n][0]; i++)
                    for (int j = i + 1; j <= order[n][0]; j++)
                        testEqual(order[n][i], order[n][j]);
            if (flag)
            {
                for (int k = 2; k < n; k++)
                    if (order[k][0] > 1)
                        for (int i = 1; i < order[k][0]; i++)
                            for (int j = i + 1; j <= order[k][0]; j++)
                                testSup(order[k][i], order[k][j]);
                if (flag) cout << "Y\n";
                else cout << "N\n";
            }
            else
                cout << "N\n";
        }
        else
            cout << "N\n";
        for (int i = 0; i < 55; i++)
            order[i][0] = 0;
    }
    return 0;
}
