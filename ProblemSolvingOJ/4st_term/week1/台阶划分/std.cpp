#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int n;
int Op[maxn][maxn];
int Unit;
bool bIsSemiGroup = true;
bool bGetInverse = true;
#define LoopHead \
for (int i = 1; i <= n; ++i)\
{\
	for (int j = 1; j <= n; ++j)\
	{
#define LoopTail \
	}\
}
int main() 
{
	scanf("%d", &n);
	LoopHead
		scanf("%d", &Op[i][j]);
	LoopTail
	
	
	LoopHead
		for (int k = 1; k <= n && bIsSemiGroup; ++k)
		{
			if (Op[Op[i][j]][k] != Op[i][Op[j][k]])
			{
				bIsSemiGroup = false;
			}
		}
	LoopTail
	if (!bIsSemiGroup)
	{
		printf("1");
		return 0;
	}
	for (int i = 1; i <= n; ++i)
	{
		bool bIsUnit = true;
		for (int j = 1; j <= n; ++j)
		{
			if (Op[i][j] != j || Op[j][i] != j)
			{
//				printf("Op %d %d = %d\n", i, j, Op[i][j]);
				bIsUnit = false;
				break;
			}
		}
		if (bIsUnit)
		{
			Unit = i;
//			printf("Unit = %d\n", Unit);
			break;
		}
	}
	if (Unit == 0 && n != 0)
	{
		printf("2");
		return 0;
	}
	
	for (int i = 1; i <= n && bGetInverse; ++i)
	{
		bool bLeftInverse = false, bRightInverse = false;
		for (int j = 1; j <= n; ++j)
		{
			bLeftInverse |= Op[j][i] == Unit;
			bRightInverse |= Op[i][j] == Unit;
//			printf("Op %d %d = %d\n", i, j, Op[i][j]);
		}
		bGetInverse &= bLeftInverse && bRightInverse;
	}
	printf(bGetInverse ? "5" : "4");
	return 0;
}
