#include <bits/stdc++.h>
using namespace std;
const int MaxNum = 1e5 + 10;
const int Mod = 998246353;
int Height[MaxNum];
int InDegree[MaxNum];
int SchemeNum[MaxNum];
vector<int> Out[MaxNum];
void Update(const int InNode)
{
	// It's Important
	--InDegree[InNode];
	for (auto Dest : Out[InNode])
	{
		SchemeNum[Dest] = (SchemeNum[Dest] + SchemeNum[InNode]) % Mod;
		if (--InDegree[Dest] == 0)
		{
			Update(Dest);
		}
	}
}
void Add(int EdgeA, int EdgeB)
{
	if (Height[EdgeA] < Height[EdgeB])
	{	
		swap(EdgeA, EdgeB);
	}
	else if (Height[EdgeA] == Height[EdgeB])
	{
		return;
	}
	++InDegree[EdgeB];
	Out[EdgeA].push_back(EdgeB);
}
int main() 
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		cin >> Height[i];
		SchemeNum[i] = 1;
	}
	int EdgeA, EdgeB;
	for (int i = 1; i <= m; ++i)
	{
		cin >> EdgeA >> EdgeB;
		Add(EdgeA, EdgeB);
	}
	for (int i = 1; i <= n; ++i)
	{
		if (InDegree[i] == 0)
		{
			Update(i);
		}
	}
	int Answer = 0;
	for (int i = 1; i <= n; ++i)
	{
		Answer = (Answer + SchemeNum[i]) % Mod;
	}
	printf("%d", Answer);
	return 0;
}
