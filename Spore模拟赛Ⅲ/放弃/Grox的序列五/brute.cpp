using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <cstring>
namespace OI {
typedef long long lld;
struct _Main {
	int mod, n, k;
	lld com[1005][1005];
	lld fastpower(lld base, lld pow, lld mod) {
		lld ret = 1;
		while (pow) {
			ret = (pow & 1) ? base * ret % mod : ret;
			base = (pow >>= 1) ? base * base % mod : base;
		}
		return ret;
	}
	_Main() {
		read(n); read(k); read(mod);
		for (int i = 0; i <= n; i++) {
			com[i][0] = 1;
			for (int j = 1; j <= i; j++) {
				com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % mod;
			}
		}
		lld ans = 0;
		for (int i = 1; i <= n; i++) {
			ans = (ans + fastpower(i, k, mod) * com[n][i]) % mod;
		}
		printf("%lld", ans);
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
