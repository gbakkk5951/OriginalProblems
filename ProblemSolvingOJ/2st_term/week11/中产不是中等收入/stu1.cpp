#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000005;
long money[maxn];
struct ele
{
    long dis;
    long Abs;
};
ele element[maxn];

bool cmp(ele a, ele b)
{
    return a.Abs < b.Abs;
}

void read(long &a)
{
    char t, f = 1;
    while (!isdigit(t = getchar()))
    {
        if (t == '-')
            f = -1;
    }
    a = t - '0';
    while (isdigit(t = getchar()))
    {
        a *= 10;
        a += t - '0';
    }
    a *= f;
}

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        read(money[i]);
        money[i] *= 2;
    }
    long mid;
    if (n % 2 == 0)
    {
        nth_element(money, money + n / 2, money + n);
        mid = money[n / 2 - 1];
        nth_element(money, money + n / 2 + 1, money + n);
        mid += money[n / 2];
        mid /= 2;
    }
    else
    {
        nth_element(money, money + (n + 1) / 2 - 1, money + n);
        mid = money[(n + 1) / 2 - 1];
    }
    // cout<<"nth_element排序后"<<endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout<<money[i]<<" ";
    // }
    // cout<<endl;
    // cout<<mid;
    for (int i = 0; i < n; i++)
    {
        element[i].dis = money[i] - mid;
        if (element[i].dis >= 0)
        {
            element[i].Abs = element[i].dis;
        }
        else
            element[i].Abs = -element[i].dis;
    }
    long mark;
    nth_element(element, element + k-1, element + n, cmp);
    mark = element[k - 1].Abs;
    long num = 0;
    long ans = 0;
    long temp = 0;
    for (int i = 0; i < n; i++)
    {
        if (num == k)
        {
            break;
        }
        if (element[i].Abs < mark)
        {
            ans += (element[i].dis + mid);
            num++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (num == k)
        {
            break;
        }
         if (element[i].Abs == mark && element[i].dis >= 0)
        {
            ans += (element[i].dis + mid);
            num++;
        }
        else if (element[i].Abs == mark && element[i].dis < 0)
        {
            temp = (element[i].dis + mid);
        }
    }
    if (num < k)
    {
        ans += (k - num) * temp;
    }
    cout << ans/2<<endl;
    return 0;
}
