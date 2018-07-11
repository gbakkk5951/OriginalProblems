using namespace std;
int main() {}
#include <cstring>
//#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#include <bitset>
//#include <iostream>
//#include <map>
//#include <queue>
//#include <set>
//#include <string>
//#include <sstream>
//#include <vector>
#include <cmath>
//#include <complex>
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
const int MXN = 1e6 + 10;
struct _Main {
	char str[MXN];
	char a1[MXN], a2[MXN];
	int n, m, h;
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
	char now[2][MXN >> 1];
	char gx[MXN >> 1];
	char from[2][MXN >> 1];
	char calc(int n, int m, char str[]) {
		if (n == 0) return m == 0;
		if (m > n) return 0;
		int use[2] = {0, 0};
		char *up = str, *down = str + h;
		//弄成AA串
		for (int i = 1; i <= h; i++) {
			now[0][i] = min(up[i], down[i]);
			gx[i] = up[i] != down[i];
			use[0] += gx[i];
		}
		//降低字典序
		for (int i = 1; i <= h && use[0] < m; i++) {
			if (now[0][i] != '0') {
				if (gx[i] == 1) {
					use[0]++;
					now[0][i] = '0';
					gx[i] = 2;
				} else
				if (use[0] + 2 <= m) {
					use[0] += 2;
					now[0][i] = '0';
					gx[i] = 2;
				}
			}
		}
		//提升字典序
		use[1] = -INF;
		if (use[0] & 1) {
			swap(use[0], use[1]);
		}
		memcpy(now[1] + 1, now[0] + 1, h * sizeof(int));
		int nuse[2]; char nc[2];
		for (int i = h; i >= 1; i--) {
			if (up[i] == down[i]) {
				for (int I = 0; I < 2; I++) {
					from[I][i] = I;
				}
				if (gx[i] == 0) {
					for (int I = 0; I < 2; I++) {
						nuse[I] = use[I] + 2;
						nc[I] = up[i] == '0' ? '1' : '0';
					}
				} else {
					continue;
				}
			} else {
				for (int I = 0; I < 2; I++) {
					from[I][i] = I ^ 1;
				}
				if (gx[i] == 1) {
					for (char c = '0'; c <= '3'; c++) {
						if (up[i] != c && down[i] != c) {
							for (int I = 0; I < 2; I++) {
								nuse[I ^ 1] = use[I] + 1;
								nc[I ^ 1] = c;
							}
							break;
						}
					}
				} else {
					for (int I = 0; I < 2; I++) {
						nuse[I ^ 1] = use[I] - 1;
						nc[I ^ 1] = min(up[i], down[i]);
					}
				}
			}
			for (int I = 0; I < 2; I++) {
				if (nuse[I] <= m && nuse[I] > use[I]) {
					use[I] = nuse[I];
					now[I][i] = nc[I];
				} else {
					from[I][i] = I;
				}
			}
		}
		
		//处理答案
		for (int I = 0; I < 2; I++) {
			if (use[I] == m) {
				for (int i = 1; i <= h; i++) {
					up[i] = down[i] = now[I][i];
					I = from[I][i];
				}
				return 1;
			}
		}
		return 0;
	}
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
			memcpy(a2, a1, n * sizeof(char));
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
				for (int i = 1; i <= h; i++) {
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
