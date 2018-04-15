using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MOD = 479 << 21 | 1;
const int MXN = 132000;
struct _Main {
	lld fac[MXN];
	lld ans[MXN];
	int n;
	_Main() {
		read(n);
		fac[0] = 1;
		for (int i = 1; i <= n; i++) {
			fac[i] = fac[i - 1] * i % MOD;
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j + i <= n; j++) {
				ans[n + i - j] += fac[i] * fac[j];
				ans[n + i - j] %= MOD;
			}
		}
		for (int i = 0; i <= 2 * n; i++) {
			printf("%lld ", ans[i]);
		}
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
