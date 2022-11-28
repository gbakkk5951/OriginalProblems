#include <bits/stdc++.h>
using namespace std;
int N;
int cnt;
const int maxN = 52;
int temp[maxN];
bool rel[maxN][maxN];
bool flag[maxN];
bool del();
bool tran();
bool checkSup();
bool checkInf();
bool findFirst();
bool findLast();
bool judge();
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		if (judge())
			printf("Y\n");
		else
			printf("N\n");
	}
	return 0;
}
bool judge()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &rel[i][j]);
	for (int i = 1; i <= N; i++)
		if (rel[i][i] == 0)
			return false;
	if (!del()) //合并元素
		return false;
	for (int i = 1; i <= N; i++)
		temp[i] = i;
	cnt = N;
	if (!findFirst())
		return false;
	for (int i = 1; i <= N; i++)
		temp[i] = i;
	cnt = N;
//	if (!findLast())
//		return false;
	if (!checkSup()) 
		return false;
//	if (!checkInf()) 
//		return false;
	if (!tran())
		return false;
	return true;
}
bool del()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (rel[i][j] && rel[j][i] && i != j)
			{
				for (int k = 1; k <= N; k++)
				{
					if (rel[i][k] != rel[j][k])
						return false;
					if (rel[k][i] != rel[k][j])
						return false;
				}
				for (int k = j + 1; k <= N; k++)
					for (int l = 1; l <= N; l++)
						rel[k - 1][l] = rel[k][l];
				for (int k = j + 1; k <= N; k++)
					for (int l = 1; l <= N; l++)
						rel[l][k - 1] = rel[l][k];
				N--;
				return del();
			}
	return true;
}
bool checkSup()
{

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			cnt = 0;
			if (j == i)
				continue;
			for (int k = 1; k <= N; k++)
				if (rel[i][k] == 1 && rel[j][k] == 1)
					temp[++cnt] = k;
			if (!findFirst())
				return false;
		}
	return true;
}
bool checkInf()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			cnt = 0;
			if (j == i)
				continue;
			for (int k = 1; k <= N; k++)
				if (rel[k][i] == 1 && rel[k][j] == 1)
					temp[++cnt] = k;
			if (!findLast())
				return false;
		}
	return true;
}
bool findFirst()
{
	int tmp;
	int num = 0;
	for (int i = 1; i <= cnt; i++)
	{
		int j;
		for (j = 1; j <= cnt; j++)
			if (!rel[temp[i]][temp[j]])
				break;
		if (j - 1 == cnt)
		{
			tmp = i;
			num++;
		}
	}
	if (num != 1)
		return false;
	return true;
}
bool findLast()
{
	int tmp;
	int num = 0;
	for (int i = 1; i <= cnt; i++)
	{
		int j;
		for (j = 1; j <= cnt; j++)
			if (!rel[temp[j]][temp[i]])
				break;
		if (j - 1 == cnt)
		{
			tmp = i;
			num++;
		}
	}
	if (num != 1)
		return false;
	return true;
}
bool tran() //检验传递性
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (rel[i][j])
				for (int k = 1; k <= N; k++)
					if (rel[j][k] && !rel[i][k])
						return false;
	return true;
}


