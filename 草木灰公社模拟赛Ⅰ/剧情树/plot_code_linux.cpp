using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <iostream>
namespace OI {
typedef long long lld;
typedef unsigned long long llu;
typedef double lf;
const int MAXN = 100050;
const lf EPS = 1e-14;
const int MAX_POW = 20;
const int INF = 0x3f3f3f3f;
int lrand() {
	return rand() & ((1 << 30) - 1);
}
struct Node {
	Node *f, *s[2];
	lf m[2], v;
	int val, idx, rand;
	Node *tf;
	void mark(lf l, lf r) {
		m[0] = l; m[1] = r; v = (l + r) / 2.0;
	}
};
bool eq(lf a, lf b) {
	return a + EPS > b && a - EPS < b;
}
class SuffixTreap { // 小根堆 
public:
	queue<Node *>q;
	Node null;
	Node *root;
	Node pool[MAXN];
	int pidx;
	Node *new_node(int val, int idx, Node *tf, Node *f) {
		Node *nd;
		if (q.empty()) {
			nd = &pool[pidx++];
		} else {
			nd = q.front();
			nd->s[0] = nd->s[1] = 0;
			q.pop();
		}
		nd->val = val;
		nd->idx = idx;
		nd->tf = tf;
		nd->f = f;
		nd->rand = lrand();
		return nd;
	}
	SuffixTreap() {
		null.rand = -INF;
		null.val = INF;
		null.mark(0, 2);
		root = &null;
	}
	inline int cmp(int val, int idx, Node *tf, Node *nd) {
		if (val != nd->val) {
			return val > nd->val;
		}
		if (!eq(tf->v, nd->tf->v)) {
			return tf->v > nd->tf->v;
		}
		return idx > nd->idx;
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
	}
	
	Node* insert(int val, int idx, Node *tf, bool mark = true) {
		Node *nd = root;
		while (1) {
			int pos = cmp(val, idx, tf, nd);
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
	Node* near(Node *nd, int pos) {
		if (nd->s[pos]) {
			nd = nd->s[pos];
			while(nd->s[pos ^ 1]) {
				nd = nd->s[pos ^1];
			}
			return nd;
		}
		Node *f = nd->f;
		while (f && nd != f->s[pos ^ 1]) {
			nd = f;
			f = nd->f;
		}
		return f == root ? 0 : f;
	}
	void erase(Node *nd) {
		Node *s, *f;
		int pos;
		while(1) {
			pos = nd->s[1] == 0;
			if (pos || nd->s[0] == 0) {
				f = nd->f;
				s = nd->s[pos ^ 1];
				f->s[nd == f->s[1]] = s;
				if (s) {
					s->f = f;
				}
				break;
			}
			s = nd->s[nd->s[1]->rand < nd->s[0]->rand];
			rotate(s);
		}
		q.push(nd);
	}
}tree[2];

llu mul(lld a, lld b, lld mod) {
	lld ret = (a * b - (lld)((lf)a / mod * b) * mod) % mod;
	if (ret < 0) {
		return ret += mod;
	}
	return ret;
}

const int HASH_CNT = 3;
const llu MOD[HASH_CNT] = {7205759403792827LL, 460846009635997LL, 46115476719943LL};
const llu BASE[HASH_CNT] = {37, 10007, 100003};
llu pow[HASH_CNT][MAX_POW];
struct Hash {
	llu val[HASH_CNT];
	void operator <<= (int val) {
		for (int i = 0; i < HASH_CNT; i++) {
			this->val[i] = mul(this->val[i], pow[i][val], MOD[i]);
		}
	}
	void operator += (int val) {
		for (int i = 0; i < HASH_CNT; i++) {
			this->val[i] = (this->val[i] + val % (BASE[i] - 1) + 1) % MOD[i]; 
		}
	}
	void operator += (const Hash &b) {
		for (int i = 0; i < HASH_CNT; i++) {
			val[i] = (val[i] + b.val[i]) % MOD[i];
		}
	}
	bool operator == (Hash &b) const {
		for (int i = 0; i < HASH_CNT; i++) {
			if (val[i] != b.val[i]) {
				return 0;
			}
		}
		return 1;
	}
	
	void zero() {
		memset(this, 0, sizeof(Hash));
	}
};


const int TOT = 0, LEA = 1;
const int DST = 0, NXT = 1;
struct _Main {

Node *ptr[2][MAXN];
int f[MAXN][MAX_POW];
int out[MAXN];
int head[MAXN];
int val[MAXN];
int s[MAXN][2];
int h[MAXN];
int eidx;

Hash hash[MAXN][MAX_POW];

void add(int f, int s) {
	eidx++;
	this->s[eidx][NXT] = head[f];
	this->s[eidx][DST] = s;
	head[f] = eidx;
}
void insert(int _f, int s, int v) {
	val[s] = v;
	add(_f, s);
	f[s][0] = _f;
	hash[s][0].zero();
	hash[s][0] += v;
	h[s] = h[_f] + 1;
	for (int i = 1; 1 << i <= h[s]; i++) {
		f[s][i] = f[f[s][i - 1]][i - 1];
		hash[s][i] = hash[f[s][i - 1]][i - 1];
		hash[s][i] <<= i - 1;
		hash[s][i] += hash[s][i - 1];
	}
	
	if (++out[_f] == 1) {
		tree[LEA].erase(ptr[LEA][_f]);
		ptr[LEA][_f] = 0;
	}
	
	ptr[TOT][s] = tree[TOT].insert(v, s, ptr[TOT][_f]);
	ptr[LEA][s] = tree[LEA].insert(v, s, ptr[TOT][_f], false);
}
void insert_root() {
	hash[0][0] += 0;
	h[0] = 1;
	for (int i = 0; i < 2; i++) {
		ptr[i][0] = tree[i].insert(0, 0, tree[TOT].root, i == TOT);
	}
}

void del(int nd) {
	if (nd == 0) {
		return;
	}
	int f = this->f[nd][0];
	only_del(nd);	
	if (--out[f] == 0) {
		if (f != 0) {
			ptr[LEA][f] = tree[LEA].insert(val[f], f, ptr[TOT][this->f[f][0]], false);	
		} else {
			ptr[LEA][f] = tree[LEA].insert(val[f], f, tree[LEA].root, false);
		}

	}
}
void only_del(int nd) {
	int t;
	for (int i = head[nd]; i; i = s[i][NXT]) {
		if (f[t = s[i][DST]][0] == nd) {
			only_del(t);
		} 
	}
	for (int i = 0; i < 2; i++) {
		if (ptr[i][nd]) {
			tree[i].erase(ptr[i][nd]);
			ptr[i][nd] = 0;
		}
	}
	
	out[nd] = f[nd][0] = head[nd] = 0;
}

int getlcp(int a, int b) {
	int i;
	int ret = 0;
	int deep = min(h[a], h[b]);
	for (i = mx_bit; i >= 0; i--) {
		if (deep >= 1 << i) {
			if (hash[a][i] == hash[b][i]) {
				a = f[a][i]; b = f[b][i];
				ret += 1 << i;
				deep -= 1 << i;
			}
		}
	}
	return ret;
}
int ask(int nd) {
	int lcp = 0;
	Node *near = 0;
	for (int i = 0; i < 2; i++) {
		near = tree[LEA].near(ptr[LEA][nd], i);
		if (near) {
			lcp = max(lcp, getlcp(nd, near->idx));
		}
	}	
	return h[nd] - lcp;
}
int mx_bit;

template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}

_Main() {
	int i, j;
	int Q, Qn;
	int oper, a, b, c;
	read(Qn);
	for (mx_bit = 0; (1 << mx_bit + 1) <= Qn; mx_bit++);
	for (i = 0; i < HASH_CNT; i++) {
		pow[i][0] = BASE[i];
		for (j = 1; j <= mx_bit; j++) {
			pow[i][j] = mul(pow[i][j - 1], pow[i][j - 1], MOD[i]);
		}
	}
	insert_root();
	for (Q = 1; Q <= Qn; Q++) {
		read(oper); read(a);
		switch (oper) {
			case 1: {
				read(b); read(c);	
				insert(a, b, c);	
				break;
			}
			case 2: {
				del(a);
				break;
			}
			case 3: {
				printf("%d\n", ask(a));
				break;
			}
		}
	}
	
	
}


}plot;

}

//注意流控语句
//注意初始节点插入 
//O（n） ！= n 有些可以达到2n 需要加倍空间或垃圾回收 
