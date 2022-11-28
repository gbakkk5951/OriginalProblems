using namespace std;
int main() {}
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 3e5 + 10;
const lld MOD = 1e9 + 7;
struct Node {
	Node *s[2], *f;
	lld c, i, p, st, cs, ps, ss, vs, as, ct, pt;
	bool operator < (const Node &b) const {
		if (c != b.c) return c < b.c;
		return i < b.i;
	}
	inline void clear() {
		st = ss = as = 0;
		pt = 0; ct = 1;
		//Forgot to clear the produce tag
	}
	inline void produce(lld t) {
		pt += t;
		st += t * p;
		ss += t * ps;
		as += vs * t % MOD;
	}
	inline void push() {
		if (ct) {
			s[0]->clear();
			s[1]->clear();
			ct = 0;
		}
		if (pt) {
			s[0]->produce(pt);
			s[1]->produce(pt);
			pt = 0;
		}
	}
	inline void update() {
		cs = (s[0]->cs + c + s[1]->cs) % MOD;
		ps = (s[0]->ps + p + s[1]->ps);
		vs = (s[0]->vs + p * c + s[1]->vs) % MOD; 
		as = (s[0]->as + st % MOD * c + s[1]->as) % MOD;
		ss = (s[0]->ss + st + s[1]->ss);
	}
	void rotate() {
		Node * gf = f->f;
		int spo;
		gf->s[f == gf->s[1]] = this;
		spo = this == f->s[1];
		(f->s[spo] = s[spo ^ 1])->f = f;
		f->f = this;
		s[spo ^ 1] = f; 
		f->update();
		update();
		f = gf;
	}
	lld sell(lld num) {
		st -= num;
		ss -= num;
		num %= MOD;
		as = (as - num * c) % MOD;
		return num * c % MOD;
	}
}pool[MXN], *null;
int pidx;
Node *new_(int id) {
	Node *nd = &pool[pidx++];
	nd->s[0] = nd->s[1] = nd->f = null;
	nd->i = id;
	return nd;
}
struct Tree {
	Node *root;
	Tree() {
		null = new_(0);
		null->s[0] = null->s[1] = null->f = null;
		root = null;
	}
	void splay(Node *nd) {
		nd->push();
		if (nd->f == null) {
			nd->update();
		}
		Node *f = nd->f, *gf;
		while (f != null) {
			/*
			gf = f->f;
			if (gf != null) {
				((f == gf->s[1]) == (nd == f->s[1]) ? f : nd)->rotate(); 
			}*/
			nd->rotate();
			f = nd->f;
		}
		root = nd;
	}
	void insert(Node *obj) {
		Node *nd = root;
		if (nd == null) {
			root = obj;
			obj->update();
			return;
		}
		int spo;
		while (1) {
			//forget Push
			nd->push();
			spo = *obj < *nd; 
			
			if (nd->s[spo] == null) {
				nd->s[spo] = obj;
				obj->f = nd;
				splay(obj);
				break;
			} else {
				nd = nd->s[spo];
			}
		}
	} 
	void find(Node *obj, char rot) {
		Node *nd = root;
		while (1) {
			nd->push();
			if (nd == obj) {
				break;
			} else {
				nd = nd->s[*obj < *nd];
			}
		}
		if (rot) {
			splay(obj);
		}
	}
	void erase(Node *nd) {
		find(nd, 0);
		int spo;
		while ((spo = nd->s[1] != null) || nd->s[0] != null) {
			nd->s[spo]->push();
			nd->s[spo]->rotate();
		}
		Node *f = nd->f;
		if (f != null) {
			f->s[nd == f->s[1]] = null;
			nd->f = null;
			splay(f);
		}
	}
	lld sell(lld mxn) {//卡一下这个不rotate
		lld ret = 0;
		Node *nd = root;
		while (1) {
			nd->push();
			if (nd->ss <= mxn) {//'ss' tobe 'st' wrongly
				ret += nd->as;
				nd->clear();
				break;
			} 
			if (nd->s[0] != null) {
				if (nd->s[0]->ss < mxn) {
					mxn -= nd->s[0]->ss;
					ret += nd->s[0]->as;
					nd->s[0]->clear();
				} else {
					nd = nd->s[0];
					continue;
				}
			}
			if (nd->st >= mxn) {
				ret += nd->sell(mxn);
				break;
			}
			mxn -= nd->st;
			ret += nd->sell(nd->st);
			//it's confimable that there must be s[1] 
			nd = nd->s[1];
		}
		splay(nd);
		ret %= MOD;
		ret += ret < 0 ? MOD : 0;
		return ret;
	}
	Node *build (Node *arr[], int l, int r) {
		int mid = l + r >> 1;
		Node *nd = arr[mid];
		if (l < mid) {
			(nd->s[0] = build(arr, l, mid - 1))->f = nd;//didn't link f
		}
		if (r > mid) {
			(nd->s[1] = build(arr, mid + 1, r))->f = nd; 
		}
		nd->update();
		return nd;
	}
}tree;
bool cmp(Node *a, Node *b) {//reversed wrongly
	return *b < *a;
}
Node *node[MXN];
Node *arr[MXN];
struct _Main {
	_Main() {
		int n, Qn;
		int op;
		lld a, b;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(a); read(b);
			node[i] = new_(i);
			node[i]->c = a;
			node[i]->p = b;
		}
		memcpy(arr, node, (n + 1) * sizeof(Node *));
		sort(arr + 1, arr + n + 1, cmp);
		tree.root = tree.build(arr, 1, n);
		for (int Q = 1; Q <= Qn; Q++) {
			/*
			printf("root = %d\n", tree.root - pool);
			for (int i = 1; i <= n; i++) {
			//	node[i]->push();
				printf("%d st = %lld ss =%lld as = %lld s1 = %d, s2 = %d, pt = %lld, ct = %lld\n", 
					i, node[i]->st, node[i]->ss,
					node[i]->as,
					node[i]->s[0] - pool, node[i]->s[1] - pool,
					node[i]->pt, node[i]->ct);
			}
			*/
			read(op);
			if (op == 1) {//鐢熶骇
				read(a);
				tree.root->produce(a);
			} else 
			if (op == 2) {//鍑哄敭
				read(a);
				printf("%lld\n", tree.sell(a));
			} else
			if (op == 3) {//浜ч噺
				read(a); read(b);
				tree.find(node[a], 1);
				tree.root->p = b;
				tree.root->update();
			} else
			if (op == 4) {//浠锋牸
				read(a); read(b);
				tree.erase(node[a]);
				node[a]->c = b;
				tree.insert(node[a]);
			}
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
}std;
}
