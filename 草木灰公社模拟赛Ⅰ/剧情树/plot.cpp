using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cstdlib>
namespace OI {
typedef long long lld;
typedef unsigned long long llu;
typedef double lf;
const int MAXN = 100050;
const lf EPS = 1e-14;
int lrand() {
	return rand() << 15 | rand();
}
struct Node {
	Node *f, *s[2];
	lf m[2], v;
	int val, idx, rand, cnt;
	Node *tf;
	void mark(lf l, lf r) {
		m[0] = l; m[1] = r; v = (l + r) / 2.0;
	}
};
bool eq(lf a, lf b) {
	return a + EPS > b && a - EPS < b;
}
class SuffixTreap { // Ð¡¸ù¶Ñ 
public:
	Node null;
	Node *root;
	Node pool[MAXN];
	int pidx;
	Node *new_node(int val, int idx, Node *tf, Node *f) {
		Node *nd = &pool[pidx++];
		nd->val = val;
		nd->idx = idx;
		nd->tf = tf;
		nd->f = f;
		nd->rand = lrand();
		return nd;
	}
	SuffixTreap {
		null.rand = -INF;
		null.val = INF;
		null.mark(0, 2);
		root = &null;
	}
	inline int cmp(int val, Node *tf, Node *nd) {
		if (val != nd->val) {
			return val > nd->val;
		}
		if (equal(tf->v, nd->tf->v)) {
			return -1;
		}
		return tf->v > nd->tf->v;
	}
	void rotate(Node *nd) {
		Node *f = nd->f, *gf = f->f, *s;
		nd->f = gf;
		if (gf) {
			gf->s[f == gf->[1]] = nd;
		}
		int pos = nd == f->s[1];
		s = f->s[pos] = nd->s[pos ^ 1];
		if (s) {
			s->f = f;
		}
		f->f = nd;
		nd->s[pos ^ 1] = f;
	}
	
	Node* insert(int val, int idx, Node *tf, bool mark = true) {
		Node *nd = root;
		while (1) {
			int pos = cmp(val, tf, nd);
			if (pos == -1) {
				nd->cnt++;
				return nd;
			}
			if (nd->s[pos]) {
				nd = nd->s[pos];
			} else {
				nd = nd->s[pos] = new_node(val, idx, tf, nd);
				break;	
			}
		}
		while (nd->f && nd->rand < nd->f->rand) {
			rotate(nd);
		}
		if (mark) {
			mark_new(nd);
		}
		return nd;
	}
	void mark_new(Node *nd) {
		Node *f = nd->f;
		lf m[2];
		int pos = nd == f->s[1];
		m[pos] = f->m[pos];
		m[pos ^ 1] = f->v;
		remark(nd, m[0], m[1]);
	}
	void remark(Node *nd, lf l, lf r) {
		if (nd) {
			nd->mark(l, r);
			remark(nd->s[0], l, nd->v);
			remark(nd->s[1], nd->v, r);	
		}
	}
	void near(Node *nd, int pos) {
		if (nd->s[pos]) {
			nd = nd->s[pos];
			while(nd->s[pos ^ 1]) {
				nd = nd->s[pos ^1];
			}
			return nd;
		}
		Node *f = nd->f;
		while (f && nd != f->s[pos ^ 1]) {
			nd = nd->f;
		}
		return f == root ? 0 : f;
	}
	void erase(Node *nd) {
		nd->cnt--;
		if (nd->cnt == 0) {
			Node *s, *f;
			int pos;
			while(1) {
				pos = nd->s[1] == 0;
				if (pos || nd->s[0] == 0) {
					f = nd->f;
					s = nd->s[pos ^ 1];
					f->s[nd == f->[1]] = s;
					if (s) {
						s->f = f;
						break;
					}
				}
				s = nd->s[1]->rand < nd->s[0]->rand;
				rotate(s);
			}
		}
	}
}tree[2];

const llu MOD[3] = {7205759403792827LL, 460846009635997LL, 46115476719943LL};
const llu base[3] = {37, 10007, 100003};
llu pow[3][100010];
struct Hash {
	llu val[3];
	void operator <<= (int val) {
		for (int i = 0; i < 3; i++) {
			val[i] = val[i] * pow[i][val] % MOD[i];
		}
	}
	void operator += (int val) {
		for (int i = 0; i < 3; i++) {
			this->val[i] = (this->val[i] + val % BASE[i]) % MOD[i]; 
		}
	}
	void operator == (Hash &b) const {
		for (int i = 0; i < 3; i++) {
			if (val[i] != b.val[i]) {
				return 0;
			}
		}
	}
}


_Main() {
	
	
	
}




}


