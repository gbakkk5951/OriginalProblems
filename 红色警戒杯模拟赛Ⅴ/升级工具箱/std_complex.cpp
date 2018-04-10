using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 1005, MXM = 8005;
const lld MOD = 1e8 + 7;
lld tmp[MXM];
struct pl {
	lld arr[MXM];
	int high;
	inline lld & operator [] (int idx) {
		return arr[idx];
	}
	void operator *= (pl &b) {
		for (int i = high + b.high; i >= 0; i--) {
			lld t1, t2;
			int mn = min(i, high);
			t1 = t2 = 0;
			for (int j = i < b.high ? 0 : i - b.high, k = min(b.high, i); j <= mn; j += 2, k -= 2) {
				t1 = (t1 + arr[j] * b[k]) % MOD;
				t2 = k ? ((t2 + arr[j + 1] * b[k - 1]) % MOD) : t2;
			}
			arr[i] = (t1 + t2) % MOD;
		}
		high += b.high;
	}
}poly[MXN];
struct _Main {
	int n;
	_Main() {
		read(n);
		int a, b, lim, sum = 0;
		for (int i = 1, id = 1; i <= n; i++, id++) {
			read(a); read(b);
			lim = min(a, b / id);
			if (lim == 0) {
				i--; n--;
				continue;
			}
			sum += lim;
			poly[i].high = lim;
			for (int j = 0; j <= lim; j++) {
				poly[i][j] = 1;
			}
		}
		if (n == 0) {
			printf("1");
			return;
		}
		for (int i = 2; i <= n; i++) {
			poly[1] *= poly[i];
		}
		for (int i = 0; i <= sum; i++) {
			printf("%lld ", poly[1][i]);
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
}toolkit;
}
