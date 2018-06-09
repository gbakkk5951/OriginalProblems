using namespace std;
int main() {}
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 1e5 + 10;
struct _Main {
	int cost[MXN];
	_Main() {
		int n, Qn;
		int op, a, b;
		lld tot;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(cost[i]); read(b);
			node[i] = new_(i, cost[i], b);
		}
		tree.root = tree.build(1, 1, n);
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {//生产
				read(a);
				tree.root->produce(a);
			} else 
			if (op == 2) {//出售
				read(tot);
				printf("%lld\n", tree.sell(tot));
			} else
			if (op == 3) {//产量
				read(a); read(b);
				tree.find((pr) {cost[a], a});
				tree.root->p = cost[a];
				tree.root->update();
			} else
			if (op == 4) {//价格
				tree.erase((pr) {cost[a], a});
				cost[a] = a;
				tree.insert(node[a]);
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
}std;
}
