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
const int MXN = 5e5 + 10;
struct _Main {
	int ans[MXN], size[MXN];
	int v[MXN];
	int n, L, R;
	int f[MXN];
	int q[MXN], qh, qt;
	int umx;//向上最长长度
	int arr[MXN];
	char mark[MXN];
	int cho, choval, tot;
	void getsize(int nd, int fa) {
		size[nd] = 1;
		int mx = 0;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa && !mark[t]) {
				getsize(t, nd);
				mx = max(mx, size[t]);
				size[nd] += size[t];
			}
		}
		mx = max(mx, tot - size[nd]);
		if (mx < choval) {//差点弄成yun子节点了 // 又改成了0号结点2333
			choval = mx;
			cho = nd;
		}
	}
	int tag[MXN];
	char vis[MXN];
	int qval[MXN];
	int d[MXN], dh, dt;
	int aidx;
	int h[MXN];
	int qf[MXN];
	void calc(int core) {//之前需要将相应的子树顶部推入队列别弄Core
		aidx = umx;
		dt = -1, dh = 0;
		qh = 1;
		while (qh <= qt) {
			int nd = q[qh];
			int dep = abs(h[nd] - h[core]) + 1;
			if (dep > R) {
				break;
			}
			while (aidx >= 0 && dep + aidx >= L) {
				while (dt >= dh && arr[aidx] > arr[d[dt]]) {
					--dt;
				}
				d[++dt] = aidx--;
			}
			while (dep + d[dh] > R) {
				++dh;
			}
			int ov = qval[qh];
			if (dt >= dh) {
				qval[qh] = qval[qh] + arr[d[dh]];
//				printf("qval %d = %d\n", nd, qval[qh]);
			} else {
				qval[qh] = -INF - 1;//this is important
			}
			for (int e = head[nd]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (!mark[t] && !vis[t]) {
					q[++qt] = t;
					qval[qt] = ov + v[t];
					qf[qt] = qh;
				}
			}
			vis[nd] = 1;
			qh++;
		}
		for (int i = qh - 1; i >= 1; i--) {
			int nd = q[i];
			printf("ans %d = max(%d)\n", nd, qval[i]);
			ans[nd] = max(qval[i], ans[nd]);
			if (int fa = qf[i]) {
				qval[fa] = max(qval[fa], qval[i]);
			} else {
				printf("ans core %d = max(%d)\n", core, qval[i]);
				ans[core] = max(ans[core], qval[i]);
			}
			vis[nd] = 0;
		}
	}
	void update(int nd, int pos, int sum, int fa) {
		sum += v[nd];
		umx = max(umx, pos);
		arr[pos] = max(arr[pos], sum);
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t] && t != fa) {
				update(t, pos + 1, sum, nd);
			}
		}
	}
	void solve(int nd) {
		choval = INF;
		getsize(nd, 0);
		nd = cho;
		mark[nd] = 1;
		printf("root = %d\n", nd);
		//单点
		if (L == 1) ans[nd] = max(ans[nd], v[nd]);
		
		//用祖先更新子孙
		umx = 0;//Don't Forget Esto
		arr[0] = v[nd];
		if (f[nd] && !mark[f[nd]]) {
			update(f[nd], 1, v[nd], nd);
		}
		qt = 0;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t] && t != f[nd]) {
				q[++qt] = t;
				qval[qt] = v[t];
				qf[qt] = 0;
			}
		}
		calc(nd);
		memset(arr + 1, 192, umx * sizeof(int));
		printf("clear\n");
		//用子孙更新祖先
		umx = 0;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t] && t != f[nd]) {
				update(t, 1, v[nd], nd);
			}
		}
		qt = 0;
		if (f[nd] && !mark[f[nd]]) {
			q[++qt] = f[nd];
			qval[qt] = v[f[nd]];
			qf[qt] = 0;
		}
		calc(nd);
		memset(arr + 1, 192, umx * sizeof(int));
		printf("clear\n");
		//更新Core
		umx = 0;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t]) {
				update(t, 1, v[nd], nd);
			}
		}
		for (int i = L - 1; i + 1 <= R && i <= umx; i++) {//Not i + 1 <= umx
			ans[nd] = max(ans[nd], arr[i]);
			printf("udp core ans %d = max %d\n", nd, arr[i]);
		}
		memset(arr + 1, 192, umx * sizeof(int));
		//递归子树
		
		getsize(nd, 0);
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!mark[t]) {
				tot = size[t];
				solve(t);
			}
		}
	}
	
	void dfs0(int nd, int fa) {
		h[nd] = h[fa] + 1;
		f[nd] = fa;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				dfs0(t, nd);
			}
		}
	}
	
	_Main() {
		read(n); read(L); read(R);
		memset(ans + 1, 192, n * sizeof(int));
		memset(arr + 1, 192, n * sizeof(int));
		for (int i = 1; i <= n; i++) {
			read(v[i]);
		}
		int a, b;
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		dfs0(1, 0);
		tot = n;
		solve(1);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
	
	int head[MXN], edge[MXN << 1][2], eidx; 
	inline void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
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
