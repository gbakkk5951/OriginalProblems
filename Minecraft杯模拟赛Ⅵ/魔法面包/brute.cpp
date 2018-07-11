#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
namespace OI {
const int MXN = 2e6 + 10;
int ans[MXN >> 1][21];//开多了
int log[MXN >> 1];
int n, kn;
struct Node {
	Node *s[2], *fail;
	Node *f[21];
	int len, h, cnt[21];
}pool[MXN];
int pidx;
inline Node *new_(int len) {
	Node *nd = &pool[pidx++];
	memset(nd, 0, sizeof(Node));
	nd->len = len;
	return nd;
}//AC
struct PalinTree {
	PalinTree() {
		clear();
	}
	Node *r1, *r0, *lst;
	int str[MXN], cn;
	void clear() {
		cn = pidx = 0;
		r1 = new_(-1);
		r1->fail = r1;
		r0 = new_(0);
		r0->fail = r1;
		lst = r1;
		str[0] = -1;
	}//AC
	void insert(int val, int aid) {
		Node *nd = lst;
		str[++cn] = val;
		while (nd->len + 2 > n || str[cn - 1 - nd->len] != val) nd = nd->fail;
		if (!nd->s[val]) {
			Node *s = new_(nd->len + 2), *up = nd->fail, *f;
			while (str[cn - 1 - up->len] != val) up = up->fail;
			f = s->fail = up->s[val] ? up->s[val] : r0;
			s->h = f->h + 1;
			memcpy(s->cnt, f->cnt, sizeof(s->cnt));
			for (int i = 1; i <= kn; i++) {
				s->cnt[i] += s->len % i == 0;
			}
			s->f[0] = f;
			for (int I = 1; 1 << I <= s->h; I++) {
				s->f[I] = s->f[I - 1]->f[I - 1];
			}
			nd->s[val] = s;
		}
		nd = nd->s[val];
		//Ac
		//贡献答案
		if (aid) {
			Node *top, *f;	
			for (int i = 1; i <= kn && i <= nd->len; i++) {
				if (nd->cnt[i] == nd->len / i) {
					ans[aid][i] = max(ans[aid][i], nd->cnt[i] * i);
					continue;
				}
				top = nd;
				for (int I = log[top->h]; I >= 0; I--) {
					f = top->f[I];
					if (f && f->cnt[i] < f->len / i) {
						top = f;
					}
				}
				top = top->fail;//神Tm = f->fail
				ans[aid][i] = max(ans[aid][i], top->cnt[i] * i);
			}
		}
		lst = nd;
		//AC
	}
}tree;
struct _Main {
	char str[MXN];
	_Main() {
		scanf("%d%d%s", &n, &kn, str + 1);
		for (int i = 1; i <= n; i++) {
			log[i] = log[i - 1] + (i == 1 << log[i - 1] + 1);
		}
		for (int i = 1; i <= n; i++) {
			str[i] -= '0';
		}
		memmove(str + n + 1, str + 1, n * sizeof(char));//sizeof char
		for (int i = 1; i <= 2 * n - 1; i++) {
			tree.insert(str[i], i >= n ? (i - 1) % n + 1 : 0);
		}
		for (int i = 1; i <= n; i++) {
			swap(str[i], str[(n << 1) - i + 1]);
		}
		tree.clear();
		for (int i = 1; i <= 2 * n - 1; i++) {
			tree.insert(str[i], i >= n ? n - ((i - 1) % n + 1) + 1 : 0);
		}
		int out;
		for (int i = 1; i <= n; i++) {
			out = 0;
			for (int j = 1; j <= kn; j++) {
				out ^= ans[i][j] * j;
			}
			printf("%d\n", out);
		}
	}//AC
}std;
}
