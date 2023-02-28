#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
struct DijkInfo
{
	lld Value;
	int From;
	bool operator == (const DijkInfo & b) const 
	{
		return Value == b.Value && From == b.From;
	}
	bool operator < (const DijkInfo & b) const 
	{
		return Value < b.Value;
	}
	bool operator > (const DijkInfo & b) const 
	{
		return Value > b.Value;
	}
};

const int Inf = 0x3f3f3f3f;
const lld LInf = ((lld)Inf << 32) | Inf;
struct OEdge
{
	int Dst;
	lld Value;	
};

const int MaxV = 1e5 + 10, MaxE = 5e5;
struct SingleCaseSolver 
{
	DijkInfo Dis[MaxV][2];
	vector<OEdge> Out[MaxV];
	
	int V, E, SNum;
	int Scene[MaxV];
	lld Answer;
	void Dijkstra()
	{
		priority_queue<pair<DijkInfo, int>, vector<pair<DijkInfo, int> >, greater<pair<DijkInfo, int> > > heap;
		for (int i = 1; i <= SNum; ++i)
		{
			Dis[Scene[i]][0] = {0ll, Scene[i]};
			heap.push(make_pair(Dis[Scene[i]][0], Scene[i]));
		}
		while (!heap.empty())
		{
			auto HeapNode = heap.top();
			heap.pop();
			int now = HeapNode.second;
			auto Info = HeapNode.first;
			if (Info == Dis[now][0] || Info == Dis[now][1])
			{
				for (auto Edge : Out[now])
				{
					const int &EValue = Edge.Value;
					const int &Dst = Edge.Dst;
					if (Dis[Dst][0].From == Info.From)
					{
						if (Dis[Dst][0].Value > Info.Value + EValue)
						{
							Dis[Dst][0].Value = Info.Value + EValue;
							heap.push(make_pair(Dis[Dst][0], Dst));
						}
					}
					else if (Dis[Dst][0].Value > Info.Value + EValue)
					{
						swap(Dis[Dst][0], Dis[Dst][1]);
						Dis[Dst][0].From = Info.From;
						Dis[Dst][0].Value = Info.Value + EValue;
						heap.push(make_pair(Dis[Dst][0], Dst));
					}
					else if (Dis[Dst][1].Value > Info.Value + EValue)
					{
						Dis[Dst][1].From = Info.From;
						Dis[Dst][1].Value = Info.Value + EValue;
						heap.push(make_pair(Dis[Dst][1], Dst));
					}
				}
			}
		}
	}
	void Solve()
	{
		Answer = LInf;
		assert(3 == scanf("%d%d%d", &V, &E, &SNum));
		for (int i = 0; i <= V; ++i)
		{
			Out[i].clear();
			Dis[i][0] = Dis[i][1] = (DijkInfo) {LInf, -1};
		}
		int a, b, c;
		
		for (int i = 1; i <= E; ++i)
		{
			assert(3 == scanf("%d%d%d", &a, &b, &c));
			Out[a].push_back((OEdge) {b, c});
		}
		for (int i = 1; i <= SNum; ++i)
		{
			assert(1 == scanf("%d", &Scene[i]));
		}
		Dijkstra();
		lld Answer = LInf;
		for (int i = 1; i <= SNum; ++i)
		{
			Answer = min(Answer, Dis[Scene[i]][1].Value);
		}
		assert(Answer < LInf);
		printf("%lld\n", Answer);
	}
}solver;
int main()
{
	int CaseNum = 0;
	assert(1 == scanf("%d", &CaseNum));
	for (int i = 1; i <= CaseNum; ++i)
	{
		solver.Solve();	
	}
	return 0;
}
