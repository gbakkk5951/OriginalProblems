using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <functional>
namespace OI {
typedef pair<int, int> p;
const int DST = 0, NXT = 1, CUT = 2;
const int MXN = 2e5 + 10;
priority_queue<p> heap;
struct _Main {
	int n;
	int vis[MXN];
	int arr[MXN];
	int arridx;
	int dp[MXN];
	p mx[MXN][3];
	void getdp(int nd, int fa, int idx) {
		vis[nd] = idx;
		dp[nd] = 0;
		memset(mx[nd], 0, sizeof(mx[nd]));
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa && !edge[e][CUT]) {
				getdp(t, nd, idx);
				mx[nd][2] = (p) {mx[t][0].first + 1, e};
				sort(mx[nd], mx[nd] + 3, greater<p>());
			}
		}
		dp[nd] = mx[nd][0].first + mx[nd][1].first;
		if (dp[nd]) {
			heap.push((p) {dp[nd], nd});
		}
	}
	void update() {
		static int updidx = 0;
		++updidx;
		for (int i = 1; i <= arridx; i++) {
			if (vis[arr[i]] != updidx) {
				getdp(arr[i], 0, updidx); //没有h设定
			}
		}
		arridx = 0;
	}
	void push(int nd) {
		arr[++arridx] = nd;
	}
	void push_block(int nd, int fa) {
		push(nd);
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!edge[e][CUT] && t != fa) {
				push_block(t, nd);
			}
		}
	}
	void delchain(int nd, int e) {
		do {
			edge[e][CUT] = 1; edge[e ^ 1][CUT] = 1;	
			nd = edge[e][DST];
			e = mx[nd][0].second;
		} while (e);
	}
	int getans() {
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			push(i);
		}
		update();
		int nd;
		while (!heap.empty()) {//只需考虑pop, 无需考虑插入(update里面已经做了)
			if (heap.top().first == dp[nd = heap.top().second]) {
				++ret;
				push_block(nd, 0);
				if (mx[nd][0].second) {
					delchain(nd, mx[nd][0].second);
				}
				if (mx[nd][1].second) {
					delchain(nd, mx[nd][1].second);
				}
				update();
			}
			heap.pop();
		}
		return ret;
	}
	_Main() {
		int a, b, c, cnt = 0, ans;
		read(n);
		eidx = 1;
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b); read(c);
			add(a, b, c); add(b, a, c);
			cnt += c;
		}
		ans = getans();
		printf("%d\n", ans);
		if (cnt == 0) {
			printf("%d\n", ans);
			return;
		}
		for (int e = 2; e <= eidx; e++) {
			edge[e][CUT] = 0;
		}
		ans = getans();
		printf("%d\n", ans);
	}
	int eidx;
	int head[MXN], edge[MXN][3];
	void add(int a, int b, int c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][CUT] = c;
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
}brute;
}
