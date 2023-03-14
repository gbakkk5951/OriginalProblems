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
	lld Exp = 0;
	for (int i = Begin; s[i]; ++i)
	{
		Exp = (Exp * 10 + s[i] - '0') % (p - 1);
	}
	if (a % p == 0)
	{
		cout << 0;
		return 0;
	}
	cout << QuickPower(a, Exp, p);
	return 0;
}
