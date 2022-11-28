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
#include <cmath>
#include <complex>
#include <cassert>
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
typedef long double Lf;
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1e6 + 10;
const char S = 'S', s = 's', h = 'h';
struct Node {
	Node *l, *r;
	int sum;
	char type;
}pool[MXN << 1];
Node *lh, *rh, *null;
int pidx;
Node* new_(char type) {
	Node *ret = &pool[pidx++];
	*ret = (Node) {null, null, 1, type};
	return ret;
}
struct _Main {
	int ans;
	void link(Node *l, Node *r) {
		l->r = r;
		r->l = l;
	}
	void eraser() {
		Node *l = rh->l;
		l->r = null;
		l->type = S;
		l->sum += rh->sum;
		rh = l;
		ans = max(ans, l->sum);
	}
	void rinsert(char type) {
		if (type == S) ans = max(ans, 1);
		Node *nd = new_(type);
		if (rh != null) {
			link(rh, nd);
			rh = nd;
		} else {
			rh = lh = nd;
		}
		if (rh->type == h && rh->l->type == S && rh->l->l->type == s) {
			eraser(); eraser();
		} else if (rh->type == h && rh->l->type == s) {
			eraser();
		}
		if (rh->type == S && rh->l->type == S) {
			eraser();
		}
	}
	void erasel() {
		Node *r = lh->r;
		r->l = null;
		r->type = S;
		r->sum += lh->sum;
		lh = r;
		ans = max(ans, r->sum);
	}
	void linsert(char type) {
		if (type == S) ans = max(ans, 1);
		Node *nd = new_(type);
		if (lh != null) {
			link(nd, lh);
			lh = nd;
		} else {
			lh = rh = nd;
		}
		if (lh->type == s && lh->r->type == S && lh->r->r->type == h) {
			erasel(); erasel();
		} else if (lh->type == s && lh->r->type == h) {
			erasel();
		}
		if (lh->type == S && lh->r->type == S) {
			erasel();
		}
	}
	int n, m;
	char buf[10];
	_Main() {
		freopen("hss.in", "r", stdin);
		freopen("hss.out", "w", stdout);
		null = &pool[pidx++];
		null->l = null->r = null;
		rh = lh = null;
		read(n); read(m);
		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			rinsert(buf[0]);
		}
		printf("%d\n", ans);
		for (int i = 1, op; i <= m; i++) {
			read(op);
			scanf("%s", buf);
			if (op == 1) {
				linsert(buf[0]);
			} else {
				rinsert(buf[0]);
			}
			printf("%d\n", ans);
		}
		fclose(stdout);
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
