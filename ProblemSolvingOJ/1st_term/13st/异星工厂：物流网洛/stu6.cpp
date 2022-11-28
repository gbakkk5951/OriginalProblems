#include <iostream>
using namespace std;
const int N = 50 + 5;
int n;
int a[N][N];
bool legal = true;
int sup[N][N];
void init()
{
    legal = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sup[i][j] = a[i][j] = 0;
        }
    }
}
void solve_exist(int k)
{
    if (k == n)
    {
        return;
    }
    for (int l = k + 1; l <= n; l++)
    {
        for (int o = 1; o <= n; o++)
        {
            if (a[k][o] == 1 && a[l][o] == 1) //检查sup(k,l)的存在性
            {
                sup[k][l] = o; //the first one
                break;
            }
            if (o == n)
            {
                legal = false;
                return;
            }
        }
        for (int o = 1; o <= n; o++)
        {
            if (a[o][k] == 1 && a[o][l] == 1) //检查inf(k,l)的存在性
            {
                break;
            }
            if (o == n)
            {
                legal = false;
                return;
            }
        }
    }
    solve_exist(k + 1);
}
void solve_unique(int k)
{
    if (k == n)
    {
        return;
    }
    for (int l = k + 1; l <= n; l++)
    {
        if (sup[k][l] == n)
            continue;
        for (int o = sup[k][l]; o <= n - 1; o++)
        {
            if (a[k][o] == 1 && a[l][o] == 1)
            {
                for (int p = o + 1; p <= n; p++)
                {
                    if (a[k][p] == 1 && a[l][p] == 1)
                    {
                        if ((a[o][p] == 0 && a[p][o] == 0) || (a[k][l] == 0 && a[l][k] == 0))
                        {
                            legal = false;
                            return;
                        }
                    }
                }
            }
        }
    }
    solve_unique(k + 1);
    return; //?
}
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
                cin >> a[i][j];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (a[i][i] == 0)
            {
                legal = false;
                break;
            }
        } //reflexive
        if (legal)
        {
            for (int i = 1; i <= n - 1; i++)
            {
                for (int j = i + 1; j <= n; j++)
                {
                    if ((a[i][j] == 1) && (a[j][i] == 1))
                    {
                        for (int k = 1; k <= n; k++)
                        {
                            if (!(a[i][k] == a[j][k] && a[k][i] == a[k][j]))
                            {
                                legal = false;
                                goto stop;
                            }
                        }
                    }
                }
            }
        }
    stop:
        if (legal) //1
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (i == j || a[i][j] == 0)
                        continue;
                    for (int k = 1; k <= n; k++)
                    {
                        if (a[j][k] == 0)
                            continue;
                        if (a[i][k] == 0)
                        {
                            legal = false;
                            goto here;
                        }
                    }
                }
            }
        here: //transitive
            if (legal)
            { //2
                solve_exist(1);
                if (legal)
                    solve_unique(1);
            }
        }
        if (legal)
            cout << 'Y' << endl;
        else
            cout << 'N' << endl;
        init();
    }
    return 0;
}
