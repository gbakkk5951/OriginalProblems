#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const lld mod = 10000079;
lld getfact(int n)
{
	if (n >= mod)
	{
		return 0;
	}
	lld ret = 1;
	if (n == 0)
	{
		return 1;
	}
	do
	{
		ret = ret * n % mod;
	} while(--n);
	return ret;
}
lld fastpower(lld base, lld exp)
{
	lld ret = 1;
	while (exp)
	{
		if (exp & 1)
		{
			ret = ret * base % mod;
		}
		base = base * base % mod;
		exp >>= 1;
	}
	return ret;
}
int main() 
{
	int n;
	scanf("%d", &n);
	printf("%lld\n%lld", getfact(n - 1), fastpower(2, n - 1));
	return 0;
}
