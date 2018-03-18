using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
namespace OI {
const int MXN = 100010;
struct _Main {
	int n;
	char v[MXN];
	int x[MXN][3];
	int xn[MXN][3];
	int ans, arr[MXN];
	void rd(int arr[]) {
		for (int i = 0; i < 3; i++) {
			read(arr[i]);
		}
	}
	_Main() {
		read(n); 
		rd(x[0]);
		for (int i = 1; i <= n; i++) {
			rd(xn[i]); rd(x[i]);
		}
		for (int i = 0; i <= ans; i++) {
			for (int j = 1; j <= n; j++) if (!v[j]) {
				int k;
				for (k = 0; k < 3; k++) {
					if (xn[j][k] > x[arr[i]][k]) {
						break;
					}
				}
				if (k == 3) {
					arr[++ans] = j;
					v[j] = 1;
				}
			}
		}
		printf("%d", ans);
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
