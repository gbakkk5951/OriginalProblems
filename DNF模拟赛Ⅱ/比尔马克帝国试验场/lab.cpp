#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <iostream>
namespace OI {
typedef long long lld;
typedef set<int>::iterator it;
const int MXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
struct LS {
	inline int operator [] (const int &a) {
		return a << 1;
	}
}ls;
struct RS {
	inline int operator [] (const int &a) {
		return a << 1 | 1;
	}
}rs;

int d[MXN], cnt[MXN];
struct Node {
	int negsum, zerosum, possum, negmax, posmin, zero; 
	int tag;
};
struct SegTree {
	Node node[270000];
	void update(int nd) {
		node[nd].negsum = node[ls[nd]].negsum + node[rs[nd]].negsum;
		node[nd].possum = node[ls[nd]].possum + node[rs[nd]].possum;
		node[nd].zerosum = node[ls[nd]].zerosum + node[rs[nd]].zerosum;
		node[nd].negmax = max(node[ls[nd]].negmax, node[rs[nd]].negmax);
		node[nd].posmin = min(node[ls[nd]].posmin, node[rs[nd]].posmin);
		node[nd].zero = node[ls[nd]].zero + node[rs[nd]].zero;
	}
	inline void push(int nd) {
		if (node[nd].tag) {
			add(ls[nd], node[nd].tag);
			add(rs[nd], node[nd].tag);
			node[nd].tag = 0;
		}
	}
	inline void add(int nd, int v) {
		node[nd].tag += v;
		node[nd].posmin += node[nd].posmin ? v : 0;
		node[nd].negmax += node[nd].negmax ? v : 0;
	}
	void init(int nd, int nl, int nr) {
		if (nl == nr) {
			node[nd].zero = 1;
			node[nd].zerosum = d[nl];
			node[nd].negmax = -INF; //卡一下没赋值
			node[nd].posmin = INF; //卡一下没赋值
			return;
		}
		int mid = nl + nr >> 1;
		init(ls[nd], nl, mid);
		init(rs[nd], mid + 1, nr);
		update(nd);
	}
	int query(int nd, int nl, int nr, int l, int r, int sym) {
		if (l <= nl && nr <= r) {
			return node[nd].zerosum + sym * (node[nd].possum - node[nd].negsum);
		}
		//push(nd); 不用push
		int mid = nl + nr >> 1;
		return ((l <= mid) ? query(ls[nd], nl, mid, l, r, sym) : 0)
			 + ((r > mid) ? query(rs[nd], mid + 1, nr, l, r, sym) : 0);
	}
	void change(int nd, int nl, int nr, int l, int r, int sym) {
		//到底了
		if (nl == nr) {
			cnt[nl] += node[nd].tag + sym;//忘了tag 
			memset(node + nd, 0, sizeof(Node));
			if (cnt[nl] > 0) {
				node[nd].possum = d[nl];
				node[nd].posmin = cnt[nl];
				node[nd].negmax = -INF; //卡一下没赋值 
			} else 
			if (cnt[nl] == 0) {
				node[nd].zerosum = d[nl];
				node[nd].zero = 1;
			} else {
				node[nd].negsum = d[nl];
				node[nd].negmax = cnt[nl];
				node[nd].posmin = INF; //卡一下没赋值
			}
			
		} else
		//走下去
		if (   (l > nl || r < nr)
			|| (node[nd].zero)
			|| (node[nd].posmin + sym == 0)
			|| (sym + node[nd].negmax == 0)) 
		{
			int mid = nl + nr >> 1;
			push(nd);
			if (l <= mid) change(ls[nd], nl, mid, l, r, sym);
			if (r > mid) change(rs[nd], mid + 1, nr, l, r, sym);
			update(nd);
		} else {
		//直接加
			add(nd, sym);
		}
	}
}tree;

struct _Main {
	
	set<int> near;
	int rl[MXN];
	int n, Qn;
	lld ans;
	_Main() {
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(rl[i]);
		}
		rl[0] = INF;
		d[0] = INF;
		rl[n + 1] = INF;
		for (int i = 1; i <= n; i++) {
			read(d[i]);
		}
		for (int i = 0; i <= n + 1; i++) {
			if (rl[i]) near.insert(i);
		}
		tree.init(1, 0, n);
		int l, r, pos, dl, dr;
		it tmp;
		for (int Q = 1; Q <= Qn; Q++) {
			read(pos);
			if (rl[pos]) {
				if (--rl[pos] == 0) {
					near.erase(pos);
				}
			} else {
				tmp = near.lower_bound(pos);
				r = *tmp;
				l = *(--tmp);
				dl = tree.query(1, 0, n, l, pos - 1, -1);
				dr = tree.query(1, 0, n, pos, r - 1, +1);
				if (dl <= dr) {
					ans += dl;
					tree.change(1, 0, n, l, pos - 1, -1);
					if (--rl[l] == 0) {
						near.erase(l);
					}
				} else {
					ans += dr;
					tree.change(1, 0, n, pos, r - 1, +1);
					if (--rl[r] == 0) {
						near.erase(r);
					}
				}
			}
			printf("%lld\n", ans);
		}
	}
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
	}
}lab;
}
