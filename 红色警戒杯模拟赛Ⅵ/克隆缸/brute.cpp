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
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 2000 + 5;
char dp[MXN >> 1][MXN];//i 到 n/2 修改j次是否存在
struct _Main {
	char str[MXN];
	char a1[MXN], a2[MXN];
	bool calc(int n, int m, char str[]) {
		char *up, *down;
		int h = n >> 1;
		up = str; down = str + h;
		for (int i = h + 1; i >= 1; i--) {
			memset(dp[i], 0, (n + 1) * sizeof(char));
		}
		dp[h + 1][0] = 1;
		for (int i = h; i >= 1; i--) {
			for (int j = 0; j <= m && j <= h - i << 1; j++) {
				if (dp[i + 1][j] == 0) continue; 
				if (up[i] == down[i]) {
					dp[i][j] = dp[i][j + 2] = 1;
				} else {
					dp[i][j + 1] = dp[i][j + 2] = 1;
				}
			}
		}
		if (dp[1][m] == 0) {
			return 0;
		}
		int t, rem = m;
		for (int i = 1; i <= h; i++) {
			for (char c = '0'; c <= '3'; c++) {
				t = rem - (up[i] != c) - (down[i] != c);
				if (dp[i + 1][t]) {
					up[i] = down[i] = c;
					rem = t;
					break;
				}
			}
		}
		return 1;
	}
	void print1() {
		for (int i = 1; i <= h; i++) {
			putchar(a1[i]);
		}
		putchar(str[h + 1]);
		for (int i = 1; i <= h; i++) {
			putchar(a1[i]);
		}
		putchar('\n');
	}
	void print2() {
		for (int i = 1; i <= h; i++) {
			putchar(a2[i]);
		}
		putchar(str[h + 1] == '0' ? '1' : '0');
		for (int i = 1; i <= h; i++) {
			putchar(a2[i]);
		}
		putchar('\n');
	}
	int n, m, h;
	_Main() {
		int Qn; 
		read(Qn);
		for (int Q = 1; Q <= Qn; Q++) {
			read(n); read(m);
			scanf("%s", str + 1);
			h = n >> 1;
			for (int i = 1; i <= h; i++) {
				a1[i] = str[i];
				a1[h + i] = str[h + 1 + i];
			}
			memcpy(a2 + 1, a1 + 1, (n - 1) * sizeof(char));
			char f1 = calc(n - 1, m, a1);
			char f2 = m >= 1 ? calc(n - 1, m - 1, a2) : 0;
			if (!f1 && !f2) {
				printf("failed\n");
			} else
			if (f1 && !f2) {
				print1();
			} else 
			if (!f1 && f2) {
				print2();
			} else {
				for (int i = 1; i <= h; i++) {//两者必然能比出来
					if (a1[i] != a2[i]) {
						if (a1[i] < a2[i]) {
							print1();
						} else {
							print2();
						}
						break;
					}
				}
			}
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
