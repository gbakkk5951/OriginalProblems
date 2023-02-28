#include <bits/stdc++.h>
using namespace std;
#define FAST_IO

const int MaxV = 1e5 + 10;

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
int StuNum, RelaNum;

/* a->b : a < b */
vector<int> OutEdges[MaxV];
int InDeg[MaxV];
void AddEdge(int Src, int Dest)
{
	OutEdges[Src].push_back(Dest);
	++InDeg[Dest];
}
int main() 
{
	int CaseNum = -1;
	ReadInt(CaseNum);
	
	for (int CaseCnt = 1; CaseCnt <= CaseNum; ++CaseCnt)
	{
		ReadInt(StuNum);
		ReadInt(RelaNum);
		memset(InDeg + 1, 0, StuNum * sizeof(int));
		for (int i = 1; i <= StuNum; ++i)
		{
			OutEdges[i].clear();
		}
		for (int i = 1, a, b; i <= RelaNum; ++i)
		{
			#ifdef FAST_IO
				ReadInt(a);
				ReadInt(b);
			#else
				cin >> a >> b;
			#endif
			AddEdge(a, b);
		}
		int TopoedNum = 0;
		if (RelaNum >= StuNum - 1)
		{
			queue<int> TopoQueue;
			for (int i = 1; i <= StuNum; ++i)
			{
				if (InDeg[i] == 0)
				{
					TopoQueue.push(i);
					break;
				}
			}
			while (!TopoQueue.empty())
			{
				int Vertex = TopoQueue.front();
				TopoQueue.pop();
				++TopoedNum;
				for (auto Dest : OutEdges[Vertex])
				{
					if (--InDeg[Dest] == 0)
					{
						TopoQueue.push(Dest);
					}
				}
				if (TopoQueue.size() > 1)
				{
					break;
				}
			}
		}
		printf("%s\n", (TopoedNum == StuNum) ? "YES" : "NO");
	}
	return 0;
}
