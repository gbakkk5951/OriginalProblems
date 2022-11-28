#include <bits/stdc++.h>
using namespace std;
int l[4], oppush, a[4000100], v[2000100];
long long ans;
int main()
{
	int n, m, cnt = 0, now = 0;
	scanf("%d%d\n", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		char z;
		scanf("%c", &z);
		a[i] = z - '0';
		if (a[i])
			cnt++;
		else
			++now;
		if (cnt > now)
		{
			cnt--;
			--i;
			--m;
		}
	}
	oppush = 1;
	l[1] = n;
	bool flag = true;
	int tot1 = 0, tot2 = 0;
	for (int i = 1; i <= m; i++)
	{
		if (!a[i])
		{
			++tot1;
			if (cnt < tot1)
				break;
			if (l[1] == 0)
				oppush = 2;
			else
				oppush = 1;
			if (oppush == 1)
			{
				ans += 2;
				l[1]--;
				v[tot1] = 1;
			}
			else if (oppush == 2)
			{
				ans += 4;
				l[2]++;
				v[tot1] = 2;
			}
		}
		else
		{
			tot2++;
			if (v[tot2] == 1)
			{
				if (v[tot2 + 1] != 2)
					l[1]++;
				else if (v[tot2 + 1] == 2 && l[1] != n - 1)
				{
					l[1]++;
					flag = false;
				}
			}
			else if (v[tot2] == 2)
			{
				l[2]--;
				if (l[2] == 0)
				{
					if (flag)
						l[1]++;
					flag = true;
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
} 
