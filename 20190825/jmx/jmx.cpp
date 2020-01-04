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
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
struct _Main {
	char s[3379389 + 10];
	int len[71];
	int q[11];
	int mx;
	_Main() {
		
		freopen("jmx.in", "r", stdin);
		freopen("jmx.out", "w", stdout);
		scanf("%s", s);
		int Qn;
		read(Qn);
		for (int i = 1; i <= Qn; i++) {
			read(q[i]); mx = max(mx, q[i]);
		}
		len[1] = strlen(s);
		for (int i = 2; i <= mx; i++) {
			len[i] = len[i - 1] + ((len[i - 1] + 4) / 5);
		}
		for (int i = 2; i <= mx; i++) {
			memmove(s + len[i - 1], s, (len[i] - len[i - 1]) * sizeof(char));
		}
		for (int Q = 1; Q <= Qn; Q++) {
			for (int i = 0; i < len[q[Q]]; i++) {
				putchar(s[i]);
			}
			putchar('\n');
		}
		fclose(stdout);
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
