#include <bits/stdc++.h>
using namespace std;
int sum[2000], num[2000], v[2000], a[2000];
int main()
{
    int n, N;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &num[i]);
        sum[i] = num[i] + sum[i - 1];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= num[i]; j++)
            scanf("%d", &a[sum[i - 1] + j]);
    scanf("%d", &N);
    a[sum[n] + 1] = 1;
    while (N--)
    {
        int op;
        scanf("%d", &op);
        if (op == 0)
        {
            int x, y, v, c;
            scanf("%d%d%d%d", &x, &y, &v, &c);
            ++x, ++y;
            if (c == 0)
            {
                printf("true\n");
                continue;
            }
            if (sum[x - 1] + y + c - 1 > sum[n] || sum [x-1] + y <= 0)
                printf("overflow\n");
            else
            {
                if (sum[x - 1] + y + c - 1 > sum[x] || y <= 0)
                    printf("w");
                printf("true\n");
                for (int i = sum[x - 1] + y; i <= sum[x - 1] + y + c - 1; i++)
                    a[i] = v;
            }
        }
        else if (op == 1)
        {
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            ++x0, ++x1, ++y0, ++y1;
            memset(v, 0, sizeof(v));
            if (sum[x0 - 1] + y0 > sum[n] || sum[x1 - 1] + y1 > sum[n] || sum[x0 - 1] + y0 <= 0 || sum[x1 - 1] + y1 <= 0)
                printf("overflow\n");
            else
            {
                int sou, sou0, der, der0, flag = 0;
                sou = sou0 = sum[x0 - 1] + y0;
                der = der0 = sum[x1 - 1] + y1;
                while (a[sou - 1] || sou == sou0)
                {
                    if (sou > sum[n] || der > sum[n])
                    {
                        printf("overflow\n");
                        flag = 1;
                        break;
                    }
                    der++, sou++;
				}
                if (flag)
                	continue;
                sou = sou0, der = der0;
                while ((a[sou - 1] || sou == sou0))
                {
                    if (v[der] > 0 || v[sou] > 0 || sou == der)
                    {
                        printf("overwrite\n");
                        flag = 1;
                        break;
                    }
                    v[der]++;
                    v[sou]++;
                    ++sou;
                    ++der;
                }
                if (flag)
                    continue;
                sou = sou0;
                der = der0;
                while (a[sou - 1] || sou == sou0)
                {
                    if (!flag && (sou <= sum[x0 - 1] || der <= sum[x1 - 1] || sou > sum[x0] || der > sum[x1]))
                    {
                        printf("w");
                        flag = 1;
                    }
                    a[der] = a[sou];
                    ++sou;
                    ++der;
                }
                printf("true\n");
            }
        }
        else
        {
            int x, y, cnt = 0, flag = 0;
            scanf("%d%d", &x, &y);
            ++x, ++y;
            if (sum[x - 1] + y > sum[n] || sum[x - 1] + y <= 0)
            {
                printf("overflow\n");
                continue;
            }
            for (int i = sum[x - 1] + y;; i++)
            {
                if (i > sum[n])
                {
                    flag = -1;
                    printf("overflow\n");
                    break;
                }
                if (!flag && (i <= sum[x - 1] || i > sum[x]))
                    flag = 1;
                if (!a[i])
                    break;
                ++cnt;
            }
            if (sum[x - 1] + y > sum[x])
            {
                flag = 1;
            }
            if (flag < 0)
                continue;
            else if (flag == 1)
            	printf("w");
            printf("%d\n", cnt);
        }
    }
    return 0;
}
