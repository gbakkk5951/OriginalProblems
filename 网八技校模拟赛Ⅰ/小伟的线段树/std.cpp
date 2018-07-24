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
struct Query {
	int l, r, id;
	bool operator < (const Query&b) const {
		return r < b.r;
	}
}q[MXN];
int arr[MXN];
int ans[MXN];
struct Node {
	int min, size;
};
struct Tree {
	Node node[1050000];
	void update(int nd) {
		node[nd].min = min(node[ls[nd]].min, node[rs[nd]].min);
		node[nd].size = node[ls[nd]].size + node[rs[nd]].size;
	}
	void build(int nd, int nl, int nr) {
		if (nl == nr) {
			node[nd].min = arr[nl];
			node[nd].size = 1;
			return;
		}
		int mid = nl + nr >> 1;
		build(ls[nd], nl, mid);
		build(rs[nd], mid + 1, nr);
		update(nd);
	}
	void erase(int nd, int nl, int nr, int rb, int v) {
		if (nl == nr) {
			node[nd].min = INF;
			node[nd].size = 0;
			return;
		}
		int mid = nl + nr >> 1;
		if (node[ls[nd]].min <= v) erase(ls[nd], nl, mid, rb, v);
		if (rb > mid && node[rs[nd]].min <= v) erase(rs[nd], mid + 1, nr, rb, v);
		update(nd);
	}
	int query(int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			return node[nd].size;
		}
		int mid = nl + nr >> 1;
		int ret = 0;
		if (l <= mid && node[ls[nd]].size) ret += query(ls[nd], nl, mid, l, r);
		if (r > mid && node[rs[nd]].size) ret += query(rs[nd], mid + 1, nr, l, r);
		return ret;
	}
}tree;
struct _Main {
	_Main() {
		int n, Qn, lst = 1;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
		}
		tree.build(1, 1, n);
		for (int Q = 1; Q <= Qn; Q++) {
			q[Q].id = Q;
			read(q[Q].l); read(q[Q].r);
		}
		sort(q + 1, q + Qn + 1);
		for (int i = 1; i <= Qn; i++) {
			while (lst < q[i].l) {
				++lst;
				if (tree.node[1].min <= arr[lst]) {
					tree.erase(1, 1, n, lst - 1, arr[lst]);
				}
			}
			ans[q[i].id] = tree.query(1, 1, n, q[i].l, q[i].r);
		}
		for (int i = 1; i <= Qn; i++) {
			printf("%d\n", ans[i]);
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
