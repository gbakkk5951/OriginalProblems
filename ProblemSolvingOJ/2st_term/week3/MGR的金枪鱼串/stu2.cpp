#include <iostream>
#include <algorithm>
using namespace std;

const int con = 2e6 + 10;
const int MAX = 1e9;
int input[con];
int ans[con];
int fac[] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
int T, N, K;

inline int read();
inline void out(int a);
int check(int goal, int n);
void show();

int main()
{
    T = read();
    while (T--)
    {
        N = read();
        K = read();
        for (int i = 1; i <= N; i++)
            input[i] = read();
        if (N <= 12)
        {
            K %= fac[N];
            while (K > 0)
            {
                bool flag = true;
                int m;
                for (m = N - 1; m > 0 && K > 0; m--)
                {
                    if (input[m] < input[m + 1])
                    {
                        int board = check(m, N);
                        int sub = (board - m) * fac[N - m];
                        if (K >= sub)
                        {
                            K -= sub;
                            int temp = input[m];
                            int j;
                            for (j = m; j < board; j++)
                            {
                                input[j] = input[j + 1];
                            }
                            input[j] = temp;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                    if (!flag)
                        break;
                }
                if (K && flag)
                {
                    for (int i = 1; i <= N; i++)
                        input[i] = i;
                    K--;
                    for (int x = 1; x < N && K > 0; x++)
                    {
                        if (K >= fac[N - x])
                        {
                            int t = K / fac[N - x];
                            K %= fac[N - x];
                            int temp = input[x + t];
                            for (int j = x + t; j > x; j--)
                                input[j] = input[j - 1];
                            input[x] = temp;
                        }
                    }
                }
                if (K && !flag)
                {
                    for (int x = N; x > m; x--)
                    {
                        if (input[x] > input[m])
                        {
                            K--;
                            swap(input[x], input[m]);
                            for (int j = m + 1; j <= (m + 1 + N) / 2; j++)
                                swap(input[j], input[N + m + 1 - j]);
                            break;
                        }
                    }
                    for (int x = m + 1; x < N && K > 0; x++)
                    {
                        if (K >= fac[N - x])
                        {
                            int t = K / fac[N - x];
                            if (x + t > N)
                            {
                                K -= (N - x) * fac[N - x];
                                int temp = input[N];
                                for (int j = N; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                            else
                            {
                                K %= fac[N - x];
                                int temp = input[x + t];
                                for (int j = x + t; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            while (K > 0)
            {
                int m;
                bool flag = true;
                for (m = N - 1; m > N - 13 && K > 0; m--)
                {
                    if (input[m] < input[m + 1])
                    {
                        long long sub = (check(m, N) - m) * (long long)fac[N - m];
                        if (K >= sub)
                        {
                            K -= sub;
                            int temp = input[m];
                            int j;
                            int board = check(m, N);
                            for (j = m; j < board; j++)
                            {
                                input[j] = input[j + 1];
                            }
                            input[j] = temp;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                    if (!flag)
                        break;
                }
                if (K && flag)
                {
                    bool rev = true;
                    for (int i = N - 13; i > 0; i--)
                    {
                        if (input[i] < input[i + 1])
                        {
                            rev = false;
                            K--;
                            swap(input[i], input[i + 1]);
                            i++;
                            for (int j = i; j <= (i + N) / 2; j++)
                                swap(input[j], input[N + i - j]);
                            break;
                        }
                    }
                    if (rev && K > 0)
                    {
                        K--;
                        for (int i = 1; i <= N; i++)
                            input[i] = i;
                    }
                    for (int x = N - 12; x < N && K > 0; x++)
                    {
                        if (K >= fac[N - x])
                        {
                            int t = K / fac[N - x];
                            if (x + t > N)
                            {
                                K -= (N - x) * fac[N - x];
                                int temp = input[N];
                                for (int j = N; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                            else
                            {
                                K %= fac[N - x];
                                int temp = input[x + t];
                                for (int j = x + t; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                        }
                    }
                }
                if (K && !flag)
                {
                    for (int x = N; x > m; x--)
                    {
                        if (input[x] > input[m])
                        {
                            K--;
                            swap(input[x], input[m]);
                            for (int j = m + 1; j <= (m + 1 + N) / 2; j++)
                                swap(input[j], input[N + m + 1 - j]);
                            break;
                        }
                    }
                    for (int x = m + 1; x < N && K > 0; x++)
                    {
                        if (K >= fac[N - x])
                        {
                            int t = K / fac[N - x];
                            if (x + t > N)
                            {
                                K -= (N - x) * fac[N - x];
                                int temp = input[N];
                                for (int j = N; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                            else
                            {
                                K %= fac[N - x];
                                int temp = input[x + t];
                                for (int j = x + t; j > x; j--)
                                    input[j] = input[j - 1];
                                input[x] = temp;
                            }
                        }
                    }
                }
            }
        }
        show();
    }
    return 0;
}

inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

inline void out(int a)
{
    if (a >= 10)
        out(a / 10);
    putchar(a % 10 + '0');
}

int check(int goal, int n)
{
    int ans = 0;
    for (int i = n; i > goal; i--)
    {
        if (input[i] > input[goal])
        {
            return i;
        }
    }
    return 0;
}
void show()
{
    for (int i = 1; i <= N; i++)
    {
        out(input[i]);
        printf(" ");
    }
    printf("\n");
}

