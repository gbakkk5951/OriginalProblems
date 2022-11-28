using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <functional>
namespace OI {
typedef pair<int, int> pr;
typedef long long lld;
typedef set<pr, greater<pr> > st;
const int MXN = 1e5 + 10;
const lld MOD = 1e9 + 7;
st tree;
struct _Main {
	int c[MXN], p[MXN];
	lld s[MXN]; //val, production, storge
	_Main() {
		int n, Qn;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(c[i]); read(p[i]);
			tree.insert((pr) {c[i], i});//忘了插入了
		}
		int op, a, b, nd;
		lld rem;
		unsigned long long ans;
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {//生产
				read(a);
				for (int i = 1; i <= n; i++) {
					s[i] += p[i] * a;
				}
			} else if (op == 2) {//出售
				read(rem);
				ans = 0;
				for (st::iterator it = tree.begin(); it != tree.end(); ++it) {
					nd = it->second;
					if (rem <= s[nd]) {
						ans = (ans + rem % MOD * c[nd]) % MOD;
						s[nd] -= rem;
						break;
					} else {
						ans = (ans + s[nd] % MOD * c[nd]) % MOD;
						rem -= s[nd];
						s[nd] = 0;
					}
				}
				ans += (ans < 0) ? MOD : 0;
				printf("%lld\n", ans);
			} else if (op == 3) {//改产量
				read(a); read(b);
				p[a] = b;
			} else if (op == 4) {//改价格
				read(a); read(b);
				tree.erase((pr) {c[a], a});
				c[a] = b;
				tree.insert((pr) {c[a], a});
			}
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
