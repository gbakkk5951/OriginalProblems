#include <bits/stdc++.h>
using namespace std;

double mul(double x, int y)
{
	double ans = 1;
	for (int i = 1; i <= y; i++)
	  ans *= x;
	return ans;
}

int main()
{
	string s;
	bool judge[100010];
	int n;
	long long sum1 = 0;
	double sum2 = 0, num = 0;
	string s1, s2;
	int i, j;
	int k, m;
	int p, q;
	cin >> s;
	n = s.length();
	memset(judge, 0, sizeof(judge));
	p = q = 1;
	k = -1;
	m = -2;
	i = 0;
	while (i <= n)
	{
		if (s[i] >= '0' && s[i] <= '9' && !judge[i])
		{
			if (k == -1)
			  k = i;
			m = i;
		}
		else
		{
			if (s[i] == '.')
		    {
		    	judge[i] = 1;
			    num = 0;
			    k = -1;
				m = -2;
			    j = i - 1;
			    while (s[j] >= '0' && s[j] <= '9')
			    {
				    num += (s[j] - '0') * mul(10, i-j-1);
				    judge[j] = 1;
				    j--;
			    }
			    j = i + 1;
			    while (s[j] >= '0' && s[j] <= '9')
			    {
				    num += (s[j] - '0') * mul(0.1, j-i);
				    judge[j] = 1;
				    j++;
			    }
			    sum2 += num;
		    }
			if (m >= k)
			{
				num = 0;
				for (j = k; j <= m; j++)
				{
					if (!judge[j])
					  num += (s[j] - '0') * mul(10, m-j);
					else
					{
						num = 0;
						break;
					}
				}
				sum1 += num;
				k = -1;
				m = -2;
			}
			if (s[i] >= 'A' && s[i] <= 'Z')
		    {
			    s1[p] = s[i] - 'A' + 'a';
			    p++;
		    }
		    if (s[i] >= 'a' && s[i] <= 'z')
		    {
			    s2[q] = s[i] - 'a' + 'A';
			    q++;
		    }
		}
		i++;	
	}
	printf("%lld\n%.2f\n", sum1, sum2);
	for (i = 1; i <= p; i++)
	  cout << s1[i], cout <<"(" << (int)s1[i] << ")";
	cout << endl;
	for (i = 1; i <= q; i++)
	  cout << s2[i];
	return 0;
}

