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
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1e6 + 10;
struct _Main {
	int head[MXN], edge[MXN << 1][2], dp[MXN], eidx;
	char top[MXN];
	int sort[MXN];
	int dfs(int nd, int f) {
		int mxs = 0, mxdp = 0;
		for (int e = head[nd], t, tdp; e; e = edge[e][NXT]) {
			if ((t = edge[e][DST]) != f) {
				tdp = dfs(t, nd);
				if (tdp > mxdp) {
					mxdp = tdp;
					mxs = t;
				}
			}
		}
		top[mxs] = 0;
		return dp[nd] = mxdp + 1;
	}
	inline void dir_add(int a, int b) {
		++eidx;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	inline void add(int a, int b) {
		dir_add(a, b);
		dir_add(b, a);
	}
	int n;
	_Main() {
		read(n);
		memset(top + 1, 1, n);
		int a, b;
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			add(a, b);
		}
		dfs(1, 0);
		int cnt = 1;
		sort[dp[1] - 1]++;
		for (int i = 2; i <= n; i++) {
			if (top[i]) sort[dp[i]]++, cnt++;
		}
		printf("%d\n", cnt);
		for (int i = dp[1] - 1, sum = 0; cnt; i--) {
			while (sort[i]) {
				--sort[i];
				sum += i;
				--cnt;
				printf("%d\n", sum);
			}
		}
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
