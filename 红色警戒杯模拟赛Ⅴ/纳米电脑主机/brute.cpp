using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
namespace OI {
typedef long long lld;
const int MXN = 100010;
struct _Main {
	int n, Qn;
	int arr[MXN];
	int sum[MXN];
	void getsum(int l) {
		for (int i = l; i <= n; i++) {
			sum[i] = sum[i - 1] ^ arr[i];
		}
	}
	lld query(int l, int r) {
		lld ret = 0;
		for (int i = l - 1; i <= r; i++) {
			for (int j = i + 1; j <= r; j++) {
				ret += sum[j] ^ sum[i];
			}
		}
		return ret;
	}
	_Main() {
		int op, a, b;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
		}
		getsum(1);
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); read(a); read(b);
			if (op == 1) {
				printf("%lld\n", query(a, b));
			} else {
				arr[a] = b;
				getsum(a);
			}
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

