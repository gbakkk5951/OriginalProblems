#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const lld Mod = 998244353;
const int MaxNum = 1e5 + 10;
lld SavedFact[MaxNum];
void InitFact(int InMaxNum)
{
	SavedFact[0] = 1;
	for (int i = 1; i <= InMaxNum; ++i)
	{
		SavedFact[i] = SavedFact[i - 1] * i % Mod;
	}
}
lld QuickPower(lld Base, lld Exp)
{
	lld Result = 1;
	while (Exp)
	{
		if (Exp & 1) 
		{
			Result = Result * Base % Mod;
		}
		if (Exp >>= 1) 
		{
			Base = Base * Base % Mod;
		}
	}
	return Result;
}

lld GetReverse(lld x)
{
	return QuickPower(x, Mod - 2);
}

lld GetCombination(int TotalNum, int ChooseNum)
{
	lld Result = 0;
	if (ChooseNum <= TotalNum && ChooseNum >= 0)
	{
		/* You can multiply arguments of GetReverse first to improve performance */
		Result = SavedFact[TotalNum] * GetReverse(SavedFact[ChooseNum] * SavedFact[TotalNum - ChooseNum] % Mod) % Mod;
	}
	printf("Com %d %d = %lld\n", TotalNum, ChooseNum, Result);
	return Result;
}

/*	
	if (MinLeafNum < legal Min Left Num)
	{
		return Num of all legal combinations.
	}
*/
lld GetSum(const int Num, int MinLeafNum)
{
	lld Result = 0;
	if (Num <= 2)
	{
		Result = MinLeafNum <= Num;
	}
	else if (MinLeafNum < Num) /* Num > 2*/
	{
		MinLeafNum = max(MinLeafNum, 2);
		/* Wrong! 2nd Stirling is supposed to be used*/
		Result = SavedFact[Num - 1] * GetCombination(Num, MinLeafNum) % Mod * QuickPower(Num - MinLeafNum, Num - 2) % Mod;
	}
	printf("GetSum %d %d = %lld \n", Num, MinLeafNum, Result);
	return Result;
}
int main() {
	int Num, LeafNum;
	cin >> Num >> LeafNum;
	InitFact(Num);
	lld Answer = GetSum(Num, LeafNum) - GetSum(Num, LeafNum + 1);
	Answer += Mod * 2;
	Answer %= Mod;
	printf("%lld", Answer);
	return 0;
}
