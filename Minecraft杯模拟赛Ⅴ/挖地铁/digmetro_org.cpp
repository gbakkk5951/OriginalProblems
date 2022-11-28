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
typedef priority_queue<dp, vector<dp>, greater<dp> > heap;
const int MXN = 500050;
const int DST = 0, NXT = 1, VAL = 2;
const int INF = 0x3f3f3f3f;
const int LEAF = 0, BEG = 1;
struct dp {
	int val, id;
	bool operator < (const dp &b) const {
		return val < b.val;
	}
	bool operator > (const dp &b) const {
		return val > b.val;
	}
	inline bool friend operator == (const dp &a, int b) {
		return a.id == b;
	}
	inline bool friend operator == (int a, const dp &b) {
		return a == b.id;
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
	
	int root;
	int sum;
	int ans[MXN], int idx;
	int calc() {
		dp p, l1, l2, b1, b2, l, b;
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
			ret = l.val + r.val;
			beg = l();
			leaf = r();
			mark[beg] = mark[leaf] = 1;
		} else {
			//走公共
			ret = p.val;
			mark[p.id] = 1;
			for (nd = p.id, nxt; nd; nd = nxt) {
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
		if (beg != 0) for (int nd = beg, nxt; nd; nd = nxt) { 
			nxt = far_beg[nd]();
			mark[nxt] = 1;
			push(nd);
		}
		//走leaf
		if (leaf != 0) for (int nd = leaf, nxt; nd; nd = nxt) { 
			nxt = far_leaf[nd]();
			mark[nxt] = 1;
			push(nd);
		}
		return ret;
	}
	_Main() {
		int a, b, c;
		read(n); read(k);
		for (int i = 1; i <= k; i++) {
			read(beg[i]);
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
		for (int nd = root, lst = 0, nxt; nd; ) {
			nxt = mx[i][0]() == lst ? mx[i][1]() : mx[i][0]();
			mark[nxt] = 1;
			push(nd);
			lst = nd;
			nd = nxt;
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
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				getdp(t, nd);
				v = edge[e][VAL];
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
	}
	
	void push(int nd) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!mark[t]) {
				lh.push(far_leaf[t][t]);
				bh.push(far_beg[t][t]);
				ph.push((dp) {far_pair[t][VAL], t});
			}
		}
	}

	dp get_top(heap &a) {
		while (!a.empty() && mark[a.top()()]) { //其实不用判这个empty
			a.pop();
		}
		return a.empty() ? (dp) {-INF, 0} : heap.top();
	}

	dp get_sec(heap &a) {//调之前确保top没被mark
		dp ret;
		if (!a.empty()) {//其实不用判这个empty
			dp tmp = a.top();
			a.pop();
			while (!a.empty() && mark[a.top()()]) {
				a.pop();
			}
			ret = a.empty() ? (dp) {-INF, 0} : a.top();	
			a.push(tmp); 
		} else {
			ret.val = dp {-INF, 0};
		}
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
				mx[nd][2] = (dp[t] + edge[e][VAL])[t];
				sort(mx[nd], mx[nd] + 3, greater<dp>());
			}
		}
	}
	
	void dfs2(int nd, int fa, const dp &from) {
		sort(mx[nd], mx[nd] + 3, greater<dp>());
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd, 
				((mx[nd][0] == t ? mx[nd][1] : mx[nd][0])
					[nd] + edge[e][VAL]) );
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
