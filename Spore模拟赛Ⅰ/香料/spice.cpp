using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cstdlib>
namespace OI {
typedef long long lld;
const lld mod = 1e9 + 7;
const int MXN = 1e5 + 10;
lld rev[MXN];
lld dp[MXN];
int low[MXN];
int ha, hb;
const int DST = 0, NXT = 1, VAL = 2, DEL = 3;
int edge[MXN << 1][4], head[MXN], eidx;
void add(int a, int b, int c) {
	eidx++;
	edge[eidx][DST] = b;
	edge[eidx][VAL] = c; 
	edge[eidx][NXT] = head[a];
	head[a] = eidx;
}

struct _Main {
	lld rev[MXN];
	void getrev(int mx) {
		rev[1] = 1;
		for (int i = 2; i <= mx; i++) {
			rev[i] = - mod / i * rev[mod % i] % mod+ mod;
		}
	}
	void getdp(int nd, int fa = 0) {
		if (low[nd]) {
			dp[nd] = 0;
			return;
		}
		dp[nd] = 1;
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa && !inc[t]) {
				getdp(t, nd);
				dp[nd] = (dp[nd] * edge[e][VAL] + dp[nd] * ((1 - edge[e][VAL]) * dp[t] % mod)) % mod;
			}
		}
	}
	int f[MXN], fe[MXN], s[MXN], se[MXN];
	char gotlow;
	char inc[MXN];
	void getchain(int nd, int fa = 0) {
		if (nd == hb) {
			inc[nd] = 1;
			if (low[nd]) gotlow = 1;
			return;
		}
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				getchain(t, nd);
				if (inc[t]) {
					fe[t] = se[nd] = e;
					f[t] = nd;
					se[nd] = e;
					s[nd] = t;
					inc[nd] = 1;
					if (low[nd]) gotlow = 1;
					return;
				}
			}
		}
	}
	
	int an, bn, n;
	_Main() {
		static lld c[MXN], v[MXN];
		int nd;
		static lld pi[MXN];
		lld sum = 1;

		lld ans = 0;
		int a, b, q, p;
		getrev(1e5);
		read(n);  
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b);
			read(q); read(p);
			q = q * rev[p] % mod;
			add(a, b, q); add(b, a, q);
		}
		read(an);
		for (int i = 1; i <= an; i++) {
			read(a); low[a] = 1;
		}
		read(bn);
		if (an == 0 || bn == 0) {
			ans = 1;
			goto EndMain;
		}			
		read(ha); 
		if (bn == 2) {
			read(hb);
			if (hb == ha) {
				bn--;
			}
		}
		if (low[ha] || low[hb]) {
			ans = 0;
			goto EndMain;
		}
		if (bn == 1) {
			getdp(ha);
			ans = dp[ha];
			goto EndMain;
			return;
		}
		
		getchain(ha);
		if (gotlow) {
			memset(inc, 0, (n + 1) * sizeof(char));
			getdp(ha);
			ans = dp[ha];
			getdp(hb);
			ans = ans * dp[hb] % mod;
			goto EndMain;
			return;
		}
		
		for (int nd = hb; nd; nd = f[nd]) {
			getdp(nd);
		}
		

		nd = f[hb];
		v[nd] = c[nd] = dp[nd];
		for (nd = f[f[hb]]; nd; nd = f[nd]) {
			c[nd] = dp[nd] * edge[se[nd]][VAL] % mod;
			v[nd] = (c[nd] + dp[nd] * (1 - edge[se[nd]][VAL]) % mod * v[s[nd]]) % mod;
		}
		sum = 1;
		for (int nd = ha; nd != hb; nd = s[nd]) {
			pi[nd] = sum;
			sum = sum * (1 - edge[se[nd]][VAL]) % mod * dp[s[nd]] % mod;
		}
		sum = dp[ha];
		for (int nd = f[hb]; nd != ha; nd = f[nd]) {//断点(上) 连通特判
			ans = (ans + sum * v[ha] % mod * edge[se[nd]][VAL]) % mod;
			//之前都连通的概率；v[ha]不包含断边概率
			sum = sum * (1 - edge[se[nd]][VAL]) % mod * dp[nd] % mod;
			v[ha] -= pi[nd] * dp[nd] % mod;
			v[ha] -= pi[f[nd]] * edge[fe[nd]][VAL] % mod * dp[f[nd]] % mod;
			v[ha] += pi[f[nd]] * dp[f[nd]] % mod;
			v[ha] %= mod;
		}
		ans = (ans + sum) % mod;//连通
		EndMain:
		ans = (1 - ans) % mod;
		ans = ans < 0 ? mod + ans : ans;
		printf("%lld", ans);
	}
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}
}spice;
}
