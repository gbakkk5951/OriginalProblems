#include <bits/stdc++.h>
int n, k, t, idx;
int C[5300000][30];
int temp[30];
bool num[30];
int v[30];
long long three[26];
long long S[5300000];
long long cal(int i)
{
    long long sum = 0;
    for (int j = 1; j <= k; j++)
    {
        sum += (long long)v[C[i][j]] * three[k-j];
    }
    return sum;
}
void f(int ordinal, int last)
{
    if (ordinal > k)
    {
        for (int i = 1; i <= k; i++)
        {
            C[idx][i] = temp[i];
        }
        idx++;
        return;
    }
    for (int i = ordinal; i <= n; i++)
    {
        if (!num[i] && i > last)
        {
            temp[ordinal] = i;
            last = i;
            num[i] = true;
            f(ordinal + 1, last);
            num[i] = false;
        }
    }
}
int combination(int n, int k)
{
    int result;
    if (k == 0 || n == k)
    {
        result = 1;
    }
    else
    {
        result = combination(n - 1, k) + combination(n - 1, k - 1);
    }
    return result;
}
long long MAX(long long a)
{
    int max_a, a_next;
    if (--t)
    {
        a_next = S[t];
        max_a = std ::max(a, MAX(a_next));
        return max_a;
    }
    return a;
}
int main()
{
	idx=1;
	three[0]=1;
	for (int i = 1; i <= 25; i++)
    {
      	three[i]=three[i-1]*3;
	}
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        num[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
    }
    t = combination(n, k);
    f(1, 0);
    for (int i = 1; i <= t; i++)
    {
        S[i] = cal(i);
    }
    printf("%lld", MAX(S[t]));
    return 0;
}
