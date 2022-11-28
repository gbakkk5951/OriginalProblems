#include <iostream>
#include<set>
using namespace std;
int in[100][100] = {}, total, siz;
set<int> s[100];
bool flag = true, flagg = true, flaggg = true;
int main()
{
	cin >> total;
	for (int i = 1; i <= total; i++)
	{
		cin >> siz;
		for (int j = 1; j <= siz; j++)
		{
			for (int k = 1; k <= siz; k++)
			{
				cin >> in[j][k];
			}
		}
		for (int j = 1; j <= siz; j++)
		{
			for (int k = 1; k <= siz; k++)
			{
				if (in[j][k] == 1)
				{
					s[j].insert(k);
					for (int m = 1; m <= siz; m++)
						if (in[k][m] == 1)s[j].insert(m);
				}
			}
		}
		flag = true;
		for (int i = 1; i <= siz; i++)
		{
			for (int j = i + 1; j <= siz; j++)
			{
				flagg = false;
				for (int m = 1; m <= siz; m++)
				{
					if (s[m].find(i) != s[m].end() && s[m].find(j) != s[m].end())flagg = true;
				}
				if (!flagg) {
					flag = false; break;
				}
				for (int m = 1; m <= siz; m++)
				{
					for (int k = 1; k <= siz; k++)
					{
						if (s[i].find(m) != s[i].end() && s[j].find(m) != s[j].end() && s[i].find(k) != s[i].end() && s[j].find(k) != s[j].end())
							if (s[m].find(k) == s[m].end() && s[k].find(m) == s[k].end()) {
								flag = false; break;
							}
					}
				}
			}
		}
		for (int i = 1; i <= siz; i++)if (in[i][i] != 1) {
			flag = false; break;
		}
		for (int j = 1; j <= siz; j++)
			for (int m = 1; m <= siz; m++)
				for (int t = 1; t <= siz; t++)
				{
					if (in[j][m] == 1 && in[m][t] == 1)
						if (in[j][t] != 1) {
							flag = false; break;
						}
				}
		if (flag)cout << "Y" << endl;
		else cout << "N" << endl;
		for (int i = 1; i <= siz; i++)s[i].clear();
	}
}
