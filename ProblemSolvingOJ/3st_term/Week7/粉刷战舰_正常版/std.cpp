#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const lld Mod = 998244353;
const int MaxNum = 1e6 + 10;
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


lld GetAnswer(const int Num)
{
	lld Result = 0;
	if (Num <= 2)
	{
		Result = 1;
	}
	else /* Num > 2*/
	{
		Result = SavedFact[Num - 1] * QuickPower(Num, Num - 2) % Mod;
	}
//	printf("GetAns %d = %lld \n", Num, Result);
	return Result;
}
int main() {
	int Num;
	cin >> Num;
	InitFact(Num - 1);
	lld Answer = GetAnswer(Num);
	Answer += Mod;
	Answer %= Mod;
	printf("%lld", Answer);
	return 0;
}
