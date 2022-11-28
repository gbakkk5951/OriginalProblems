#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <functional>
#include <queue>
namespace OI {
struct dp;
typedef priority_queue<dp> heap; //要的就是大根堆 
const int MXN = 500050;
const int DST = 0, NXT = 1, VAL = 2;
const int INF = 0x3f3f3f3f;
const int LEAF = 0, BEG = 1;
struct dp {
	int val, id;
	inline bool operator < (const dp &b) const {
		return val < b.val;
	}
	inline bool operator > (const dp &b) const {
		return val > b.val;
	}
	inline bool friend operator == (const dp &a, int b) {
		return a() == b;
	}
	inline bool friend operator == (int a, const dp &b) {
		return a == b();
	}
	inline dp operator + (int add) const {
		return (dp) {val + add, id};
	}
	inline dp friend operator + (int add, const dp &b) {
		return (dp) {b.val + add, b.id};
	}
	inline dp operator [] (int new_id) const {
		return (dp) {val, new_id};
	}
	inline int operator () () const {
		return id;
	}
};



struct _Main {
	heap lh, bh, ph;

	dp far_leaf[MXN];
	dp far_beg[MXN];
	int far_pair[MXN][3];
	int mark[MXN];
	
	int calc() {
		dp p, l1, l2, b1, b2, l, b;
		int ret;
		p = get_top(ph);
		l1 = get_top(lh);
		b1 = get_top(bh);
		if (l1() != b1()) {
			l = l1;
			b = b1;
		} else {
			b2 = get_sec(bh);
			l2 = get_sec(lh);
			if (l1.val + b2.val > l2.val + b1.val) {
				l = l1;
				b = b2;
			} else {
				l = l2;
				b = b1;
			}
		}
		int beg = 0, leaf = 0;
		if (l.val + b.val > p.val) {
			ret = l.val + b.val;
			beg = b();
			leaf = l();
			mark[beg] = mark[leaf] = 1;
		} else {
			//走公共
			ret = p.val;
			mark[p()] = 1;
			for (int nd = p(), nxt; nd; nd = nxt) {
				if ((nxt = far_pair[nd][BEG]) != far_pair[nd][LEAF]) {
					beg = far_pair[nd][BEG];
					leaf = far_pair[nd][LEAF];
					mark[beg] = mark[leaf] = 1;
					push(nd); //卡下这个
					break;
				}
				mark[nxt] = 1;
				push(nd);
			}
		}
		// 走beg
		for (int nd = beg, nxt; nd; nd = nxt) {
			nxt = far_beg[nd]();
			mark[nxt] = 1;
			push(nd);
		}
		//走leaf
		for (int nd = leaf, nxt; nd; nd = nxt) { 
			nxt = far_leaf[nd]();
			mark[nxt] = 1;
			push(nd);
		}
		return ret;
	}
	_Main() {
		static int ans[MXN];
		int root;
		int sum = 0;
		int idx = 0;
		int a, b, c, pos;
		read(n); read(k);
		for (int i = 1; i <= k; i++) {
			read(pos); beg[pos] = 1;
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b); read(c);
			add(a, b, c); add(b, a, c);
			sum += c;
		}
		dfs1(1, 0);
		dfs2(1, 0);
		root = init_ans();
		getdp(root, 0);
		mark[root] = 1;
		for (int nd = root, lst = 0, nxt; nd; nd = nxt) {
			nxt = mx[nd][0]() == lst ? mx[nd][1]() : mx[nd][0]();
			mark[nxt] = 1;
			push(nd);
			lst = nd;
		}
		ans[++idx] = init_ans.val;
		while (ans[idx] != sum) {
			++idx;
			ans[idx] = ans[idx - 1] + calc();
		}
		printf("%d\n", idx);
		for (int i = 1; i <= idx; i++) {
			printf("%d\n", ans[i]);
		}
	}
	int n, k;
	int beg[MXN];
	
	void getdp(int nd, int fa) {
		int t, v;
		dp leaf, beg;
		//far_beg得先赋初值-INF
		//并不会影响到纯叶子节点的路径，因为叶子的far_pair = 0 
		far_beg[nd].val = -INF; 
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				v = edge[e][VAL];
				getdp(t, nd);
				leaf = far_leaf[t][t] + v;
				beg = far_beg[t][t] + v;
				if (far_pair[nd][VAL] < far_pair[t][VAL] + v) {
					far_pair[nd][BEG] = t;
					far_pair[nd][LEAF] = t;
					far_pair[nd][VAL] = far_pair[t][VAL] + v;
				}
				if (far_pair[nd][VAL] < leaf.val + far_beg[nd].val) {
					far_pair[nd][VAL] = leaf.val + far_beg[nd].val;
					far_pair[nd][BEG] = far_beg[nd]();
					far_pair[nd][LEAF] = leaf();
				}
				if (far_pair[nd][VAL] < beg.val + far_leaf[nd].val) {
					far_pair[nd][VAL] = beg.val + far_leaf[nd].val;
					far_pair[nd][BEG] = beg();
					far_pair[nd][LEAF] = far_leaf[nd]();
				}
				far_leaf[nd] = max(far_leaf[nd], leaf);
				far_beg[nd] = max(far_beg[nd], beg);
			}
		}
		if (this->beg[nd]) {
			far_beg[nd] = max(far_beg[nd], (dp) {0, 0});
		}
	}
	
	void push(int nd) {
		int t, v;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			v = edge[e][VAL];
			if (!mark[t]) {
				lh.push(far_leaf[t][t] + v);
				bh.push(far_beg[t][t] + v);
				ph.push((dp) {far_pair[t][VAL] + v, t});
			}
		}
	}

	dp get_top(heap &a) {
		while (mark[a.top()()]) { 
			a.pop();
		}
		return a.top();
	}

	dp get_sec(heap &a) {//assert !mark[a.top()]
		dp ret;
		dp tmp = a.top();
		a.pop();
		while (!a.empty() && mark[a.top()()]) {
			a.pop();
		}
		ret = a.empty() ? (dp) {-INF, 0} : a.top();	
		a.push(tmp); 
		return ret;
	}
	
	int head[MXN], edge[MXN << 1][3];
	int eidx;
	void add(int a, int b, int c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][VAL] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}

	dp mx[MXN][3];
	dp init_ans;
	
	void dfs1(int nd, int fa) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs1(t, nd);
				mx[nd][2] = (mx[t][0] + edge[e][VAL])[t];
				sort(mx[nd], mx[nd] + 3, greater<dp>());
			}
		}
	}
	
	void dfs2(int nd, int fa) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				mx[t][2] = (mx[nd][0] == t ? mx[nd][1] : mx[nd][0])[nd] + edge[e][VAL];
				sort(mx[t], mx[t] + 3, greater<dp>());
				dfs2(t, nd);
			}
		}
		if (beg[nd]) {
			init_ans = max(init_ans, mx[nd][0][nd]);
		}
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
}digmetro;
}
