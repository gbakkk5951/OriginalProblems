#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int CaseNum = 0;
	assert(1 == scanf("%d", &CaseNum));
	assert(1 <= CaseNum && CaseNum <= 10);
	for (int T = 1; T <= CaseNum; ++T)
	{
		int V = 0, E = 0;
		assert(2 == scanf("%d%d", &V, &E));
		assert(1 <= V && V <= (int)1e5 && 1 <= E && E <= (int)2e5);
		vector<int> InDeg;
		vector<vector<int>> OutEdges;
		InDeg.resize(V + 1);
		OutEdges.resize(V + 1);
		int Src = 0;
		int OutDst = 0;
		for (int i = 1; i <= E; ++i)
		{
			assert(2 == scanf("%d%d", &Src, &OutDst));
			assert(1 <= min(Src, OutDst) && max(Src, OutDst) <= V);
			OutEdges[Src].push_back(OutDst);
			++InDeg[OutDst];
		}
		int MaxLen = 0;
		for (int i = 1; i <= V; ++i)
		{
			if (0 == InDeg[i]) 
			{
				queue<int> Q[2];
				Q[1].push(i);
				for (int Len = 1; !Q[Len & 1].empty(); ++Len)
				{
					MaxLen = Len;
					while (!Q[Len & 1].empty())
					{
						int Now = Q[Len & 1].front();
						Q[Len & 1].pop();
						for (auto Dst : OutEdges[Now])
						{
							assert(--InDeg[Dst] >= 0);
							if (InDeg[Dst] == 0)
							{
								Q[(Len & 1) ^ 1].push(Dst);
							}
						}
					}
				}
				break;
			}
		}
//		printf("MaxLen = %d\n", MaxLen);
		printf("%s\n", MaxLen == V ? "YES" : "NO");
	}
	
	int TestInt;
	assert(EOF == scanf("%d", &TestInt));
	return 0;
}
