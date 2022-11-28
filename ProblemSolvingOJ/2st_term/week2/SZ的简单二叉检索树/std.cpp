#include <bits/stdc++.h>
using namespace std;
struct Node {
	int value, cnt;
	Node *f, *s[2];
	Node(int value, Node *f) {
		this->f = f;
		this->value = value;
		cnt = 1;
		s[0] = s[1] = nullptr;//写成了s[0] = s[0] = nullptr
	}
};

class Tree {
	Node *root = nullptr;
	void swapdata(Node *a, Node *b) {
		swap(a->value, b->value);
		swap(a->cnt, b->cnt);
	}
	void print(Node *nd) {
		printf("%d ", nd->value);
		for (int i = 0; i < 2; ++i) {
			if (nd->s[i]) print(nd->s[i]);
		}
	}
public:
	void erase(int v) {
		Node *nd = root;
		while (nd) {
			if (nd->value == v) {
				if (--nd->cnt) break;
				if (nd->s[0] && nd->s[1]) {
					Node *succ = nd->s[1];
					while (succ->s[0]) succ = succ->s[0];
					swapdata(succ, nd);
					nd = succ;
				}
				// one or zero kid
				Node *s = nd->s[!!nd->s[1]];
				if (nd->f) nd->f->s[nd == nd->f->s[1]] = s;
				else root = s;
				if (s) s->f = nd->f;
				delete nd;
				break;
			} else {
				nd = nd->s[nd->value < v];
			}
		}
	}
	void insert(int v) {
		if (!root) {
			root = new Node(v, nullptr);
			return;
		}
		Node *nd = root;
		while (1) {
			if (nd->value == v) {
				++nd->cnt;
				return;
			}
			int spo = v > nd->value;
			if (nd->s[spo]) {
				nd = nd->s[spo];
			} else {
				nd->s[spo] = new Node(v, nd);
				return;
			}
		}
	}
	void print() {
		if (root) print(root);
		printf("\n");
	}
}tree;

int main() {
	int M;
	cin >> M;
	for (; M--; ) {
		int op, x;
		cin >> op;
		switch (op) {
			case 0 : {
				tree.print();
				break;
			}
			case 1 : {
				cin >> x;
				tree.insert(x);
				break;
			}
			case 2 : {
				cin >> x;
				tree.erase(x);
				break;
			}
			default : {
				throw "Wrong input";
			}
		}
	}
	return 0;
}
