#include <iostream>
#include <cstring>
using namespace std;
const int N = 25 + 5;
int n, k;
long long ans = -0x3f3f3f3f3f3f3f3f;
long long product[25];
void solve(int *a, int m, int last, long long sum)
{
    if (m == k + 1)
    {
        if (sum > ans)
        {
            ans = sum;
        }
        return;
    }
    for (int i = last + 1; i <= n; i++)
    {
        solve(a, m + 1, i, sum + a[i] * product[m]);
    }
}
int main()
{
    cin >> n >> k;
    int a[N];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    product[k] = 1;
    for (int i = k - 1; i > 0; i--)
    {
        product[i] = 3 * product[i + 1];
    }
    solve(a, 1, 0, 0);
    cout << ans;
    return 0;
}
