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
const int MXN = 2e4 + 10, MXM = 2e5 + 10;
struct Dinic {
	int src, dst, eidx, size;
	int head[MXN], now[MXN], lay[MXN];
	lld edge[(MXN << 1) + MXM][3];
	Dinic() {
		init();
	}
	void init() {
		eidx = 1;
		memset(head, 0, size * sizeof(int));
	}
	void dir_add(int a, int b, lld c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][FLOW] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	void add(int a, int b, lld c) {
		dir_add(a, b, c);
		dir_add(b, a, 0);
	}
	int getlay() {
		memset(lay, 0, size * sizeof(int));
		static int q[MXN];
		int qh = 1, qt = 0;
		q[++qt] = src;
		lay[src] = 1;
		while (qh <= qt) {
			int nd = q[qh++];
			for (int e = head[nd]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (edge[e][FLOW] && !lay[t]) {
					lay[t] = lay[nd] + 1;
					q[++qt] = t;
				}
			}
		}
		return lay[dst];
	}
	lld getflow(int nd, lld mx) {
		if (nd == dst) {
			return mx;
		}
		lld rem = mx;
		for (int e = now[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (edge[e][FLOW] && lay[t] > lay[nd]) {
				t = getflow(t, min(rem, edge[e][FLOW]));
				if (t) {
					edge[e][FLOW] -= t;
					edge[e ^ 1][FLOW] += t;
					rem -= t;
					if (rem == 0) {
						now[nd] = e;
						return mx;
					}
				}
			}
		}
		now[nd] = 0;
		return mx - rem;
	}
	lld run() {
		lld ret = 0;
		while (getlay()) {
			memcpy(now, head, size * sizeof(int));
			ret += getflow(src, LINF);
		}
		return ret;
	}
}flow;
struct _Main {
	int thead[6][MXN], edge[MXM][2], eidx;
	void add(int t, int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = thead[t][a];
		thead[t][a] = eidx;
	}
	void build(int tid, int nd, int fa) {
		if (tid == 1) {
			if (a[nd] > 0) {
				flow.add(flow.src, nd, a[nd]);
			} else {
				flow.add(nd, flow.dst, -a[nd]);
			}
		}
		if (fa) {
			flow.add(nd, fa, LINF);
		}
		for (int e = thead[tid][nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				build(tid, t, nd);
			}
		}
	}
	int a[MXN];
	int n, m;
	_Main() {
		lld ans = 0, sum = 0;
		read(n); read(m);
		flow.dst = n + 1;
		flow.size = n + 2;
		int u, v;
		for (int i = 1; i <= n; i++) {
			read(a[i]); sum += a[i] > 0 ? a[i] : 0;
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n - 1; j++) {
				read(u); read(v);
				add(i, u, v);
				add(i, v, u);
			}
		}
		for (int i = 1; i <= n; i++) {
			flow.init();
			for (int j = 1; j <= m; j++) {
				build(j, i, 0);
			}
			ans = max(ans, sum - flow.run());
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
}brute;
}
