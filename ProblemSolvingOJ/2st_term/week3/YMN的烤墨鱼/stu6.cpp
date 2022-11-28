#include <cstdio>
#include <cstring>
#define MOD 998244353
#define MAXV 1000010
int T, n, a[1000100], mark[1000100], prime[1000100], prime_cnt, powv[1000100], primt[1000100];
void init()
{
	for(int i = 2; i <= MAXV; i++)
	{
		if(!mark[i])
		{
			prime[++prime_cnt] = i;
			primt[i] = prime_cnt;
		}
		for(int j = 1; j <= prime_cnt && 1ll * i * prime[j] <= MAXV; j++)
		{
			mark[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	memset(mark, 0, sizeof(mark));
}
long long fp(long long b, long long p)
{
	long long ans = 1;
	while(p)
	{
		if(p & 1)
			ans = (ans * b) % MOD;
		p /= 2;
		b = (b * b) % MOD;
	}
	return ans;
}
int main()
{
	init();
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		memset(mark, 0, (n + 1) * sizeof(int));
		int mxct = 0;
		for(int i = 1; i <= n; i++)
		{
			if(mark[i])
				continue;
			int t = a[i], c = 1;
			mark[i] = 1;
			while(t != i)
			{
				mark[t] = 1;
				t = a[t];
				c++;
			}	
			for(int j = 1; j <= prime_cnt && c != 1 && 1ll * prime[j] * prime[j] <= c; j++)
			{
				if(c % prime[j] == 0)
				{
					int p = 0;
					while(c % prime[j] == 0)
					{
						p++;
						c /= prime[j];
					}
					powv[j] = powv[j] > p ? powv[j] : p;
					if(c == 1)
					{
						mxct = mxct > j ? mxct : j;
						break;
					}
				}
			}
			if(c != 1)
			{
				mxct = mxct > primt[c] ? mxct : primt[c];
				powv[primt[c]] = powv[primt[c]] > 1 ? powv[primt[c]] : 1;
			}
		}
		long long ans = 1;
		for(int i = 1; i <= mxct; i++)
		{
			ans = (ans * fp(prime[i], powv[i])) % MOD;
			powv[i] = 0;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
