using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const lld MOD = 479 << 21 | 1;
const lld G = 3;
const lld PHI = MOD - 1;
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow += pow < 0 ? PHI : 0;
	while (pow) {
		ret = (pow & 1) ? ret * base % MOD : ret;
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
		if (arr[i] < arr[j]) {
			swap(arr[i], arr[j]);
		}
	}
}
void NTT(lld arr[], int len, int pow) {
	static lld w[257];
	lld *a, *b, x, y, wn;
	mov_ele(arr, len);
	w[0] = 1;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		wn = fastpower(G, pow * PHI >> I);
		for (int i = half - 1; i > 0; i -= 2) {
			w[i] = w[i >> 1];
		}
		for (int i = 1; i < half; i += 2) {
			w[i] = w[i - 1] * wn % MOD;
		}
		for (int i = 0; i < len; i += half << 1) {
			a = arr + i; b = arr + i + half;
			for (int j = 0; j < half; j ++) {
				x = a[j];
				y = b[j] * w[j];
				a[j] = (x + y) % MOD;
				b[j] = (x - y) % MOD;
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
	lld a[512][512];
	lld ans[512];
	int k, n;
	_Main() {
		read(k); n = 1 << k;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				read(a[i][j]);
			}
			NTT(a[i], n, 1);
		}
		fill(ans, ans + n, 1);
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (k = 0; k < n; k++) {
					ans[k] = ans[k] * (a[j][k] - a[i][k]) % MOD;
				}
			}
		}
		NTT(ans, n, -1);
		for (int i = 0; i < n; i++) {
			printf("%lld ", ans[i] + (ans[i] < 0 ? MOD : 0));
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
}instance;

}


