using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 500050;
const int DST = 1, NXT = 0;
int f[MXN], h[MXN], edge[MXN << 1][2], head[MXN];
lld val[MXN];
struct _Main {
	void dfs(int nd, int fa) {
		f[nd] = fa;
		h[nd] = h[fa] + 1;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			if ((t = edge[e][DST]) != fa) {
				dfs(t, nd);
			}
		}
	}
	void run(int op, int a, int b, int c) {
		lld ret = 0;
		if (h[a] < h[b]) swap(a, b);
		if (op == 1) {
			while (h[a] > h[b]) {
				val[a] += c;
				a = f[a];
			}
			while (a != b) {
				val[a] += c;
				val[b] += c;
				a = f[a]; b = f[b];
			}
			val[a] += c;
		} else if (op == 2) {
			while (h[a] > h[b]) {
				val[a] = c;
				a = f[a];
			}
			while (a != b) {
				val[a] = c;
				val[b] = c;
				a = f[a]; b = f[b];
			}
			val[a] = c;
		} else if (op == 3) {
			while (h[a] > h[b]) {
				ret += val[a] >= c;
				a = f[a];
			}
			while (a != b) {
				ret += val[a] >= c;
				ret += val[b] >= c;
				a = f[a]; b = f[b];
			}
			ret += val[a] >= c;
			printf("%lld\n", ret);
		} else if (op == 4) {
			while (h[a] > h[b]) {
				ret += (val[a] >= c) * val[a];
				a = f[a];
			}
			while (a != b) {
				ret += (val[a] >= c) * val[a];
				ret += (val[b] >= c) * val[b];
				a = f[a]; b = f[b];
			}
			ret += (val[a] >= c) * val[a];
			printf("%lld\n", ret);
		}
	}
	int eidx;
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
	_Main() {
//		freopen("data0.in", "r", stdin);
		int n, en, Qn;
		int op, a, b, c;
		read(n); read(en); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(val[i]);
		}
		
		for (int i = 1; i <= en; i++) {
//			if (i %100== 0)printf("e = %d\n", i);

			read(a); read(b);
			/*if (i >= 306500) {
				printf("add %d %d\n", a, b);
			}*/
			add(a, b); add(b, a);
		}
		for (int i = 1; i <= n; i++) {
			if (!h[i]) {
				dfs(i, 0);
			}
		}
		for (int Q = 1; Q <= Qn; Q++) {
			
			read(op); read(a); read(b); read(c);
			run(op, a, b, c);
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
			a *= 10;
			a += t - '0';
		}
		a *= f;
	}
}brute;
}
