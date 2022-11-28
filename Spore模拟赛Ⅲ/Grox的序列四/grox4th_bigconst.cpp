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
const int MXN = 1050000;
const int MXP = 21;
const int XOR = 0, OR = 1, AND = 2;
const lld REV2 = MOD + 1 >> 1;
typedef pair<int, int> p;
struct _Main {
	//0 XOR, 1 OR, 2 AND
	vector <p> mission[MXP];
	lld res[3][MXP][MXN];
	lld a[3][MXN], b[3][MXN];
	int n, mxpow, mxbit;
	void getmission(int al, int ar, int bl, int br, int bit) {
		if (al + bl > n) return;
		if (ar + br <= n) {
			mission[bit].push_back(make_pair(al, bl));
			return;
		}
		int amid = al + ar >> 1, bmid = bl + br >> 1;
		getmission(al, amid, bl, bmid, bit - 1);
		getmission(al, amid, bmid + 1, br, bit - 1);
		getmission(amid + 1, ar, bl, bmid, bit - 1);
		getmission(amid + 1, ar, bmid + 1, br, bit - 1);
	}
	void FWT() {
		lld *x, *y, *arr, t1, t2;
		for (int I = 0; I <= mxbit; I++) {
			if (I) {
				int half = 1 << I - 1;
				for (int J = 0; J < 2; J++) {
					arr = J ? a[XOR] : b[XOR];
					for (int i = 0; i < mxpow; i += half << 1) {
						x = arr + i; y = arr + i + half;
						for (int j = 0; j < half; j++) {
							t1 = x[j]; t2 = y[j];
							x[j] = (t1 + t2) % MOD;
							y[j] = (t1 - t2) % MOD;
						}
					}
					// ORÊÇ0, 1 X 0 
					arr = J ? a[OR] : b[OR];
					for (int i = 0; i < mxpow; i += half << 1) {
						x = arr + i; y = arr + i + half;
						for (int j = 0; j < half; j++) {
							y[j] = (y[j] + x[j]) % MOD;
						}
					}
					
					arr = J ? a[AND] : b[AND];
					for (int i = 0; i < mxpow; i += half << 1) {
						x = arr + i; y = arr + i + half;
						for (int j = 0; j < half; j++) {
							x[j] = (x[j] + y[j]) % MOD;
						}
					}
				}
			}
			for (int i = 0; i < mission[I].size(); i++) {
				t1 = mission[I][i].first;
				t2 = mission[I][i].second;
				for (int J = 0; J < 3; J++) {
					x = a[J] + t1;
					y = b[J] + t2;
					arr = res[J][I] + ((J == XOR) ? (t1 ^ t2) : ((J == OR) ? (t1 | t2) : (t1 & t2)));
					for (int j = 0; j < 1 << I; j++) {
						arr[j] = (arr[j] + x[j] * y[j]) % MOD;
					}
				}
			}
		}
	}
	
	void NFWT() {
		lld *arr, *x, *y, t1, t2;
		for (int I = mxbit; I >= 1; I--) {
			int half = 1 << I - 1;
			
			arr = res[XOR][I];
			for (int i = 0; i < mxpow; i += half << 1) {
				x = arr + i; y = arr + i + half;
				for (int j = 0; j < half; j++) {
					t1 = x[j]; t2 = y[j];
					x[j] = (t1 + t2) * REV2 % MOD;
					y[j] = (t1 - t2) * REV2 % MOD;
				}
			}
			
			
			arr = res[OR][I];
			for (int i = 0; i < mxpow; i += half << 1) {
				x = arr + i; y = arr + i + half;
				for (int j = 0; j < half; j++) {
					y[j] = (y[j] - x[j]) % MOD;
				}
			}
			
			arr = res[AND][I];
			for (int i = 0; i < mxpow; i += half << 1) {
				x = arr + i; y = arr + i + half;
				for (int j = 0; j < half; j++) {
					x[j] = (x[j] - y[j]) % MOD;
				}
			}
			
			for (int J = 0; J < 3; J++) {
				x = res[J][I - 1];
				arr = res[J][I];
				for (int i = 0; i < mxpow; i++) {
					x[i] = (x[i] + arr[i]) % MOD;
				}	
			}

		}
	}
	
	_Main() {
		read(n);
		for (int i = 0; i <= n; i++) {
			read(a[1][i]);
		}
		memmove(a[0], a[1], (n + 1) * sizeof(lld));
		memmove(a[2], a[1], (n + 1) * sizeof(lld));
		for (int i = 0; i <= n; i++) {
			read(b[1][i]);
		}
		memmove(b[0], b[1], (n + 1) * sizeof(lld));
		memmove(b[2], b[1], (n + 1) * sizeof(lld));
		for (mxbit = 0; 1 << mxbit <= n; mxbit++);
		mxpow = 1 << mxbit;
		getmission(0, mxpow - 1, 0, mxpow - 1, mxbit);
		FWT();
		NFWT();
		lld ans[3] = {0, 0, 0};
		for (int J = 0; J < 3; J++) {
			lld *arr = res[J][0];
			for (int i = 0, j = 0; i <= n; i++) {
				ans[j] = (ans[j] + arr[i]) % MOD;
				j += (j == 2) ? -2 : 1;
			}
		}

		for (int i = 0; i < 3; i++) {
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
