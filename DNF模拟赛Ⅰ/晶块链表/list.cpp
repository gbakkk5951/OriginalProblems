using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
namespace OI {
typedef long long lld;
const int MXN = 500005;
int cost[MXN], kind[MXN];
struct LS {
	int operator [] (int a) {
		return a << 1;
	}	
}ls;
struct RS {
	int operator [] (int a) {
		return a << 1 | 1;
	}	
}rs;
class SegTree {
public:
	int node[1050000];
	void build(int nd, int nl, int nr) {
		if (nl == nr) {
			node[nd] = kind[nl];
			return;
		}
		int mid = nl + nr >> 1;
		build(ls[nd], nl, mid);
		build(rs[nd], mid + 1, nr);
		node[nd] = (node[ls[nd]] == node[rs[nd]]) ? node[ls[nd]] : 0;
	}
	lld sum;
	lld operate (int nd, int nl, int nr, int l, int r, int c) {
		lld ret = 0;
		if (l <= nl && nr <= r && node[nd]) {
			ret = abs(cost[c] - cost[node[nd]]) * (nr - nl + 1LL);
			node[nd] = c;
			return ret;
		}
		int mid = nl + nr >> 1;
		if (node[nd]) {
			node[ls[nd]] = node[rs[nd]] = node[nd];
		}
		if (l <= mid) {
			ret += operate(ls[nd], nl, mid, l, r, c);
		}
		if (mid < r) {
			ret += operate(rs[nd], mid + 1, nr, l, r, c);
		}
		node[nd] = (node[ls[nd]] == node[rs[nd]]) ? node[ls[nd]] : 0;
		return ret;
	}
	
}tree;


struct _Main {
	_Main() {
//		freopen("list0.in", "r", stdin);
		int n, K, Qn;
		int op, l, r, c, e;
		read(n); read(K); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(kind[i]);
		}
		tree.build(1, 1, n);
		for (int i = 1; i <= K; i++) {
			read(cost[i]);
		}
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 0) {
				read(l); read(r); read(c);
				printf("%lld\n", tree.operate(1, 1, n, l, r, c));
			} else {
				read(c); read(e);
				cost[c] = e;
			}
		}
	}
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}
}list;
}
