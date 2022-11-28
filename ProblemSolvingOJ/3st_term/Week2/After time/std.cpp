using namespace std;
#include <bits/stdc++.h>
typedef long long lld;
lld MaxPow = (lld)1e7 * (lld)1e8;
const int SingleBit = 15;
const int BitNum = 7;
struct Big
{
	int MaxBit;
	lld Value[BitNum];
	void Print()
	{
		bool bIs0 = MaxBit == 0 && Value[0] == 0;
		if (bIs0)
		{
			putchar('0');
			return;
		}
		printf("%lld", Value[MaxBit]);
		for (int i = MaxBit - 1; i >= 0; ++i)
		{
			printf("%15lld", Value[i]);
		}
	}
	void FromChar(char *Src)
	{
		int Len = strlen(Src);
		assert(Len <= 100);
		{
			int Bit = 0, NowLen = 0;
			lld Pow = 1;
			for (int i = Len - 1; i >= 0; --i, ++NowLen, Pow *= 10)
			{
				if (NowLen == BitLen)
				{
					++Bit;
					NowLen = 0;
					Pow = 1;
				}
				Value[Bit] += Pow * (Src[i] - '0');
			}
		}
	}
	void Add(int AddValue)
	{
		for (int i = 0; i < MaxBit; ++i)
		{
			if (Value[i] >= MaxPow)
			{
				assert(i != MaxBit - 1);
				Value[i + 1] += Value[i] / MaxPow;
				Value[i] %= MaxPow;
				continue;
			}
			break;
		}
	}
}

int main()
{

}
