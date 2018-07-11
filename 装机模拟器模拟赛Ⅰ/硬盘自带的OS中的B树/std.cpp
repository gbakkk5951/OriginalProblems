#pragma GCC optimize(2)
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
const int MXN = 2e5 + 10;
struct Node {
	Node *s[2], *f;
	int len, h;
	int val;
	int id;
	char swp, isnode;
	void update() {
		len = s[0]->len + s[1]->len + val;
		h = s[0]->h + s[1]->h + isnode;
	}
	void rotate() {
		Node *gf = f->f;
		int spo;
		if ((spo = f == gf->s[1]) || f == gf->s[0]) {
			gf->s[spo] = this;
		}
		spo = this == f->s[1];
		(f->s[spo] = s[spo ^ 1])->f = f;
		s[spo ^ 1] = f;
		f->f = this;
		f->update();
		update();
		f = gf;
	}
	inline void swap() {
		std::swap(s[0], s[1]);
		swp ^= 1;
	}
	void push() {
		if (swp) {
			s[0]->swap();
			s[1]->swap();
			swp = 0;
		}
	}
}pool[MXN << 1], *null;
int pidx;
Node *new_(int val, int isnode) {
	Node *nd = &pool[pidx++];
	nd->s[0] = nd->s[1] = nd->f = null;
	nd->val = val; nd->isnode = isnode;
	return nd;
}
struct LCT {
void push_to(Node *nd) {
	static Node *stk[MXN << 1];
	int top = 0;
	while (nd != null) {
		stk[++top] = nd;
		nd = nd->f;
	}
	while (top) {
		stk[top--]->push();
	}
}
Node *access(Node *nd) {
	push_to(nd);
	Node *lst = null, *org = nd;
	while (nd != null) {
		splay(nd);
		nd->s[1] = lst;
		lst = nd;
		nd = nd->f;
	}
	splay(org);
	return lst;
}
Node *getfa(Node *nd) {
	access(nd);
	nd->push();
	nd = nd->s[0];
	nd->push();
	while (nd->s[1] != null) {
		nd = nd->s[1];
		nd->push();
	}
	splay(nd);
	return nd;
}
void splay(Node *nd) {
	nd->update();
	Node *f = nd->f, *gf;
	char a, b;
	while ((a = nd == f->s[1]) || nd == f->s[0]) {
		gf = f->f;
		if ((b = f == gf->s[1]) || f == gf->s[0]) {
			(a == b ? f : nd)->rotate();
		}
		nd->rotate();
		f = nd->f;
	}
}
void mkrt(Node *nd) {
	access(nd);
	nd->swap();
}
void link(Node *s, Node *f) {
	mkrt(s);
	s->f = f;
}
void cut(Node *nd) {//将nd与f割下来
	access(nd);
	nd->s[0]->f = null;
	nd->s[0] = null;
}
inline Node *getlca(Node *a, Node *b) {
	access(a);
	return access(b);
}
inline int geth(Node *nd) {
	access(nd);
	return nd->h;
}
inline int getlen(Node *nd) {
	access(nd);
	return nd->len;
}
LCT() {
	null = new_(0, 0);
	null->f = null->s[0] = null->s[1] = null;
}

}tree;
struct _Main {
	Node *node[MXN], *edge[MXN];
	int f[MXN];
	int n;
	void move() {
		int a, b, v;
		read(a); read(b); read(v);
		Node *s = node[a];
		Node *dst = node[b];
		if (tree.getlca(s, dst) == s) {//b在a的子树中
			return;
		}
		s = tree.getfa(s);
		tree.cut(s);
		s->val = v;
		tree.link(s, dst);
	}
	void mkrt() {
		int a;
		read(a);
		tree.mkrt(node[a]);
	}
	void change_val() {
		int x, y, v;
		read(x); read(y); read(v);
		if (x == y) return;//神Tm输入2个一
		Node *a = node[x], *b = node[y];
		
		Node *lca = tree.getlca(a, b);
		if (lca != a && lca != b) return;
		if (lca == a) swap(a, b);
		a = tree.getfa(a);
		if (tree.getfa(a) == b) {
			tree.access(a);
			a->val = v;
		}
	}
	void query() {
		int kn;
		read(kn);
		int h = INF;
		int a;
		Node *lst, *now;
		Node *lca = null;
		read(a);
		lca = lst = node[a];
		for (int i = 1; i <= kn - 1; i++) {
			read(a);
			now = node[a];
			Node *nd = tree.getlca(lst, now);
			int t = tree.geth(nd);
			if (t < h) {
				lca = nd;
				h = t;
			}
			lst = now;
		}
		printf("%d\n", tree.getlen(lca));
	}
	_Main() {
		int Qn;
		int a, b, c;
		Node *edge;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			node[i] = new_(0, 1);
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b); read(c);
			edge = new_(c, 0);
			tree.link(node[a], edge);
			tree.link(node[b], edge);
		}
		tree.mkrt(node[1]);
		int op;
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {
				move();
			} else
			if (op == 2) {
				mkrt();
			} else
			if (op == 3) {
				change_val();
			} else
			if (op == 4) {
				query();
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
