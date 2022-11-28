#include <bits/stdc++.h>

#define MAKING_DATA

using namespace std;
typedef long long lld;
const int MaxVertexNum = 1e5 + 10;
const int MaxEdgeNum = 2e5 + 10;

int TotalCost;
int UFSetParent[MaxVertexNum];
int GetUFSetParent(int Id)
{
	return UFSetParent[Id] ? (UFSetParent[Id] = GetUFSetParent(UFSetParent[Id])) : Id;
}
struct FOutEdge
{
	int Dest;
	int Id;
	int Cost;
};
struct FEdge
{
	int u, v, Cost, Id;
	bool operator < (const FEdge &Obj) const 
	{
		return Cost < Obj.Cost;
	}
}Edges[MaxEdgeNum];
vector<FOutEdge> OutEdges[MaxVertexNum];

int VertexNum, EdgeNum;

void Add(int NowEdgeId)
{
	OutEdges[Edges[NowEdgeId].u].push_back((FOutEdge) {Edges[NowEdgeId].v, Edges[NowEdgeId].Id, Edges[NowEdgeId].Cost});
	OutEdges[Edges[NowEdgeId].v].push_back((FOutEdge) {Edges[NowEdgeId].u, Edges[NowEdgeId].Id, Edges[NowEdgeId].Cost});
}
void Kruskal()
{
	sort(Edges + 1, Edges + EdgeNum + 1);
	for (int i = 1; i <= EdgeNum; ++i)
	{
		int UParent = GetUFSetParent(Edges[i].u);
		int VParent = GetUFSetParent(Edges[i].v);
		if (UParent != VParent)
		{
			Add(i);
			UFSetParent[UParent] = VParent;
		}
	}
}
lld GetWalk(int VertexId, int Parent)
{
	lld ChildDistSum = 0;
	for (auto OutEdge : OutEdges[VertexId])
	{
		if (OutEdge.Dest != Parent)
		{
			ChildDistSum += OutEdge.Cost * 2;
			#ifndef MAKING_DATA
				printf("%d\n", OutEdge.Id);
			#endif
			ChildDistSum += GetWalk(OutEdge.Dest, VertexId);
			#ifndef MAKING_DATA
				printf("%d\n", OutEdge.Id);
			#endif			
		}
	}
	return ChildDistSum;
}
int main() 
{
	scanf("%d%d", &VertexNum, &EdgeNum);
	for (int i = 1; i <= EdgeNum; ++i)
	{
		scanf("%d%d%d", &Edges[i].u, &Edges[i].v, &Edges[i].Cost);	
		Edges[i].Id = i;
	}
	Kruskal();
	
	#ifndef MAKING_DATA
	    printf("%d\n", 2 * (VertexNum - 1));
	#endif
	lld TotalDist = GetWalk(1, -1);
	#ifdef MAKING_DATA
		printf("%lld\n", TotalDist);
	#endif
	return 0;
}
