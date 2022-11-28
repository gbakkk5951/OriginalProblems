#include <bits/stdc++.h>
using namespace std;
const int MaxNum = 1e6 + 10;
typedef pair<int, int> FSoldier;

vector<FSoldier> Soldiers;
deque<int> Chains; // Mono Increasing
/*
* Dilworth's Theorem:
* The largest antichain has the same size as the smallest chain decomposition.
*/
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
/*
* Rightest Value that <= X
*/
int FindIndex(int X)
{
	if (Chains.empty() || Chains[0] > X)
	{
		return -1;
	}
	int Left = 0, Right = Chains.size() - 1, Middle;
	while (Left < Right)
	{
		Middle = (Left + Right) / 2 + 1;
		if (Chains[Middle] > X)
		{
			Right = Middle - 1;
		}
		else
		{
			Left = Middle;
		}
	}
	return Left;
}

int Num;
int main() 
{
	ReadInt(Num);
	Soldiers.resize(Num);
	for (int i = 0; i < Num; ++i)
	{
		ReadInt(Soldiers[i].first);
		ReadInt(Soldiers[i].second);
	}
	sort(Soldiers.begin(), Soldiers.end());
	for (auto Soldier : Soldiers)
	{
		int Index = FindIndex(Soldier.second);
		if (Index == -1)
		{
			Chains.push_front(Soldier.second);
		} else 
		{
			Chains[Index] = Soldier.second;
		}
	}
	printf("%u", (uint32_t)Chains.size());
	return 0;
}
