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
struct Node {
	lld sum, mx;
	lld add;
	int asi;
	Node () {
		asi = INF;
	}
};
int n;
struct SegTree {
	Node node[270000];
	inline void add(int nd, int nl, int nr, int val) {
		node[nd].sum += (nr - nl + 1LL) * val;
		node[nd].mx += val;
		node[nd].add += val;
	}
	inline void asi(int nd, int nl, int nr, int val) {
		node[nd].sum = (nr - nl + 1LL) * val;
		node[nd].mx = val;
		node[nd].asi = val;
		node[nd].add = 0;
	}
	inline void push(int nd, int nl, int mid, int nr) {
		lld t;
		if ((t = node[nd].asi) != INF) {
			asi(ls[nd], nl, mid, t);
			asi(rs[nd], mid + 1, nr, t);
			node[nd].asi = INF;
		}
		if (t = node[nd].add) {
			add(ls[nd], nl, mid, t);
			add(rs[nd], mid + 1, nr, t);
			node[nd].add = 0;
		}
	}
	void update(int nd) {
		node[nd].sum = node[ls[nd]].sum + node[rs[nd]].sum;
		node[nd].mx = max(node[ls[nd]].mx, node[rs[nd]].mx);
	}
	void add(int nd, int nl, int nr, int l, int r, int val) {
		if (l <= nl && nr <= r) {
			add(nd, nl, nr, val);
			return;
		}
		int mid = nl + nr >> 1;
		push(nd, nl, mid, nr);
		if (l <= mid) add(ls[nd], nl, mid, l, r, val);
		if (r > mid) add(rs[nd], mid + 1, nr, l, r, val);
		update(nd);
	}
	void asi(int nd, int nl, int nr, int l, int r, int val) {
		if (l <= nl && nr <= r) {
			asi(nd, nl, nr, val);
			return;
		}
		int mid = nl + nr >> 1;
		push(nd, nl, mid, nr);
		if (l <= mid) asi(ls[nd], nl, mid, l, r, val);
		if (r > mid) asi(rs[nd], mid + 1, nr, l, r, val);
		update(nd);
	}
	lld mx(int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			return node[nd].mx;
		}
		int mid = nl + nr >> 1;
		lld ret = -LINF;
		push(nd, nl, mid, nr);
		if (l <= mid) ret = max(ret, mx(ls[nd], nl, mid, l, r));
		if (r > mid) ret = max(ret, mx(rs[nd], mid + 1, nr, l, r));
		return ret;
	}
	lld sum(int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			return node[nd].sum;
		}
		int mid = nl + nr >> 1;
		lld ret = 0;
		push(nd, nl, mid, nr);
		if (l <= mid) ret += sum(ls[nd], nl, mid, l, r);
		if (r > mid) ret += sum(rs[nd], mid + 1, nr, l, r);
		return ret;
	}
	void add(int l, int r, int val) {
		if (l > 0 && l <= r) add(1, 1, n, l, r, val);
	}
	void asi(int l, int r, int val) {
		if (l > 0 && l <= r) asi(1, 1, n, l, r, val);
	}
	lld mx(int l, int r) {
		if (l > 0 && l <= r) return mx(1, 1, n, l, r);
		return -LINF;
	}
	lld sum(int l, int r) {
		if (l > 0 && l <= r) return sum(1, 1, n, l, r);
		return 0;
	}
	void add(int nd, int val) {
		if (nd > 0) add(1, 1, n, nd, nd, val);
	}
	void asi(int nd, int val) {
		if (nd > 0) asi(1, 1, n, nd, nd, val);
	}
	lld mx(int nd) {
		if (nd > 0) return mx(1, 1, n, nd, nd);
		return -LINF;
	}
	lld sum(int nd) {
		if (nd > 0) return sum(1, 1, n, nd, nd);
		return 0;
	}
}tree;	


struct _Main {
	
	
	_Main() {
		int Qn;
		int op, a, b, v;
		read(n); read(Qn);
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		predfs(1, 0);
		getid(1, 1);
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {
				read(a); read(b); read(v);
				pathadd(a, b, v);
			} else
			if (op == 2) {
				read(a); read(b); read(v);
				wormadd(a, b, v);
			} else
			if (op == 3) {
				read(a); read(v);
				treeadd(a, v);
			} else
			if (op == 4) {
				read(a); read(b); read(v);
				pathasi(a, b, v);
			} else 
			if (op == 5) {
				read(a); read(b); read(v);
				wormasi(a, b, v);
			} else
			if (op == 6) {
				read(a); read(v);
				treeasi(a, v);
			} else
			if (op == 7) {
				read(a); read(b); 
				printf("%lld\n", pathmx(a, b));
			} else
			if (op == 8) {
				read(a); read(b);
				printf("%lld\n", wormmx(a, b));
			} else
			if (op == 9) {
				read(a);
				printf("%lld\n", treemx(a));
			} else 
			if (op == 10) {
				read(a); read(b);
				printf("%lld\n", pathsum(a, b));
			} else
			if (op == 11) {
				read(a); read(b);
				printf("%lld\n", wormsum(a, b));
			} else 
			if (op == 12) {
				read(a);
				printf("%lld\n", treesum(a, v));
			}
		}
	}
	int wl[3], wr[3], wcnt;
	int arr[4];
	void white(int l, int r, int la, int lb) {
		int aidx = 0;
		if (la >= l && la <= r) arr[++aidx] = la;
		if (lb >= l && lb <= r) arr[++aidx] = lb;
		arr[++aidx] = l - 1;
		arr[++aidx] = r + 1;
		sort(arr, arr + 4);
		aidx = unique(arr, arr + 4) - arr;
		for (int i = 0; i < aidx - 1; i++) {
			wl[wcnt] = arr[i] + 1;
			wr[wcnt] = arr[i + 1] - 1;
			++wcnt;
		}
		return;
	}
	void wormadd(int a, int b, int v) {
		int la = 0, lb = 0;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) {
				swap(a, b); swap(la, lb);
			}
			white(ml[top[a]], mr[a], la, lb);
			for (int i = 0; i < wcnt; i++) {
				tree.add(wl[i], wr[i], v);
			}
			tree.add(nid[son[a]], v);
			la = nid[top[a]];
			a = f[top[a]];
		}
		if (h[a] < h[b]) {
			swap(a, b); 
		}
		white(ml[b], mr[a], la, lb);
		for (int i = 0; i < wcnt; i++) {
			tree.add(wl[i], wr[i], v);
		}
		tree.add(nid[son[a]], v);
		tree.add(nid[f[b]], v);
	}
	void wormasi(int a, int b, int v) {
		int la = 0, lb = 0;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) {
				swap(a, b); swap(la, lb);
			}
			white(ml[top[a]], mr[a], la, lb);
			for (int i = 0; i < wcnt; i++) {
				tree.asi(wl[i], wr[i], v);
			}
			tree.asi(nid[son[a]], v);
			la = nid[top[a]];
			a = f[top[a]];
		}
		if (h[a] < h[b]) {
			swap(a, b); 
		}
		white(ml[b], mr[a], la, lb);
		for (int i = 0; i < wcnt; i++) {
			tree.asi(wl[i], wr[i], v);
		}
		tree.asi(nid[son[a]], v);
		tree.asi(nid[f[b]], v);
	}
	lld wormmx(int a, int b) {
		lld ret = -LINF;
		int la = 0, lb = 0;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) {
				swap(a, b); swap(la, lb);
			}
			white(ml[top[a]], mr[a], la, lb);
			for (int i = 0; i < wcnt; i++) {
				ret = max(ret, tree.mx(wl[i], wr[i]));
			}
			ret = max(ret, tree.mx(nid[son[a]]));
			la = nid[top[a]];
			a = f[top[a]];
		}
		if (h[a] < h[b]) {
			swap(a, b); 
		}
		white(ml[b], mr[a], la, lb);
		for (int i = 0; i < wcnt; i++) {
			ret = max(ret, tree.mx(wl[i], wr[i]));
		}
		ret = max(ret, tree.mx(nid[son[a]]));
		ret = max(ret, tree.mx(nid[f[b]]));
	}
	lld wormsum(int a, int b) {
		lld ret = 0;
		int la = 0, lb = 0;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) {
				swap(a, b); swap(la, lb);
			}
			white(ml[top[a]], mr[a], la, lb);
			for (int i = 0; i < wcnt; i++) {
				ret += tree.sum(wl[i], wr[i]);
			}
			ret += tree.sum(nid[son[a]]);
			la = nid[top[a]];
			a = f[top[a]];
		}
		if (h[a] < h[b]) {
			swap(a, b); 
		}
		white(ml[b], mr[a], la, lb);
		for (int i = 0; i < wcnt; i++) {
			ret += tree.sum(wl[i], wr[i]);
		}
		ret += tree.sum(nid[son[a]]);
		ret += tree.sum(nid[f[b]]);
	}
	
	
	void treeadd(int a, int v) {
		if (top[a] == a) {
			tree.add(nid[a], v);
			tree.add(ml[a], mr[a], v);
			tree.add(sl[a], sr[a], v);
			a = son[a];
		}
		if (a == 0) return;
		tree.add(nid[a], cr[top[a]], v);
		tree.add(ml[a], mr[oid[cr[top[a]]]], v);
		tree.add(sl[a], sr[oid[cr[top[a]]]], v);
	}
	void treeasi(int a, int v) {
		if (top[a] == a) {
			tree.asi(nid[a], v);
			tree.asi(ml[a], mr[a], v);
			tree.asi(sl[a], sr[a], v);
			a = son[a];
		}
		if (a == 0) return;
		tree.asi(nid[a], cr[top[a]], v);
		tree.asi(ml[a], mr[oid[cr[top[a]]]], v);
		tree.asi(sl[a], sr[oid[cr[top[a]]]], v);
	}
	lld treemx(int a) {
		lld ret = -LINF;
		if (top[a] == a) {
			ret = max(ret, tree.mx(nid[a]));
			ret = max(ret, tree.mx(ml[a], mr[a]));
			ret = max(ret, tree.mx(sl[a], sr[a]));
			a = son[a];
		}
		if (a == 0) return ret;
		ret = max(ret, tree.mx(nid[a], cr[top[a]]));
		ret = max(ret, tree.mx(ml[a], mr[oid[cr[top[a]]]]));
		ret = max(ret, tree.mx(sl[a], sr[oid[cr[top[a]]]]));
		return ret;
	}
	lld treesum(int a, int v) {
		lld ret = 0;
		if (top[a] == a) {
			ret += tree.sum(nid[a]);
			ret += tree.sum(ml[a], mr[a]);
			ret += tree.sum(sl[a], sr[a]);
			a = son[a];
		}
		if (a == 0) return ret;
		ret += tree.sum(nid[a], cr[top[a]]);
		ret += tree.sum(ml[a], mr[oid[cr[top[a]]]]);
		ret += tree.sum(sl[a], sr[oid[cr[top[a]]]]);
		return ret;
	}
	void pathadd(int a, int b, int v) {
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) swap(a, b);
			if (a != top[a]) {
				tree.add(nid[son[top[a]]], nid[a], v);
			}
			a = top[a];
			tree.add(nid[a], v);
			a = f[a];
		}
		if (a == b) {
			tree.add(nid[a], v);
			return;
		}
		if (h[a] < h[b]) {
			swap(a, b);
		}
		if (b == top[b]) {
			tree.add(nid[b], v);
			b = son[b];
		}
		tree.add(nid[b], nid[a], v);
	}
	void pathasi(int a, int b, int v) {
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) swap(a, b);
			if (a != top[a]) {
				tree.asi(nid[son[top[a]]], nid[a], v);
			}
			a = top[a];
			tree.asi(nid[a], v);
			a = f[a];
		}
		if (a == b) {
			tree.asi(nid[a], v);
			return;
		}
		if (h[a] < h[b]) {
			swap(a, b);
		}
		if (b == top[b]) {
			tree.asi(nid[b], v);
			b = son[b];
		}
		tree.asi(nid[b], nid[a], v);
	}
	lld pathmx(int a, int b) {
		lld ret = -LINF;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) swap(a, b);
			if (a != top[a]) {
				ret = max(ret, tree.mx(nid[son[top[a]]], nid[a]));
			}
			a = top[a];
			ret = max(ret, tree.mx(nid[a]));
			a = f[a];
		}
		if (a == b) {
			ret = max(ret, tree.mx(nid[a]));
			return ret;
		}
		if (h[a] < h[b]) {
			swap(a, b);
		}
		if (b == top[b]) {
			ret = max(ret, tree.mx(nid[b]));
			b = son[b];
		}
		ret = max(ret, tree.mx(nid[b], nid[a]));
		return ret;
	}
	
	lld pathsum(int a, int b) {
		lld ret = 0;
		while (top[a] != top[b]) {
			if (h[top[a]] < h[top[b]]) swap(a, b);
			if (a != top[a]) {
				ret += tree.sum(nid[son[top[a]]], nid[a]);
			}
			a = top[a];
			ret += tree.sum(nid[a]);
			a = f[a];
		}
		if (a == b) {
			ret += tree.sum(nid[a]);
			return ret;
		}
		if (h[a] < h[b]) {
			swap(a, b);
		}
		if (b == top[b]) {
			ret += tree.sum(nid[b]);
			b = son[b];
		}
		ret += tree.sum(nid[b], nid[a]);
		return ret;
	}
	
	int ml[MXN], mr[MXN];//毛的左，毛的右
	int sl[MXN], sr[MXN];//毛的子树（不含顶）的左右
	int cl[MXN], cr[MXN];//不含top的重链左右区间, 记在top处
	int top[MXN], oid[MXN], nid[MXN], idx;
	void getid(int nd, int top) {
		if (!nid[nd]) oid[nid[nd] = ++idx] = nd;
		this->top[nd] = top;
		if (top != nd) {//非top只标号重儿子
			if (son[nd]) getid(son[nd], top);
			return;
		}
		cl[nd] = idx + 1;
		if (son[nd]) getid(son[nd], top);
		cr[nd] = idx;
		
		////标记毛边
		ml[nd] = idx + 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (!nid[t]) {
				oid[nid[t] = ++idx] = t;//忘了标记oid了
			}
		}
		mr[nd] = idx;
		
		for (int i = cl[nd]; i <= cr[nd]; i++) {
			ml[oid[i]] = idx + 1;
			for (int e = head[oid[i]]; e; e = edge[e][NXT]) {
				int t = edge[e][DST];
				if (!nid[t]) {
					oid[nid[t] = ++idx] = t;
				}
			}
			mr[oid[i]] = idx;
		}
		////标记毛子树
		sl[nd] = idx + 1;
		for (int i = ml[nd]; i <= mr[nd]; i++) {
			getid(oid[i], oid[i]);
		}
		sr[nd] = idx;
		
		for (int i = cl[nd]; i <= cr[nd]; i++) {
			sl[oid[i]] = idx + 1;
			for (int j = ml[oid[i]]; j <= mr[oid[i]]; j++) {
				getid(oid[j], oid[j]);
			}
			sr[oid[i]] = idx;
		}
	}
	int size[MXN], h[MXN], f[MXN], son[MXN];
	void predfs(int nd, int fa) {
		f[nd] = fa;
		h[nd] = h[fa] + 1;
		size[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				predfs(t, nd);
				size[nd] += size[t];
				if (size[t] > size[son[nd]]) {
					son[nd] = t;
				}
			}
		}
	}
	int head[MXN], edge[MXN << 1][2], eidx;
	void inline add(int a, int b) {
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
