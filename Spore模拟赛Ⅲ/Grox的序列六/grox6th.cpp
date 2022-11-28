using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
namespace OI {
typedef long long lld;
const lld mod = 1e9 + 7;
const lld phi = mod - 1;
const int MXN = 210;
const int CHANGE = 1;
lld fastpower(lld base, lld pow) {
	if (base == 0) return 0;
	lld ret = 1;
	pow %= phi;
	pow += pow < 0 ? phi : 0;
	while (pow) {
		ret = (pow & 1) ? ret * base % mod : ret;
		base = (pow >>= 1) ? base * base % mod : base;
	}
	return ret;
}

int b, k;
struct Poly {
	lld a[MXN];
	lld & operator [] (int id) {
		return a[id];
	}
	Poly operator * (lld b) {
		Poly ret = *this;
		for (int i = 0; i <= k + 2; i++) {
			ret[i] = ret[i] * b % mod;
		}
		return ret;
	}
	void operator += (Poly b) {
		for (int i = 0; i <= k + 2; i++) {
			a[i] = (a[i] + b[i]) % mod;
		}
	}
};
struct _Main {
	
	lld xishu[MXN][MXN];
	int mx[MXN];
	void init() {
		static int use[MXN];
		static int cnt[MXN];
		static Poly right[MXN];
		static lld ma[MXN][MXN]; // k + 2 为 a 的系数方程, 0 为 1, 1 ~ k + 1 = n ^ k
		static lld com[MXN][MXN];
		//预处理组合数
		for (int i = 0; i <= k + 1; i++) {
			com[i][0] = 1;
			for (int j = 1; j <= i; j++) {
				com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % mod;
			}
		}
		// 0
		ma[0][0] = 1 - b;
		ma[0][k + 2] = 1;
		right[0][0] = 1;
		// k + 2
		ma[k + 2][k + 2] = 1;
		right[k + 2][k + 2] = 1;
		// 1 ~ k + 1
		for (int i = 1; i <= k + 1; i++) {
			for (int j = 0; j <= i; j++) {
				ma[i][j] = (-com[i][j] * b * fastpower(-1, i - j)) % mod;
			}
			ma[i][i]++;
			ma[i][i] %= mod;
			right[i][i] = 1;
		}
		//未知数计数
		for (int i = 0; i <= k + 2; i++) {
			for (int j = 0; j <= k + 2; j++) {
				if (ma[i][j]) ++cnt[i];
			}
		}
		//gause 半三角阵，只要第二步即可
		for (int i = 0; i <= k + 2; i++) {
			int now, pow;
			for (now = 0; now <= k + 2; now++) {
				if (!use[now] && cnt[now] == 1) break;
			}
			if (now == k + 3) break;
			use[now] = 1;
			for (pow = 0; pow <= k + 2; pow++) {
				if (ma[now][pow]) break;
			}
			lld div = fastpower(ma[now][pow], -1);
			ma[now][pow] = ma[now][pow] * div % mod;
			for (int i = 0; i <= k + 2; i++) {
				right[now][i] = right[now][i] * div % mod;
			}
			for (int i = 0; i <= k + 2; i++) {
				if (i != now && ma[i][pow]) {
					right[i] += right[now] * (-ma[i][pow]);
					ma[i][pow] = 0;
					cnt[i]--;
				}
			}
		}
		//getans
		for (int i = 0; i <= k + 2; i++) {
			if (cnt[i] != 1) continue;
			int now;
			for (now = 0; now <= k + 2; now++) {
				if (ma[i][now]) break;
			}
			for (int j = 0; j <= k + 2; j++) {
				xishu[now][j] = right[i][j];
			}
		}
		// getmx (except for b ^ n = k + 2)
		for (int i = 0; i <= k + 2; i++) {
			for (int j = k + 1; j >= 0; j--) {
				if (xishu[i][j]) {
					mx[i] = j;
					break;
				}
			}
		}
	}
	
	_Main() {
		int Qn;
		lld arr[MXN];
		lld a;
		int op;
		read(Qn); read(b); read(k);
		init();
		for (int Q = 0; Q <= Qn; Q++) {
			if (Q == 0) {
				op = CHANGE;
			} else {
				read(op);
			}
			if (op == CHANGE) {
				read(a);
				for (int i = 0; i <= k; i++) {
					read(arr[i]);
				}
			} else {
				lld n, ans, tmp;
				read(n);
				if (n == 0) {
					printf("%lld\n", a + (a < 0 ? mod : 0));
					continue;
				}
				ans = a * fastpower(b, n) % mod;
				for (int i = k; i >= 0; i--) { //k + 2 为 b ^ n, 
					tmp = 0;
					for (int j = mx[i]; j >= 0; j--) {
						tmp = (tmp * n + xishu[i][j]) % mod;
					}
					tmp =  (tmp + fastpower(b, n) * xishu[i][k + 2]) % mod;
					ans = (ans + tmp * arr[i]) % mod;
				}
				ans += ans < 0 ? mod : 0;
				printf("%lld\n", ans);
			}
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
}grox6th;
}
