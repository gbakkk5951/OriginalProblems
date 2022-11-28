using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 1050000;
const lld MOD = 479 << 21 | 1;
struct _Main {
	lld res[MXN];
	lld a[MXN], b[MXN];
	int n;
	_Main() {
		read(n);
		for (int i = 0; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 0; i <= n; i++) {
			read(b[i]);
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; i + j <= n; j++) {
				res[i ^ j] += a[i] * b[j] % MOD;
			}
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; i + j <= n; j++) {
				res[i | j] += a[i] * b[j] % MOD;
			}
		}		
		for (int i = 0; i <= n; i++) {
			for (int j = 0; i + j <= n; j++) {
				res[i & j] += a[i] * b[j] % MOD;
			}
		}		

		lld ans[3] = {0, 0, 0};
		for (int i = 0; i <= n; i++) {
			res[i] %= MOD;
			ans[i % 3] += res[i];
		}
		for (int i = 0; i < 3; i++) {
			printf("%lld\n", ans[i] % MOD);
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
