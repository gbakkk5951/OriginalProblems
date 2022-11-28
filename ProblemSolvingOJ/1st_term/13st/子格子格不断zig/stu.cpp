#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 100 + 10;
int res[maxn][maxn];
int pow2[maxn];
int n, m, ans;
bool check(int state)
{
	for (int i = 1; i <= n; i++)
	{
		if (pow2[i - 1] & state)
		{
			for (int j = 1; j <= n; j++)
			{
				if (pow2[j - 1] & state)
				{
					if (!(pow2[res[i][j] - 1] & state) || !(pow2[res[j][i] - 1] & state))
						return false;
				}
			}
		}
	}
	return true;
}
int main()
{
	scanf("%d", &n);
	m = 1 << n;
	pow2[0] = 1;
	for (int i = 1; i <= n; i++)
		pow2[i] = pow2[i - 1] << 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> res[i][j];
	for (int i = 1; i < m; i++)
	{
		if (check(i))
			ans++;
	}
	printf("%d", ans);
	return 0;
}

