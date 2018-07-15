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
const int MXN = 1e5 + 10;
const int MXM = 2e5 + 10;
int l[MXN], r[MXN];
int ln, rn;
int match[MXN];

struct Flow {
	int src, dst;
	Flow() {
		init();
	}
	void init() {
		eidx = 1;
	}
	
	int head[MXN], edge[MXN + MXM << 1][3], eidx;
	void dir_add(int a, int b, int c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][FLOW] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	void add(int a, int b, int c) {
		dir_add(a, b, c);
		dir_add(b, a, 0);
	}
	int size;
	int lay[MXN];
	int q[MXN];
	int getlay() {
		memset(lay, 0, size * sizeof(int));
		int qh = 0, qt = -1;
		lay[src] = 1;
		q[++qt] = src;
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
	
	int now[MXN];
	int getflow(int nd, int mx) {
		if (nd == dst) return mx;
		int rem = mx;
		for (int e = now[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (edge[e][FLOW] && lay[t] > lay[nd]) {
				t = getflow(t, min(edge[e][FLOW], rem));
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
	int run() {
		int ret = 0;
		while (getlay()) {
			memcpy(now, head, size * sizeof(int));
			ret += getflow(src, INF);
		}
		return ret;
	}
	
	void getmatch() {
		for (int i = 1; i <= ln; i++) {
			for (int e = head[l[i]]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (t != src && edge[e][FLOW] == 0) {
					match[l[i]] = t;
					match[t] = l[i];
					break;
				}
			}
		}
	}
}flow;
struct _Main {
	int head[MXN], edge[MXN << 1][2], eidx;
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	int mark[MXN];
	void domark(int nd) {
		if (mark[nd]) {
			return;
		}
		mark[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t] && t != match[nd]) {
				mark[t] = 1;
				domark(match[t]);
			}
		}
	}
	int n, m;
	char bel[MXN];
	_Main() {
		read(n); read(m);
		int a, b;
		flow.size = n + 2;
		flow.dst = n + 1;
		for (int i = 1; i <= n; i++) {
			read(bel[i]);
			if (bel[i] == 0) {
				flow.add(0, i, 1);
				l[++ln] = i;
			} else {
				flow.add(i, n + 1, 1);
				r[++rn] = i;
			}
		}
		for (int i = 1; i <= m; i++) {
			read(a); read(b);
			if (bel[a] == 1) swap(a, b);
			add(a, b);
			flow.add(a, b, 1);
		}
		int cnt = flow.run();
		printf("%d\n", cnt);
		flow.getmatch();
		for (int i = 1; i <= rn; i++) {
			if (!match[r[i]]) {
				domark(r[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (bel[i] == 0 && mark[i] || bel[i] == 1 && !mark[i]) {
				printf("%d ", i);
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
