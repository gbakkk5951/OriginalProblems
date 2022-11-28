#include <bits/stdc++.h>
using namespace std;
int n;
int Box[55][55];
int C[55];
bool flag; //判断是否是格
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> Box[i][j]; //编号1-n
            }
        }
        for (int i = 1; i <= n; i++) //判断自反性
        {
            if (Box[i][i] == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << "N" << endl;
            flag = 0;
            continue;
        }
        for (int i = 1; i <= n; i++) //判断传递性
        {
            for (int j = 1; j <= n; j++)
            {
                if (Box[i][j] == 1)
                {
                    for (int k = 1; k <= n; k++)
                    {
                        if (Box[j][k] == 1 && Box[i][k] != 1)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
        if (flag == 1)
        {
            cout << "N" << endl;
            flag = 0;
            continue;
        }

        for (int i = 1; i <= n - 1; i++) //取任意两个
        {
            for (int j = i + 1; j <= n; j++)
            {
                int k3 = 0;
                if (Box[i][j] == 1)
                {
                    continue;
                }
                for (int id = 1; id <= n; id++)
                {

                    if (Box[i][id] == 1 && Box[j][id] == 1)
                    {
                        C[++k3] = id;
                        // printf("c=%d\n", C[k3]);
                    }
                }
                if (k3 == 0)
                {
                    flag = 1;
                    break;
                }
                else if (k3 >= 2)
                {

                    for (int k1 = 1; k1 <= k3; k1++)
                    {
                        int num = 0;
                        for (int k2 = 1; k2 <= k3; k2++)
                        {
                            if (Box[C[k1]][C[k2]] == 1)
                            {
                                num++;
                            }
                        }
                        if (num != k3)
                        {
                            flag = 1;
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                }
            }
            if (flag == 1)
            {
                break;
            }
            for (int j = i + 1; j <= n; j++)
            {
                int k3 = 0;
                if (Box[i][j] == 1)
                {
                    continue;
                }
                for (int id = 1; id <= n; id++)
                {
                    if (Box[id][i] == 1 && Box[id][j] == 1)
                    {
                        C[++k3] = id;
                        // printf("2c=%d\n", C[k3]);
                    }
                }
                if (k3 == 0)
                {
                    flag = 1;
                    break;
                }
                else if (k3 >= 2)
                {
                    for (int k1 = 1; k1 <= k3; k1++)
                    {
                        int num = 0;
                        for (int k2 = 1; k2 <= k3; k2++)
                        {
                            if (Box[C[k2]][C[k1]] == 1)
                            {
                                num++;
                            }
                        }
                        if (num != k3)
                        {
                            flag = 1;
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                }
            }
        }
        if (flag == 1)
        {
            cout << "N" << endl;
        }
        else
            cout << "Y" << endl;

        flag = 0;
    }
    return 0;
}

