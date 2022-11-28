#include <iostream>
using namespace std;
const int maxn = 400 + 5;
struct Dir
{
    int up = 0;
    int down = 0;
    int Left = 0;
    int Right = 0;
};
Dir dir[maxn][maxn];
int road[maxn][maxn] = {0}, cur[maxn][maxn] = {0}, y = 0, x = 0, n, m, countt;
void edit(int a, int b)
{
    countt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (cur[i][j] == 0)
                continue;
            else if (i + b < 1 || i + b > n || j + a < 1 || j + a > n){ 
                cur[i][j] = 0;
            }
            else if(road[i+b][j+a] == 0){
                cur[i][j] = 0;
            }
            else
            {
                countt += cur[i][j];
            }
        }
    }
}
int main()
{

    scanf("%d%d", &n, &m);
    countt = 0;
    int row1 = 1, row2 = n, col1 = 1, col2 = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char a;
            scanf(" %c", &a);
            int temp = a - '0';
            road[i][j] = temp;
            cur[i][j] = road[i][j];
            countt += cur[i][j];
        }
    }
    printf("%d\n", countt);
    for (int i = 1; i <= m; i++)
    {
        int op = 0;
        scanf("%d", &op);
        if (op == 0)
        {
            y--; //上移
            if (abs(y) >= n || abs(x) >= n)
            {
                countt = 0;
                printf("%d\n", countt);
                continue;
            }
        }
        else if (op == 1)
        {
            y++; //下移
            if (abs(y) >= n || abs(x) >= n)
            {
                countt = 0;
                printf("%d\n", countt);
                continue;
            }
        }
        else if (op == 2)
        {
            x--; //左移
            if (abs(x) >= n || abs(y) >= n)
            {
                countt = 0;
                printf("%d\n", countt);
                continue;
            }
        }
        else if (op == 3)
        {
            x++; //右移
            if (abs(x) >= n || abs(y) >=n)
            {
                countt = 0;
                printf("%d\n", countt);
                continue;
            }
        }
        int sign = 0;
        if (x >= 0 && y >= 0)
            sign = 4;
        else if (x >= 0 && y < 0)
            sign = 3;
        else if (y >= 0 && x < 0)
            sign = 2;
        else
            sign = 1;
        if (sign == 4)
        {
            if (dir[abs(x)][abs(y)].up != 1)
            {
                dir[abs(x)][abs(y)].up = 1;
                edit(x, y);
            }
        }
        else if (sign == 3)
        {
            if (dir[abs(x)][abs(y)].down != 1)
            {
                dir[abs(x)][abs(y)].down = 1;
                edit(x, y);
            }
        }
        else if (sign == 2)
        {
            if (dir[abs(x)][abs(y)].Left != 1)
            {
                dir[abs(x)][abs(y)].Left = 1;
                edit(x, y);
            }
        }
        else if (sign == 1)
        {
            if (dir[abs(x)][abs(y)].Right != 1)
            {
                dir[abs(x)][abs(y)].Right = 1;
                edit(x, y);
            }
        }
        printf("%d\n", countt);
    }
    return 0;
}
