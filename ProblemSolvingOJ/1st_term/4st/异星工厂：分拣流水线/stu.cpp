#include<iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;
long long A;
long double B;
char str[100000];
char C[100000], D[100000];
bool flag = 0;
int main()
{
    int l1=0, l2=0, po=0;
    cin >> str;
    long n = strlen(str);
    long long sum1=0 ;
    double sum2 = 0.00;
    for (long i = 0; i < n; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            D[l2] = str[i] - 'A' + 'a';
            l2=l2+1;
                A = A + sum1;
                B = B + sum2;
                sum1 = 0;
                sum2 = 0;
                flag = 0;
                po = 0;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            C[l1] = str[i] + 'A' - 'a';
            l1 = l1 + 1;
            A = A + sum1;
            B = B + sum2;
            sum1 = 0;
            sum2 = 0;
            flag = 0;
            po = 0;
        }
        else if (str[i] <='9' && str[i]>='0')
        {
            if (flag == 0)
            {
                sum1 = sum1 * 10 + str[i] - '0';
            }
            else
            {
                po++;
                sum2 = sum2 + ((double)str[i] -(double)'0') * pow(0.1, po);

            }
        }
        else
        {
            flag = 1;
            sum2 = sum1;
            sum1 = 0;
        }
    }
    A = A + sum1;
    B = B + sum2;
    sum1 = 0;
    sum2 = 0;
    flag = 0;
    po = 0;
    cout << A << endl;
    printf("%.2Lf\n", B);
    for (long k = 0; k < l2; k++)
    {
        cout << D[k];
    }
    cout << endl;
    for (long m = 0; m < l1; m++)
    {
        cout << C[m];
    }
    return 0;
}
