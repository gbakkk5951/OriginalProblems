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
#include <ctime>
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
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3, ID = 3;
const int MXN = 2 * (3e5 + 10);
struct _Main {
	int val[MXN >> 1];
	int n, L, R;
	int size[MXN];
	int mnsize, cho;
	char mark[MXN << 1];
	int tot;
	void getsize(int nd, int fa = 0) {
		size[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[e] && t != fa) {
				getsize(t, nd);
				size[nd] += size[t];
				int v = max(size[t], tot - size[t]);
				if (v < mnsize) {
					mnsize = v;
					cho = e;
				}
			}
		}
	}
	int arr[MXN >> 1];
	int umx;
	void putinarr(int nd, int fa, int h, int sum = 0) {
		umx = max(umx, h);
		if (nd <= n) {
			arr[h] = max(arr[h], sum + val[nd]);
		}
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[e] && t != fa) {
				putinarr(t, nd, h + (edge[e][ID] > 0), sum + edge[e][VAL]);
			}
		}
	}
	int dep;
	int d[MXN >> 1], dh, dt, aidx;
	
	void dpush() {
		while (dep + aidx >= L && aidx >= 0) {
			while (dh <= dt && arr[d[dt]] <= arr[aidx]) {
				dt--;
			}
			d[++dt] = aidx--;
		}
	}
	void dpop() {
		while (dh <= dt && d[dh] + dep > R) {
			++dh;
		}
	}
	int q[MXN];
	int f[MXN], fe[MXN], h[MXN];
	int sum[MXN], tag[MXN], ea[MXN >> 1];
	void push(int nd, int f, int fe, int h, int sum) {
		this->f[nd] = f;
		this->fe[nd] = fe;
		this->h[nd] = h;
		this->sum[nd] = sum;
		tag[nd] = -INF - 1;
	}
	int out[MXN], oidx;
	void calcans(int core) {
		int qh = MXN >> 1, qt = qh - 1;
		q[++qt] = core;
		dh = 0, dt = -1, aidx = umx;
		oidx = 0;
		while (qh <= qt) {
			int nd = q[qh++];
			if (h[nd] > R) break;
			out[++oidx] = nd;
			if (nd <= n) {
				dep = h[nd];
				dpush();
				dpop();
				if (dh <= dt) {
					tag[nd] = sum[nd] + val[nd] + arr[d[dh]];
				}
			}
			for (int e = head[nd]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (!mark[e] && t != f[nd]) {
					if (edge[e][ID]) {
						q[++qt] = t;
					} else {
						q[--qh] = t;
					}
					push(t, nd, edge[e][ID], h[nd] + (edge[e][ID] > 0), sum[nd] + edge[e][VAL]);
				}
			}
		}
		for (int i = oidx; i >= 1; i--) {
			int nd = out[i];
			ea[fe[nd]] = max(ea[fe[nd]], tag[nd]);
			tag[f[nd]] = max(tag[f[nd]], tag[nd]);
		}
	}
	void dnc(int nd) {
		int a = 0, b = 0;
		mnsize = INF;
		getsize(nd);
		for (int I = 0; I < 2; I++) {
			mark[cho] = 1;
			a = edge[cho][DST];
			swap(a, b); cho ^= 1;
		}
		for (int I = 0; I < 2; I++) {
			putinarr(a, b, 0, 0);
			push(b, a, edge[cho][ID], edge[cho][ID] > 0, edge[cho][VAL]);
			calcans(b);
			memset(arr, 192, (umx + 1) * sizeof(int));
			umx = 0;//forgot
			swap(a, b); 
		}
		for (int I = 0; I < 2; I++) {
			getsize(a, b);
			if (size[a] > 1) {
				tot = size[a];
				dnc(a);
			}
			swap(a, b);	
		}
	}
	int oa[MXN >> 1], ob[MXN >> 1];
	_Main() {
		eidx = 1;
		int a, b;
		read(n); read(L); read(R);
		memset(arr, 192, n * sizeof(int));//forgot
		for (int i = 1; i <= n; i++) {
			read(val[i]); 
		}
		if (R == 0) {
			memcpy(ans + 1, val + 1, n * sizeof(int));
			goto EndMain;
			return;
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			oadd(a, b, val[a] + val[b], i); 
			oadd(b, a, val[b] + val[a], i);
			oa[i] = a; ob[i] = b;
		}
		
		rebuild(1, 0);
		tot = 2 * n - 1;
		memset(ea + 1, 192, n * sizeof(int));
		dnc(1);
		if (L == 0) {
			memcpy(ans + 1, val + 1, n * sizeof(int));
		} else {
			memset(ans + 1, 192, n * sizeof(int));
		}
		for (int i = 1; i <= n - 1; i++) {
			ans[oa[i]] = max(ans[oa[i]], ea[i] >> 1);
			ans[ob[i]] = max(ans[ob[i]], ea[i] >> 1);
		}
		EndMain:
		for (int i = 1; i <= n; i++) {
			if (ans[i] < -3e8) {
				printf("%d\n", -INF - 1);
			} else {
				printf("%d\n", ans[i]);
			}
		}
	}
	int ans[MXN >> 1];
	void rebuild(int nd, int fa) {
		int lst = nd;
		for (int e = oh[nd]; e; e = oe[e][NXT]) {
			int t = oe[e][DST];
			if (t != fa) {
				link(lst, t + n, 0, 0);
				link(t + n, t, oe[e][VAL], oe[e][ID]);
				lst = t + n;
				rebuild(t, nd);
			}
		}
	}
	int oh[MXN >> 1], oe[MXN][4], ox;
	void oadd(int a, int b, int c, int d) {
		ox++;
		oe[ox][DST] = b;
		oe[ox][VAL] = c;
		oe[ox][ID] = d;
		oe[ox][NXT] = oh[a];
		oh[a] = ox;
	}
	int head[MXN], edge[MXN << 1][4], eidx;
	void link(int a, int b, int c, int d) {
		add(a, b, c, d); add(b, a, c, d);
	}
	void add(int a, int b, int c, int d) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][VAL] = c;
		edge[eidx][ID] = d;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
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
