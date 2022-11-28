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
inline int lb(int a) {
	return a & (-a);
}
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
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const lld MOD = 998244353;
const lld PHI = MOD - 1;
const int MXN = 1e6 + 10;
const int MXP = 2.4e7;
struct Node {
	Node *s[3];
	lld dp;
}pool[];
Node *nw() {

}
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow += pow < 0 ? PHI : 0;
	while (pow) {
		if (pow & 1) ret = ret * base % MOD;
		if (pow >>= 1) base = base * base % MOD;
	}
	return ret;
}
struct _Main {
	int n, m, mm;
	int nrcnt;
	lld ans;
	char syn[MXN]; // 0, +1, -1
	char cover[MXN];
	lld dp[MXN];
	
	
	void brute() {
		
	}
	
	
	_Main() {
		brute(), return;
		int a, b, c;
		read(n); read(m); read(mm);
		if (m == 1) {
			printf("%d", 1);
			return;
		}
		for (int i = 1; i <= mm; i++) {
			read(a); read(b); read(c);
			nrcnt += c;
			if (a > b) swap(a, b);
			syn[a] = +1;
			syn[b] = -1;
			cover[a + 1]++;
			cover[b]--;
		}
		for (int i = 2; i <= n; i++) {
			cover[i] += cover[i - 1];
		}
		
		
		getdp();
		
		for (int i = n; i >= 0; i--) {
			ans = ans
			if ()
		}
		
		
		
		
		
		ans = (ans % MOD * fastpower(2, -nrcnt) % MOD + MOD) % MOD;
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
