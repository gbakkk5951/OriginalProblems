using namespace std;
int main() {}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
namespace OI {
typedef long long lld;
const lld MOD = 479 << 21 | 1;
const lld PHI = MOD - 1;
const lld G = 3;
lld fastpower(lld base, lld pow) {
	pow %= PHI;
	pow += pow < 0 ? PHI : 0;
	lld ret = 1;
	while (pow) {
		ret = (pow & 1) ? ret * base % MOD : ret;
		base = (pow >>= 1) ? base * base % MOD : base;
	}
	return ret;
}
namespace NTTsp {
	const int MXN = 270000;
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
		lld wn, x, y;
		lld *a, *b;
		int half;
		mov_ele(arr, len);
		w[0] = 1;
		for (int I = 1; 1 << I <= len; I++) {
			wn = fastpower(G, pow * PHI >> I);
			half = 1 << I - 1;
			for (int i = half - 2; i > 0; i -= 2) {
				w[i] = w[i >> 1];
			}
			for (int i = 1; i < half; i += 2) {
				w[i] = w[i - 1] * wn % MOD;
			}
			for (int i = 0; i < len; i += half << 1) {
				a = arr + i; b = arr + (i + half);
				for (int j = 0; j < half; j++) {
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
}

const int MXN = 100010;
struct _Main {
	lld a, b, c, n;
	lld f[MXN], fr[MXN];
	void getfact(int mx) {
		f[0] = fr[0] = 1;
		for (int i = 1; i <= mx; i++) {
			f[i] = f[i - 1] * i % MOD; //½×³ËÃ»Ä£mod ±¬³É0 
			fr[i] = fastpower(f[i], -1);
		}
	}
	void getcom(int b) {
		for (int i = 0; i <= b; i++) {
			com[i] = f[b] * fr[i] % MOD * fr[b - i] % MOD;
		}
	}
	lld com[MXN];// C b 0 -> C b b
	lld pb[270000], pc[270000];
	_Main() {
		lld ans = 0;
		int mxpow;
		read(a, MOD); read(b); read(c); read(n, PHI);
		getfact(max(b, c));
		getcom(b);
		if (n == 0) {
			printf("1");
			return;
		} else 
		if (a + b + c == 0) {
			printf("0");
			return;
		}
		for (int i = 0; i <= b << 1; i += 2) {
			pb[i] = com[i / 2];
		}
		for (int i = 0; i <= c; i++) {
			for (int j = 0; j + i <= c; j++) {
				pc[i - j + c] = (pc[i - j + c] + 
								((j & 1) ? -1 : 1) * fr[i] * fr[j] % MOD * fr[c - i - j]
								) % MOD;
			}
		}
		for (int i = 0; i <= 2 * c; i++) {
			pc[i] = pc[i] * f[c] % MOD;
		}
		for (mxpow = 1; mxpow < (b + c) << 1; mxpow <<= 1);
		using NTTsp::NTT;
		NTT(pb, mxpow, 1);
		NTT(pc, mxpow, 1);
		for (int i = 0; i < mxpow; i++) {
			pb[i] = pb[i] * pc[i] % MOD;
		}
		NTT(pb, mxpow, -1);
		for (int i = 0; i <= (b + c) << 1; i++) {
			ans = (ans + pb[i] * fastpower(a + (i - b - c), n)) % MOD; // ¿¨ a + i - b - c == 0;
		}
		ans = ans * fastpower(2, -(b + c)) % MOD;
		ans += ans < 0 ? MOD : 0;
		printf("%lld", ans);
	}
template <typename Type>
	void read(Type &a, lld mod = (lld)1e18) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a = (a * 10 + t - '0') % mod;
		}
	}

}groxu;
}
