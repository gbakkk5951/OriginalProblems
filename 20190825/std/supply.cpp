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
const int MXN = 3e5;
const int P = 1, C = 0;
int n;
struct Node {
	lld cr, ct, pr, pt;
}node[(int)1.05e6];
int qt, q[50];
struct Tree {
	Node merge(Node l, Node r) {
		lld ln, rn, n2;
		ln = min(l.cr, r.pr);
		rn = min(r.cr, l.pr);
		l.cr -= ln;
		r.pr -= ln;
		l.pr -= rn;
		r.cr -= rn;
		if (l.pr && l.cr) {
			n2 = min(l.cr, min(r.ct - rn, l.pr));
			l.cr -= n2;
			l.pr -= n2;
		} else
		if (r.cr && r.pr) {
			n2 = min(r.cr, min(l.ct - ln, r.pr));
			r.cr -= n2;
			r.pr -= n2;
		}
		l.cr += r.cr;
		l.ct += r.ct;
		l.pr += r.pr;
		l.pt += r.pt;
		return l;
	}
	void change(int nd, int nl, int nr, int pos, int val, int type) {
		if (nl == nr) {
			if (type == C) {
				node[nd].cr = node[nd].ct = val;
			} else {
				node[nd].pr = node[nd].pt = val;
			}
			return;
		}
		int mid = nl + nr >> 1;
		if (pos <= mid) change(ls[nd], nl, mid, pos, val, type);
		else change(rs[nd], mid + 1, nr, pos, val, type);
		node[nd] = merge(node[ls[nd]], node[rs[nd]]);
	}
	void build(int nd, int nl, int nr) {
		if (nl == nr) {
			read(node[nd].cr);
			node[nd].ct = node[nd].cr;
			read(node[nd].pr);
			node[nd].pt = node[nd].pr;
			return;
		}
		int mid = nl + nr >> 1;
		build(ls[nd], nl, mid);
		build(rs[nd], mid + 1, nr);
		node[nd] = merge(node[ls[nd]], node[rs[nd]]);
	}
	void find(int nd, int nl, int nr, int l, int r) {
		if (l <= nl && nr <= r) {
			q[++qt] = nd;
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) find(ls[nd], nl, mid, l, r);
		if (r > mid) find(rs[nd], mid + 1, nr, l, r);
	}
}tree;

struct _Main {
	_Main() {
		freopen("supply.in", "r", stdin);
		freopen("supply.out", "w", stdout);
		Node tmp;
		int Qn;
		read(n); read(Qn);
		tree.build(1, 1, n);
		int op, x, c, p, l, r;
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); 
			if (op == 1) {
				read(x); read(c);
				tree.change(1, 1, n, x, c, C);
			} else
			if (op == 2) {
				read(x); read(p);
				tree.change(1, 1, n, x, p, P);
			} else {
				read(l); read(r);
				qt = 0;
				tree.find(1, 1, n, l, r);
				tmp = node[q[1]];
				for (int i = 2; i <= qt; i++) {
					tmp = tree.merge(tmp, node[q[i]]);
				}
				printf("%lld\n", tmp.pt - tmp.pr);
			}
		}
		fclose(stdout);
	}
}std;
}
