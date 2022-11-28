#include <bits/stdc++.h>
using namespace std;
int R[55][55], order[55][55];
int t, n, flag, cnt, sup, inf, first, last = 0;
int testTran() //不改，测满足传递否
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
void testSup(int a, int b) 
{
    for (int i = 0; i < n; i++)
        if (R[a][i] == 2)
        {
            if (R[b][i])
            {
                if (sup == -1)
                    sup = i;
                else if (!testEqual(sup, i) && !R[sup][i] && !R[i][sup])
                    flag = 0;
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
                if (inf == -1)
                    inf = i;
                else if (!testEqual(inf, i) && !R[i][inf] && !R[inf][i])
                    flag = 0;
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
            last = order[last][1]; //first last都是比实际减1的(last要不要检查竖着的？)
            adjacent();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    if (!R[i][j] && !R[j][i])
                    {
                        sup = -1, inf = -1;
                        testSup(i, j);
                        testInf(i, j);
                        if (sup == -1 || inf == -1)
                            flag = 0;
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
        for (int i = 0; i <= n;i++)
            order[i][0] = 0;
        last = 0;
    }
    return 0;
}
