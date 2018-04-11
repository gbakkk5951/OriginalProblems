using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>

namespace OI {
const int DST = 0, NXT = 1, FLOW = 2;
const int FMXN = 2018, MXM = 8012, MXN = 1005;
int lstvis[FMXN];
int dst;
int size;
struct Flow {
	int head[FMXN];
	int vis[FMXN];
	int edge[MXM][3];
	int eidx;
	void init() {
		eidx = 1;
		memset(head, 0, size * sizeof(int));
		memset(lstvis, 0, size * sizeof(int));
	}
	void dir_add(int a, int b, int c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][FLOW] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	void add(int a, int b, int c) {
		dir_add(a, b, c); dir_add(b, a, 0);
	}
	void run(int nd) {
		memset(vis, 0, size * sizeof(int));
		dfs(nd);
	}
	int dfs(int nd) {
		if (nd == dst) return 1;
		vis[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			if (edge[e][FLOW]) {
				int t = edge[e][DST];
				if (!vis[t] && dfs(t)) {
					--edge[e][FLOW];
					++edge[e ^ 1][FLOW];
					return 1;
				}
			}
		}
		return 0; //写成1了 
	}
	void getvis(int nd, int id) {
		lstvis[nd] = id;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			if (edge[e ^ 1][FLOW]) {
				int t = edge[e][DST];
				if (lstvis[t] < id) {
					getvis(t, id);
				}
			}
		}
	}
}flow;
struct _Main {
	int n, m, Qn;
	int arr[MXN];//rk为i学生的编号
	int zy[MXN][MXN][3];
	int cnt[MXN][MXN];
	int need[MXN];//档次需求
	int mne[MXN];//名额
	int mid[MXN], nid[MXN];
	int ans1[MXN], ans2[MXN];
	int idx;
	int node() {
		return idx++;
	}
	_Main() {
		int a;
		read(n); read(m); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(need[i]);
		}
		for (int i = 1; i <= m; i++) {
			read(mne[i]);
			
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				read(a);
				if (a != -1) {
					zy[i][a][cnt[i][a]++] = j;
				}
			}
		}
		dst = node();
		for (int i = 1; i <= n; i++) {
			nid[i] = node();
		}
		for (int i = 1; i <= m; i++) {
			mid[i] = node();
		}
		size = idx;
		for (int Q = 1; Q <= Qn; Q++) {
			flow.init();
			for (int i = 1; i <= m; i++) {
				flow.add(mid[i], dst, mne[i]);
			}
			for (int i = 1; i <= n; i++) {
				read(arr[i]);
				
			}
			for (int I = 1; I <= n; I++) {
				flow.getvis(dst, I);
				int nd = arr[I], mx = 0;
				for (int i = 1; i <= need[nd]; i++) {
					for (int j = 0; j < cnt[nd][i]; j++) {
						mx = max(mx, lstvis[mid[zy[nd][i][j]]]);
					}
				}
				if (mx == 0) mx = I + 1;
				ans2[nd] = I - mx;
				int a1 = 0;
				for (int i = 1; i <= m; i++) {
					for (int j = 0; j < cnt[nd][i]; j++) {
						if (lstvis[mid[zy[nd][i][j]]] == I) {
							a1 = ans1[nd] = i;
							break;
						}
					}
					if (a1) {
						break;
					}
				}
				if (a1) {
					for (int j = 0; j < cnt[nd][a1]; j++) {
						int t = mid[zy[nd][a1][j]];
						if (lstvis[t] == I) flow.add(nid[nd], t, 1);//小剪枝
					}
					flow.run(nid[nd]);
				} else {
					ans1[nd] = -1;
				}
			}
			for (int i = 1; i <= n; i++) {
				printf("%d ", ans1[i]);
			}
			printf("\n");
			for (int i = 1; i <= n; i++) {
				printf("%d ", ans2[i]);
			}
			printf("\n");
		}
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			if (t == '-') f = -1;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}spode;

}
