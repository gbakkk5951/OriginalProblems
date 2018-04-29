using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef double lf;
typedef long long lld;
const lld MOD = 7LL << 52 | 1;
const lld PHI = MOD - 1;
const int MXN = 3e6;
const lf LF_MOD = MOD;
struct _Main {
	char str[MXN];
	int n, k;
	lld rem, fact;
	inline lld mul(lld a, lld b) {
		return (a * b - (lld)((lf)a / LF_MOD * b) * MOD) % MOD;
	}
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		pow += pow < 0 ? PHI : 0;
		while (pow) {
			ret = (pow & 1) ? mul(ret, base) : ret;
			base = (pow >>= 1) ? mul(base, base) : base;
		}
		return ret;
	}
	_Main() {
		scanf("%d%d", &n, &k);
		scanf("%s", str);
		fact = 1;
		for (int i = 2; i <= n; i++) {
			fact = mul(fact, i);
		}
		fact += fact < 0 ? MOD : 0;
		for (int i = 0; i < k; i++) {
			rem = (rem * 10 + str[i] - '0') % MOD;
		}
		rem = mul(rem, fastpower(fastpower(10, k), -1));
		fact = mul(fact, fastpower(fastpower(10, k), -1));
		rem += rem < 0 ? MOD : 0;
		fact += fact < 0 ? MOD : 0;
		lld ans = fact - rem;
		ans += ans < 0 ? MOD : 0;
		if (ans != 0) printf("%lld", ans);
		printf("%s", str);
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
}instance;

}


