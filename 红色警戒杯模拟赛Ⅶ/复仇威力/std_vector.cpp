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
typedef vector<int>::iterator it;
struct _Main {
	int n, L, R;
	int v[MXN];
	int ans[MXN];
	void init() {
		memset(ans + 1, 192, n * sizeof(int));
		memset(arr, 192, n * sizeof(int));
		memset(tag + 1, 192, n * sizeof(int));
	}
	
	_Main() {
		read(n); read(L); read(R);
		init();
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
		dnc(1);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
	int q[MXN], tag[MXN], qf[MXN], qh, qt;//1 ~ qt
	void calc1(int core) {//用祖先更新子孙
		fupdate(core);
		qh = 1; qt = 0;
		q[0] = core;
		tag[0] = 0;
		for (int i = 0; i <= qt; i++) {
			int nd = q[i];
			for (it e = head[nd].begin(); e != head[nd].end(); ++e) {
				int t = *e;
				if (!mark[t] && t != f[nd]) {
					q[++qt] = t;
					tag[qt] = tag[i] + v[t];
					qf[qt] = i;
				}
			}
		}
		subcalc(core);
		memset(tag, 192, (qt + 1) * sizeof(int));
		memset(arr, 192, (amx + 1) * sizeof(int));
		amx = 0;
	}
	void calc2(int core) {//用子孙更新祖先
		supdate(core, 0, 0);
		qh = 1; qt = 0;
		q[0] = core;
		tag[0] = 0;
		for (int i = 0; i <= qt; i++) {
			int t = f[q[i]];
			if (t && !mark[t]) {
				q[++qt] = t;
				tag[qt] = tag[i] + v[t];
				qf[qt] = i;
			}
		}
		subcalc(core);
		memset(tag, 192, (qt + 1) * sizeof(int));
		memset(arr, 192, (amx + 1) * sizeof(int));
		amx = 0;
	}
	void calc3(int core) {//更新core
		fupdate(core);
		supdate(core, 0, 0);
		for (int i = L - 1; i + 1 <= R && i <= amx; i++) {
			ans[core] = max(ans[core], arr[i]);
		}
		memset(arr, 192, (amx + 1) * sizeof(int));
		amx = 0;
	}
	
	void calcans(int core) {
		calc1(core);
		calc2(core);
		calc3(core);
	}
	int dep;
	void subcalc(int core) {
		dh = 0; dt = -1; aidx = amx;
		while (qh <= qt) {
			dep = abs(h[q[qh]] - h[core]) + 1;
			if (dep > R) break;
			push();
			pop();
			if (dh <= dt) {
				tag[qh] += arr[d[dh]];
			} else {
				tag[qh] = -INF - 1;//here
			}
			qh++;
		}
		for (int i = qh - 1; i >= 1; i--) {
			if (qf[i]) {
				tag[qf[i]] = max(tag[qf[i]], tag[i]);
			} else {
				ans[core] = max(ans[core], tag[i]);
			}
			ans[q[i]] = max(ans[q[i]], tag[i]);
		}
	}
	
	int d[MXN], dh, dt;
	void push() {
		while (aidx >= 0 && dep + aidx >= L) {
			while (dh <= dt && arr[aidx] >= arr[d[dt]]) {//神Tm弄成了 <= 
				dt--;
			}
			d[++dt] = aidx--;
		}
	}
	void pop() {
		while (dh <= dt && dep + d[dh] > R) {
			++dh;
		}
	}
	
	int arr[MXN], amx, aidx;
	void fupdate(int nd) {//向上
		arr[0] = v[nd];
		int pos = 1, sum = v[nd] + v[f[nd]];
		nd = f[nd];
		while (nd && !mark[nd]) {
			amx = max(amx, pos);
			arr[pos] = max(arr[pos], sum);
			nd = f[nd];
			sum += v[nd];
			++pos;
		}
	}
	void supdate(int nd, int dep, int sum) {
		sum += v[nd];
		arr[dep] = max(arr[dep], sum);
		amx = max(amx, dep);
		for (it e = head[nd].begin(); e != head[nd].end(); ++e) {
			int t = *e;
			if (!mark[t] && t != f[nd]) {
				supdate(t, dep + 1, sum);
			}
		}
	}
	
	char mark[MXN];
	void dnc(int nd) {
		mnval = INF;
		getsize(nd, 0);
		nd = cho;
		mark[nd] = 1;
		calcans(nd);
		getsize(nd, 0);
		for (it e = head[nd].begin(); e != head[nd].end(); ++e) {
			int t = *e;
			if (!mark[t]) {
				tot = size[t];
				dnc(t);
			}
		}
	}
	
	int size[MXN], mnval, cho, tot;
	void getsize(int nd, int fa) {
		size[nd] = 1;
		int mx = 0;
		for (it e = head[nd].begin(); e != head[nd].end(); ++e) {
			int t = *e;
			if (!mark[t] && t != fa) {
				getsize(t, nd);
				size[nd] += size[t];
				mx = max(mx, size[t]);
			}
		}
		mx = max(mx, tot - size[nd]);
		if (mx < mnval) {
			mnval = mx;
			cho = nd;
		}
	}
	
	int f[MXN], h[MXN];
	void dfs0(int nd, int fa) {
		f[nd] = fa;
		h[nd] = h[fa] + 1;
		for (it e = head[nd].begin(); e != head[nd].end(); ++e) {
			if (*e != fa) {
				dfs0(*e, nd);
			}
		}
	}
	vector<int> head[MXN];
	inline void add(int a, int b) {
		head[a].push_back(b);
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
