#include <iostream>
#include <cstdio>
using namespace std;
bool warn = false;
int *p[100005] = {};
int s[100005] = {}, m[100005] = {};
int tol = 0;
void check(int x, int y)
{
    if (m[x] <= y || y < 0)
        warn = true;
}
void mem(int *po, int v, int c)
{
    for (int i = 0; i < c; ++i)
    {
        *(po + i) = v;
    }
}
void mylen(int x, int y)
{
    int len = 0;
    if (p[x] + y < p[0] || p[0] + tol - 1 < p[x] + y)
    {
        printf("overflow\n");
        return;
    }
    while (*(p[x] + y + len) != 0)
    {
        if (p[x] + y + len == p[0] + tol - 1)
        {
            printf("overflow\n");
            return;
        }
        len++;
    }
    check(x, y);
    check(x, y + len);
    if (warn == true)
    {
        printf("w");
        warn = false;
    }
    printf("%d\n", len);
}
void cpy(int x0, int y0, int x1, int y1)
{
    int len = 0;
    while (*(p[x0] + y0 + len) != 0)
    {
        if (p[x0] + y0 + len == p[0] + tol - 1)
        {
            printf("overflow\n");
            return;
        }
        len++;
    }
    len++;
    if (p[x0] + y0 < p[0] || p[x1] + y1 < p[0] || p[x0] + y0 + len - 1 > p[0] + tol - 1 || p[x1] + y1 + len - 1 > p[0] + tol - 1)
    {
        printf("overflow\n");
        return;
    }
    if (!(p[x0] + y0 > p[x1] + y1 + len - 1 || p[x1] + y1 > p[x0] + y0 + len - 1))
    {
        printf("overwrite\n");
        return;
    }
    check(x0, y0);
    check(x0, y0 + len - 1);
    check(x1, y1);
    check(x1, y1 + len - 1);
    if (warn == true)
    {
        printf("w");
        warn = false;
    }
    for (int i = 0; i < len; ++i)
    {
        *(p[x1] + y1 + i) = *(p[x0] + y0 + i);
    }
    printf("true\n");
}
int main()
{
    int n = 0, k = 0;
    int x = 0, y = 0, v = 0, c = 0;
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    int opt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        p[i] = &s[tol];
        scanf("%d", &m[i]);
        tol += m[i];
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m[i]; ++j)
        {
            scanf("%d", p[i] + j);
        }
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &opt);
        switch (opt)
        {
        case 0:
            warn = false;
            scanf("%d%d%d%d", &x, &y, &v, &c);
            if (c == 0)
            {
                printf("true\n");
                break;
            }
            if (p[x] + y < p[0] || p[x] + y + c - 1 > p[0] + tol - 1 || p[x] + y + c - 1 > p[0] + tol - 1)
            {
                printf("overflow\n");
                break;
            }
            check(x, y);
            check(x, y + c - 1);
            if (warn == true && c != 0)
            {
                printf("w");
                warn = false;
            }
            else if (c == 0)
            {
                warn = false;
            }
            mem(p[x] + y, v, c);
            printf("true\n");
            break;
        case 1:
            warn = false;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            cpy(x0, y0, x1, y1);
            break;
        case 2:
            warn = false;
            scanf("%d%d", &x, &y);
            mylen(x, y);
            break;
        }
    }
    return 0;
}
