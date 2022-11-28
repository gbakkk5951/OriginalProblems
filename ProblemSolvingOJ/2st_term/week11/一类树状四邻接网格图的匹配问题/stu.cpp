#include<iostream>
#include<queue>
using namespace std;
int n, m, op;
int A[500][500], B[1000][1000];
string temp;
struct point
{
	int i, j;
};
queue<point> star;
int ans, mini, maxi, minj, maxj, nowi, nowj;
void changeC()
{
	int te = 0;
	int deltai = nowi - 500, deltaj = nowj - 500;
	for (int i = 1; i <= ans; i++)
	{
		point tem = star.front();
		star.pop();
		if (tem.i + deltai > 0 && tem.i + deltai <= n && tem.j + deltaj > 0 && tem.j + deltaj <= n)
		{
			if (A[tem.i + deltai][tem.j + deltaj])
			{
				te++;
				star.push(tem);
			}
		}
	}
	printf("%d\n", te);
	ans = te;
	return;
}
void changeB(int op)
{
	if (maxi - mini + 1 > n || maxj - minj + 1 > n)
		printf("%d\n", 0);
	else
	{
		if (op == 0)
		{
			nowi--;
			mini = min(mini, nowi);
		}
		if (op == 1)
		{
			nowi++;
			maxi = max(maxi, nowi);
		}
		if (op == 2)
		{
			nowj--;
			minj = min(minj, nowj);
		}
		if (op == 3)
		{
			nowj++;
            maxj = max(maxj, nowj);
		}
		
		if (maxj - minj + 1 > n || maxi - mini + 1 > n)
		{
			printf("%d\n", 0);
			return;
		}
		if (B[nowi][nowj])
		{
			printf("%d\n", ans);
			return;
		}
		else
		{
			B[nowi][nowj] = 1;
			changeC();
			return;
		}
	}
}
// 快读 
int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') {
			f = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> temp;
		for (int j = 1; j <= n; j++)
		{
			A[i][j] = temp[j - 1] - '0';
			if (A[i][j])
			{
				point t;
				t.i = i;
				t.j = j;
				ans++;
				star.push(t);
			}
		}
	}//初始化
	printf("%d\n", ans);
	B[500][500] = 1;
	mini = 500;
	maxi = 500;
	minj = 500;
	maxj = 500;
	nowi = 500;
	nowj = 500;
	for (int i = 1; i <= m; i++)
	{
		op = read();
		changeB(op);
	}
	return 0;
}
