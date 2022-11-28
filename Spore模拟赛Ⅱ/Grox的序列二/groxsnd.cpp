using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 270000;
const lld MOD = 479 << 21 | 1;
const lld PHI = MOD - 1;
const lld G = 3;
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow %= PHI; pow += pow < 0 ? PHI : 0;
	while (pow) {
		ret = (pow & 1) ? ret * base % MOD : ret;
		base = (pow >>= 1) ? base * base % MOD : base;
	}
	return ret;
}
namespace NTTsp {
	lld *ww[2][19];//0表示正运算 1 表示逆运算
	void init(int len) {
		for (int pow = 0; pow < 2; pow++) {
			for (int I = 1; 1 << I <= len; I++) {
				lld *w = ww[pow][I] = (lld*)calloc(1 << I - 1, sizeof(lld));
				lld wn = fastpower(G, (pow ? -1 : 1) * PHI >> I);
				w[0] = 1;
				for (int i = 1; i < 1 << I - 1; i++) {
					w[i] = w[i - 1] * wn % MOD;
				}
			}
		}
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
		lld x, y;
		lld *a, *b, *w;
		int half;
		mov_ele(arr, len);
		for (int I = 1; 1 << I <= len; I++) {
			w = ww[pow == -1][I];
			half = 1 << I - 1;
			for (int i = 0; i < len; i += half << 1) {
				a = arr + i; b = arr + i + half;
				for (int j = 0; j < half; j++) {
					x = a[j];
					y = b[j] * w[j];
					a[j] = (x + y) % MOD;
					b[j] = (x - y) % MOD;
				}
			}
		}
		if (pow == -1) {
			lld wn = fastpower(len, -1);
			for (int i = 0; i < len; i++) {
				arr[i] = arr[i] * wn % MOD;
			}
		}
	}
}

struct _Main {
	int n;
	lld ans[MXN];
	lld fr[MXN];
	lld rfr[MXN];
	lld a[MXN];
	lld b[MXN];
	void calc(int l, int r, int rl, int rr) { //坐标为卷积坐标，不是指数
		int len = r - l + 1;
		int t;
		if (len == 1) {
			for (int i = rr; i >= rl && l + (n - i) <= n; i--) {
				ans[l + i] = (ans[l + i] + fr[l] * rfr[i]) % MOD;
			}
			return;
		}
		int mid = l + r >> 1, rmid = rr + 1;
		for (; rmid - 1 >= rl && n - (rmid - 1) + mid <= n; rmid--);

		int s1 = mid - l + 1, s2 = rr - rmid + 1;
		int mxpow;
		for (mxpow = 1; mxpow < s1 + s2; mxpow <<= 1);
		memset(a, 0, mxpow * sizeof(lld));
		memset(b, 0, mxpow * sizeof(lld));
		memcpy(a, fr + l, s1 * sizeof(lld));
		memcpy(b, rfr + rmid, s2 * sizeof(lld));
		using NTTsp::NTT;
		NTT(a, mxpow, 1);
		NTT(b, mxpow, 1);
		for (int i = 0; i < mxpow; i++) {
			a[i] = a[i] * b[i] % MOD;
		}
		NTT(a, mxpow, -1);
		t = l + rmid;
		for (int i = 0; i < s1 + s2; i++) {
			ans[t + i] = (ans[t + i] + a[i]) % MOD;
		}
		
		if (rmid > rl) {
			calc(l, mid, rl, rmid - 1);
		}
		if (rmid <= rr) {
			calc(mid + 1, r, rmid, rr);
		}
	}
	_Main() {
		read(n);
		fr[0] = 1;
		int mxpow;
		for (mxpow = 1; mxpow < 2 * n + 1; mxpow <<= 1);
		NTTsp::init(mxpow);
		for (int i = 1; i <= n; i++) {
			fr[i] = fr[i - 1] * fastpower(i, -1) % MOD;
		}
		for (int i = 0; i <= n; i++) {
			rfr[i] = fr[n - i];
		}
		calc(0, n, 0, n);
		lld out[3] = {0, 0, 0};
		int j = ((-n % 3) + 3) % 3;
		for (int i = 0; i <= n << 1; i++) {
			out[j] += ans[i];
			if (++j == 3) j = 0;
		}
		for (int i = 0; i < 3; i++) {
			printf("%lld ", (out[i] % MOD + MOD) % MOD);
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
	
}groxsnd;
}
