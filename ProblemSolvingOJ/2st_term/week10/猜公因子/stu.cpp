/*
要找到的x
(1)x至少整除m个集合中的元素。
(2)x <= k
(3)x是满足1、2的所有元素的上确界 


注意，我们不需要对所有元素进行质因数分解，只需要判定某个元素是否
被整除了即可！
显然，我们可以在 


考察一些特例：
(1)随机抽取十个不同的数，然后做因子分解。
对所有的因子，检测是否合法即可 
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int N = 1e3 + 1, MAXN = 1e6 + 2;
int a[N], p[MAXN], cnt, n, ans, m, k;//10个数， 3^5=243, 2^5 = 32, 5^5 = 3125, 7^5 ....
// 
bool book[N];
void find_divisor(int x)
{
	p[++cnt] = x;
	for (int i = 2 ; i * i <= x ; i++)
		{
			if(x % i == 0)
				{	
					p[++cnt] = i;
					if(i != x / i)
						p[++cnt] = x / i;
				}
		}
}
bool check(int x)
{
	if(x > k)
		return false;
	int tot = 0;
	for (int i = 1 ; i <= n ; i++)
		{
			if(a[i] >= x && a[i] % x == 0)
			{
				tot++;
				if(tot >= m)
	                return true;
			}
		}
	return false;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1 ; i <= n ; i++)
		scanf("%d", &a[i]);
	random_shuffle(a + 1, a + 1 + n);
	
	p[++cnt] = 1;
	for (int i = 1 ; i <= min(300, n) ; i++)
	{
		find_divisor(a[i]);
	}
	sort(p + 1, p + 1 + cnt);

	int len = unique(p + 1, p + 1 + cnt) - p - 1;
	for (int i = len ; i >= 1 ; i--)
		{
			if(check(p[i]))
				{
					ans = p[i];
					break;
				}	
		}
		printf("%d", ans);
	return 0;
}	
