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
const int MXN = 3e6 + 10;
struct Node {
	lld lmax, rmax, sum, lmin, rmin;
}node[(int)2.1e6], null;
int b[MXN];
struct Tree {
	void merge(Node &ret, const Node &l, const Node &r) {
		ret.lmax = max(l.lmax, l.sum + r.lmax);
		ret.rmax = max(r.rmax, r.sum + l.rmax);
		ret.lmin = min(l.lmin, l.sum + r.lmin);
		ret.rmin = min(r.rmin, r.sum + l.rmin);
		ret.sum = l.sum + r.sum;
	}
	void lmaxmerge(Node &ret, const Node &l, const Node &r) {
		ret.lmax = max(l.lmax, l.sum + r.lmax);
		ret.sum = l.sum + r.sum;
	}
	void lminmerge(Node &ret, const Node &l, const Node &r) {
		ret.lmin = min(l.lmin, l.sum + r.lmin);
		ret.sum = l.sum + r.sum;
	}
	void rmaxmerge(Node &ret, const Node &l, const Node &r) {
		ret.rmax = max(r.rmax, r.sum + l.rmax);
		ret.sum = l.sum + r.sum;
	}
	void rminmerge(Node &ret, const Node &l, const Node &r) {
		ret.rmin = min(r.rmin, r.sum + l.rmin);
		ret.sum = l.sum + r.sum;
	}
	void build(int nd, int nl, int nr) {
		if (nl == nr) {
			node[nd].lmax = node[nd].rmax = max(0, b[nl]);
			node[nd].lmin = node[nd].rmin = min(0, b[nl]);
			node[nd].sum = b[nl];
			return;
		}
		int mid = nl + nr >> 1;
		build(ls[nd], nl, mid);
		build(rs[nd], mid + 1, nr);
		merge(node[nd], node[ls[nd]], node[rs[nd]]);
	}
	void lmaxquery(Node &ret, int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			lmaxmerge(ret, ret, node[nd]);
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) lmaxquery(ret, ls[nd], nl, mid, l, r);
		if (r > mid) lmaxquery(ret, rs[nd], mid + 1, nr, l, r);
	}
	void lminquery(Node &ret, int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			lminmerge(ret, ret, node[nd]);
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) lminquery(ret, ls[nd], nl, mid, l, r);
		if (r > mid) lminquery(ret, rs[nd], mid + 1, nr, l, r);
	}
	void rmaxquery(Node &ret, int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			rmaxmerge(ret, ret, node[nd]);
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) rmaxquery(ret, ls[nd], nl, mid, l, r);
		if (r > mid) rmaxquery(ret, rs[nd], mid + 1, nr, l, r);
	}
	void rminquery(Node &ret, int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			rminmerge(ret, ret, node[nd]);
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) rminquery(ret, ls[nd], nl, mid, l, r);
		if (r > mid) rminquery(ret, rs[nd], mid + 1, nr, l, r);
	}
}tree;

struct _Main {

	int l[MXN], r[MXN];
	lld ans = -LINF;
	int arr[MXN];
	int stk[MXN], top;
	int n;
	void getrange() {
		stk[++top] = 0;
		for (int i = 1; i <= n + 1; i++) {
			while (arr[i] < arr[stk[top]]) {
				r[stk[top]] = i - 1;
				--top;
			}
			l[i] = stk[top] + 1;
			stk[++top] = i;
		}
	}
	lld getmax(int l, int mid, int r) {
		Node nd;
		lld ret = b[mid];
		if (l < mid) {
			nd = null;
			tree.rmaxquery(nd, 1, 1, n, l, mid - 1);
			ret += nd.rmax;
		}
		if (r > mid) {
			nd = null;
			tree.lmaxquery(nd, 1, 1, n, mid + 1, r);
			ret += nd.lmax;
		}
		return ret;
	}
	lld getmin(int l, int mid, int r) {
		Node nd;
		lld ret = b[mid];
		if (l < mid) {
			nd = null;
			tree.rminquery(nd, 1, 1, n, l, mid - 1);
			ret += nd.rmin;
		}
		if (r > mid) {
			nd = null;
			tree.lminquery(nd, 1, 1, n, mid + 1, r);
			ret += nd.lmin;
		}
		return ret;
		
	}
	_Main() {
		freopen("shortage.in", "r", stdin);
		freopen("shortage.out", "w", stdout);
		read(n);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
		}
		arr[n + 1] = -INF;
		arr[0] = -INF - 1;
		getrange();
		for (int i = 1; i <= n; i++) {
			read(b[i]);
		}
		tree.build(1, 1, n);
		for (int i = 1; i <= n; i++) {
			if (arr[i] < 0) {
				ans = max(ans, arr[i] * getmin(l[i], i, r[i]));
			} else
			if (arr[i] > 0) {
				ans = max(ans, arr[i] * getmax(l[i], i, r[i]));
			} else {
				ans = max(ans, 0LL);
			}
		}
		printf("%lld", ans);
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
