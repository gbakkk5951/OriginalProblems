#include<iostream>
#include <iomanip>
#pragma warning(disable:4996)
typedef __uint128_t lll;
using namespace std;

int read()
{
	static char c = getchar();
	int f = 0, x = 0;
	while (c < '0' || c > '9')
		f |= (c == '-'), c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return f ? -x : x;
}


int main()
{
	lll a;
	int times;
	int op;
	times = read();
	for (int i = 0; i < times; i++)
	{
		op = read();
		if (op == 1)
		{
			int x = read();
			x = (x % 128 + 128) % 128;
			lll b = a & (((lll)1 << (lll)x) - (lll)1);
			a >>= (lll)x;
			a = (b << (lll)(128 - x)) + a;
		}
		else if (op == 2)
		{
			printf("%X\n", (unsigned short)a);
		}
		else if (op == 3)
		{
			int le, ri;
			le = read();
			ri = read();
			++ri;
			a ^= ri == 128 ? (lll)-1 : ((1 << ri) - 1);
			a ^= le == 0 ? 0 : ((1 << le) - 1);
		}
	}
	return 0;
}

//位运算我%￥&%￥&￥&￥#￥#&￥#……￥#￥%#……
