#include <bits/stdc++.h>
#define FAST_IO
using namespace std;

typedef long long lld;

const int MaxV = 1e6 + 10;

int SelectedNum, VNum, InputType;
int PairNum;

struct FEdge
{
	int Dest, Val, Nxt;
};

FEdge OutEdge[MaxV * 2];
int OEHead[MaxV];
int OEIndex = 0;
void AddEdge(int Src, int Dest, int Val)
{
	++OEIndex;
	OutEdge[OEIndex] = (FEdge) {Dest, Val, OEHead[Src]};
	OEHead[Src] = OEIndex;
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
	for (int e = OEHead[Node]; e; e = OutEdge[e].Nxt)
	{
		const int Dest = OutEdge[e].Dest;
		if (Dest != Parent)
		{
			GetSelectedSize(Dest, Node);
			SelectedSize[Node] += SelectedSize[Dest];
			TotalDist += OutEdge[e].Val * min(SelectedSize[Dest], SelectedNum - SelectedSize[Dest]);
		}
	}
//	printf("SelectedSize[%d] == %d\n", Node, SelectedSize[Node]);
}
int SchemeRoot = 0;

template <typename T1, typename T2>
inline void AssignMax(T1 &a, const T2 &b) 
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
	for (int e = OEHead[Node]; e; e = OutEdge[e].Nxt)
	{
		const int Dest = OutEdge[e].Dest;
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
	
	for (int e = OEHead[Node]; e; e = OutEdge[e].Nxt)
	{
		const int Dest = OutEdge[e].Dest;
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


struct FListItem
{
	int Val, Nxt;
};
template <size_t ItemNum, size_t HeadNum>
struct List
{
	FListItem Items[ItemNum + 1];
	int Head[HeadNum + 1];
	int Size[HeadNum + 1];
	int Index = 0;
	inline void Transplant(const int HeadId, const int Id)
	{
		++Size[HeadId];
		Items[Id].Nxt = Head[HeadId];
		Head[HeadId] = Id;
	}
	inline void Insert(const int HeadId, const int Val)
	{
		++Size[HeadId];
		Items[++Index] = (FListItem) {Val, Head[HeadId]};
		Head[HeadId] = Index;
	}
	inline int PopHead(const int HeadId)
	{
		--Size[HeadId];
		int Id = Head[HeadId];
		Head[HeadId] = Items[Head[HeadId]].Nxt;
		return Id;
	}
	inline int GetHeadVal(const int HeadId)
	{
		return Items[Head[HeadId]].Val;
	}
	/* Call if used as local non-static variable*/
	void Init()
	{
	
	}
};

List<MaxV, MaxV> ChildSelectedNode;


void GetSchemeChild(int Node, int Parent, int ChildId)
{
	if (bIsSelected[Node])
	{
		ChildSelectedNode.Insert(ChildId, Node);
	}
	for (int e = OEHead[Node]; e; e = OutEdge[e].Nxt)
	{
		const int Dest = OutEdge[e].Dest;
		if (Dest != Parent)
		{
			GetSchemeChild(Dest, Node, ChildId);
		}
	}
	
}

void GetScheme()
{
	int MaxChildSelectedSize = 0;

	typedef pair<int, int> p;
	priority_queue<pair<int, int> > ChildQueue;
	
	int ChildId = -1;
	if (bIsSelected[SchemeRoot])
	{
		ChildSelectedNode.Insert(++ChildId, SchemeRoot);
		MaxChildSelectedSize = 1;
	}
	for (int e = OEHead[SchemeRoot]; e; e = OutEdge[e].Nxt)
	{
		++ChildId;
		const int Dest = OutEdge[e].Dest;
		GetSchemeChild(Dest, SchemeRoot, ChildId);
		AssignMax(MaxChildSelectedSize, ChildSelectedNode.Size[ChildId]);
	}
	for (size_t i = 0; i <= ChildId; ++i)
	{
		ChildQueue.push((p) {ChildSelectedNode.Size[i], i});
	}
	int QueueIndex1 = MaxChildSelectedSize;
	int QueueIndex2 = QueueIndex1;
	for (int i = 1; i <= PairNum; ++i)
	{	

		p Top, Second;
		Top = ChildQueue.top();
		ChildQueue.pop();
		Second = ChildQueue.top();
		ChildQueue.pop();

		int ChildId1 = Top.second;
		int ChildId2 = Second.second;
		
		#ifdef FAST_IO
		printf("%d %d\n", ChildSelectedNode.GetHeadVal(ChildId1), ChildSelectedNode.GetHeadVal(ChildId2));
		#else
		cout << ChildSelectedNode.GetHeadVal(ChildId1)
			<< " " 
			<< ChildSelectedNode.GetHeadVal(ChildId2)
			<< endl;
		#endif
		
		ChildSelectedNode.PopHead(ChildId1);
		ChildSelectedNode.PopHead(ChildId2);
		
		if (--Top.first)
		{
			ChildQueue.push(Top);
		}
		if (--Second.first)
		{
			ChildQueue.push(Second);
		}
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


