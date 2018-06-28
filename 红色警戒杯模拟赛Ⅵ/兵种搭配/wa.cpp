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
	int size, src, dst;
	int head[MXN], lay[MXN], now[MXN];
	lld edge[(MXN << 1) + MXM][3];
	int eidx;
	Dinic() {
		init();
	}
	void init() {
		eidx = 1;
		memset(head, 0, size * sizeof(int));
	}
	inline void dir_add(int a, int b, lld c) {
		++eidx;
		edge[eidx][DST] = b;
		edge[eidx][FLOW] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	inline void add(int a, int b, lld c) {
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
			//printf("nd = %d\n", nd);
			for (int e = head[nd]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (!lay[t] && edge[e][FLOW]) {
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
				t = getflow(t, min(edge[e][FLOW], rem));
				if (t) {
					rem -= t;
					edge[e][FLOW] -= t;
					edge[e ^ 1][FLOW] += t;
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
//		printf("run\n");
		lld ret = 0;
		while (getlay()) {
			memcpy(now, head, size * sizeof(int));
			ret += getflow(src, LINF);
		}
//		printf("ret %lld\n", ret);
		return ret;
	}
}flow;
struct _Main {
	int thead[6][MXN], edge[MXM][2];
	int head[MXN];//1号的边
	int size[MXN], cnt[MXN], mark[MXN];
	int eidx;
	int flowid[MXN];
	int flowidx;//流id 为了防止memcpyTLE
	int cho, val;
	int tot;
	lld ans;
	int a[MXN];
	int n, m;
	void getsize(int nd, int fa) {
		size[nd] = 1;
		int mx = 0;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa && !mark[t]) {
				getsize(t, nd);
				size[nd] += size[t];
				mx = max(mx, size[t]);
			}
		}
		mx = max(mx, tot - size[nd]);
		if (mx < val) {
			cho = nd; 
			val = mx;
//			mx = val;// 卡下这个
		}
	}
	void setcnt(int nd, int fa, int val) {
		cnt[nd] = val;
//		printf("set cnt %d = %d\n", nd, cnt[nd]);
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa && !mark[t]) {
				setcnt(t, nd, val);
			}
		}
	}
	lld build(int tid, int nd, int fa) {
		lld ret = 0;
		if (tid == 1) {
			cnt[nd] = -1;
			flowid[nd] = ++flowidx;
			if (a[nd] < 0) {
				flow.add(flowid[nd], flow.dst, -a[nd]);
			} else {
				ret += a[nd];
				flow.add(flow.src, flowid[nd], a[nd]);
			}
		}
		if (fa) {
			flow.add(flowid[nd], flowid[fa], LINF);
		}
		for (int e = thead[tid][nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa && (tid == 1 && cnt[t] == m || cnt[t] == -1)) {//assert !mark[t]
//				printf("cnt %d = %d\n", t, cnt[t]);
				ret += build(tid, t, nd);//nd to be fa
			}
		}
		return ret;
	}
	void getcnt(int tid, int nd) {
		++cnt[nd];
		for (int e = thead[tid][nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (cnt[t] == tid - 1) {//assert t != fa && !mark[t]
				getcnt(tid, t);
			}
		}
	}
	void solve(int nd, int tot) {
		val = INF;
		this->tot = tot;
		getsize(nd, 0);
		nd = cho;
		mark[nd] = 1;
		setcnt(nd, 0, 1);
		for (int i = 2; i <= m; i++) {
			getcnt(i, nd);
		}
		flow.dst = tot + 1;
		flow.size = tot + 2;
		flow.init();
		flowidx = 0;
		lld ans = build(1, nd, 0);
		for (int i = 2; i <= m; i++) {
			build(i, nd, 0);
		}
		ans -= flow.run();
		this->ans = max(this->ans, ans);
		setcnt(nd, 0, 0);
		getsize(nd, 0);
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t]) {
				solve(t, size[t]);
			}
		}
	}
	void add(int tid, int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = thead[tid][a];
		thead[tid][a] = eidx;
		if (tid == 1) head[a] = eidx;
	}
	_Main() {
		read(n); read(m);
		int u, v;
		for (int i = 1; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n - 1; j++) {
				read(u); read(v);
				add(i, u, v); add(i, v, u);
			}
		}
		solve(1, n);
		printf("%lld", ans);
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
