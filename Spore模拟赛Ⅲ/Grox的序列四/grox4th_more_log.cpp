#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace OI {
typedef long long lld;
const lld MOD = 479 << 21 | 1;
//const int MXN = 4200000;
const lld REV2 = MOD + 1 >> 1;
const int MXN = 1050000;
//const int MXP = 21;

void XOR(lld arr[], int len) {
	lld *x, *y, t1, t2;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				t1 = x[k]; t2 = y[k];
				x[k] = (t1 + t2) % MOD;
				y[k] = (t1 - t2) % MOD;
			}
		}
	}
}

void NXOR(lld arr[], int len) {
	lld *x, *y, t1, t2;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				t1 = x[k]; t2 = y[k];
				x[k] = (t1 + t2) % MOD * REV2 % MOD;
				y[k] = (t1 - t2) % MOD * REV2 % MOD;
			}
		}
	}
}	

void OR(lld arr[], int len) {
	lld *x, *y;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				(y[k] += x[k]) %= MOD;
			}
		}
	}
}

void NOR(lld arr[], int len) {
	lld *x, *y;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				(y[k] -= x[k]) %= MOD;
			}
		}
	}
}

void AND(lld arr[], int len) {
	lld *x, *y;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				(x[k] += y[k]) %= MOD;
			}
		}
	}
}

void NAND(lld arr[], int len) {
	lld *x, *y;
	for (int I = 1; 1 << I <= len; I++) {
		int half = 1 << I - 1;
		for (int j = 0; j < len; j += half << 1) {
			x = arr + j; y = arr + j + half;
			for (int k = 0; k < half; k++) {
				(x[k] -= y[k]) %= MOD;
			}
		}
	}
}

struct _Main {
	lld a[MXN], b[MXN], tmp[MXN];
	lld ans[3];
	int n, mxpow, mxbit;
	void getmission(int al, int ar, int bl, int br, int bit) {
		if (al + bl > n) return;
		if (ar + br <= n) {
			
			int len = ar - al + 1;
			lld *x = a + al, *y = b + bl;
			for (int I = 0; I < 3; I++) {
				void (*FWT)  (lld [], int);
				void (*NFWT) (lld [], int);
				int pos;
				if (I == 0) {
					FWT = XOR;
					NFWT = NXOR;
					pos = al ^ bl;
				} else
				if (I == 1) {
					FWT = OR;
					NFWT = NOR;
					pos = al | bl;
				} else {
					FWT = AND;
					NFWT = NAND;
					pos = al & bl;
				}
				
				
				FWT(x, len);
				FWT(y, len);
				for (int i = 0; i < len; i++) {
					tmp[i] = x[i] * y[i] % MOD;
				}
				NFWT(tmp, len);
				for (int i = 0, j = pos % 3; i < len; i++) {
					ans[j] = (ans[j] + tmp[i]) % MOD;
					j += (j == 2 ? -2 : 1); 
				}
				NFWT(x, len);
				NFWT(y, len);
			}

			
			
			
			return;
		}
		int amid = al + ar >> 1, bmid = bl + br >> 1;
		getmission(al, amid, bl, bmid, bit - 1);
		getmission(al, amid, bmid + 1, br, bit - 1);
		getmission(amid + 1, ar, bl, bmid, bit - 1);
		getmission(amid + 1, ar, bmid + 1, br, bit - 1);
	}

	
	
	
	_Main() {
		read(n);
		
		for (int i = 0; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 0; i <= n; i++) {
			read(b[i]);
		}
		for (mxbit = 0; 1 << mxbit <= n; mxbit++);
		mxpow = 1 << mxbit;
		getmission(0, mxpow - 1, 0, mxpow - 1, mxbit);
		for (int i = 0; i < 3; i++) {
			ans[i] %= MOD;
			ans[i] += ans[i] < 0 ? MOD : 0;
			printf("%lld\n", ans[i]);
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
}grox4th;
}
