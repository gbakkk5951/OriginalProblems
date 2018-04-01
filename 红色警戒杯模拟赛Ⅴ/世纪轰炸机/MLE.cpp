using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
namespace OI {
const int MXN = 2005;
struct _Main {
	short cf[MXN][MXN];
	int a[MXN];
	int tar[MXN];
	int pn, n, m, Qn;
	_Main() {
		read(n); read(m); read(pn); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(a[i]);
		}
		for (int i = 1; i <= pn; i++) {
			read(tar[i]);
		}
		int l, r;
		for (int Q = 1; Q <= Qn; Q++) {
			read(l); read(r);
			for (int i = 1; i <= pn; i++) {
				cf[l][tar[i]]++;
				if (r + 1 <= n && tar[i] + r - l + 1 <= m)
					cf[r + 1][tar[i] + r - l + 1]--;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cf[i][j] += cf[i - 1][j - 1];
			}
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) {
			ans = 0;
			for (int j = 1; j <= n; j++) {
				ans += cf[j][i] * a[j];
			}
			printf("%d ", ans);
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
}MLE;
}

