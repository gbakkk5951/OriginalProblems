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
const lld PHI = MOD - 1;
struct _Main {
	lld fp(lld b, lld p) {
		lld r = 1;
		while (p) {
			if (p & 1) r = r * b % MOD;
			if (p >>= 1) b = b * b % MOD;
		}
		return r;
	}
	lld calc(lld l, lld r, lld a, lld b, lld c, lld d) {
		lld ret = 0;
		for (lld i = l; i <= r; i++) {
			ret += (a + i * b) % MOD * fp(c, (d + i * b) % PHI);
			ret %= MOD;
		}
		return ret;
	}
	_Main() {
		int Qn;
		lld l, r, a, b, c, d;
		read(Qn);
		for (int Q = 1; Q <= Qn; Q++) {
			read(l); read(r); read(a); read(b); read(c); read(d);
			printf("%lld\n", calc(l, r, a, b, c, d));
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
