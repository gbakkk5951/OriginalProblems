using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>
#include <vector>
namespace OI {
typedef long long lld;
typedef pair<lld, lld> p;
const int MXN = 1e5 + 10;
priority_queue<p, vector<p>, greater<p> > heap;//单位售价、数量
struct Node {
	Node *s[2], *f;
	lld p, psum, sold, tag;
	int id;
	void update() {
		psum = s[0]->psum + s[1]->psum + p;
	}
	void push() {
		if (tag) {
			s[0]->add(tag);
			s[1]->add(tag);
			tag = 0;
		}
	}
	void rotate() {
		Node *gf = f->f;
		gf->s[f == gf->s[1]] = this;
		int spo = nd == f->s[1];
		(f->s[spo] = s[spo ^ 1])->f = f;
		s[spo ^ 1] = f;
		f->f = nd;
		f->update();
		update();
		f = gf;
	}
	void add(lld val) {
		sold += val * p;
		tag += val;
	}
}pool[MXN], *null;
int pidx;
inline Node *new_(int id, int p) {
	Node *nd = &pool[pidx++];
	nd->f = nd->s[0] = nd->s[1] = null;
	nd->id = id; nd->p = p;
	return nd;
}
lld v[MXN], p[MXN];
struct Splay {
	Node *root;
	void splay(Node *nd) {
		Node *f = nd->f, *gf;
		nd->update();
		while (f != null) {
			gf = f->f;
			if (gf != null) {
				((f == gf->s[1]) == (nd == f->s[1]) ? f : nd)->rotate();
			}
			nd->rotate();
		}
		root = nd;
	}
	char cmp(int id, Node *nd) {
		return v[id] == v[nd->id] ? id < nd->id : v[id] < v[nd->id];
	}
	void insert(int id) {
		if (root == null) {
			root = node[id];
			return;
		}
		Node *nd = root;
		int spo;
		while (1) {
			nd->push();
			spo = cmp(id, nd);
			if (nd->s[spo] != null) {
				nd = nd->s[spo];
			} else {
				nd->s[spo] = node[id];
				node[id]->f = nd;
			}
		}
		splay(node[id]);
	}
	void find(int id) {
		Node *nd = root;
		while (1) {
			nd->push();
			if (nd->id == id) {
				break;
			} else {
				nd = nd->s[cmp(id, nd)];
			}
		}
		splay(nd);
	}
	lld erase(int id) {
		Node *nd = root;
		int spo;
		lld ret = 0;
		while (1) {
			nd->push();
			if (nd->id == id) {
				ret = nd->sold;
				break;
			} else {
				nd = nd->s[cmp(id, nd)];
			}
		}
		while ((spo = nd->s[1] != null) || nd->s[0] != null) {
			nd->s[spo]->push();
			nd->s[spo]->rotate();
		}
		Node *f = nd->f;
		f->s[nd == f->s[1]] = null;
		nd->f = null;
		if (f != null) splay(f);
		else root = null;
		nd->sold = 0;
		return ret;
	}
	void add(int mxp) {
		Node *nd = root;
		while (mxp > 0) {
			nd->push();//不用吧; 用的，因为要旋转
			if (nd->s[0]->psum >= mxp) {
				nd = nd->s[0];
			} else {
				mxp -= nd->s[0]->psum;
				nd->s[0]->add(1);
				if (nd->p >= mxp) {
					nd->sold += mxp;
					break;
				} else {
					nd->sold += nd->p;
					mxp -= nd->p;
					if (nd->s[1] != null) {
						nd = nd->s[1];
					} else {
						break;
					}
				}
			}
		}
		splay(nd);
	}
	Splay() {
		null = new_(0, 0);
		null->f = null->s[0] = null->s[1] = null;
	}
}tree;



struct _Main {
	lld out[MXN];
	lld sold[MXN];
	lld sold_sum, vsum, outsum[MXN];
	void init() {
		for (int i = 1; i <= n; i++) {
			node[i] = new_(i, p[i]);
			tree.insert(i);
		}
	}
	void change(val)
	int n, m, Qn;
	_Main() {
		int op, a, b;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(v[i]);
		}
		for (int i = 1; i <= n; i++) {
			read(p[i]);
		}
		init();
		for (int i = 1; i <= m; i++) {
			read(out[i]);
			read(Qn);
			for (int Q = 1; Q <= Qn; Q++) {
				read(op); read(a); read(b);
				if (op == 1) {//改价值
					change_val(a, b);
				} else {//改产量
					change_product(a, b);
				}
			}
			get_sold(out[i]);
		}
		printf("%lld\n", vsum);
		for (int i = 1; i <= m - 1; i++) {
			
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
