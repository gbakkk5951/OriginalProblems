using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
namespace OI {
const int MXN = 4005;
struct _Main {
	int a[MXN], ans[MXN], tar[MXN];
	int n, m, pn, Qn;
	_Main() {
		int l, r;
		read(n); read(m); read(pn); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 1; i <= pn; i++) {
			read(tar[i]);
		}
		for (int Q = 1; Q <= Qn; Q++) {
			read(l); read(r);
			for (int i = 1; i <= pn; i++) {
				for (int j = 0; j <= r - l && tar[i] + j <= m; j++) {
					ans[tar[i] + j] += a[l + j];
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			printf("%d ", ans[i]);
		}
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
}brute;
}

