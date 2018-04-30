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
dp mx[MXN][3];
dp ans;
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
		ans = max(ans, mx[nd][0][nd]);
	}
}




struct _Main {
	dp far_leaf[MXN];
	dp far_beg[MXN];
	
	int far_pair[MXN][3];
	int mark[MXN];
	
	void push(int nd) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!mark[t]) {
				
			}
		}
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
		}
		dfs1(1, 0);
		dfs2(1, 0);
		root = ans.id;
		mark(ans.id, 0);
		
	}
	int n, k;
	int beg[MXN];
	
	heap lh, bh, ph;
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
