using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 132000;
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
	lld *ww[2][18];//0表示正运算 1 表示逆运算
	void init(int len) {
		for (int pow = 0; pow < 2; pow++) {
			for (int I = 1; 1 << I <= len; I++) {
				lld *w = ww[pow][I] = callc(1 << I - 1, sizeof(lld));
				lld wn = fastpower(G, (pow ? -1 : 1) * PHI >> I)
				w[0] = 1;
				for (int i = 1; i < 1 << I - 1; i++) {
					w[i] = w[i - 1] * wn % MOD;
				}
			}
		}
	}
	void swp(lld arr[], int len) {
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
	void NTT(lld arr[], int len) {
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
	lld a[MXN];
	lld b[MXN];
	int mxpow;
	void calc(int l, int r, int rl, int rr) { //坐标为卷积坐标，不是指数
		int len = r - l + 1;
		int t;
		if (len == 1) {
			t = mxpow + l - rl;
			ans[t] = (ans[t] + fr[l] * fr[rl]) % MOD;
			return;
		}
		int mid = l + r >> 1, rmid = rl + rr >> 1;
		memcpy(a, fr + l, len * sizeof(lld));
		memcpy(b, rfr + rmid + 1, len * sizeof(lld));
		NTT(a, len << 1, 1);
		NTT(b, len << 1, 1);
		for (int i = 0; i < len << 1; i++) {
			a[i] = a[i] * b[i] % MOD;
		}
		NTT(a, len << 1, -1);
		//t = mxpow + (-mxpow + rmid + 1) + l;
		t = l + rmid + 1;
		for (int i = 0; i < len << 1; i++) {
			ans[t + i] = (ans[t + i] + a[i]) % MOD;
		}
		calc(l, mid, rl, rmid);
		calc(mid + 1, r, rmid + r, rr);
	}	
	_Main() {
		read(n);
		for (mxpow = 1; mxpow < n + 1; mxpow++);
		fr[0] = 1;
		for (int i = 1; i < mxpow; i++) {
			fr[i] = fr[i - 1] * fastpower(i, -1) % MOD;
		}
		for (int i = 0; i < mxpow; i++) {
			rfr[i] = fr[mxpow - i - 1];
		}
		calc(0, mxpow - 1, 0, mxpow - 1);
		for (int i = mxpow - n; i <= mxpow + n; i++) {
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
	
}groxsnd;
}
