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
typedef __int128 in;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1e3 + 10;
const in IINF = (in)LINF << 64 | LINF;
struct _Main {
	in map[MXN][MXN];
	in lx[MXN], ly[MXN], s[MXN];
	char vx[MXN], vy[MXN];
	int mx[MXN], my[MXN];// match of x / y
	int n;
	int ans[MXN];
	in pw[71];
	char dfs(int x) {
		vx[x] = 1;
		for (int y = 1; y <= n; y++) if (!vy[y]) {
			in t = ly[y] + lx[x] - map[x][y];	
			if (t == 0) {
				vy[y] = 1;
				if (!my[y] || dfs(my[y])) {
					mx[x] = y;
					my[y] = x;
					return 1;
				}
			} else {
				s[y] = min(s[y], t);
			}
		}
		return 0;
	}
	void KM() {
		for (int x = 1; x <= n; x++) {
			memset(s + 1, 0x3f, n * sizeof(in));
			while (1) {
				memset(vx + 1, 0, n * sizeof(char));
				memset(vy + 1, 0, n * sizeof(char));
				if (dfs(x)) break;
				in del = IINF;
				for (int y = 1; y <= n; y++) if (!vy[y]) {
					del = min(del, s[y]);
				}
				for (int x = 1; x <= n; x++) if (vx[x]) {
					lx[x] -= del;
				}
				for (int y = 1; y <= n; y++) if (vy[y]) {
					ly[y] += del;
				} else {
					s[y] -= del;
				}
			}
		}
	}
	int org[MXN][MXN];
	_Main() {
		int a, mxl;
		read(n);
		pw[1] = n + 1;
		for (int i = 2; i <= 70; i++) pw[i] = pw[i - 1] * (n + 1);
		for (int i = 1; i <= n; i++) {
			mxl = 0;
			for (int j = 1; j <= n; j++) {
				read(org[i][j]); mxl = max(mxl, org[i][j]);
				map[i][j] = pw[org[i][j]];
			}
			lx[i] = pw[mxl];
		}
		KM();
		for (int x = 1; x <= n; x++) {
			ans[org[x][mx[x]]]++;
		}
		for (int i = 70; i >= 0; i--) {
			printf("%d ", ans[i]);
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
