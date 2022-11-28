#include <bits/stdc++.h>
using namespace std;
int R[55][55], order[55][55] = {0}, sup[50], inf[50];
int t, n, flag, cnt, first, last = 0;
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
bool testEqual(int a, int b)
{
    if (a != b)
        for (int i = 0; i < n; i++)
            if ((R[a][i] > 0 && R[b][i] == 0) || (R[b][i] > 0 && R[a][i] == 0) || (R[i][a] > 0 && R[i][b] == 0) || (R[i][b] > 0 && R[i][a] == 0))
                return false;
    return true;
}
void adjacent() //两个节点连接（“覆盖”）不相等，赋值为2
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (R[i][j] && i != j)
            {
                int adjacentflag = 1;
                for (int k = 0; k < n; k++)
                    if (R[i][k] && R[k][j] && !testEqual(j, k) && !testEqual(i, k))
                        adjacentflag = 0;
                if (adjacentflag && !testEqual(i, j))
                    R[i][j]++;
            }
        }
}
void testSup(int a, int b) //ab是数组里的数
{
    for (int i = 0; i < n; i++)
        if (R[a][i] == 2)
        {
            if (R[b][i])
            {
                if (!sup[0])
                    sup[++sup[0]] = i;
                else if (R[i][sup[1]])
                    sup[1] = i;
                else if (!testEqual(sup[1], i) && !R[sup[1]][i])
                    sup[++sup[0]] = i;
            }
            else if (!testEqual(last, i))
                testSup(i, b);
            if (!flag)
                break;
        }
}
void testInf(int a, int b)
{
    for (int i = 0; i < n; i++)
        if (R[i][a] == 2)
        {
            if (R[i][b])
            {
                if (!inf[0])
                    inf[++inf[0]] = i;
                else if(R[inf[1]][i])
                    inf[1] = i;
                else if (!testEqual(inf[1], i) && !R[i][inf[1]])
                    inf[++inf[0]] = i;
            }
            else if (!testEqual(first, i))
                testInf(i, b);
            if (!flag)
                break;
        }
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
            order[cnt][++order[cnt][0]] = i; //指向了多少个
            if (!R[i][i])
                flag = 0;
        }
        if (flag && testTran() && order[n][0])
        {
            first = order[n][1];
            while (!order[last][0])
                last++;
            last = order[last][1];
            adjacent();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (!R[i][j] && !R[j][i])
                    {
                        sup[0] = 0, inf[0] = 0;
                        testSup(i, j);
                        testInf(i, j);
                        if (sup[0] == 0 || inf[0] == 0)
                            flag = 0;
                        else
                        {
                            if (sup[0] > 1)
                            {
                                flag = 0;
                                for (int s = 1; s <= sup[0]; s++)
                                {
                                    cnt = 0;
                                    for (int m = 1; m <= sup[0]; m++)
                                        if (R[s][m] || testEqual(s, m))
                                            cnt++;
                                    if (cnt == sup[0])
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                            if (flag && inf[0] > 1)
                            {
                                flag = 0;
                                for (int s = 1; s <= inf[0]; s++)
                                {
                                    cnt = 0;
                                    for (int m = 1; m <= inf[0]; m++)
                                        if (R[m][s] || testEqual(s, m))
                                            cnt++;
                                    if (cnt == inf[0])
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (!flag)
                        break;
                }
                if (!flag)
                    break;
            }
            if (flag)
                cout << "Y\n";
            else
                cout << "N\n";
        }
        else
            cout << "N\n";
        for (int i = 0; i <= n; i++)
            order[i][0] = 0;
        last = 0;
    }
    return 0;
}
