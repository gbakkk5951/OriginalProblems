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
const lld PHI = 1e9 + 6;
const lld REV2 = 5e8 + 4;
struct _Main {
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		while (pow) {
			if (pow & 1) ret = ret * base % MOD;
			if (pow >>= 1) base = base * base % MOD;
		}
		return ret;
	}
	lld pf(lld a) {
		return a * a % MOD;
	}
	lld calc(lld l, lld r, lld a, lld b, lld c, lld d) {
		if (c == 1) {
			return ((r - l + 1) * a + b * (l + r) % MOD * (r - l + 1) % MOD * REV2) % MOD;
		}
		lld cr1b_1, cr1b, cb_1, cb, clb_1, clb;
		cr1b_1 = fastpower(c, ((r + 1) * b - 1) % PHI);\
		cr1b = cr1b_1 * c % MOD;
		cb_1 = fastpower(c, b - 1);
		cb = cb_1 * c % MOD;
		clb_1 = fastpower(c, (l * b - 1) % PHI);
		clb = clb_1 * c % MOD;
		return (fastpower(c, d) * (
				(
					a *
					(cr1b - clb) % MOD 
					* fastpower(cb - 1, PHI - 1)
					+ 
					c *
					((((r + 1) * b % MOD * cr1b_1 - l * b % MOD * clb_1) % MOD * (cb - 1) 	
					- (cr1b - clb) * (b * cb_1 % MOD) ) % MOD) % MOD
					* fastpower(pf(cb - 1), PHI - 1) 
					
				) % MOD
			)
			% MOD + MOD
		) % MOD;
		
		
	}
	_Main() {
		int Qn, l, r, a, b, c, d;
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
