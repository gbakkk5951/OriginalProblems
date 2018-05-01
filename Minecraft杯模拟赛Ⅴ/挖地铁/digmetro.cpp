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

	dp far_leaf[MXN][3];
	dp far_beg[MXN][3];
	
	int far_pair[MXN][3];
	int mark[MXN];
	
	void getdp(int nd, int fa) {
		int t, v;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				getdp(t, nd);
				v = edge[e][VAL];
				far_leaf[nd][2] = far_leaf[t][0][t] + v;
				far_beg[nd][2] = far_beg[t][0][t] + v;
				if (far_pair[nd][VAL] < far_pair[t][VAL] + v) {
					far_pair[nd][BEG] = t;
					far_pair[nd][LEAF] = t;
					far_pair[nd][VAL] = far_pair[t][VAL] + v;
				}
				if (far_pair[nd][VAL] < far_leaf[nd][2].val + far_beg[nd][0].val) {
					far_pair[nd][VAL] = far_leaf[nd][2].val + far_beg[nd][0].val;
					far_pair[nd][BEG] = far_beg[nd][0].beg;
					far_pair[nd][LEAF] = far_leaf[nd][2].id;
				}
				if (far_pair[nd][VAL] < far_beg[nd][2].val + far_leaf[nd][0].val) {
					far_pair[nd][VAL] = far_beg[nd][2].val + far_leaf[nd][0].val;
					far_pair[nd][BEG] = far_beg[nd][2].id;
					far_pair[nd][LEAF] = far_leaf[nd][0].id;
				}
				sort(far_leaf[nd], far_leaf[nd] + 3, greater<dp>());
				sort(far_leaf[nd], far_leaf[nd] + 3, greater<dp>());
			}
		}
		
		
	}
	int root;
	int sum;
	_Main() {
		int a, b, c;
		read(n); read(k);
		for (int i = 1; i <= k; i++) {
			read(beg[i]);
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b); read(c);
			add(a, b, c); add(b, a, c);
		}
		dfs1(1, 0);
		dfs2(1, 0);
		root = init_ans();
		getdp(root, 0);
		mark[root] = 1;
		for (int nd = root, lst = 0, nxt; i > 0; ) {
			nxt = mx[i][0]() == lst ? mx[i][1]() : mx[i][0]();
			mark[nxt] = 1;
			push(nd);
			lst = nd;
			nd = nxt;
		}
		
		
	}
	int n, k;
	int beg[MXN];
	
	void push(int nd) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!mark[t]) {
				lh.push(far_leaf[t][0][t]);
				bh.push(far_beg[t][0][t]);
				ph.push((dp) {far_pair[t][VAL], t});
			}
		}
	}

	dp get_top(heap &a) {
		while (!a.empty() && mark[a.top()()]) {
			a.pop();
		}
		return a.empty() ? (dp) {-INF, 0} : heap.top();
	}
	dp get_sec(heap &a) {
		dp tmp, ret;
		tmp = a.top();
		a.pop();
		while (!a.empty() && mark[a.top()()]) {
			a.pop();
		}
		ret = heap.empty() ? (dp) {-INF, 0} : heap.top();	
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
};
}
