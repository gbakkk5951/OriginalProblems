using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace OI {
const int MXN = 1e5 + 10;
const int DST = 0, NXT = 1;
struct _Main {
	int con[MXN];
	int head[MXN], edge[MXN << 1][2];
	int h[MXN]; 
	int mark[MXN], val[MXN];
	int n;
	int ans[MXN];
	int top;
	int eidx;
	int now;
	void dfs(int nd, int fa) {
		h[nd] = h[fa] + 1;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd);
			}
		}
		now = 0;
		top = con[nd];
		markdfs(nd, fa);
		getans(top, 0);
		ans[nd] = now;
	}
	void markdfs(int nd, int fa) {
		mark[con[nd]] = 1;
		if (h[con[nd]] < h[top]) {
			top = con[nd];
		}
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				markdfs(t, nd);
			}
		}
	}
	int getans(int nd, int fa) {
		int flag = 0;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				flag |= getans(t, nd);
			}
		}
		if (flag && !mark[nd]) {
			now += val[nd];
		} else
		if (mark[nd]) {
			mark[nd] = 0;
			flag = 1;
		}
		return flag;
	}
	_Main() {
		int a, b;
		read(n);
		for (int i = 1; i <= n; i++) {
			read(val[i]); read(con[i]);
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		dfs(1, 0);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
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
