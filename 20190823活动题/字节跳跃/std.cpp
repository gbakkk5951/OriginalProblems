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
const int MXN = 2e6 + 5;
const int MXM = 3e6 + 5;
const int MX = 5e6 + 5;
const int LEN = 6;
struct Node {
	char end, vis, idx, len, str[6];
	int from;
	//str正着存，跑路径的时候倒着读，输出正着读
}node[MX];
struct _Main {
	int n, m, en;
	int q[2][2][MX];
	int t[2][2];
	void print(int ed) {
		for (int nd = ed; nd; nd = node[nd].from) {
			printf("%s", node[nd].str);
		}
		putchar('\n');
		for (int nd = ed; nd; nd = node[nd].from) {
			if (nd <= n) {
				printf("%d ", nd);
			}
		}
	}
	int lh[MXN], lidx;
	int l[MXM][3];
	void ladd(int a, int b, int c) {
		++lidx;
		l[lidx][DST] = b;
		l[lidx][VAL] = c;
		l[lidx][NXT] = lh[a];
		lh[a] = lidx;
	}
	
	int h[MX], eidx, e[MXM << 1][2];
	void add(int a, int b) {
		eidx++;
		e[eidx][DST] = b;
		e[eidx][NXT] = h[a];
		h[a] = eidx;
	}
	void push(int it, int nd) {
		char c = node[nd].str[node[nd].len - node[nd].idx - 1] - '0';
		q[it][c][++t[it][c]] = nd;
		node[nd].vis = 1;
	}
	_Main() {
		read(n); read(m); read(en);
		for (int i = 1; i <= n; i++) {
			scanf("%s", node[i].str);
		}
		for (int i = 1, nd; i <= en; i++) {
			read(nd); node[nd].end = 1;
		}
		for (int i = 1, a, b; i <= m; i++) {
			read(a); read(b);
			scanf("%s", node[n + i].str);
			ladd(a, b, n + i);
		}
		for (int i = 1; i <= n + m; i++) {
			node[i].len = strlen(node[i].str);
		}
		//加反向边
		for (int i = n; i >= 1; i--) {//后加的在先
			for (int nl = lh[i]; nl; nl = l[nl][NXT]) {
				//边权化点权
				add(l[nl][DST], l[nl][VAL]);
				add(l[nl][VAL], i);
			}
		}
		int it = 0;
		push(it, 1);
		while (1) {
			it ^= 1;
			for (int i = 0; i <= 1; i++) {
				for (int j = 1, nd; j <= t[it ^ 1][i]; j++) {
					nd = q[it ^ 1][i][j];
					//继续在串上走
					if ((++node[nd].idx) < node[nd].len) {
						push(it, nd);
					} else { //走边
						if (node[nd].end) {
							print(nd);
							goto End;
						}
						for (int nh = h[nd], t; nh; nh = e[nh][NXT]) {
							if (node[t = e[nh][DST]].vis == 0) {
								push(it, t);
								node[t].from = nd;
							}
						}
					}
				}
				t[it ^ 1][i] = 0;
			}
		}
		End:
		
		;
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
