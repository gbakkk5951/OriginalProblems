using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cstdlib>
namespace OI {
typedef long long lld;
const int MXN = 500005;
int cost[MXN], kind[MXN];

struct _Main {
	lld calc(int l, int r, int c) {
		lld ret = 0;
		for (int i = l; i <= r; i++) {
			ret += abs(cost[c] - cost[kind[i]]);
		}
		return ret;
	}
	void change(int l, int r, int c) {
		for (int i = l; i <= r; i++) {
			kind[i] = c;
		}
	}
	_Main() {
		int n, Qn, K; 
		int l, r, c, e, op;
		read(n); read(K); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(kind[i]);
		}
		for (int i = 1; i <= K; i++) {
			read(cost[i]);
		}
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 0) {
				read(l); read(r); read(c);
				printf("%lld\n", calc(l, r, c));
				change(l, r, c);
			} else {
				read(c); read(e);
				cost[c] = e;
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
}list; 
}
