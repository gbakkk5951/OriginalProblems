using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
namespace OI {
const int MXN = 1e5 + 10;
struct _Main {
	int arr[MXN];
	int ans[250020];
	int r[MXN];
	_Main() {
		int mx = 0, n;
		read(n);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
			mx = max(mx, arr[i]);
		}
		memset(r, 63, (n + 1) * sizeof(int));
		int l;
		for (int i = n - 1; i >= 1; i--) {
			l = 0x3f3f3f3f;
			for (int j = i + 1; j <= n; j++) {
				l = r[j] = min(min(l, r[j]), abs(arr[i] - arr[j]));
				ans[l] = max(ans[l], j - i + 1);
			}
		}
		for (int i = 0; i < mx; i++) {
			printf("%d\n", ans[i]);
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
