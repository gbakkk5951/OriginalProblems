#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
const int DST = 0, NXT = 1;
const int MXN = 2e6 + 10;
int n, Qn, Tn;
int k;
int ans[MXN >> 1][21];
struct Node {
	Node *s[2], *fail;
	int ans[21];
	int len;
}pool[MXN];
int pidx;
Node *new_(int len) {
	Node *nd = &pool[pidx++];
	nd->s[0] = nd->s[1] = 0;
	nd->len = len;
	return nd;
}
struct PalinTree {
	Node *r0, *r1, *lst;
	char str[MXN];
	int n;
	PalinTree() {
		init();
	}
	void init() {
		n = pidx = 0;
		r1 = new_(-1);
		r1->fail = r1;
		r0 = new_(0);
		r0->fail = r1;
		lst = r1;
		str[0] = -1;
	}
	void insert(char val, int aid) {
		Node *nd = lst;
		str[++n] = val;
		while (str[n - 1 - nd->len] != val || nd->len + 2 > OI::n) nd = nd->fail;
		//第二个条件忘了加，加了之后没注意到重名，需要OI::
		
		if (!nd->s[val]) {
			Node *s, *f;
			s = new_(nd->len + 2);
			f = nd->fail;
			while (str[n - 1 - f->len] != val) f = f->fail;
			f = s->fail = f->s[val] ? f->s[val] : r0;
			for (int i = 1; i <= k; i++) {//神Tm nd
				if (s->len == f->ans[i] + i) {
					s->ans[i] = f->ans[i] + i;
				} else {
					s->ans[i] = f->ans[i];
				}
			}
			nd->s[val] = s;
		}
		nd = nd->s[val];
		if (aid) {
			for (int i = 1; i <= k; i++) {
				ans[aid][i] = max(ans[aid][i], nd->ans[i]);
			}
		}
		lst = nd;
	}
}tree;
struct _Main {
char str[MXN];
	_Main() {
		read(n); read(k);
		scanf("%s", str + 1);
		for (int i = 1; i <= n; i++) {
			str[i] -= '0'; 
		}
		memmove(str + n + 1, str + 1, n);
		for (int i = 1; i <= 2 * n - 1; i++) {
			tree.insert(str[i], i >= n ? (i - 1) % n + 1 : 0);
		}
		tree.init();
		for (int i = 2 * n - 1; i >= 1; i--) {
			tree.insert(str[i], i <= n ? i : 0);
		}
		int out;
		for (int i = 1; i <= n; i++) {
			out = 0;
			for (int j = 1; j <= k; j++) {
				out ^= ans[i][j] * j;
			}
			printf("%d\n", out);
		}
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
