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
inline int lb(int a) {
	return a & (-a);
}
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
const int MXN = 1e6 + 10;
int n, m;
int** data;
struct Node {
	int tag, val;
};	
struct Tree {
	Node **node;
	int *tag;
	int getsize(int n) {
		if (n == 1) return 1;		
		int nd = 1, l = 1, r = n, mid;
		do {
			mid = l + r >> 1;
			if (r - mid > mid - l + 1) {
				l = mid + 1;
			} else {
				r = mid;
			}
			nd = rs[nd];
		} while (l != r);
//		printf("\nsize of %d = %d\n ", n, nd);
		return nd;
	}
	void ybuild(Node *node, int *data, int nd, int nl, int nr) {
//		printf("ybuild %d %d %d\n", nd, nl, nr);
		if (nl == nr) {
			node[nd].val = data[nl];
			return;
		}
		int mid = nl + nr >> 1;
		ybuild(node, data, ls[nd], nl, mid);
		ybuild(node, data, rs[nd], mid + 1, nr);
		node[nd].val = max(node[ls[nd]].val, node[rs[nd]].val);
	}
	void buildupdate(int Nd, int nd, int nl, int nr) {
//		printf("buildupdate %d %d %d %d\n", Nd, nd, nl, nr);
//		return;
		if (nl != nr) {
			int mid = nl + nr >> 1;
			buildupdate(Nd, ls[nd], nl, mid);
			buildupdate(Nd, rs[nd], mid + 1, nr);
		}
		node[Nd][nd].val = max(node[ls[Nd]][nd].val, node[rs[Nd]][nd].val);
	}
	void xbuild(int nd, int nl, int nr) {
//		printf("xbuild %d [%d %d]\n", nd, nl, nr);
		if (nl == nr) {
			ybuild(node[nd], data[nl], 1, 1, m);
			return;
		}
		int mid = nl + nr >> 1;
		xbuild(ls[nd], nl, mid);
		xbuild(rs[nd], mid + 1, nr);
		buildupdate(nd, 1, 1, m);
	}
	void build() {
		int xsize = getsize(n), ysize = getsize(m);
		node = (Node **)calloc(xsize, sizeof(Node *)) - 1;
		for (int i = 1; i <= xsize; i++) node[i] = (Node *)calloc(ysize, sizeof(Node)) - 1;
		tag = (int *)calloc(ysize, sizeof(int)) - 1;
		xbuild(1, 1, n);
	}
	int yquery(Node *node, int nd, int nl, int nr, int yl, int yr) {
		if (yl <= nl && nr <= yr) {
			return tag[nd] + node[nd].val;
		}
		int ret;
		int mid = nl + nr >> 1;
		if (yl <= mid) {
			ret = yquery(node, ls[nd], nl, mid, yl, yr);
			if (yr > mid) ret = max(ret, yquery(node, rs[nd], mid + 1, nr, yl, yr));
		} else ret = yquery(node, rs[nd], mid + 1, nr, yl, yr);
		return ret + tag[nd] + node[nd].tag;
	}
	void addtag(Node *node, int nd, int nl, int nr, int yl, int yr, int factor) {
		tag[nd] += node[nd].tag * factor;
		printf("tag %d += %d\n", nd, node[nd].tag * factor);
		if (yl <= nl && nr <= yr) {
			return;
		}
		int mid = nl + nr >> 1;
		if (yl <= mid) {
			addtag(node, ls[nd], nl, mid, yl, yr, factor);
			if (yr >= mid + 1) addtag(node, rs[nd], mid + 1, nr, yl, yr, factor); 
		} else addtag(node, rs[nd], mid + 1, nr, yl, yr, factor);
		
	}
	int query(int nd, int nl, int nr, int xl, int xr, int yl, int yr) {
		if (xl <= nl && nr <= xr) {
//			return -1;
			return yquery(node[nd], 1, 1, m, yl, yr);
		}
		printf("addtag");
		addtag(node[nd], 1, 1, m, yl, yr, +1);
		int mid = nl + nr >> 1;
		int ret;
		if (xl <= mid) {
			ret = query(ls[nd], nl, mid, xl, xr, yl, yr);
			if (xr > mid) ret = max(ret, query(rs[nd], mid + 1, nr, xl, xr, yl, yr));
		} else ret = query(rs[nd], mid + 1, nr, xl, xr, yl, yr);
		addtag(node[nd], 1, 1, m, yl, yr, -1);
		return ret;
	}
	
	
	void yupdate(int Nd, int nd, int nl, int nr, int yl, int yr) {
		if (nl < yl || yr < nr) {
			int mid = nl + nr >> 1;
			if (yl <= mid) {
				yupdate(Nd, ls[nd], nl, mid, yl, yr);
				if (yr >= mid + 1) yupdate(Nd, rs[nd], mid + 1, nr, yl, yr);
			} else yupdate(Nd, rs[nd], mid + 1, nr, yl, yr);
		}
	//	node[Nd][nd].val = node[Nd][nd].tag + max(node[Nd][rs[nd]].val, max(node[Nd][ls[nd]].val, max(node[ls[Nd]][nd].val, node[rs[Nd]][nd].val)));
		node[Nd][nd].val = node[Nd][nd].tag + max(node[ls[Nd]][nd].val, node[rs[Nd]][nd].val);
		printf("node %d %d[y:%d %d] val = %d\n", Nd, nd, nl, nr, node[Nd][nd].val);
		/// ?????????
	}
	
	void yadd(Node *node, int nd, int nl, int nr, int yl, int yr, int v) {
		if (yl <= nl && nr <= yr) {
			printf("Small node %d[%d %d] += %d\n", nd, nl, nr, v);
			node[nd].tag += v;
			node[nd].val += v;
			printf("Small %d[%d, %d] = tag: %d, val: %d\n", nd, nl, nr, node[nd].val, node[nd].tag);
			return;
		}
		int mid = nl + nr >> 1;
		if (yl <= mid) {
			yadd(node, ls[nd], nl, mid, yl, yr, v);
			if (yr >= mid + 1) yadd(node, rs[nd], mid + 1, nr, yl, yr, v);
		} else yadd(node, rs[nd], mid + 1, nr, yl, yr, v);
		node[nd].val = node[nd].tag + max(node[ls[nd]].val, node[rs[nd]].val);
		printf("Small %d[%d, %d] = tag: %d, val: %d\n", nd, nl, nr, node[nd].tag, node[nd].val);
	}
	
	void add(int nd, int nl, int nr, int xl, int xr, int yl, int yr, int v) {
		if (xl <= nl && nr <= xr) {
			printf("Big node %d[%d %d]\n", nd, nl, nr);
			yadd(node[nd], 1, 1, m, yl, yr, v);
			return;
		}
		int mid = nl + nr >> 1;
		if (xl <= mid) {
			add(ls[nd], nl, mid, xl, xr, yl, yr, v);
			if (mid + 1 <= xr) add(rs[nd], mid + 1, nr, xl, xr, yl, yr, v);
		} else add(rs[nd], mid + 1, nr, xl, xr, yl, yr, v);
		yupdate(nd, 1, 1, m, yl, yr);
	}
	
	inline int query(int x1, int y1, int x2, int y2) {
		assert(x1 <= x2 && y1 <= y2);
		return query(1, 1, n, x1, x2, y1, y2);
	}
	inline void add(int x1, int y1, int x2, int y2, int v) {
		assert(x1 <= x2 && y1 <= y2);
		add(1, 1, n, x1, x2, y1, y2, v);
	}
}tree;
struct Brute {
	
	
	void add(int x1, int y1, int x2, int y2, int v) {
		assert(x1 <= x2 && y1 <= y2);
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				data[i][j] += v;
			}
		}
	}
	int query(int x1, int y1, int x2, int y2) {
		assert(x1 <= x2 && y1 <= y2);
		int ret = -2147483647;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				ret = max(ret, data[i][j]);
			}
		}
		return ret;
	}
}brute;
struct _Main {
	_Main() {
		srand(99713);
		int Qn; 
		for (int I = 1; I <= 10; I ++) {
//		read(n); read(m); read(Qn);
//		n = (rand() % 37) + 1;
//		m = (rand() % 37) + 1;
		n  = m = 2;
		printf("[%d %d]\n", n, m);
		/*
		n = (rand() % (int)1e6) + 1;
		m = (int)(1e6 / n);
		*/
		Qn = 100;
		data = (int **)calloc(n, sizeof(int *)) - 1;
		for (int i = 1; i <= n; i++) {
			data[i] = (int *)calloc(m, sizeof(int)) - 1;
			for (int j = 1; j <= m; j++) {
				data[i][j] = rand() % (int)1;
//				read(data[i][j]);
//				printf("data %d %d\n", i, j);
			}
		}
		tree.build();		
		
//		return;
		int op, x1, x2, y1, y2, v;
		for (int Q = 1; Q <= Qn; Q++) {
//			printf("Q = %d\n", Q);
		//	read(op); read(x1); read(y1); read(x2); read(y2);
			op = rand() % 2 + 1;
			x1 = rand() % n + 1;
			x2 = rand() % n + 1;
			y1 = rand() % m + 1;
			y2 = rand() % m + 1;
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			
			
			if (op == 1) {
		//		read(v);
				v = 1;
				printf("Q{%d %d %d %d %d %d}\n", op, x1, y1, x2, y2, v);
				tree.add(x1, y1, x2, y2, v);
				brute.add(x1, y1, x2, y2, v);
			} else { // op == 2
				printf("Q{%d %d %d %d %d}\n", op, x1, y1, x2, y2);
				if (brute.query(x1, y1, x2, y2) != tree.query(x1, y1, x2, y2)) {
					printf("%d != %d\n", brute.query(x1, y1, x2, y2), tree.query(x1, y1, x2, y2));
					exit(-1);
				}
	//			printf("Ans : %d\n", tree.query(x1, y1, x2, y2));
				
			}
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
