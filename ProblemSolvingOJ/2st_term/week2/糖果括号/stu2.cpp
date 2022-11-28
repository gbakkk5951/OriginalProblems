#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
const int MAX = 2000005;
unsigned long long stack[2][MAX + 5] = {};
unsigned long long a[2][MAX + 5] = {};
unsigned long long maxi = 0;
int rbracket = 0, candy = 0;
int r = 1, l = 1, lbracket = 0;

unsigned long long findmax(int r)
{

    for (int i = 1; i <= r; i++)
    {
        if (stack[1][i] > maxi && stack[0][i] == 2)
            maxi = stack[1][i];
    }
    return maxi;
}
int main()
{
    int n, sum, opt, i;
    cin >> n >> opt;

    for (i = 1; i <= n; i++)
    {
        scanf("%llu", &a[0][i]);
    }
    for (i = n + 1; i <= MAX; i++)
    {
        stack[0][i] = 3;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%llu", &a[1][i]);
    }

    for (i = 1; i <= n; i++)
    {
        if (a[0][i] == 2)
        {
            if (r == 1 || stack[0][r - 1] != 2)
            {
                stack[0][r] = 2;
                stack[1][r] = a[1][i];
                r++;

                continue;
            }
            else
            {
                stack[1][r - 1] += a[1][i];
                continue;
            }
        }
        else if (a[0][i] == 0)
        {
            lbracket++;
            stack[0][r] = 0;
            stack[1][r] = a[1][i];
            r++;
            continue;
        }
        else if (a[0][i] == 1)
        {
            if (lbracket == 0)
            {
                stack[0][r] = 1;
                stack[1][r] = a[1][i];
                r++;
                rbracket++;
                continue;
            }
            else
            {
                lbracket--;
                int j = r - 1;
                stack[1][j] += a[1][i];
                while (j >= 1 && stack[0][j] != 0)
                {
                    stack[1][j - 1] += stack[1][j];
                    j--;
                }
                stack[0][j] = 2;
                while (j >= 2 && stack[0][j - 1] == 2)
                {
                    stack[1][j - 1] += stack[1][j];
                    j--;
                }
                r = j + 1;
            }
        }
    }
    printf("%llu\n", findmax(r));

    int flag = 0;
    r--;
    while (opt--)
    {
        unsigned long long position, type, value;
        scanf("%llu%llu%llu", &position, &type, &value);
        if (n == 0 && flag == 0)
        {
            flag = 1;
            if (type == 0)
                lbracket++;
            else if (type == 1)
                rbracket++;
            else
                maxi = value;
            
            stack[0][1] = type;
            stack[1][1] = value;
           
            r=1;
            l=1;
            printf("%llu\n", findmax(r));
            continue;
        }
        if (position == 0)
        {
            if (type == 0)
            {
                if (stack[0][l] == 0)
                {
                    l--;
                    if (l == 0)
                        l = MAX - 1;
                    stack[0][l] = 0;
                    stack[1][l] = value;
                    lbracket++;
                }
                else
                {
                    if (rbracket == 0)
                    {
                        l--;
                        if (l == 0)
                            l = MAX - 1;
                        stack[0][l] = 0;
                        stack[1][l] = value;
                        lbracket++;
                    }
                    else
                    {
                        int numlb = 0, numrb = 0;
                        int temp = l;
                        rbracket--;
                        unsigned long long tempsum = value;
                        while (1)
                        {
                            if (stack[0][temp] == 0)
                                numlb++;
                            else if (stack[0][temp] == 1)
                                numrb++;

                            if (temp != r + 1 && !(temp == 1 && r == MAX - 1) && numlb == 0 && numrb <= 1)
                            {
                                tempsum += stack[1][temp];
                                temp++;
                                if (temp == MAX)
                                    temp = 1;
                            }
                            else
                                break;
                        }
                        l = temp - 1;
                        stack[0][l] = 2;
                        stack[1][l] = tempsum;
                        maxi = max(tempsum, maxi);
                    }
                }
            }
            else if (type == 1)
            {
                l--;
                if (l == 0)
                    l = MAX - 1;
                stack[0][l] = 1;
                stack[1][l] = value;
                rbracket++;
            }
            else
            {
                if (stack[0][l] == 2)
                {
                    stack[1][l] += value;
                    maxi = max(maxi, stack[1][l]);
                }
                else
                {
                    l--;
                    if (l == 0)
                        l = MAX - 1;
                    stack[0][l] = 2;
                    stack[1][l] = value;
                    maxi = max(maxi, stack[1][l]);
                }
            }
        }
        else
        {
            if (type == 1)
            {
                if (stack[0][r] == 1)
                {
                    r++;

                    stack[0][r] = 1;
                    stack[1][r] = value;
                    rbracket++;
                }
                else
                {
                    if (lbracket == 0)
                    {
                        r++;
                        stack[0][r] = 1;
                        stack[1][r] = value;
                        rbracket++;
                    }
                    else
                    {
                        int numlb = 0, numrb = 0;
                        int temp = r;
                        lbracket--;
                        unsigned long long tempsum = value;
                        while (1)
                        {
                            if (stack[0][temp] == 0)
                                numlb++;
                            else if (stack[0][temp] == 1)
                                numrb++;

                            if (temp != l - 1 && !(temp == MAX - 1 && l == 1) && numrb == 0 && numlb <= 1)
                            {
                                tempsum += stack[1][temp];
                                temp--;
                                if (temp == 0)
                                    temp = MAX - 1;
                            }
                            else
                                break;
                        }
                        r = temp + 1;
                        if (r == MAX)
                            r = 1;
                        stack[1][r] = tempsum;
                        stack[0][r] = 2;
                        maxi = max(tempsum, maxi);
                    }
                }
            }
            else if (type == 0)
            {
                r++;
                stack[0][r] = 0;
                stack[1][r] = value;
                lbracket++;
            }
            else
            {
                if (stack[0][r] == 2)
                {
                    stack[1][r] += value;
                    maxi = max(maxi, stack[1][r]);
                }
                else
                {
                    r++;
                    stack[0][r] = 2;
                    stack[1][r] = value;
                    maxi = max(maxi, stack[1][r]);
                }
            }
        }
        printf("%llu\n", maxi);
    }
}
/*
 1 6
 1
 0
 1 1 4000000
 0 0 4000000
 1 2 4000000
 0 1 4000000
 1 2 4000000
 1 1 6
 1
 
*/

