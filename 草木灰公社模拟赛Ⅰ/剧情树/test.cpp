using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>

namespace OI {
typedef long long lld;
typedef double lf;
const int 
	MAXN = 100010,
	INF = 0x3f3f3f3f
;
struct Node	{
	Node *f, *s[2], *nxt;
	int val, rand, id;
	lf m[2], v;
	void mark(lf l, lf r) {
		m[0] = l; m[1] = r; v = (l + r) / 2.0;
	}
};

class SuffixTreap {
public:
	Node p[MAXN];
	Node *root;
	int pidx;
	Node *node(int val, int id, Node *nxt = 0,Node *f = 0) {
		Node *nd = &p[pidx++];
		nd->val = val;
		nd->nxt = nxt;
		nd->f = f;
		nd->rand = rand() & ((1 << 30) - 1);
		nd->id = id;
		return nd;
	}
	SuffixTreap() {
		root = node(INF, -1);
		root->rand = -INF;
		root->mark(0, 2);
	}
	int cmp(int val, Node *nxt, Node *nd) {
		if (val != nd->val) {
			return val > nd->val;
		}
		return nxt->v > nd->nxt->v;
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
	Node* insert(int val, int id, Node *nxt) {
		Node *nd = root;
		while (1) {
			int pos = cmp(val, nxt, nd);
			if (nd->s[pos]) {
				nd = nd->s[pos];
			} else {
				nd = nd->s[pos] = node(val, id, nxt, nd);
				break;
			}
		}
		while (nd->f->rand > nd->rand) {
			rotate(nd);
		}
		lf m[2];
		Node *f = nd->f;
		int pos = nd == f->s[1];
		m[pos] = f->m[pos];
		m[pos ^ 1] = f->v;
		remark(nd, m[0], m[1]);
		return nd;
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
			while (nd->s[pos ^ 1]) {
				nd = nd->s[pos ^ 1];
			}
			return nd;
		}
		while (nd->f && nd != nd->f->s[pos ^ 1]) {
			nd = nd->f;
		}
		nd = nd->f;
		return (nd == root) ? 0 : nd;
	}
	void erase(Node *nd) {
		while (1) {
			int pos = nd->s[1] != 0;
			if (nd->s[0] && pos) {
				pos = nd->s[1]->rand < nd->s[0]->rand;
				rotate(nd->s[pos]);
			} else {
				Node *f = nd->f, *s = nd->s[pos];
				f->s[nd == f->s[1]] = s;
				if (s) {
					s->f = f;
				}
				break;
			}
		}
	}
}tree[2];
const int LEA = 1, TOT = 0;
const int MAXBIT = 16;
const int HC = 2;
const lld mod[HC + 2] = {31525197391593473LL, 31525197391593467LL};
const lld base[HC + 2] = {100019, 100043};
lld pow[HC + 2][MAXBIT + 1];
lld mul(lld a, lld b, lld mod) {
	lld ret = (a * b - (lld)((lf)a / mod * b) * mod) % mod;
	if (ret < 0) ret += mod;
	return ret;
}

struct Hash {
	lld hash[HC];
	bool operator == (const Hash &b) {
		return memcmp(this, &b, sizeof(Hash)) == 0;
	}
	void operator <<= (int bit) {
		for (int i = 0; i < HC; i++) {
			hash[i] = mul(hash[i], pow[i][bit], mod[i]);
		}
	}
	void operator += (const Hash &b) {
		for (int i = 0; i < HC; i++) {
			hash[i] += b.hash[i];
			if (hash[i] >= mod[i]) hash[i] -= mod[i];
		}
	}
	void operator += (int a) {
		for (int i = 0; i < HC; i++) {
			hash[i] = (hash[i] + a + 1) % mod[i]; 
		}
	}
	void zero() {
		memset(this, 0, sizeof(Hash));
	}
};
void initHash() {
	for (int i = 0; i < HC; i++) {
		pow[i][0] = base[i];
	}
	for (int I = 1; I <= MAXBIT; I++) {
		for (int j = 0; j < HC; j++) {
			pow[j][I] = mul(pow[j][I - 1], pow[j][I - 1], mod[j]);
		}
	}
}


int fa[MAXN][MAXBIT + 1];
Hash hash[MAXN][MAXBIT + 1];
int out[MAXN];
int head[MAXN];
int h[MAXN];
const int NXT = 1, DST = 0;
int s[MAXN][2];
int val[MAXN];
int sidx;
Node *ptr[2][MAXN];

struct _Main {
	void add(int f, int s) {
		sidx++;
		OI::s[sidx][DST] = s;
		OI::s[sidx][NXT] = head[f];
		head[f] = sidx;
	}
	void insert(int f, int s, int v) {
		add(f, s);
		if (++out[f] == 1) {
			tree[LEA].erase(ptr[LEA][f]);
		}
		for (int i = 0; i < 2; i++) {
			ptr[i][s] = tree[i].insert(v, s, ptr[TOT][f]);
		}
		fa[s][0] = f;
		val[s] = v;
		h[s] = h[f] + 1;
		hash[s][0].zero();
		hash[s][0] += v;
		Hash tmp;
		for (int I = 1; 1 << I <= h[s]; I++) {
			fa[s][I] = fa[fa[s][I - 1]][I - 1];
			tmp = hash[fa[s][I - 1]][I - 1];
			tmp <<= I - 1;
			hash[s][I] = hash[s][I - 1];
			hash[s][I] += tmp;
		}
	}
	int match(int a, int b) {
//		printf("match %d %d", a, b);
		int mnlen = min(h[a], h[b]);
		int ret = 0;
		for (int I = MAXBIT; I >= 0; I--) if (1 << I <= mnlen) {
			if (hash[a][I] == hash[b][I]) {
				ret += 1 << I;
				mnlen -= 1 << I;
				a = fa[a][I];
				b = fa[b][I];
			}
		}
//		printf(" = %d\n", ret);
		return ret;
	}
	void ask(int a) {
		int lcp = 0;
		for (int i = 0; i < 2; i++) {
			Node *near = tree[LEA].near(ptr[LEA][a], i);
			if (near) {
				lcp = max(lcp, match(near->id, a));
			}
		}
		printf("%d\n", h[a] - lcp);
	}
	void del(int id) {
		if (id == 0) return;
		int f = fa[id][0];
		if (--out[f] == 0) {
			ptr[LEA][f] = tree[LEA].insert(val[f], f, ptr[TOT][f]->nxt);
		}
		del_dfs(id);
	}
	void del_dfs(int id) {
		int scnt = 0, t;
		for (int i = head[id]; i; i = s[i][NXT]) if(fa[t = s[i][DST]][0] == id) {
			del_dfs(t);
			scnt++;
		}
		tree[TOT].erase(ptr[TOT][id]);
		if (scnt == 0) {
			tree[LEA].erase(ptr[LEA][id]);
		}
		out[id] = 0;
		h[id] = 0;
		fa[id][0] = -1;
		head[id] = 0;
	}
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
		int i, j, k;
		int op; 
		int a, b, c;
		int Q, Qn;
		initHash();
		for (i = 0; i < 2; i++) {
			ptr[i][0] = tree[i].insert(0, 0, tree[i].root);
		}
		h[0] = 1;
		hash[0][0] += 0;
		read(Qn);
		for (Q = 1; Q <= Qn; Q++) {
			read(op); read(a);
			switch (op) {
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
					ask(a);
					break;
				}
			}
		}
	}

}plot;

}

