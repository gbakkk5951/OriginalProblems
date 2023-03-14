#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int MaxLen = 1e6 + 10;
char s[MaxLen];
lld QuickPower(lld Base, lld Exp, lld Mod)
{
	lld Ret = 1;
	while (Exp)
	{
		if (Exp & 1)
		{
			Ret = Ret * Base % Mod;
		}
		Exp >>= 1;
		Base = Base * Base % Mod;
	}
	return Ret;
}
int main() 
{
	lld a, p;
	cin >> a >> s >> p;
	if (p == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	int Begin = -1;
	for (int i = 0; s[i]; ++i)
	{
		if (s[i] != '0')
		{
			Begin = i;
			break;
		} 
	}
	if (Begin == -1)
	{
		cout << 1;
		return 0;
	}
	int Phi = p, Remain = p;
	for (int i = 2; i * i <= Remain; ++i)
	{
		if (Remain % i == 0)
		{
			Phi = (lld)Phi * (i - 1) / i; // 找个爆的
			do {
				Remain /= i;
			} while (Remain % i == 0);
		}
	}
	if (Remain > 1)
	{
		Phi = (lld)Phi * (Remain - 1) / Remain; // 找个爆的
	}
	lld Exp = 0;
	for (int i = Begin; s[i]; ++i)
	{
		Exp = (Exp * 10 + s[i] - '0') % (Phi);
	}
	cout << QuickPower(a, Exp, p);
	return 0;
}
