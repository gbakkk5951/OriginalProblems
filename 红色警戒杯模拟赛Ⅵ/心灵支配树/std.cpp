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
typedef set<int>::iterator it;
const int DST = 0, NXT = 1;
const int MXN = 1e5 + 10;
int dfn[MXN], sum[MXN], val[MXN], ctrl[MXN], h[MXN];
int head[MXN], edge[MXN << 1][2];//忘了 * 2
int log[MXN], f[MXN][17];
int ans[MXN], size[MXN], cho[MXN];
int dfnidx;
struct Cmp {
	bool operator () (int a, int b) {
		return dfn[a] < dfn[b];
	}
};
set<int, Cmp>tree;

void dfs(int nd, int fa) {
	dfn[nd] = ++dfnidx;
	sum[nd] = sum[fa] + val[nd];
	h[nd] = h[fa] + 1;
	f[nd][0] = fa;
	for (int I = 1; 1 << I < h[nd]; I++) {
		f[nd][I] = f[f[nd][I - 1]][I - 1];
	}
	size[nd] = 1;
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		t = edge[e][DST];
		if (t != fa) {
			dfs(t, nd);
			size[nd] += size[t];
			if (size[t] > size[cho[nd]]) {
				cho[nd] = t;
			}
		}
	}
}
int getlca(int a, int b) {
	if (h[a] < h[b]) swap(a, b);
	for (int I = log[h[a] - h[b]]; I >= 0; I--) {
		if (h[a] - (1 << I) >= h[b]) {
			a = f[a][I];
		}
	}
	if (a == b) return a;
	for (int I = log[h[a] - 1]; I >= 0; I--) {
		if (f[a][I] != f[b][I]) {
			a = f[a][I];
			b = f[b][I];
		}
	}
	return f[a][0];
}
inline int getdis(int a, int b) {
	return h[a] + h[b] - (h[getlca(a, b)] << 1);
}
inline it getpre(it a) {
	a = a == tree.begin() ? tree.end() : a;
	return --a;
}
inline it getnxt(it a) {
	if (++a == tree.end()) {
		a = tree.begin();
	}
	return a;
}
int top, now;
void insert(int nd) {
	if (tree.empty()) {
		tree.insert(nd);
		now = sum[nd] - val[nd];
		top = nd;
		return;
	}
	if (h[nd] < h[top]) {
		top = nd;
	}
	it pos = tree.insert(nd).first;
	int plca = getlca(nd, *getpre(pos)), nlca = getlca(nd, *getnxt(pos));
	int lca = h[plca] > h[nlca] ? plca : nlca;
	if (h[lca] < h[top]) {
		top = lca;
	}
	now += sum[nd] - sum[lca] - val[nd];
}
void collect(int nd, int fa) {
	insert(ctrl[nd]);
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		t = edge[e][DST];
		if (t != fa) {
			collect(t, nd);
		}
	}
}
void getans(int nd, int fa) {
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		t = edge[e][DST];//神Tm没这一句
		if (t != fa && t != cho[nd]) {
			getans(t, nd);
			tree.clear();
		}
	}
	if (cho[nd]) {
		getans(cho[nd], nd);
	}
	insert(ctrl[nd]);//神tm发现了没改，写暴力的时候再发现
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		t = edge[e][DST];//NXT..
		if (t != fa && t != cho[nd]) {
			collect(t, nd);
		}
	}
	ans[nd] = now - sum[top] + val[top];
}
struct _Main {
	int n, Qn, Tn;
	_Main() {
		int a, b;
		read(n);
		for (int i = 1; i <= n; i++) {
			read(val[i]); read(ctrl[i]);
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		log[0] = -1;
		for (int i = 1; i <= n; i++) {
			log[i] = log[i - 1] + (i == 1 << log[i - 1] + 1);
		}
		dfs(1, 0);
		getans(1, 0);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
	int eidx;
	inline void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
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
