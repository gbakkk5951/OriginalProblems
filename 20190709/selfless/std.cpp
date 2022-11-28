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
const int MXN = 1e5 + 10, MXE = 2e5 + 10;
const int U = 0, V = 1, C = 2;
const int F = 0, MX = 1, SEC = 2;
struct E {
	int u, v, c;	
	inline bool friend operator < (const E &a, const E &b) {
		return a.c < b.c;
	}
} e[MXE];
bool used[MXE];
struct _Main {
	int edge[MXN << 1][3];
	int head[MXN];
	int eidx;
	inline void dir_add(int a, int b, int c) {
		++eidx;
		edge[eidx][DST] = b;
		edge[eidx][VAL] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	void add(int a, int b, int c) {
		dir_add(a, b, c);
		dir_add(b, a, c);
	}
	int n, m;
	int h[MXN], up[MXN][18][3];
	int minans;
	int ans;
	int log[MXN];
	int mxh;
	int tmp[4];
	int getsec(int *a, int *b) {
		tmp[0] = a[MX], tmp[1] = a[SEC],
		tmp[2] = b[MX], tmp[3] = b[SEC];
		sort(tmp, tmp + 4, greater<int>());
		int i = 1;
		while(i < 3 && tmp[i] == tmp[0]) i++;
		return tmp[i];
	}
	void dfs(int nd, int f, int val) {
		up[nd][0][F] = f;
		up[nd][0][SEC] = up[nd][0][MX] = val;
		h[nd] = h[f] + 1;
		mxh = max(mxh, h[nd]);
		for (int i = 1; 1 << i < h[nd]; i++) {
			up[nd][i][F] = up[up[nd][i - 1][F]][i - 1][F];
			up[nd][i][MX] = max(up[nd][i - 1][MX], up[up[nd][i - 1][F]][i - 1][MX]);
			up[nd][i][SEC] = getsec(up[nd][i - 1], up[up[nd][i - 1][F]][i - 1]);
		}
		for (int e = head[nd], t; e; e = edge[e][NXT]) {
			if ((t = edge[e][DST]) != f) {
				dfs(t, nd, edge[e][VAL]);
			}
		}
	}
	int jump(int &nd, int bit, int c) {
		int ret = -1;
		if (up[nd][bit][MX] < c) {
			ret = up[nd][bit][MX];
		} else if(up[nd][bit][SEC] < c) {
			ret = up[nd][bit][SEC];
		}
		nd = up[nd][bit][F];
		return ret;
	}
	int getans(int a, int b, int c) {
		int ans = -1;
		if (h[a] < h[b]) swap(a, b);
		while(h[a] != h[b]) {
			for (int i = log[h[a] - h[b]]; i >= 0; i--) {
				if (h[a] - (1 << i) >= h[b]) {
					ans = max(ans, jump(a, i, c));
				}
			}
		}
		if (a != b) {
			for (int i = log[h[a] - 2]; i >= 0; i--) {
				if (up[a][i][F] != up[b][i][F]) {
					ans = max(ans, jump(a, i, c));
					ans = max(ans, jump(b, i, c));
				}
			}
			ans = max(ans, jump(a, 0, c));
			ans = max(ans, jump(b, 0, c));
		}
		
		return ans;
	}
	int f[MXN];
	int getfa(int nd) {
		if (f[nd]) return f[nd] = getfa(f[nd]);
		else return nd;
	}
	void kruskal() {
		sort(e + 1, e + m + 1);
		int a, b, fa, fb;
		for (int i = 1; i <= m; i++) {
			a = e[i].u, b = e[i].v;
			if ((fa = getfa(a)) != (fb = getfa(b))) {
				used[i] = 1;
				f[fa] = fb;
				minans += e[i].c; 
				add(a, b, e[i].c);
			}
		}
	}
	_Main() {
		ans = 2147483647;
		read(n); read(m);
		for (int i = 1; i <= m; i++) {
			read(e[i].u); read(e[i].v); read(e[i].c);
		}
		kruskal();
		dfs(1, 0, 0);
		for (int i = 0, j = 1; j < mxh; j++) {
			if (1 << i + 1 == j) i++;
			log[j] = i;
		}
		int t;
		for (int i = 1; i <= m; i++) {
			if (!used[i]) {
				t = getans(e[i].u, e[i].v, e[i].c);
				if (t != -1) {
					ans = min(ans, minans + e[i].c - t);
				} else {
					ans = min(ans, minans + e[i].c);
				}
			}
		}
		printf("%d", ans);
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
