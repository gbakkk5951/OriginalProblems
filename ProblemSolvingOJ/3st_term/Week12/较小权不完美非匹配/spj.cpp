#include <bits/stdc++.h>
#define AC 0
#define WA 1
using namespace std;
typedef long long lld;
const int MaxEdgeNum = 2e5 + 10;
const int MaxVertexNum = 1e5 + 10;
lld StdAnswer;
lld UserEdgeNum = -1;
int n, m, total = 0;
struct FEdge
{
	int u, v, c;
}Edges[MaxEdgeNum];
bitset<MaxVertexNum> bIsVertexVisited;
int VertexVisitedCount;
int main(int argc, char *argv[])
{
	FILE *f_in = fopen(argv[1], "r");
	FILE *f_out = fopen(argv[3], "r");
	FILE *f_user = fopen(argv[2], "r");

	fscanf(f_in, "%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		fscanf(f_in, "%d%d%d", &Edges[i].u, &Edges[i].v, &Edges[i].c);
	}
	
	fscanf(f_out, "%lld", &StdAnswer);
	
	lld TotalDist = 0;
	try 
	{
		if (fscanf(f_user, "%lld", &UserEdgeNum) == EOF || UserEdgeNum < 0 || UserEdgeNum > n * 5)
		{
			throw ("Invalid Edge Num");
		}
		int CurrentVertex = 1;
		for (int i = 1; i <= UserEdgeNum; ++i)
		{
			lld EdgeId = -1;
			if (fscanf(f_user, "%lld", &EdgeId) == EOF || EdgeId <= 0 || EdgeId > m)
			{
				throw ("Invalid Edge Id");
			}
			if (CurrentVertex == Edges[EdgeId].u)
			{
				CurrentVertex = Edges[EdgeId].v;
				TotalDist += Edges[EdgeId].c;				
			}
			else if (CurrentVertex == Edges[EdgeId].v)
			{
				CurrentVertex = Edges[EdgeId].u;
				TotalDist += Edges[EdgeId].c;
			}
			else
			{
//				throw "Not a Path";
			}
			if (!bIsVertexVisited[CurrentVertex])
			{
				bIsVertexVisited[CurrentVertex] = 1;
				++VertexVisitedCount;
			}
		}
		if (CurrentVertex != 1)
		{
//			throw "Not end at 1";
		}
		if (VertexVisitedCount != n)
		{
//			throw "did not visit all vertices";
		}
	}
	catch (...)
	{
		printf("0\n");
		return WA;
	}
	int Score = 40;
	if (TotalDist <= StdAnswer * 2)
	{
		Score += 60;
	}
	else if (TotalDist <= StdAnswer * 5)
	{
		Score += (int)ceil(60.0 * (StdAnswer * 5 - TotalDist) / (StdAnswer * 3.0));
	}	
	fclose(f_in);
	fclose(f_out);
	fclose(f_user);
	printf("%d\n", Score);
	return AC;
}
