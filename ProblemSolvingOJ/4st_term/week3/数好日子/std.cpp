#include <bits/stdc++.h>
using namespace std;
const int MaxV = 3e7 + 10;
int Step = 50;
int Sum[MaxV / 50 + 10];
bitset<MaxV> Vis;
void Sieve(int Max)
{
	Vis[0] = Vis[1] = 1;
	int BlockIndex = 0;
	for (int i = 2; i <= Max; ++i)
	{
		if (Vis[i] == 0)
		{	
			while (i >= (BlockIndex + 1) * Step)
			{
				++BlockIndex;
				Sum[BlockIndex] = Sum[BlockIndex - 1];
			}
			++Sum[BlockIndex];
			for (int j = i << 1; j <= Max; j += i)
			{
				Vis[j] = 1;
			}
		}
	}
}
int main() 
{
	Sieve(MaxV - 5);
	int n;
	cin >> n;

	while (n--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = max(l, 2);
		if (l > r)
		{
			puts("0");
			continue;
		}
		int LBlock, RBlock;
		LBlock = (l + Step - 1) / Step;
		RBlock = r / Step - 1;
		int Answer = 0;
		if (LBlock <= RBlock)
		{
			Answer = Sum[RBlock] - Sum[LBlock - 1];
			int LStop = LBlock * Step;
			for (; l < LStop; ++l)
			{
				Answer += !Vis[l];
			}
			int RStop = (RBlock + 1) * Step - 1;
			for (; r > RStop; --r)
			{
				Answer += !Vis[r];
			}
		}
		else
		{
			for (; l <= r; ++l)
			{
				Answer += !Vis[l];
			}
		}
		printf("%d\n", Answer);
	}
	return 0;
}
