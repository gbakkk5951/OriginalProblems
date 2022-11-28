#include <iostream>
using namespace std;
const int maxn = 52;
int r[maxn][maxn] = {};
int n;

bool refle()
{
    for (int i = 1; i <= n; i++)
    {
        if (r[i][i] == 0)
            return false;
    }
    return true;
}

bool tran()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (r[i][j])
            {
                for (int k = 1; k < n; k++)
                {
                    if (r[j][k])
                    {
                        if (r[i][k] == 0)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

int mark[maxn];
int flag = 0;
bool exi;
int numb;
bool lat()
{
    numb = 0;
    for (int i = 1; i <= n; i++)
    {
        exi = true;
        for (int j = 1; j <= n; j++)
        {
            if ((j != i) && (r[i][j] == 1))
            {
                exi = false;
            }
        }
        if (exi)
        {
            numb++;
        }
        if (numb > 1)
        {
            return false;
        }
    }
    numb = 0;
    for (int i = 1; i <= n; i++)
    {
        exi = true;
        for (int j = 1; j <= n; j++)
        {
            if ((j != i) && (r[j][i] == 1))
            {
                exi = false;
            }
        }
        if (exi)
        {
            numb++;
        }
        if (numb > 1)
        {
            return false;
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if ((r[i][j] == 0) && (r[j][i] == 0))
            {
                flag = 0;
                for (int k = 1; k <= n; k++)
                {
                    if ((r[k][i] == 1) && (r[k][j] == 1))
                    {
                        flag++;
                        mark[flag] = k;
                    }
                }
                if (flag == 0)
                {
                    return false;
                }
                if (flag > 1)
                {
                    exi = false;
                    for (int ii = 1; ii <= flag; ii++)
                    {
                        bool fl = true;
                        for (int jj = 1; jj <= flag; jj++)
                        {
                            if (r[mark[jj]][mark[ii]] == 0)
                            {
                                fl = false;
                            }
                        }
                        if (fl)
                        {
                            exi = true;
                            break;
                        }
                    }
                    if (exi == false)
                    {
                        return false;
                    }
                }
                flag = 0;
                for (int k = 1; k <= n; k++)
                {
                    if ((r[i][k] == 1) && (r[j][k] == 1))
                    {
                        flag++;
                        mark[flag] = k;
                    }
                }
                if (flag == 0)
                {
                    return false;
                }
                if (flag > 1)
                {
                    exi = false;
                    for (int ii = 1; ii <= flag; ii++)
                    {
                        bool fl = true;
                        for (int jj = 1; jj <= flag; jj++)
                        {
                            if (r[mark[ii]][mark[jj]] == 0)
                            {
                                fl = false;
                            }
                        }
                        if (fl)
                        {
                            exi = true;
                            break;
                        }
                    }
                    if (exi == false)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    int t;
    cin >> t;
    for (int k = 0; k < t; k++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> r[i][j];
            }
        }
        if (refle() && tran())
        {
            if (lat())
            {
                cout << 'Y' << endl;
            }
            else
            {
                cout << 'N' << endl;
            }
        }
        else
        {
            cout << 'N' << endl;
        }
    }
    return 0;
}
