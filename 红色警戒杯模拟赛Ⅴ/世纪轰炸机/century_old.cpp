using namespace std;
int main() {}
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
namespace OI {
typedef long long lld;
const int POWN = 2055;
const int MXN = 1005;

namespace NTTsp {
	const lld MOD = 479 << 21 | 1;
	const lld PHI = MOD - 1;
	const lld G = 3;
	lld zheng[12][POWN >> 1];
	lld fu[12][POWN >> 1];
	lld *wn;
	int len;
	int swp[POWN];
	
	lld fastpower(lld base, lld pow) {
		if (pow < PHI) pow += PHI;
		lld ret = 1;
		while (pow) {
			if (pow & 1) {
				ret = ret * base % MOD;
			}
			if (pow >>= 1) {
				base = base * base % MOD;
			}
		}
		return ret;
	}
	
	void calc_wn() {
		lld w;
		for (int POW = 1; POW >= -1; POW -= 2) {
			for (int I = 1; 1 << I <= len; I++) {
				wn = (POW == 1 ? zheng[I] : fu[I]);
				wn[0] = 1;
				w = fastpower(G, POW * (PHI >> I));
				for (int i = 1; i < 1 << I - 1; i++) {
					wn[i] = wn[i - 1] * w % MOD; //没取模 
				}
			}
		}
	}
	void calc_mov() {
		int i, j = 0, k;
		for (i = 1; i < len; i++) {
			for (k = len >> 1; j & k; k >>= 1) {
				j ^= k;
			}
			j |= k;
			swp[i] = j;
		}
	}

	void prepro(int _len) {
		len = _len;
		calc_mov();
		calc_wn();
	}
	
	void mov_ele(lld arr[]) {
		for (int i = 0; i < len; i++) {
			if (swp[i] > i) {
				swap(arr[swp[i]], arr[i]);
			}
		}
	}
	
	void NTT(lld arr[], int pow) {
		int half;
		lld x, y;
		lld *a, *b;
		mov_ele(arr);
		for (int I = 1; 1 << I <= len; I++) {
			wn = (pow == 1 ? zheng[I] : fu[I]);
			half = 1 << I - 1;
			for (int j = 0; j < len; j += half << 1) {
				a = arr + j; b = arr + j + half;
				for (int k = 0; k < half; k++) {
					x = a[k];
					y = b[k] * wn[k];
					a[k] = (x + y) % MOD;
					b[k] = (x - y) % MOD;
				}
			}
		}
		if (pow == -1) {
			x = fastpower(len, PHI - 1);
			for (int i = 0; i < len; i++) {
				arr[i] = arr[i] * x % MOD;
				if (arr[i] < 0) arr[i] += MOD;
			}
		}
	}
}

int mxpow;
int pre_xishu[MXN][MXN << 1]; //前缀为i(1开始), 偏移为j(0开始);
int a[MXN];
lld ans[POWN];
lld suf[POWN], xishu[POWN];
int tar[MXN];
struct _Main {
int mxpow;
int n, m, pn, Qn;
void solve() {
	using NTTsp::NTT;
	using NTTsp::MOD;
	NTTsp::prepro(mxpow);
	int flag1, flag2;
	for (int I = 1; I <= n; I++) {//枚举后缀开头
		memset(suf, 0, mxpow * sizeof(lld));
		memset(xishu, 0, mxpow * sizeof(lld));
		flag1 = flag2 = 0;
		for (int j = 0; j < m; j++) {
			xishu[j] = pre_xishu[I][j];
			flag1 |= xishu[j];
		}
		for (int j = 0; I + j <= n; j++) {
			suf[j] = a[I + j];
			flag2 |= suf[j];
		}
		if (!flag1 || !flag2) continue;
//		if (mx1 < 0 || mx2 == 0) continue; //这玩意把负数给过掉了 
		NTT(xishu, 1);
		NTT(suf, 1);
		for (int i = 0; i < mxpow; i++) {
			ans[i] = (ans[i] + xishu[i] * suf[i]) % MOD;
		}
	}
	NTT(ans, -1);
}
void prepro() {
	int l, r;
	read(n); read(m); read(pn); read(Qn);
	for (mxpow = 1; mxpow < n + m; mxpow <<= 1);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
	}
	for (int j = 1; j <= pn; j++)  {
		read(tar[j]); 
	}
	for (int Q = 1; Q <= Qn; Q++) {
		read(l); read(r);
		for (int j = 1; j <= pn; j++) {
			pre_xishu[l][tar[j] - 1]++; 
			pre_xishu[r + 1][tar[j] + r - l + 1 - 1]--;
		}
	}
}
void print() {
	for (int i = 0; i < m; i++) {
		printf("%lld ", ans[i]);
	}
}

_Main() {
	prepro();
	solve();
	print();
}

template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}
}century;
}
