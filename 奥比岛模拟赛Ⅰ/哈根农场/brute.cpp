using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <cstdio>
namespace OI {
typedef long long lld;
const int DST = 0, NXT = 1;
const lld MOD = 1e9 + 7;
const lld PHI = MOD - 1;
const int MXN = 2e3 + 5;
struct _Main {
	int a[MXN], b[MXN];
	lld c[MXN];
	lld rev[MXN];
	lld com[MXN][MXN];
	lld comr[MXN][MXN];
	lld fc[MXN], fcr[MXN];
	lld ans;
	int n;
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		pow += (pow < 0) * PHI;
		while (pow) {
			ret = (pow & 1) ? base * ret % MOD : ret;
			base = (pow >>= 1) ? base * base % MOD : base;
		}
		return ret;
	}
	void init() {
		fc[0] = fcr[0] = 1;
		for (int i = 1; i <= n; i++) {
			rev[i] = fastpower(i, -1);
			fc[i] = fc[i - 1] * i % MOD;
			fcr[i] = fcr[i - 1] * rev[i] % MOD;
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				com[i][j] = fc[i] * fcr[j] % MOD * fcr[i - j] % MOD;
				comr[i][j] = fcr[i] * fc[j] % MOD * fc[i - j] % MOD;
			}
		}
	}
	int size[MXN], f[MXN];
	void dfs(int nd, int fa) {
		size[nd] = 1;
		f[nd] = fa;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				dfs(t, nd);
				size[nd] += size[t];
			}
		}
	}
	_Main() {
		read(n);
		init();
		for(int i = 1; i <= n - 1; i++) {
			read(a[i]); read(b[i]); read(c[i]);
			c[i] <<= 1;
			add(a[i], b[i]); add(b[i], a[i]);
		}
		dfs(1, 0);
		lld gx;
		for (int i = 1; i <= n - 1; i++) {
			if (f[a[i]] == b[i]) swap(a[i], b[i]);
			for (int j = a[i]; j; j = f[j]) {
				for (int k = 2; k <= size[j]; k++) {
					gx = com[size[j]][k];
					if (size[b[i]] >= k) {
						gx -= com[size[b[i]]][k];
					}
					if (size[j] - size[b[i]] >= k) {
						gx -= com[size[j] - size[b[i]]][k];
					}
					gx = gx * comr[size[j]][k] % MOD * c[i] % MOD;
					ans = (ans + gx * rev[size[j]] % MOD * rev[n]) % MOD;
				}
			}
		}
		ans += (ans < 0) * MOD;
		printf("%lld", ans);
	}
	int eidx, head[MXN], edge[MXN << 1][2];
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
