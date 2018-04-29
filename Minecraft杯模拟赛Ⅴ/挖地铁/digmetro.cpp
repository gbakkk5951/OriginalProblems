using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <functional>
namespace OI {
const int MXN = 500050;
const int DST = 0, NXT = 1, VAL = 2;
int head[MXN], edge[MXN << 1][3];
int eidx;
void add(int a, int b, int c) {
	eidx++;
	edge[eidx][DST] = b;
	edge[eidx][VAL] = c;
	edge[eidx][NXT] = head[a];
	head[a] = eidx;
}
int n, k;
int beg[MXN];
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
	inline dp friend operator + (int add, const dp &b) const {
		return (dp) {val + add, id};
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
			mx[nd][2] = dp[t] + edge[e][VAL];
			mx[nd][2].id = t;
			sort(mx[nd], mx[nd] + 3, greater<dp>());
		}
	}
}
void dfs2(int nd, int fa, const dp &from) {
	mx[nd][2] = from;
	mx[nd][2].id = fa;
	sort(mx[nd], mx[nd] + 3, greater<dp>());
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		t = edge[e][DST];
		if (t != fa) {
			dfs(t, nd, (mx[nd][0] == t ? mx[nd][1] : mx[nd][0]) + edge[e][VAL]);
		}
	}
	if (beg[nd]) {
		mx[nd][0].id = nd;
		ans = max(ans, nd);
	}
}


struct _Main {
	
	
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
