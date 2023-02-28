#include <bits/stdc++.h>
#define AC 0
#define WA 1
using namespace std;
typedef long long lld;
typedef double lf;
lld UserDist = 0, AnsDist = 0;
const lf eps = 1e-6;
const int MaxV = 1e5 + 10;
const int LogMaxV = 2 + (int)ceil(log((lf)MaxV) / log(2.0)+ eps);
int VNum, Depth[MaxV], Parent[MaxV][LogMaxV], DistSum[MaxV];
int SelectedNum;
int PairNum;
struct FOutEdge
{
	int Dest, Val;
};
vector<FOutEdge> OutEdge[MaxV];
void AddEdge(int Src, int Dest, int Val)
{
	OutEdge[Src].push_back((FOutEdge) {Dest, Val});
}
void AddBidirectedEdge(int Src, int Dest, int Val)
{
	AddEdge(Src, Dest, Val);
	AddEdge(Dest, Src, Val);
}
void PrepareLCAAndDistSum(const int Vertex)
{
	for (int Exp = 1; (1 << Exp) <= Depth[Vertex]; ++Exp)
	{
		Parent[Vertex][Exp] = Parent[Parent[Vertex][Exp - 1]][Exp - 1];
	}
	for (auto Edge: OutEdge[Vertex])
	{
		const int &Dest = Edge.Dest;
		if (Dest != Parent[Vertex][0])
		{
			Depth[Dest] = Depth[Vertex] + 1;
			Parent[Dest][0] = Vertex;
			DistSum[Dest] = DistSum[Vertex] + Edge.Val;
			PrepareLCAAndDistSum(Dest);
		}
	}
}
int GetLCA(int A, int B)
{
	if (Depth[B] > Depth[A])
	{
		swap(A, B);
	}
	for (int Exp = LogMaxV - 1; Exp >= 0; --Exp)
	{
		if (Depth[A] - (1 << Exp) >= Depth[B])
		{
			A = Parent[A][Exp];
		}
	}
	assert(Depth[A] == Depth[B]);
	if (A == B) 
	{
		return A;
	}
	for (int Exp = LogMaxV - 1; Exp >= 0; --Exp)
	{
		if ((1 << Exp) < Depth[A] && Parent[A][Exp] != Parent[B][Exp])
		{
			A = Parent[A][Exp];
			B = Parent[B][Exp];
		}
	}
	return Parent[A][0];
}
bool CanBeUsed[MaxV];
int main(int argc, char *argv[])
{
	FILE *f_in = fopen(argv[1], "r");
	FILE *f_user = fopen(argv[2], "r");
	FILE *f_out = fopen(argv[3], "r");
	int Score = 0;
	
	if (fscanf(f_user, "%lld", &UserDist))
	{
		fscanf(f_out, "%lld", &AnsDist);
	} 
	else
	{
		printf("%d\n", Score);
		return WA;
	}
	if (UserDist == AnsDist)
	{
		Score = 80;
	}
	fscanf(f_in, "%*d%d%d", &VNum, &SelectedNum);
	PairNum = SelectedNum / 2;
	int V1 = 0, V2 = 0, Val = 0;
	for (int i = 1; i <= VNum - 1; ++i)
	{
		fscanf(f_in, "%d%d%d", &V1, &V2, &Val);
		AddBidirectedEdge(V1, V2, Val);
	}
	for (int i = 1; i <= SelectedNum; ++i)
	{
		fscanf(f_in, "%d", &V1);
		CanBeUsed[V1] = true;
	}
	PrepareLCAAndDistSum(1);
	
	lld RealUserDist = 0;
	bool bIsSchemeLegal = false;
	char Report[500];
	try
	{	
		int X[2];
		for (int i = 1; i <= PairNum; ++i)
		{
			fscanf(f_user, "%d%d", &X[0], &X[1]);
			if (ferror(f_user))
			{
				throw "error occurred reading user's scheme";
			}

			for (int XId = 0; XId < 2; ++XId)
			{	
				int V = X[XId];
				if (0 < V && V <= VNum && CanBeUsed[V])
				{
					CanBeUsed[V] = false;
				}
				else
				{
					sprintf(Report, "Invalid Vertex %d, [%d - %d], used = %d\n", V, 1, VNum, (int)CanBeUsed[V]);
					throw Report;
		//			throw "Invalid vertex is used";
				}
			}
			int X0 = X[0], X1 = X[1]; 
			int LCA = GetLCA(X0, X1);
			RealUserDist += DistSum[X0] + DistSum[X1] - DistSum[LCA] * 2;
		}
		bIsSchemeLegal = RealUserDist == UserDist;
	}
	catch (char const *s)
	{
		printf("Throw %s\n", s);
		bIsSchemeLegal = false;
	}
	catch (char *s)
	{
		printf("Throw %s\n", s);
		bIsSchemeLegal = false;
	}
	
	if (bIsSchemeLegal)
	{
		Score = max(Score + 20, 30);
	}
	fclose(f_in);
	fclose(f_out);
	fclose(f_user);
	printf("%d\n", Score);
	return Score ? AC : WA;
}
