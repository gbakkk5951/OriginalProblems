using namespace std;
int main() {/* Counter: 1 */}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
namespace OI {
typedef long long lld;
const lld MOD = 479 << 21 | 1;
const int MXN = 4200000;
const int MXP = 23;
//const int MXN = 1050000;
//const int MXP = 21;
typedef pair<int, int> p;
struct _Main {
	vector <p> mission[MXP];
	lld res[MXP][MXN];
	lld a[MXN], b[MXN];
	int n, mxpow, mxbit;
	int cnt;
	void getmission(int al, int ar, int bl, int br, int bit) {/* Counter: 11382917 */
		if (al + bl > n) return;
		if (ar + br <= n) {/* Counter: 2894755 */
			cnt++;
			mission[bit].push_back(make_pair(al, bl));
			return;
		}
		int amid = al + ar >> 1, bmid = bl + br >> 1;
		getmission(al, amid, bl, bmid, bit - 1);
		getmission(al, amid, bmid + 1, br, bit - 1);
		getmission(amid + 1, ar, bl, bmid, bit - 1);
		getmission(amid + 1, ar, bmid + 1, br, bit - 1);
	}
	void FWT() {/* Counter: 1 */
		lld *x, *y, *arr;
		for (int I = 0; I <= mxbit; I++) {/* Counter: 22 */
			if (I) {/* Counter: 21 */
				int half = 1 << I - 1;
				for (int J = 0; J < 2; J++) {/* Counter: 42 */
					arr = J ? a : b;
					for (int i = 0; i < mxpow; i += half << 1) {/* Counter: 4194302 */
						x = arr + i; y = arr + i + half;
						for (int j = 0; j < half; j++) {/* Counter: 44040192 */
							x[j] = (x[j] + y[j]) % MOD;
						}
					}
				}
			}
			for (int i = 0; i < mission[I].size(); i++) {
				x = a + mission[I][i].first;
				y = b + mission[I][i].second;
				arr = res[I] + (((mission[I][i].first >> I) & (mission[I][i].second >> I)) << I);
				for (int j = 0; j < 1 << I; j++) {/* Counter: 35955393 */
					arr[j] = (arr[j] + x[j] * y[j]) % MOD;
				}
			}
		}
	}
	
	void NFWT() {/* Counter: 1 */
		lld *arr, *x, *y;
		for (int I = mxbit; I >= 1; I--) {/* Counter: 21 */
			int half = 1 << I - 1;
			arr = res[I];
			for (int i = 0; i < mxpow; i += half << 1) {/* Counter: 2097151 */
				x = arr + i; y = arr + i + half;
				for (int j = 0; j < half; j++) {/* Counter: 22020096 */
					x[j] = (x[j] - y[j]) % MOD;
				}
			}
			x = res[I - 1];
			for (int i = 0; i < mxpow; i++) {/* Counter: 44040192 */
				x[i] = (x[i] + arr[i]) % MOD;
			}
		}
	}
	
	_Main() {/* Counter: 1 */
		freopen("data0.in", "r", stdin);
		read(n);
		/*for (int i = 0; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 0; i <= n; i++) {
			read(b[i]);
		}*/
		for (mxbit = 0; 1 << mxbit <= n; mxbit++);
		mxpow = 1 << mxbit;
		getmission(0, mxpow - 1, 0, mxpow - 1, mxbit);
		cerr << cnt;
		FWT();
		NFWT();
		lld ans[3] = {0, 0, 0};
		for (int i = 0; i <= n; i++) {/* Counter: 1897153 */
			ans[i % 3] += res[0][i];
		}
		for (int i = 0; i < 3; i++) {/* Counter: 3 */
			ans[i] %= MOD;
			ans[i] += ans[i] < 0 ? MOD : 0;
			printf("%lld\n", ans[i]);
		}
	}
template <typename Type>
	void read(Type &a) {/* Counter: 1 */
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {/* Counter: 6 */
			a *= 10; a += t - '0';
		}
	}
}grox4th;
}
