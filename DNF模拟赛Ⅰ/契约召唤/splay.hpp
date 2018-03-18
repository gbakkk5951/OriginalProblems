#include <cstdio>
#include <cstdlib>
struct Node;

struct Node {
	Node *f, *s[2];
	int size, val;
};
template <int pool_size>
class Splay {
private:
	Node *pool;
	Node *root;
	int pidx;
	int size_;

	Node *new_node(int val, Node *f = 0) {
		Node* nd = &pool[pidx++];
		nd->s[0] = nd->s[1] = 0;
		nd->f = f;
		nd->val = val;
		nd->size = 1;
		return nd;
	}
	
	void splay(Node *nd, Node *root = 0) {
		Node *f, *gf;
		while (1) {

			f = nd->f;
			/*
			if (nd->val == 37710) {
				printf("f = %lld\n", f);
			}		*/
			if (f != root) {
				gf = f->f;
				if (gf != root && (nd == f->s[1]) == (f == gf->s[1])) {
					rotate(f);
				}
				rotate(nd);
			} else {
				break;
			}
		}
		if (nd->f == 0) {
			this->root = nd;
		} 
	}
	void update(Node *nd) {
		nd->size = 1;
		for (int i = 0; i < 2; i++) {
			if (nd->s[i]) {
				nd->size += nd->s[i]->size;
			}
		}
	}
	
	void rotate(Node *nd) {
		Node *f = nd->f, *gf = f->f, *s;
		nd->f = gf;
		if (gf) {
			gf->s[f == gf->s[1]] = nd;
		}
		int pos = nd == f->s[1];
		s = f->s[pos] = nd->s[pos ^ 1];
		if (s) {
			s->f = f;
		}
		f->f = nd;
		nd->s[pos ^ 1] = f;
		update(f);
		update(nd);
	}
	int lrand() {
		return rand() << 15 | rand();
	}
	int getVal(int rk) {
		Node *nd = root;
		int l;
		while (1) {
			l = nd->s[0] ? nd->s[0]->size : 0;
			if (l >= rk) {
				nd = nd->s[0];	
			} else if(l + 1 == rk) {
				return nd->val;
			} else {
				rk -= l + 1;
				nd = nd->s[1];
			}
		}
	}
public:
	~Splay() {
		free(pool);
	}
	Splay() {
		clear();
		pool = (Node*)calloc(pool_size, sizeof(Node));
	}
	int size() {
		return size_;
	}
	int getRand() {
		if (size_) {
			return getVal(lrand() % size_ + 1);
		} 
		return 0;
	}
	void insert(int val) {
		size_++;
//		printf("ins");
//		printf("size_ += %d", size_);
		Node *nd = root;
		if (nd == 0) {

			root = new_node(val);
			return;
		}
		while (1) {
			/*if (val == 37710) {
				printf("nd = %lld\n", (nd - pool) / sizeof(Node));
			}*/
			int pos = nd->val < val;
			/*if (val == 37710) {
				printf("chose %d\n", pos);
			}
			*/
			if (nd->s[pos]) {
				nd = nd->s[pos];
			} else {
				nd = nd->s[pos] = new_node(val, nd);
				/*if (val == 37710) {
					printf("new\n");
				}*/
				break;
			}
		}
		/*
		if (val == 37710) {
			printf("nd = %lld val = %d\n", nd, nd->val);
		}		*/
		splay(nd);
	}
	void erase(int val) {
		if (--size_ == 0) {
			clear();
			return;
		}
		Node *nd = root, *s, *f;
		while (nd->val != val) {
			nd = nd->s[nd->val < val];
		}
		while (nd->s[0] && nd->s[1]) {
			rotate(nd->s[0]);
		}
		f = nd->f;
		s = nd->s[nd->s[1] != 0];
		
		if (f) {
			f->s[nd == f->s[1]] = s;
		}
		if (s) {
			s->f = f;
		}
		if (s) {
			splay(s);
		} else {
			splay(f);
		}
	}
	void clear() {
		pidx = 0;
		root = 0;
		size_ = 0;
	}
};

