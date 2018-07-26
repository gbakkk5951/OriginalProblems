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
const lf e = exp(1.0);
struct _Main {

	lld dp[1005][400];
	int A, B, C, D;
	int Qn;
	int n;
	lld getdp(int on, int en) {
		if (n - on * 1 - en * e < B) {
			return A;
		} 
		if (dp[on][en]) return dp[on][en];
		return dp[on][en] = (C * getdp(on + 1, en) + D * getdp(on, en + 1)) % MOD;
	}
	_Main() {
		read(A); read(B); read(C); read(D);
		read(Qn);
		for (int Q = 1; Q <= Qn; Q++) {
			read(n);
			memset(dp, 0, sizeof(dp));
			printf("%lld\n", getdp(0, 0));
		}
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
