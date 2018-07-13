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
struct _Main {
	char c[5][5];
	_Main() {
		int n;
		read(n);
		int ans = 0;
		for (int I = 0; I < 1 << (n * n); I++) {
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					c[i][j] = I >> (cnt++) & 1;
				}
			}
			int i, j;
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (c[i][j]) break;
				}
				if (j == n) break;
				for (j = 0; j < n; j++) {
					if (c[j][i]) break;
				}
				if (j == n) break;
			}
			if (i == n) {
				for (i = 0; i < n; i++) {
					if (c[i][i]) break;
				}
				if (i == n) continue;
				for (i = 0; i < n; i++) {
					if (c[i][n - i - 1]) break;
				}
				if (i == n) continue;
				++ans;
			}
			
		}
		printf("%d", ans);
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
