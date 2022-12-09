#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int MaxV = 5e5 + 10, MaxE = 5e5 + 10, MaxC = 1e9 + 10;
const int MaxFloydV = 505;
const int Inf = 0x3f3f3f3f;
const lld LInf = (lld)Inf << 32 | Inf;
struct FOutEdge
{
	int Dest, Cost;
};
vector<FOutEdge> OutEdges[MaxV];
lld DistMatrix[MaxFloydV][MaxFloydV];
int V, E, Q;
int S, T;
inline lld AssignMin(lld &a, lld b)
{
	return a = min(a, b);
}
void Floyd()
{
	memset(DistMatrix[0], 63, sizeof(DistMatrix));
	int u, v, c;
	for (int i = 1; i <= E; ++i)
	{
		cin >> u >> v >> c;
		DistMatrix[v][u] = AssignMin(DistMatrix[u][v], c);
	}
	for (int k = 1; k <= V; ++k)
	{
		DistMatrix[k][k] = 0;
		for (int i = 1; i <= V; ++i)
		{
			for (int j = 1; j <= V; ++j)
			{
				AssignMin(DistMatrix[i][j], DistMatrix[i][k] + DistMatrix[k][j]);
			}
		}
	}

	for (int i = 1; i <= Q; ++i)
	{
		cin >> V >> E;
		printf("%lld\n", DistMatrix[V][E] < LInf ? DistMatrix[V][E] : -1);
	}
}

typedef pair<lld, int> HeapPair;
lld DistArray[MaxV];
priority_queue<HeapPair, vector<HeapPair>, greater<HeapPair> > Heap;
inline void Push(int Dest, lld Dist)
{
	if (DistArray[Dest] > Dist)
	{
		DistArray[Dest] = Dist;
		Heap.push((HeapPair) {Dist, Dest});
	}
}
void Dijkstra()
{
	int u, v, c;
	for (int i = 1; i <= E; ++i)
	{
		cin >> u >> v >> c;
		OutEdges[u].push_back((FOutEdge) {v, c});
		OutEdges[v].push_back((FOutEdge) {u, c});
	}
	cin >> S >> T;
	memset(DistArray, 63, (V + 2) * sizeof(lld));
	Push(S, 0);
	while (!Heap.empty())
	{
		int CurrentV = Heap.top().second;
		lld CurrentDist = Heap.top().first;
		Heap.pop();
		if (CurrentDist == DistArray[CurrentV])
		{
			for (auto OutEdge : OutEdges[CurrentV])
			{
				Push(OutEdge.Dest, OutEdge.Cost + CurrentDist);
			}
		}
	}
	printf("%lld\n", DistArray[T] < LInf ? DistArray[T] : -1);
}
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> V >> E >> Q;
	if (V <= 500)
	{
		Floyd();
	}
	else
	{
		assert(Q == 1);
		Dijkstra();
	}
	return 0;
}
