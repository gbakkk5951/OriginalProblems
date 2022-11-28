#include <bits/stdc++.h>
using namespace std;

long long num[110];

bool search(int n, int sum, int last, int total)
{
	int i, j;
	if (n == 1)
	{
		for (i = 1; i <= total; i++)
		  if (num[i] == sum)
		    return true;
	    return false;
	}
	int m = ceil(sum / n);
	for (i = last; num[i] >= m; i--)
    {
    	if (sum - num[i] < num[1])
    	  continue;
    	if (search(n-1, sum-num[i], i, total))
    	  return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); 
	int n, T;
	long long m;
	int i, j;
	cin >> T;
	while(T--)
	{
		cin >> n >> m;
		bool flag;
		for (i = 1; i <= n; i++)
		{
			cin >> num[i];
			if (num[1] < 0)
			  num[i] -= num[1]; 
		}
		if (num[1] < 0)
		  m -= 6 * num[1];
		flag = search(6, m, n, n);
		if (flag)
		  cout << "Yes" << endl;
		else
		  cout << "No" << endl;
	}
	return 0;
}
