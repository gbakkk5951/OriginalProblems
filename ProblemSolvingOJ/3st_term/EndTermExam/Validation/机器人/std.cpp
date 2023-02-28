#include <bits/stdc++.h>
using namespace std;

typedef long long lld;
vector<vector<int> > NumOfTile;
vector<vector<bool> > IsLeftBoundConnected;
vector<vector<bool> > IsTopBoundConnected;
vector<vector<bool> > Visited;
/*
	(x, y) : x -> Row Index, y -> Column Index
*/
template <typename T>
void Init2DVector(vector<vector<T> > &ObjVector, int FirstDimSize, int SecondDimSize)
{
	ObjVector.resize(FirstDimSize);
	for (int i = 0; i < FirstDimSize; ++i)
	{
		ObjVector[i].resize(SecondDimSize);
	}
}
inline lld Square(lld x)
{
	return x * x;
}
int CollectRobot(int x, int y)
{
	if (Visited[x][y])
	{
		return 0;
	}
	Visited[x][y] = true;
	int Num = NumOfTile[x][y];
	NumOfTile[x][y] = 0;
	if (IsLeftBoundConnected[x][y])
	{
		Num += CollectRobot(x, y - 1);
	}
	if (IsLeftBoundConnected[x][y + 1])
	{
		Num += CollectRobot(x, y + 1);
	}
	if (IsTopBoundConnected[x][y])
	{
		Num += CollectRobot(x - 1, y);
	}
	if (IsTopBoundConnected[x + 1][y])
	{
		Num += CollectRobot(x + 1, y);
	}
	return Num;
}
int main() 
{
	int TestInt = 0;
	int RobotNum = 0, n = 0, m = 0;
	scanf("%d%d%d", &n, &m, &RobotNum);
	assert(1 <= n && n <= 600 && 1 <= m && m <= 600 && 1 <= RobotNum && RobotNum <= (int)1e5);
	/*
	My Coordinate (x', y') ranges from (0, 0) to (n + 1, m + 1) including
	*/
	Init2DVector(NumOfTile, n + 2, m + 2);
	Init2DVector(IsLeftBoundConnected, n + 2, m + 2);
	Init2DVector(IsTopBoundConnected, n + 2, m + 2);
	Init2DVector(Visited, n + 2, m + 2);
	int ConnectStatus = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 2 ; j <= m; ++j)
		{
			assert(1 == scanf("%d", &ConnectStatus));
			IsLeftBoundConnected[i][j] = (bool)ConnectStatus;
		}
	}
	
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 1 ; j <= m; ++j)
		{
			assert(1 == scanf("%d", &ConnectStatus));
			IsTopBoundConnected[i][j] = (bool)ConnectStatus;
		}
	}
	
	int x, y;
	for (int i = 1; i <= RobotNum; ++i)
	{
		assert(scanf("%d%d", &x, &y) == 2);
		++NumOfTile[x][y];
	}
	assert(scanf("%d", &TestInt) == EOF);
	lld Answer = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (0 < NumOfTile[i][j])
			{
				Answer += Square(CollectRobot(i, j));
			}
		}
	}
	printf("%lld", Answer);
	return 0;
}
