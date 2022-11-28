#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef pair<lf, int> p;
const int DST = 0, NXT = 1;
const int MXN = 5e5 + 10;
int f[MXN];
inline void setfa(int a, int b) {
	f[a] = b;
}
inline int getfa(int a) {
	return f[a] ? f[a] = getfa(f[a]) : a;
}
struct _Main {
int time[MXN];
lld sum[MXN];
int pi[MXN];
int f[MXN];
priority_queue<p> hp;
	
	_Main() {
		int n, Qn, Tn;
		int a, b;
		int fa;
		read(n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &pi[i]);
			sum[i] = pi[i];
			time[i] = 1;
			if (i != 1) {
				hp.push((p) {sum[i], i});
			}
			ps += sum[i];
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		dfs(1, 0);
		memset(head + 1, 0, n * sizeof(int));
		eidx = 0;
		while (!hp.empty()) {
			int nd = hp.top().second;
			hp.pop();
			if (getfa(nd) != nd) continue; 
			fa = getfa(f[nd]);
			setfa(nd, fa);
			add(f[nd], nd);
			sum[fa] += sum[nd];
			time[fa] += time[nd];
			if (fa != 1) {
				hp.push((p) {(lf)sum[fa] / time[fa], fa});
			}
		}
		calcans(1, 0);
		printf("%lld\n", ans);
		printans(1, 0);
	}
	lld ps;
	lld ans;
	void dfs(int nd, int fa) {
		f[nd] = fa;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd);
			}
		}
	}
	void calcans(int nd, int fa) {
		int t;	
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				calcans(t, nd);
			}
		}
		ps -= pi[nd];
		ans += ps;
	}
	void printans(int nd, int fa) {
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				printans(t, nd);
			}
		}
		printf("%d ", nd);
	}
	int head[MXN], edge[MXN << 1][2];
	int eidx;
	void inline add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
