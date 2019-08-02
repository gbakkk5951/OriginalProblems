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
const int MXN = 5e6 + 10;
struct Node {
	Node *s[2], *fail;
	char end;
}pool[MXN];
Node *root;
int idx;
inline Node *new_node() {
	return &pool[idx++];
}
struct _Main {
	char buf[MXN];
	char dst[MXN];
	int n;
	
	Node *Q[MXN];
	int qh, qt;
	void build() {
		root->fail = root;
		for (int i = 0; i <= 1; i++) {
			if (root->s[i]) {
				root->s[i]->fail = root;
				Q[qt++] = root->s[i];
			} else {
				root->s[i] = root;
			}
		}
		while (qt > qh) {
			Node *nd = Q[qh++];
			nd->end |= nd->fail->end;
			for (int i = 0; i <= 1; i++) {
				if (nd->s[i]) {
					nd->s[i]->fail = nd->fail->s[i];
					Q[qt++] = nd->s[i];
				} else {
					nd->s[i] = nd->fail->s[i];
				}
			}
		}
	}
	int ans;
	void run() {
		Node *nd = root;
		for (int i = 0; dst[i]; i++) {
			nd = nd->s[dst[i] - '0'];
			if (nd->end) {
				ans++;
				nd = root;
			}
		}
	}
	_Main() {
		root = new_node();
		read(n);
		scanf("%s", dst);
		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			Node *nd = root;
			for (int j = 0; buf[j]; j++) {
				if (!nd->s[buf[j] - '0']) {
					nd->s[buf[j] - '0'] = new_node();
				}
				nd = nd->s[buf[j] - '0'];
			}
			nd->end = 1;
		}
		build();
		run();
		printf("%d", ans);
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
