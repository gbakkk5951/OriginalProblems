#include <iostream>
#include <cstdio>
#define N 1000000
using namespace std;
int original[N + 5];
int small[N + 5];
int big[N + 5];
int copy1[N + 5];
int min_record[N + 5];
int n;
int k;
bool check();
int mymax(int a, int b);
int mymin(int a, int b);

int main()
{
    scanf("%d", &n);
    scanf("%d", &k);
    int max = -1;
    int min = k;
    int if_carry = 0;
    int max_position = 0; //最低位的max在的位置
    int min_position = 0; //最高位的min在的位置
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &original[i]);
        copy1[i] = original[i];
        small[i] = original[i];
        big[i] = original[i];
        max = mymax(max, original[i]);
        min = mymin(min, original[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (min_position == 0 && original[i] == min)
            min_position = i;
        if (original[i] == max)
            max_position = i;
    }
    for (int i = 1; i <= n; i++)
        if (original[i] + max >= k && i != max_position)
        {
            if_carry = 1;
            break;
        }
        else
            if_carry = 0;
    if (if_carry == 0)
    {
        big[1] = 0;
        big[2] = original[1] + original[2];
        for (int i = 2; i <= n; i++)
            printf("%d ", big[i]);
        printf("\n");
    }
    else
    {
        if (min == 1 && max == k - 1 && max_position > min_position)
        {
            for (int i = n; i >= min_position + 1; i--)
            {
                if (1 + original[i] == k)
                {
                    copy1[i] = 0;
                    break;
                }
            }
            int max2 = -1;
            for (int i = n; i >= 2; i--)
            {
                int sym = 0;
                max2 = mymax(max2, original[i]);
                if (max2 + original[i - 1] >= k)
                {
                    sym = 1;
                    big[i - 1] = 1;
                    for (int j = n; j >= i; j--)
                    {
                        if (original[j] + original[i - 1] >= k)
                        {
                            big[j] = original[j] + original[i - 1] - k;
                            break;
                        }
                    }
                }
                if (sym == 1)
                    break;
            }
            if (check())
            {
                for (int i = 1; i <= n; i++)
                    printf("%d ", copy1[i]);
                printf("\n");
            }
            else
            {
                for (int i = 1; i <= n; i++)
                    printf("%d ", big[i]);
                printf("\n");
            }
        }
        else
        {
            int max2 = -1;
            for (int i = n; i >= 2; i--)
            {
                int sym = 0;
                max2 = mymax(max2, original[i]);
                if (max2 + original[i - 1] >= k)
                {
                    sym = 1;
                    big[i - 1] = 1;
                    for (int j = n; j >= i; j--)
                    {
                        if (original[j] + original[i - 1] >= k)
                        {
                            big[j] = original[j] + original[i - 1] - k;
                            break;
                        }
                    }
                }
                if (sym == 1)
                    break;
            }
            for (int i = 1; i <= n; i++)
                printf("%d ", big[i]);
            printf("\n");
        }
    }

    int min1 = k;
    int goal = 1;
    min_record[n] = original[n];
    for (int i = n - 1; i >= 1; i--)
        min_record[i] = mymin(original[i], min_record[i + 1]);
    for (int i = n; i >= 2; i--)
    {
        min1 = mymin(min1, original[i]);
        if (min1 + original[i - 1] >= k)
            continue;
        else
        {
            goal = i; //从goal到n都可以100%进位
            break;
        }
    }
    if (goal == 1)
    {
        small[1] = 1, small[2] = original[1] + original[2] - k;
        for (int i = 1; i <= n; i++)
            printf("%d ", small[i]);
    }

    else
    {
        int flag = 0;
        for (int i = 1; i <= goal - 2; i++)
            if (original[i] < original[i + 1])
                continue;
            else
            {
                if (original[i] + min_record[i + 2] < k)
                {
                    for (int j = n; j >= i + 2; j--)
                    {
                        if (original[i] + original[j] < k)
                        {
                            small[i] = -1, small[j] = original[i] + original[j];
                            break;
                        }
                    }
                    flag = 1;
                    break;
                }
            }
        if (flag == 0)
        {
            for (int i = n; i >= goal; i--)
                if (original[goal - 1] + original[i] < k)
                {
                    small[goal - 1] = -1;
                    small[i] = original[goal - 1] + original[i];
                    break;
                }
        }
        int l = 1;
        while (small[l] == 0 || small[l] == -1)
        {
            small[l] = -1;
            l++;
        }
        for (int i = 1; i <= n; i++)
            if (small[i] != -1)
                printf("%d ", small[i]);
		printf("\n");
        return 0;
    }
}
bool check()
{
    int i = 1;
    while (i != n + 1)
    {
        if (copy1[i] > big[i])
            return true;
        if (copy1[i] < big[i])
            return false;
        i++;
    }
    return false;
}
int mymin(int a, int b)
{
    return a < b ? a : b;
}
int mymax(int a, int b)
{
    return a > b ? a : b;
}
