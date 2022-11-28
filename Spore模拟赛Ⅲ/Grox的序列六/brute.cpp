using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const lld mod = 1e9 + 7;
const int CHANGE = 1;
struct _Main {
	lld a, b, arr[205];
	int ask[1005];
	_Main() {
		int Qn, k, mx = 1, op, n;
		read(Qn); read(b); read(k);
		read(a);
		for (int i = 0; i <= k; i++) {
			read(arr[i]);
		}
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); 
			if (op == CHANGE) {
				read(a);
				for (int i = 0; i <= k; i++) {
					read(arr[i]);
				}
				continue;
			}
			read(n);
			lld ret = a;
			for (int i = 1; i <= n; i++) {
				ret = ret * b % mod;
				lld tmp = 0;
				for (int j = k; j >= 0; j--) {
					tmp = (tmp * i + arr[j]) % mod;
				}
				ret = (ret + tmp) % mod;
			}
			ret += ret < 0 ? mod : 0;
			printf("%lld\n", ret);
		}


	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			if (t == '-') f = -1;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}	
}brute;
}
