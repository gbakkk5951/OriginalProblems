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
const lld MOD = 1e9 + 7;
const lld PHI = MOD - 1;
const int MXN = 3e6;
struct _Main {
	char str[MXN];
	int n, len, k;
	lld rem, fact;
	lld fastpower(lld base, lld pow) {
		lld ret = 1;
		pow += pow < 0 ? PHI : 0;
		while (pow) {
			ret = (pow & 1) ? ret * base % MOD : ret;
			base = (pow >>= 1) ? base * base % MOD : base;
		}
		return ret;
	}
	_Main() {
		scanf("%d%d%d", &n, &k, &len);
		scanf("%s", str);
		fact = 1;
		for (int i = 2; i <= n; i++) {
			fact = fact * i % MOD;
		}
		for (int i = len - k; i < len; i++) {
			rem = (rem * 10 + str[i] - '0') % MOD;
		}
		rem = rem * fastpower(fastpower(10, k), -1) % MOD;
		fact = fact * fastpower(fastpower(10, k), -1) % MOD;
		lld ans = 0;
		for (lld i = 0; ; i++) {
			if ((rem + i) % MOD == fact) {
				ans = i;
				break;
			}
		}
		printf("%lld", ans);
		printf("%s", str + len - k);
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


