#include <bits/stdc++.h>
using namespace std;
int A[50 + 5][50 + 5];
bool check_re_tran(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (!A[i][i])
			return false;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				if (A[i][j] && A[j][k] && !A[i][k])
                    return false;
			}
		}
	}
	return true;
}
bool check(int x, int y, int n)
{
	if (A[x][y] == 1 && A[y][x] == 1)
	{
		for (int i = 1; i <= n; i++)
		{
			if ((A[x][i] != A[y][i]) || (A[i][x] != A[i][y])){
				return false;
			}
		}
		return true;
	}
	else if (A[x][y] == 1 || A[y][x] == 1)
		return true;
	else
	{
		int sup = 0, inf = 0, SUP = 0, INF = 0, temp[55], tem[55];
		memset(temp, 0, sizeof(temp));
		memset(tem, 0, sizeof(tem));
		for (int i = 1; i < x; i++)
		{
			if (A[x][i] == A[y][i] && A[x][i] == 1)
			{
				sup++;
				temp[sup] = i;
			}
			if (A[i][x] == A[i][y] && A[i][x] == 1)
			{
				inf++;
				tem[inf] = i;
			}
		}
		for (int i = x + 1; i < y; i++)
		{
			if (A[x][i] == A[y][i] && A[x][i] == 1)
			{
				sup++;
				temp[sup] = i;
			}
			if (A[i][x] == A[i][y] && A[i][x] == 1)
			{
				inf++;
				tem[inf] = i;
			}
		}
		for (int i = y + 1; i <= n; i++)
		{
			if (A[x][i] == A[y][i] && A[x][i] == 1)
			{
				sup++;
				temp[sup] = i;
			}
			if (A[i][x] == A[i][y] && A[i][x] == 1)
			{
				inf++;
				tem[inf] = i;
			}
		}
		for (int i = 1; i <= sup; i++)
		{ 
			int num = 0;
			for (int j = 1; j <= sup; j++)
			{
				if (A[temp[j]][temp[i]] == 1)
				{
					num++;
				}
			}
			if (num == 1)
				INF++;
		}
		for (int i = 1; i <= inf; i++)
		{ //����Ͻ�
			int NUM = 0;
			for (int j = 1; j <= inf; j++)
			{
				if (A[tem[i]][tem[j]] == 1)
				{
					NUM++;
				}
			}
			if (NUM == 1)
				SUP++;
		}
		if (INF == 1 && SUP == 1)
			return true;
		return false;
	}
}
int main()
{
	int T, n, flag = 0;
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cin >> A[i][j];
			}
		}
		if (!check_re_tran(n))
		{
			cout << "N" << endl;
			memset(A, 0, sizeof(A));
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = i; j <= n; j++)
			{
				if (!check(i, j, n))
				{
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}
		}
		if (flag == 1)
		{
			cout << "N" << endl;
		}
		else
		{
			cout << "Y" << endl;
		}
		flag = 0;
		memset(A, 0, sizeof(A));
	}
}
