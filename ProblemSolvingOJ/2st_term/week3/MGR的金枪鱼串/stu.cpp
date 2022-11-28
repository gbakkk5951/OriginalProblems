#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 2 * 1e6 + 10;

int f[15], p[MAXN];
int n, k;

void cal()
{
	f[1] = 1;
	for (int i = 2; i <= 15; i++)
		f[i] = i * f[i - 1];
}

inline int read()
{
	char ch = getchar();
	int x = 0, f = 1;
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
 
inline void write(int x)
{
	if (x < 0)
	  x = ~x + 1, putchar('-');
	if (x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
 
void output()
{
	for (int i = 1; i <= n; i++)
		write(p[i]), putchar(' ');
	putchar('\n');
}

int main()
{
	cal();
	int t;
	int i, j;
	t = read();
	while (t--)
	{
		n = read();
		k = read();
		if (n <= 12)
		  k %= f[n];
		for (i = 1; i <= n; i++)
		{
			p[i] = read();
		}
		p[0] = p[n+1] = 0;
		while (k)
		{
			bool repeat = false;
			for (i = n; i >= 2; i--)
			{
				if (p[i - 1] < p[i])
				{
					for (j = i; j <= n; j++)
					  if (p[j] < p[i-1])
					    break;
					//cout << "j = " << j << ", i = " << i << endl;
					if ((j-i) * f[n-i+1] <= k)
					{
					    int temp = p[i-1];
					    for (int l = i; l < j; l++)
					      p[l-1] = p[l];
					    p[j-1] = temp;
					    k -= (j-i) * f[n-i+1];
					    //output();
					    //printf("%d(1)\n", k);
					    break;
					}
					else
					{
						swap(p[j - 1], p[i - 1]);
						sort(p + i, p + n + 1);
						k--;
						//output();
						//cout << k << endl;
						if (k == 0)
							break;
						int last = i;
						//cout << last << ' ' << p[last] << endl;
						if (n - last + 1 > 12 ||(n - last + 1 <= 12 && f[n-last+1] > k))
						  repeat = true;
						while (k && repeat)
						{
							for (j = min(n - last + 1, 12); j >= 1; j--)
							  if (f[j] <= k)
								break;
						    //cout << "j = " << j << endl << "k = " << k << endl;
						    int times = floor(k / f[j]);
						    int ex = n - j;
						    while (times && ex <= n)
						    {
						    	ex++;
						    	if (p[ex] < p[n-j])
						    	  continue;
						    	times--;
							}
						    int temp = p[ex];
						    for (int l = ex - 1; l >= n - j; l--)
							    p[l + 1] = p[l];
						    p[n - j] = temp;
						    k %= f[j];
						    last = n - j;
						    //output();
						    //cout << k << "(2)" << endl;
						}
						break;
					}
				}
				if (k == 0)
					break;
			}
			if (i == 1)
			{
				k--;
				sort(p+1, p+n+1);
				//output();
				//cout << k << "(end)" << endl;
			}
		}
		output();
	}
	return 0;
}
