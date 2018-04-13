using namespace std;
int main() {}
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
namespace OI {
typedef long long lld;
const int MXN = 500015;
const int MXP = 19;
const int DST = 0, NXT = 1;
const lld MOD[2] = {(lld)1e8 + 7, (lld)1e9 + 9};

struct LS {
	int operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
template <int mxsize>
struct ArrayTree {
	int n;
	int node[mxsize];
	int query(int nd) {
		int ret = 0;
		for (; nd; nd -= nd & (-nd)) {
			ret += node[nd];
		}
		return ret;
	}
	void add(int nd, int val) {
		for (; nd <= n; nd += nd & (-nd)) {
			node[nd] += val;
		}
	}
};
ArrayTree<MXN << 1>dfstree;
ArrayTree<MXN> cantortree;
struct SegTree {
	int n;
	int node[1050000];
	void occupy(int pos) {
		int nd = 1, nl = 1, nr = n;
		while (1) {
			node[nd]++;
			if (nl == nr) break;
			int mid = nl + nr >> 1;
			if (pos <= mid) {
				nd = ls[nd];
				nr = mid;
			} else {
				nd = rs[nd];
				nl = mid + 1;
			}
		}
	}
	int query(int nd, int nl, int nr, int l, int r) {
		if (nl == nr) {//assert n > 1
			return nl;
		}
		int ret = r + 1;
		int mid = nl + nr >> 1;
		if (l <= mid && node[ls[nd]]) {
			ret = query(ls[nd], nl, mid, l, r);
		}
		if (ret == r + 1 && r > mid && node[rs[nd]]) {
			ret = query(rs[nd], mid + 1, nr, l, r);
		}
		return ret;
	}
}occupytree;

struct _Main {
	int l[MXN], r[MXN];
	int f[MXN][MXP + 1], mn[MXN][MXP + 1], h[MXN], in[MXN], out[MXN];
	int idx;
	int size[MXN];
	void dfs(int nd, int fa) {
		f[nd][0] = fa;
		h[nd] = h[fa] + 1;
		mn[nd][0] = fa;
		in[nd] = ++idx;
		size[nd] = 1;
		for (int I = 1; 1 << I < h[nd]; I++) {
			f[nd][I] = f[f[nd][I - 1]][I - 1];
			mn[nd][I] = min(mn[nd][I - 1], mn[f[nd][I - 1]][I - 1]);
		}
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd);
				size[nd] += size[t];
			}
		}
		out[nd] = ++idx;
	}
	int n;
	int eidx;
	int head[MXN], edge[MXN << 1][2];
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	int root;
	lld fac[MXN][2];
	void prepro() {
		read(n); read(root);
		for (int i = 1; i <= n - 1; i++) {
			int a, b;
			read(a); read(b);
			add(a, b); add(b, a);
		}
		dfs(root, 0);
		r[0] = n;
		dfstree.n = n << 1;
		occupytree.n = n;
		cantortree.n = n;
		for(int I = 0; I < 2; I++) {
			fac[0][I] = 1;
			for (int i = 1; i <= n; i++) {
				fac[i][I] = fac[i - 1][I] * i % MOD[I];
			}
		}
	}
	int gettop(int nd) {//第一个小于的数
		int a = nd;
		for (int I = MXP; I >= 0; I--) {
			if (mn[a][I] > nd) {
				a = f[a][I];
			}
		}
		return f[a][0];
	}
	void getans(int nd) {
		size[nd] += dfstree.query(in[nd]);
		size[nd] -= dfstree.query(out[nd]);
		
		int top = gettop(nd);
		
		if (top != f[nd][0]) {
			dfstree.add(in[top] + 1, -size[nd]);
			dfstree.add(in[nd], size[nd]);	
		} 
		
		l[nd] = occupytree.query(1, 1, n, l[top] + 1, r[top]) - size[nd];
		occupytree.occupy(l[nd]);
		r[nd] = l[nd] + size[nd] - 1; //不用考虑原size 因为被剪掉的部分的节点不会来找nd
	}
	void solve() {
		for (int i = 1; i <= n; i++) {
			getans(i);
		}
		lld ans[2] = {0, 0};
		for (int i = n; i; i--) {
			lld tmp = cantortree.query(l[i]);
			if (tmp) for (int I = 0; I < 2; I++) {
				ans[I] = (ans[I] + tmp * fac[n - i][I]) % MOD[I];
			}
			cantortree.add(l[i], 1);
		}
		for (int I = 0; I < 2; I++) {
			printf("%lld ", ans[I]);
		}
	}
	_Main() {
		prepro();
		solve();
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
}tree;
}
