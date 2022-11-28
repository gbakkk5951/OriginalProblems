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
#include <cmath>
#include <complex>
#include <cassert>
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
typedef long double Lf;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1005;
struct _Main {
	int n, head[MXN], eidx, edge[MXN << 1][2];
	int L, R;
	int v[MXN];
	int stk[MXN], top;
	int f[MXN];
	void dfs0(int nd, int fa) {
		dfs1(nd, fa, 0);
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				dfs0(t, nd);
			}
		}
	}
	void dfs1(int nd, int fa, int sum) {
		stk[++top] = nd;
		sum += v[nd];
		if (L <= top && top <= R) {
			for (int i = 1; i <= top; i++) {
				ans[stk[i]] = max(ans[stk[i]], sum);
			}
		}
		if (top < R ) for (int e = head[nd]; e; e = edge[e][NXT]) {
			int t = edge[e][DST];
			if (t != fa) {
				dfs1(t, nd, sum);
			}
		}
		top--;
	}
	int ans[MXN];
	_Main() {
		int a, b;
		read(n); read(L); read(R);
		for (int i = 1; i <= n; i++) {
			read(v[i]);
		}
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		memset(ans + 1, 192, n * sizeof(int));
		dfs0(1, 0);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
	}
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
