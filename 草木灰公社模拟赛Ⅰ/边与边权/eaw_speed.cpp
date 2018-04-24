using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
const int MXN = 100010;
const int CHANGE = 1, INS = 2, DEL = 3;
struct Node {
	Node *s[2], *f;
	int size, mn, val;
};	
struct Splay {
	Node pool[MXN << 1], *null, *root;
	int pidx;
	Node *new_(int v, Node *f) {
		Node *nd = &pool[pidx++];
		nd->f = f;
		nd->size = 1;
		nd->val = nd->mn = v;
		nd->s[0] = nd->s[1] = null;
		return nd;
	}
	Splay() {
		null = new_(2, null);
		null->f = null->s[0] = null->s[1] = null;
		null->size = 0;
	}
	void rotate(Node *nd) {
		Node *f = nd->f, *gf = f->f;
		nd->f = gf;
		gf->s[f == gf->s[1]] = nd;
		int spo = nd == f->s[1];
		(f->s[spo] = nd->s[spo ^ 1])->f = f;
		f->f = nd;
		nd->s[spo ^ 1] = f;
		update(f);
		update(nd);
	}
	void splay(Node *nd) {
		update(nd);
		Node *f;
		while ((f = nd->f) != null) {
			if (f->f != null) {
				if ((nd == f->s[1]) == (f == f->f->s[1])) {
					rotate(f);
				} else {
					rotate(nd);
				}
			}
			rotate(nd);
		}
		root = nd;
	}
	void update(Node *nd) {
		nd->size = 1, nd->mn = nd->val;
		for (int i = 0; i < 2; i++) {
			nd->mn = min(nd->mn, nd->s[i]->mn);
			nd->size += nd->s[i]->size;
		}
	}
	Node* build(int arr[], int l, int r, Node *f) {
		int mid = l + r >> 1;
		Node *nd = new_(arr[mid], f);
		if (l < mid) {
			nd->s[0] = build(arr, l, mid - 1, nd);
		}
		if (r > mid) {
			nd->s[1] = build(arr, mid + 1, r, nd);
		}
		update(nd);
		return nd;
	}
	void erase(int pos) {
		Node *nd = root;
		while (nd->s[0]->size != pos) {
			if (nd->s[0]->size < pos) {
				pos -= nd->s[0]->size + 1;
				nd = nd->s[1];
			} else {
				nd = nd->s[0];
			}
		}
		while (nd->s[0] != null && nd->s[1] != null) {
			rotate(nd->s[0]);
		}
		int spo = nd->s[0] == null;
		Node *f = nd->f;
		f->s[nd == f->s[1]] = nd->s[spo];
		nd->s[spo]->f = f;
		if (f != null) {
			splay(f);
		} else {
			root = nd->s[spo];
		}
	}
	void insert(int pos, int v) {
		Node *nd = root;
		int spo;
		while (1) {
			if (spo = nd->s[0]->size < pos) {
				pos -= nd->s[0]->size + 1;
			}
			if (nd->s[spo] != null) {
				nd = nd->s[spo];
			} else {
				nd = nd->s[spo] = new_(v, nd);
				break;
			}
		}
		splay(nd);
	}
	void change(int pos, int v) {
		Node *nd = root;
		while (1) {
			if (nd->s[0]->size == pos) {
				nd->val = v;
				break;
			} else if (nd->s[0]->size > pos) {
				nd = nd->s[0];
			} else {
				pos -= nd->s[0]->size + 1;
				nd = nd->s[1];
			}
		}
		splay(nd);
	}
	int findside(int v, int side) {
		Node *nd = root;
		int ret = 0;
		while (1) {
			if (nd->s[side]->mn == v) {
				nd = nd->s[side];
			} else 
			if (nd->val == v) {
				ret += nd->s[side]->size;
				break;
			} else {
				ret += nd->s[side]->size + 1;
				nd = nd->s[side ^ 1];
			}
		}
		splay(nd);
		return ret;
	}
}tree;

struct _Main {
	int arr[MXN];
	void ask() {
		if (tree.root->mn == 0) {
			if (!(tree.findside(0, 0) & 1) || !(tree.findside(0, 1))) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		} else 
		if (tree.root->mn == 1) {
			if ((n & 1) || !(tree.findside(1, 0) & 1) || !(tree.findside(1, 1) & 1)) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		} else {
			printf("%c\n", (char)(n & 1) + '0');
		}
	}
	int n;
	_Main() {
		int Qn;
		int op, pos, val;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
		}
		arr[0] = 2; arr[n + 1] = 2;
		tree.root = tree.build(arr, 0, n + 1, tree.null);
		ask();
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); read(pos);
			if (op == CHANGE) {
				read(val);
				tree.change(pos, val);
			} else if (op == INS) {
				read(val);
				tree.insert(pos, val);
				++n;
			} else if(op == DEL) {
				tree.erase(pos);
				--n;
			}
			ask();
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
}eaw;
}
