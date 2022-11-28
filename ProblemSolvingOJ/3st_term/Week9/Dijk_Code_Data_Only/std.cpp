/*
*	
* 0 <= EdgeNum <= 5e5;  
* 0 <= VertexNum <= 2.5e5;
* 0 <= Weight <= 1e3
* 30% : n, m <= 1000
* Data & std by zhy
*/
#include <bits/stdc++.h>
using namespace std;

namespace ProblemSolving2021Term3Week9Dijkstra 
{

	typedef pair<int, int> P;
	const int MaxVertexNum = 2.5e5 + 10;
	int DistBackward[MaxVertexNum], DistForward[MaxVertexNum];
	vector<P> ForwardEdge[MaxVertexNum];
	vector<P> BackwardEdge[MaxVertexNum];
	const int Inf = 0x3f3f3f3f;
	priority_queue<P, vector<P>, greater<P> > Heap;
	void Dijkstra(const int InVertexNum, const int InSource, vector<P> InEdges[], int OutDist[])
	{
		memset(OutDist, 0x3f, (InVertexNum + 1) * sizeof(int));
		Heap.push((P) {0, InSource});
		OutDist[InSource] = 0; 
		while (!Heap.empty())
		{
			int CurrentVertex = Heap.top().second;
			int CurrentDist = Heap.top().first;
			Heap.pop();
			if (CurrentDist != OutDist[CurrentVertex])
			{
				continue;
			}
			for (auto Edge : InEdges[CurrentVertex])
			{
				int NewDist = CurrentDist + Edge.first;
				if (OutDist[Edge.second] > NewDist)
				{
					OutDist[Edge.second] = NewDist;
					Heap.push((P) {NewDist, Edge.second});
				}
			}
		}
	}
	
	void Solve()
	{
		int VertexNum, EdgeNum;
		cin >> VertexNum >> EdgeNum;
		for (int i = 1; i <= EdgeNum; ++i)
		{
			int Src, Dst, Val;
			cin >> Src >> Dst >> Val;
			ForwardEdge[Src].push_back((P) {Val, Dst});
			BackwardEdge[Dst].push_back((P) {Val, Src});
		}
		Dijkstra(VertexNum, 1, ForwardEdge, DistForward);
		Dijkstra(VertexNum, 1, BackwardEdge, DistBackward);
		for (int i = 1; i <= VertexNum; ++i)
		{
			cout << (max(DistForward[i], DistBackward[i]) < Inf ? DistForward[i] + DistBackward[i] : -1) << endl;
		}
	}

}
int main() 
{
	ProblemSolving2021Term3Week9Dijkstra::Solve();
	return 0;
}
