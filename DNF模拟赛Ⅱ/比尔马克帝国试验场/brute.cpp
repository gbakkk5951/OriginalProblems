using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
namespace OI {
typedef long long lld;
const int MXN = 100010;
const int INF = 0x3f3f3f3f;
struct _Main {
	lld ans;
	int rl[MXN], d[MXN];
	int cnt[MXN];
	_Main() {
//		freopen("data4.in", "r", stdin);
		int n, Qn;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(rl[i]);
		}
		for (int i = 1; i <= n; i++) {
			read(d[i]);
		}
		rl[0] = rl[n + 1] = INF;
		d[0] = INF;
		int l, r, dl, dr, nd;
		for (int Q = 1; Q <= Qn; Q++) {
//			if (Q % 1000 == 0) {
//				cerr << Q << endl;
//			}
			read(nd);
//			if (Q % 1000 == 0) {
//				cerr << "nd = " << nd << endl;
//			}
			dl = dr = 0;
			if (rl[nd]) {
				--rl[nd];
			} else {
				for (r = nd; !rl[r]; r++) {
					dr += (cnt[r] < 0) ? -d[r] : d[r];
				}
				for (l = nd - 1; ; l--) {
					dl += (cnt[l] > 0) ? -d[l] : d[l];
					if (rl[l]) {
						break;
					}
				}
				if (dl <= dr) {
					ans += dl;
					for (int i = nd - 1; i >= l; i--) {
						cnt[i]--;
					}
					rl[l]--;
				} else {
					ans += dr;	
					for (int i = nd; i < r; i++) {
						cnt[i]++;
					}
					rl[r]--;
				}				
			}
			printf("%lld\n", ans);
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
}brute;
}
