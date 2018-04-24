using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const lld MOD = 1917 << 19 | 1;
const lld PHI = MOD - 1;
const lld G = 5;
const lld MXN = 270000;
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow += pow < 0 ? PHI : 0;
	while (pow) {
		ret = (pow & 1) ? base * ret % MOD : ret;
		base = (pow >>= 1) ? base * base % MOD : base;
	}
	return ret;
}
void mov_ele(lld arr[], int len) {
	for (int i = 1, j = 0, k; i < len; i++) {
		for (k = len >> 1; k & j; k >>= 1) {
			j ^= k;
		}
		j |= k;
		if (i < j) {
			swap(arr[i], arr[j]);
		}
	}
}

void NTT(lld arr[], int len, int pow) {
	static lld w[MXN >> 1];
	lld *a, *b, x, y, wn;
	w[0] = 1;
	mov_ele(arr, len);
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		wn = fastpower(G, pow * PHI >> I);
		for (int i = half - 2; i > 0; i -= 2) {
			w[i] = w[i >> 1];
		}
		for (int i = 1; i < half; i += 2) {
			w[i] = w[i - 1] * wn % MOD;
		}
		for (int i = 0; i < len; i += half << 1) {
			a = arr + i; b = arr + i + half;
			for (int k = 0; k < half; k++) {
				x = a[k];
				y = b[k] * w[k];
				a[k] = (x + y) % MOD;
				b[k] = (x - y) % MOD;
			}
		}
	}
	if (pow == -1) {
		wn = fastpower(len, -1);
		for (int i = 0; i < len; i++) {
			arr[i] = arr[i] * wn % MOD;
		}
	}
}

struct _Main {
	lld s[MXN], tmp[MXN];
	void getstirling() {
		tmp[0] = 1;
		for (int i = 1; i <= k; i++) {
			tmp[i] = tmp[i - 1] * fastpower(i, -1) % MOD;
		}
		memcpy(s, tmp, (k + 1) * sizeof(lld));
		for (int i = 0; i <= k; i++) {
			s[i] *= fastpower(-1, i);
		}
		for (int i = 0; i <= k; i++) {
			tmp[i] = tmp[i] * fastpower(i, k) % MOD;
		}
		int mxpow;
		for (mxpow = 1; mxpow <= k << 1; mxpow <<= 1);
		NTT(s, mxpow, 1);
		NTT(tmp, mxpow, 1);
		for (int i = 0; i < mxpow; i++) {
			s[i] = s[i] * tmp[i] % MOD;
		}
		NTT(s, mxpow, -1);
		/*for (int i = 0; i <= k; i++) {
			printf("%lld ", s[i] + (s[i] < 0 ? MOD : 0));
		}
		printf("\n");*/
	}
	int n, k;
	lld calc() {
		lld ret = 0;
		lld mul = 1;
		for (int i = 1; i <= k; i++) {
			mul = mul * (n - i + 1) % MOD;
			ret = (ret + mul * fastpower(2, n - i) % MOD * (s[i] % MOD)) % MOD;
		}
		return ret;
	}
	_Main() {
		lld ans;
		read(n); read(k);
		if (k == 0) {
			printf("%lld", fastpower(2, n) - 1);
			return;
		}
		getstirling();
		ans = calc();
		ans += ans < 0 ? MOD : 0;
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
}grox5th;
}
