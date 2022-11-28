#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int MaxSize = 1e6 + 5;
const int inf = 0x3f3f3f3f;
template <typename Type>
void read(Type &x)
{
    char c, f = 1;
    while (!isdigit(c = getchar()))
    {
        f = c == '-' ? -1 : f;
    }
    x = c - '0';
    while (isdigit(c = getchar()))
    {
        x = x * 10 + c - '0';
    }
    x *= f;
}
int main()
{
    int n, T, cur;
    long long int num, sum;
    int a[MaxSize], q[MaxSize] = {}, f[MaxSize] = {}; // f[]记录质因子
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; i++)
        {
            read(a[i]);
            q[i] = 0;
            f[i] = 0;
        }
        num = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!q[i])
            { //记录是否访问过
                q[i] = 1;
                cur = a[i];
                sum = 1;
                while (!q[cur])
                {
                    q[cur] = 1;
                    sum++;
                    cur = a[cur];
                }
                if (sum > 1)
                {
                    for (int j = 2; j <= sum; j++)
                    {
                        num = 0;
                        while (sum % j == 0)
                        {
                            sum /= j;
                            num++;
                        }
                        
                        if (num > f[j])
                            f[j] = num;
                    }
                }
            }
        }
        num = 1;
        for (int i = 1; i <= n; i++)
        {
            while (f[i] > 0)
            {
                num = (num * i) % 998244353;
                f[i]--;
            }
        }
        printf("%lld\n", num);
    }

    return 0;
}
