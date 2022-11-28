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
		lld t; 
		for (int i = 0; i <= high; i++) {
			t = arr[i];
			for (int j = 0; j <= b.high; j++) {
				tmp[i + j] = (tmp[i + j] + t * b[j]) % MOD;
			}
		}
		high += b.high;
		memcpy(arr, tmp, (high + 1) * sizeof(lld));
		memset(tmp, 0, (high + 1) * sizeof(lld));
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
