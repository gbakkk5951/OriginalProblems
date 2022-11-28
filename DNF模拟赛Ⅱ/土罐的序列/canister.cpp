using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
const int MXN = 2e5 + 10;
struct Node;
Node *pool, *null;
struct Node {
	Node *f, *s[2];
	int size, v;
	int lv, rv, cnt;
	int rev, asi;
	inline void assign(int val) {
		asi = val;
		lv = rv = v = val;
		cnt = 1;
	}
	inline void reverse() {
		rev ^= 1;
		swap(s[0], s[1]);
		swap(lv, rv);
	}
	inline void push() {//push 到null上去了 
		if (rev) {
			if (s[0] != null) s[0]->reverse();
			if (s[1] != null) s[1]->reverse();
			rev = 0;
		}
		if (asi) {
			if (s[0] != null) s[0]->assign(asi);
			if (s[1] != null) s[1]->assign(asi);
			asi = 0;
		}
	}
	inline Node* setf(Node* const &fa) {
		f = fa;
		return this;
	}
	inline void update() {
		cnt = 1;
		lv = s[0]->lv ? s[0]->lv : v;
		rv = s[1]->rv ? s[1]->rv : v;
		cnt += s[0]->cnt - (s[0]->rv == v);
		cnt += s[1]->cnt - (s[1]->lv == v);
		size = s[0]->size + s[1]->size + 1;
	}
	void rotate() {
		Node *f = this->f, *gf = f->f;
		this->f = gf;
		gf->s[f == gf->s[1]] = this;
		int spo = this == f->s[1];
		f->s[spo] = s[spo ^ 1]->setf(f);
		s[spo ^ 1] = f;
		f->f = this;
		f->update();
		update();		
	}
};
struct Splay {
	Node pool[MXN];
	int pidx;
	Node *root;
	inline Node *new_(Node* const &f = 0) {
		Node *nd = &pool[pidx++];
		nd->s[0] = nd->s[1] = null;
		nd->size = 1;
		nd->f = f ? f : null;
		return nd;
	}
	Splay() {
		OI::pool = pool;
		null = new_();
		null->s[0] = null->s[1] = null->f = null;
		null->size = 0;
		null->cnt = 0;
	}
	
	void splay(Node* const &nd, Node* const &top) {
		Node *f;
		
		while ((f = nd->f) != top) {
			if (f->f != top) {
				((nd == f->s[1]) == (f == f->f->s[1]) 
					? f : nd)->rotate();
			}
			nd->rotate();
		}
		root = top == null ? nd : root;
	}
	Node *build(int l, int r, int color[]) {
		int mid = l + r >> 1;
		Node *nd = new_();
		nd->v = color[mid];
		nd->s[0] = l < mid ? build(l, mid - 1, color)->setf(nd) : null;
		nd->s[1] = r > mid ? build(mid + 1, r, color)->setf(nd) : null;
		nd->update();
		return nd;
	}
	void getRange(int l, int r) {
		Node *ln, *rn;
		ln = find(l - 1);
		splay(ln, null);
		rn = find(r + 1);
		splay(rn, ln);
	}
	int query(int l, int r) {
		getRange(l, r);
		return root->s[1]->s[0]->cnt;
	}
	void mov(int l, int len, int nl) {
		Node *ins, *nd;
		int spo;
		getRange(l, l + len - 1);
		ins = root->s[1]->s[0];
		root->s[1]->s[0] = null;
		root->s[1]->update();
		root->update();
		nd = root;
		while (1) {
			nd->push();//卡一下没push 
			if (spo = nd->s[0]->size < nl) {
				nl -= nd->s[0]->size + 1;
			}
			if (nd->s[spo] == null) {
				nd->s[spo] = ins->setf(nd);
				break;//忘了break; 
			}
			nd = nd->s[spo];
		}
		ins->push();//没push会导致旋转出现问题 
		splay(ins, null);
	}
	
	void assign(int l, int r, int v) {
		getRange(l, r);
		root->s[1]->s[0]->assign(v);
		root->s[1]->update(); //没update 
		root->update();
	}
	void reverse(int l, int r) {
		getRange(l, r);
		root->s[1]->s[0]->reverse();
		root->s[1]->update();//没update 
		root->update();
	}
	Node *find(int rank) {
		Node *nd = root;
		while (1) {
			nd->push();
			if (nd->s[0]->size < rank) {
				rank -= nd->s[0]->size + 1;//上下两句顺序反了 
				nd = nd->s[1];
			} else
			if (nd->s[0]->size == rank) {
				return nd;
			} else {
				nd = nd->s[0];
			}
		}
	}
	
	
}tree;


struct _Main {
	int n, Qn;
	int color[MXN];
	_Main() {
		int op, l, r, v, nl, len;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(color[i]);
		}
		color[0] = color[n + 1] = -1;
		tree.root = tree.build(0, n + 1, color);
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {//赋值
				read(l); read(r); read(v);
				tree.assign(l, r, v);
			} else
			if (op == 2) {//rev
				read(l); read(r);
				tree.reverse(l, r);
			} else
			if (op == 3) {//mov
				read(l); read(len); read(nl);
				tree.mov(l, len, nl);
			} else { //query
				read(l); read(r);
				printf("%d\n", tree.query(l, r));
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
}canister;
}
