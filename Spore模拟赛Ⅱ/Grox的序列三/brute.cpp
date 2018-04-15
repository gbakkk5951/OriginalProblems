using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 5100;
const lld MOD = 921260340LL; 
struct _Main {
	int n, Qn;
	lld fact[MXN];
	_Main() {
		read(n); read(Qn);
		fact[0] = 1;
		for (int i = 1; i <= n; i++) {
			fact[i] = fact[i - 1] * i % MOD;
		}
		for (int Q = 1; Q <= Qn; Q++) {
			lld tmp = 1, ans = 0;
			int i, j;
			read(i); read(j);
			
			if (i != 0) for (; i <= n && j <= n; i++, j++) {
				tmp = tmp * i % MOD;
				ans = (ans + tmp * fact[j]) % MOD;
			}
			printf("%lld\n", ans);
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
