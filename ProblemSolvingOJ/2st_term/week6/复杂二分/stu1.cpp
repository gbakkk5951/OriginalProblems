#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L;
int n, m;
int a[maxn];
int Partion(int l, int r, int p)
{
    swap(a[p], a[l]);
    int i = l;
    int j = r;
    int pivot = a[l];
    while(i < j)
    {
        while (j > i && a[j] > pivot)
            j--;
        if (i < j)
            a[i] = a[j], i++;
        while (i < j && a[i] < pivot)
            i++;
        if (i < j)
            a[j] = a[i], j--;
    }
    a[i] = pivot;
    return i;
}
int BFPRT(int l, int r, int k)
{
    int p = (l + r + 1) / 2;
    int i = Partion(l, r, p);
    int m = i - l + 1;
    if(m == k) return a[i];
    if(m > k)  return BFPRT(l, i - 1, k);
    return BFPRT(i + 1, r, k - m);
}
int solve(int l, int r)
{
    if (l == r)
        return l;
    lld sum = 0;
    if (l + 1 == r)
    {
        for (int i = l; i <= r; ++i)
            sum += a[i];
        if (sum <= L)
            return r;
        else
            return l;
    }
    int mid = (l + r) / 2;
    BFPRT(l, r, mid - l + 1);
    for (int i = l; i <= mid; ++i)
        sum += a[i];
    if (sum <= L)
    {
        L = L - sum + a[mid];
        return solve(mid, r);
    }
    else
        return solve(l, mid - 1);
}
lld get_random() {
	return A = C + (A * B) % MOD;
}
int main() {
    lld t = 0, sum = 0;
    srand(time(0));
    scanf("%d%lld%lld%lld%lld%lld", &n, &A, &B, &C, &MOD, &L);
	for (int i = 1; i <= n; ++i)
    { 
        a[i] = get_random();
        if (a[i] <= 0)
        {
            sum += a[i];
            i--;
            n--;
            t++;
        }
    }
    L -= sum;
    lld cnt = solve(0, n);
    if (sum > L)
        cnt = t = 0;
    printf("%lld", cnt + t);
	return 0;
}
