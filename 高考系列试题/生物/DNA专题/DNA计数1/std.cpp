using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
#include <cassert>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef long double Lf;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const lld MOD = 1e9 + 7;
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	do {
		if (pow & 1) ret = ret * base % MOD;
		if (pow >>= 1) base = base * base % MOD;
	} while(pow);
	return ret;
}
struct _Main {
	lld calc(lld n) {
		if (n == 1) {
			return 2;
		} else
		if (!(n & 1)) {
			lld pow = fastpower(2, n - 1);
			return pow * ((pow << 1) + 1) % MOD;	
		} else {
			return fastpower(2, (n << 1) - 1);
		}
	}
	_Main() {
		int Qn, n;
		lld ans = 0;
		read(Qn);
		for (int Q = 1; Q <= Qn; Q++) {
			read(n);
			ans ^= calc(n);
		}
		printf("%lld", ans);
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
