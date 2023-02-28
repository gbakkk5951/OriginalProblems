#include <bits/stdc++.h>
#define FAST_IO
using namespace std;

typedef long long lld;

const int MaxV = 1e6 + 10;

int SelectedNum, VNum, InputType;
int PairNum;

struct FEdge
{
	int Dest, Val;
};

vector<FEdge> OutEdges[MaxV];
void AddEdge(int Src, int Dest, int Val)
{
	OutEdges[Src].push_back((FEdge) {Dest, Val});
}

void AddBidirectedEdge(int Vertex1, int Vertex2, int Val)
{
	AddEdge(Vertex1, Vertex2, Val);
	AddEdge(Vertex2, Vertex1, Val);
}

int SelectedSize[MaxV];
bool bIsSelected[MaxV];
lld TotalDist = 0;

vector<pair<int, int> > Scheme;
void GetSelectedSize(int Node, int Parent)
{
	SelectedSize[Node] = (int)bIsSelected[Node]; 
	for (auto OutEdge: OutEdges[Node])
	{
		const int &Dest = OutEdge.Dest;
		if (Dest != Parent)
		{
			GetSelectedSize(Dest, Node);
			SelectedSize[Node] += SelectedSize[Dest];
			TotalDist += OutEdge.Val * min(SelectedSize[Dest], SelectedNum - SelectedSize[Dest]);
		}
	}
//	printf("SelectedSize[%d] == %d\n", Node, SelectedSize[Node]);
}
int SchemeRoot = 0;

template <typename T1, typename T2>
void AssignMax(T1 &a, const T2 &b) 
{
	a = b > a ? b : a;
}

void GetSchemeRoot(int Node, int Parent)
{
	int MaxSelectedSize = SelectedNum - SelectedSize[Node];
	int SelectedSizeSum = MaxSelectedSize + (int)bIsSelected[Node];
//	printf("Enter (Node: %d, Parent: %d) \n{\n \tMaxSelectedSize: %d,\n\tSelectedSizeSum: %d\n}\n", Node, Parent, MaxSelectedSize, SelectedSizeSum);
	if (MaxSelectedSize > PairNum)
	{
//		printf("Case1 (Node: %d, Parent: %d)\n", Node, Parent);
		return;
	}
	for (auto OutEdge: OutEdges[Node])
	{
		const int &Dest = OutEdge.Dest;
		if (Dest != Parent)
		{
			AssignMax(MaxSelectedSize, SelectedSize[Dest]);
			if (MaxSelectedSize > PairNum)
			{
				break;
			}
			SelectedSizeSum += SelectedSize[Dest]; 
			if (SelectedSizeSum >= PairNum)
			{
				break;
			}
		}
	}
//	printf("Proc2 (Node: %d, Parent: %d)\n{\n\tMaxSelectedSize: %d\n}\n", Node, Parent, MaxSelectedSize);
	if (SelectedSizeSum >= PairNum) /* >= not > , unnecessary 'optimization' do harm */
	{
		SchemeRoot = Node;
		return;
	}
	
	for (auto OutEdge: OutEdges[Node])
	{
		const int &Dest = OutEdge.Dest;
		if (Dest != Parent)
		{
			GetSchemeRoot(Dest, Node);
			if (SchemeRoot)
			{
				return;
			}
		}
	}
}


void GetSchemeChild(int Node, int Parent, vector<int> &List)
{
	if (bIsSelected[Node])
	{
		List.push_back(Node);
	}
	for (auto OutEdge: OutEdges[Node])
	{
		const int &Dest = OutEdge.Dest;
		if (Dest != Parent)
		{
			GetSchemeChild(Dest, Node, List);
		}
	}
	
}
void GetScheme()
{
	int MaxChildSelectedSize = 0;
	vector<vector<int> > ChildSelectedNode;
	vector<vector<int> > ChildQueue;
	
	ChildSelectedNode.emplace_back();

	if (bIsSelected[SchemeRoot])
	{
		ChildSelectedNode[0].push_back(SchemeRoot);
		MaxChildSelectedSize = 1;
	}
	for (auto OutEdge: OutEdges[SchemeRoot])
	{
		const int &Dest = OutEdge.Dest;
		if (!ChildSelectedNode.rbegin()->empty())
		{
			ChildSelectedNode.emplace_back();
		}
		GetSchemeChild(Dest, SchemeRoot, *(ChildSelectedNode.rbegin()));
		AssignMax(MaxChildSelectedSize, ChildSelectedNode.rbegin()->size());
	}
	if (ChildSelectedNode.rbegin()->empty())
	{
		ChildSelectedNode.erase(ChildSelectedNode.end() - 1);
	}
	ChildQueue.resize(MaxChildSelectedSize + 1);
	for (size_t i = 0; i < ChildSelectedNode.size(); ++i)
	{
		ChildQueue[ChildSelectedNode[i].size()].push_back(i);
	}
	int QueueIndex1 = MaxChildSelectedSize;
	int QueueIndex2 = QueueIndex1;
	for (int i = 1; i <= PairNum; ++i)
	{	
		while (ChildQueue[QueueIndex1].empty())
		{
			--QueueIndex1;
		}
		while (ChildQueue[QueueIndex2].empty() || QueueIndex2 == QueueIndex1 && ChildQueue[QueueIndex2].size() == 1)
		{
			--QueueIndex2;
		}
		int ChildId1 = *ChildQueue[QueueIndex1].rbegin();
		int ChildId2 = *(ChildQueue[QueueIndex2].rbegin() + (QueueIndex2 == QueueIndex1));
		
		#ifdef FAST_IO
		printf("%d %d\n", *ChildSelectedNode[ChildId1].rbegin(), *ChildSelectedNode[ChildId2].rbegin());
		#else
		cout << *ChildSelectedNode[ChildId1].rbegin() 
			<< " " 
			<< *ChildSelectedNode[ChildId2].rbegin() 
			<< endl;
		#endif
		
		ChildSelectedNode[ChildId1].pop_back();
		ChildSelectedNode[ChildId2].pop_back();
		ChildQueue[QueueIndex1].pop_back();
		ChildQueue[QueueIndex2].pop_back();
		ChildQueue[QueueIndex1 - 1].push_back(ChildId1);
		ChildQueue[QueueIndex2 - 1].push_back(ChildId2);
	}
}
template <typename Type>
void ReadInt(Type &Result) {
	char TempChar, Sign = 1;
	while (!isdigit(TempChar = getchar())) 
	{
		Sign = TempChar == '-' ? -1 : Sign;
	}
	Result = TempChar - '0';
	while ( isdigit(TempChar = getchar())) 
	{
		Result *= 10; 
		Result += TempChar - '0';
	}
	Result *= Sign;
}

int main() 
{
	/* Redundant info */
	cin >> InputType; 
	
	cin >> VNum >> SelectedNum;
	PairNum = SelectedNum / 2;
	int V1, V2, Val;
	for (int i = 1; i <= VNum - 1; ++i)
	{
		#ifdef FAST_IO
		ReadInt(V1); 
		ReadInt(V2);
		ReadInt(Val);
		#else
		cin >> V1 >> V2 >> Val;
		#endif
		AddBidirectedEdge(V1, V2, Val);
	}
	for (int i = 1; i <= SelectedNum; ++i)
	{
		#ifdef FAST_IO
		ReadInt(V1); 
		#else
		cin >> V1;
		#endif
		bIsSelected[V1] = true;
	}
	GetSelectedSize(1, 0);
	cout << TotalDist << endl;
	GetSchemeRoot(1, 0);
//	cout << "Root is " << SchemeRoot << endl;
//	fflush(stdout);
	GetScheme();
	
	return 0;
}


