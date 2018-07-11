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
const int MXN = 305;
struct _Main {
	int f[MXN], h[MXN], sum[MXN];
	int dis[MXN][MXN];
	int n;
	int getlca(int a, int b) {
		while (a != b) {
			if (h[a] < h[b]) swap(a, b);
			a = f[a];
		}
		return a;
	}
	void build(int nd, int fa) {
		f[nd] = fa;
		h[nd] = h[fa] + 1;
		sum[nd] = sum[fa] + dis[fa][nd];
		for (int i = 1; i <= n; i++) {
			if (dis[nd][i] != INF && i != fa) {
				build(i, nd);
			}
		}
	}
	void move() {
		int a, b, c;
		read(a); read(b); read(c);
		if (getlca(a, b) == a) {
			return;
		}
		dis[f[a]][a] = dis[a][f[a]] = INF;
		dis[b][a] = dis[a][b] = c;
		build(a, b);
	}
	void setroot() {
		int a;
		read(a);
		build(a, 0);
	}
	void change_val() {
		int a, b, c;
		read(a); read(b); read(c);
		if (dis[a][b] < INF) {
			dis[a][b] = dis[b][a] = c;
			if (h[a] < h[b]) {
				swap(a, b);
			}
			build(a, b);
		}
	}
	void query() {
		int kn, lca, lst, now;
		read(kn);
		read(lst);
		lca = lst;
		for (int i = 1; i <= kn - 1; i++) {
			read(now);
			int tmp = getlca(now, lst);
			if (h[tmp] < h[lca]) {
				lca = tmp;
			}
			lst = now;
		}
		printf("%d\n", sum[lca]);
	}
	_Main() {
		int Qn;
		read(n); read(Qn);
		memset(dis, 63, sizeof(dis));
		for (int i = 0; i <= n; i++) {
			dis[i][0] = dis[0][i] = 0;
		}
		int u, v, c;
		for (int i = 1; i <= n - 1; i++) {
			read(u); read(v); read(c);
			dis[u][v] = dis[v][u] = c;
		}
		build(1, 0);
		for (int Q = 1; Q <= Qn; Q++) {
			int op;
			read(op);
			if (op == 1) {
				move();
			} else
			if (op == 2) {
				setroot();
			} else
			if (op == 3) {
				change_val();
			} else
			if (op == 4) {
				query();
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
