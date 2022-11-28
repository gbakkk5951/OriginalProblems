using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
namespace OI {
const int INF = 0x3f3f3f3f;
const int MXN = 100005;
vector<int> idv[MXN * 16];
int vidx;
int vid[MXN * 16];
int npc[MXN], ans;

int v[MXN];
int x[MXN], y[MXN], z[MXN];
int xn[MXN], yn[MXN], zn[MXN];
int xs[MXN], ys[MXN], zs[MXN];
int n;
struct Node {
	Node* s[2];
	int mn, id;
}pool[MXN * 17 * 19];
int pidx;
Node* new_() {
	Node *nd = &pool[pidx++];
	nd->mn = INF;
	return nd;
}
struct SegTree {
	Node *root;
	void insert(int id) {
		int pos = yn[id], nl = 1, nr = n, mid, spo, val = zn[id];
		Node *nd = root;
		nd->mn = min(nd->mn, val);
		while (nl < nr) {
			mid = nl + nr >> 1;
			if (spo = pos > mid) {
				nl = mid + 1;
			} else {
				nr = mid;
			}
			if (nd->s[spo] == 0) {
				nd->s[spo] = new_();
			}
			nd = nd->s[spo];
			nd->mn = min(nd->mn, val);
		}
		if (nd->id == 0) {
			nd->id = ++vidx;
		}
		idv[nd->id].push_back(id);
	}
	void getnpc(Node *nd, int nl, int nr, int yy, int zz) {
		if (nl == nr) {
//			printf("nl = nr vid = %d size = %d\n", vid[nd->id], idv[nd->id].size());
			int id = nd->id, t = 0;
			for ( ; vid[id] < idv[id].size() && zn[t = idv[id][vid[id]]] <= zz; vid[id]++) {
				if (!v[t]) {
//					printf("got %d\n", t);
					npc[++ans] = t;
					v[t] = 1;
				}
			}
//			printf("zn %d = %d\n", t, zn[t]);
//			if (idv[id].size() > vid[id] + 1)
//			printf("zn %d = %d\n", idv[id][vid[id] + 1], zn[idv[id][vid[id] + 1]]);
			nd->mn = (vid[id] == idv[id].size()) ? INF : zn[t];
//			if (vid[id] == idv[id].size() || zn[t = idv[id][vid[id]]] > zz) {
//				printf("nd->mn = %d, zn[t] = %d\n", nd->mn, zn[t]);
//			}
			return;
		}
		int mid = nl + nr >> 1;
		if (nd->s[0] && nd->s[0]->mn <= zz) {
			getnpc(nd->s[0], nl, mid, yy, zz);
		}
		if (yy > mid && nd->s[1] && nd->s[1]->mn <= zz) {
			getnpc(nd->s[1], mid + 1, nr, yy, zz);
		}
		nd->mn = min(nd->s[0] ? nd->s[0]->mn : INF, nd->s[1] ? nd->s[1]->mn : INF);
	}
};
struct ArrayTree {
	SegTree node[MXN];
	int lb(int a) {
		return a & (-a);
	}
	void insert(int id) {
		for (int nd = xn[id]; nd <= n; nd += lb(nd)) {
			node[nd].insert(id);
		}
	}
	void getnpc(int xx, int yy, int zz) {
		for (int nd = xx; nd; nd -= lb(nd)) {
			if (node[nd].root->mn <= zz) {
//				printf("ask %d\n", nd);
				node[nd].getnpc(node[nd].root, 1, n, yy, zz);
			}
		}
	}
}tree;
bool cmp(int a, int b) {
	return zn[a] < zn[b];
}
struct _Main {
	void prepro() {
		read(n);
		read(x[0]); read(y[0]); read(z[0]);
		for (int i = 1; i <= n; i++) {
			read(xn[i]); read(yn[i]); read(zn[i]);
			xs[i] = xn[i]; ys[i] = yn[i]; zs[i] = zn[i];
			read(x[i]); read(y[i]); read(z[i]);
		}
		sort(xs + 1, xs + n + 1);
		sort(ys + 1, ys + n + 1);
		sort(zs + 1, zs + n + 1);
		for (int i = 1; i <= n; i++) {
			tree.node[i].root = new_();
		}
		for (int i = 1; i <= n; i++) {
			xn[i] = lower_bound(xs + 1, xs + n + 1, xn[i]) - xs; 
			yn[i] = lower_bound(ys + 1, ys + n + 1, yn[i]) - ys;
			zn[i] = lower_bound(zs + 1, zs + n + 1, zn[i]) - zs;
//			printf("[%d] xn = %d, yn = %d, zn = %d\n", i, xn[i], yn[i], zn[i]);
			tree.insert(i);
		}
		for (int i = 1; i <= vidx; i++) {
			sort(idv[i].begin(), idv[i].end(), cmp);//没传cmp 
		}
	}
	void solve() {
		int xx, yy, zz;
		for (int i = 0; i <= ans; i++) {
//			if (i % 100 == 0) {
//				cerr << i << endl;
//			}
//			printf("use %d\n", npc[i]);
			xx = upper_bound(xs + 1, xs + n + 1, x[npc[i]]) - xs - 1;//没减、有n，没 npc
			yy = upper_bound(ys + 1, ys + n + 1, y[npc[i]]) - ys - 1;
			zz = upper_bound(zs + 1, zs + n + 1, z[npc[i]]) - zs - 1;
//			printf("x = %d, y = %d, z = %d\n", xx, yy, zz);
			if (min(min(xx, yy), zz) == 0) continue;
			tree.getnpc(xx, yy, zz);
		}
	}
	_Main() {
//		freopen("callofdeal0.in", "r", stdin); 
		prepro();
		solve();
		printf("%d", ans);
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
}callofdeal;
}
