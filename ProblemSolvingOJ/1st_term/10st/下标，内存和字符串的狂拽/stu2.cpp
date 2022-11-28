#include<iostream>


using namespace std;

int a[1005][1005] = {};
int sized[1005] = {1000};
int tmp = 0;
int n, m, total, op, x, y, v, c, countd, x2, y2, x3, y3, x4, y4, x5, y5, tempx, tempy;
bool flag = true, flagg = true, flaggg = true;
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		sized[i] = m;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < sized[i]; j++)
		{
			cin >> m;
			a[i][j] = m;
		}
	cin >> total;
	for (int i = 1; i <= total; i++)
	{
		cin >> op;
		flag = true;
		flagg = true;
		flaggg = true;
		countd = 0;
		if (op == 0)
		{
			cin >> x >> y >> v >> c;
			if (c == 0)cout << "true" << endl;
			else
			{
				while (y > sized[x] - 1)y -= (sized[x]), x++, flag = false;
				cout << "x = " << x << endl;
				while (y < 0)y += sized[x - 1], x--, flag = false;
				if (x >= n || x < 0)cout << "overflow" << endl, flagg = false;
				if (flagg)
				{
					tempy = y;
					tempx = x;
					for (int i = 0; i < c; i++)
					{
						if (y + i > sized[x] - 1)y -= (sized[x]), x++, flag = false;
						if (x >= n)
						{
							cout << "overflow" << endl;
							flagg = false;
							break;
						}
					}
					if (flagg)
					{
						for (int i = 0; i < c; i++)
						{
							if (tempy + i > sized[tempx] - 1)tempy -= (sized[tempx]), tempx++, flag = false;
							a[tempx][tempy + i] = v;
						}
					}
					if (!flag && flagg)cout << "w";
					if (flagg)cout << "true" << endl;
				}
			}
		}
		else if (op == 2)
		{
			cin >> x >> y;
			while (y > sized[x] - 1)y -= (sized[x]), x++, flag = false;
			while (y < 0)y += sized[x - 1], x--, flag = false;
			if (x >= n || x < 0)cout << "overflow" << endl, flagg = false;
			else
				while (a[x][y] == 1)
				{
					y++;
					while (y > sized[x] - 1)y -= (sized[x]), x++, flag = false;
					if (x >= n)
					{
						cout << "overflow" << endl;
						flagg = false;
						break;
					}
					countd++;
				}
			if (!flag && flagg)cout << "w";
			if (flagg)cout << countd << endl;
		}
		else if (op == 1)
		{
			cin >> x2 >> y2 >> x3 >> y3;
			while (y2 > sized[x2] - 1)y2 -= (sized[x2]), x2++, flag = false;
			while (y3 > sized[x3] - 1)y3 -= (sized[x3]), x3++, flag = false;
			while (y2 < 0)y2 += (sized[x2 - 1]), x2--, flag = false;
			while (y3 < 0)y3 += (sized[x3 - 1]), x3--, flag = false;
			x4 = x2;
			y4 = y2;
			x5 = x3;
			y5 = y3;
			if (x2 >= n || x3 >= n || x2 < 0 || x3 < 0)
			{
				cout << "overflow" << endl;
				flagg = false;
			}
			if (flagg)
			{
				while (a[x2][y2] != 0)
				{
					y2++;
					y3++;
					while (y3 > sized[x3] - 1)y3 -= (sized[x3]), x3++, flag = false;
					while (y2 > sized[x2] - 1)y2 -= (sized[x2]), x2++, flag = false;
					countd++;
				}
				if (x2 >= n || x3 >= n)
				{
					cout << "overflow" << endl;
					flagg = false;
				}
				countd++;
				if (flagg)
				{
					if (countd != 1)
					{
						x2 = x4;
						y2 = y4;
						x3 = x5;
						y3 = y5;
						for (int i = 0; i < countd - 1; i++)
						{
							y2++;
							y3++;
							if (y2 >= sized[x2])
							{
								y2 -= sized[x2];
								x2++;
							}
							if (y3 >= sized[x3])
							{
								y3 -= sized[x3];
								x3++;
							}
						}
					}
					if (x3 == x5)
					{
						if (x2 == x3 && y5 <= y2 && y2 <= y3)flaggg = false;
					}
					else if ((x5 < x2 && x2 < x3) || (x2 == x5 && y2 >= y5) || (x2 == x3 && y2 <= y3))flaggg = false;
					if (x2 == x4)
					{
						if (x3 == x2 && y4 <= y3 && y3 <= y2)flaggg = false;
					}
					else if ((x4 < x3 && x3 < x2) || (x3 == x4 && y3 >= y4) || (x3 == x2 && y3 <= y2))flaggg = false;
					if (flaggg)
					{
						x2 = x4;
						y2 = y4;
						x3 = x5;
						y3 = y5;
						for (int i = 1; i <= countd; i++)
						{
							while (y3 > sized[x3] - 1)y3 -= (sized[x3]), x3++, flag = false;
							if (i < countd)a[x3][y3] = 1;
							else a[x3][y3] = 0;
							y3++;
						}
					}

					if (!flaggg)cout << "overwrite" << endl;
					if (!flag && flaggg)cout << "wtrue" << endl;
					if (flag && flaggg)cout << "true" << endl;

				}
			}
		}
	}
	return 0;
}
