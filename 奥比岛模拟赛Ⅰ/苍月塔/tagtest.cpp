#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
namespace OI {
typedef long long lld;
typedef pair<int, int> p;
const int MXN = 5e6 + 10;
const int X = 0, Y = 1, NXT = 2;
int cnt;
struct ArrayTree {
	int n;
	int node[MXN]; //卡一下int 1 Vam = 0, 2 Csthp = 0 3怪物的攻击力集中，
	void add(int nd, int v) {//攻击力=n时复杂度最大
		for (nd = n - nd + 1; nd <= n; nd += nd & (-nd)) {
			node[nd] += v;
			++cnt;
		}
	}
	int query(int nd, int v) {
		int ret = 0;
		for (nd  = n - nd + 1; nd > 0; nd -= nd & (-nd)) {
			ret += node[nd];
		}
		return ret;
	}
}tree;
struct _Main {
	vector<p> a[MXN];
	int head[MXN];
	int list[MXN * 5][3];
	int lidx;
	void add(int pos, int x, int y) {
		lidx++;
		list[lidx][X] = x;
		list[lidx][Y] = y;
		list[lidx][NXT] = head[pos];
		head[pos] = lidx;
	 }
	_Main() {
		int n = 1000000, cnt = 25000000 / n;
		tree.n = n;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= cnt; j++) {
				tree.add(n, j);
			}
		}
		printf("cnt = %d\n", OI::cnt);
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
}tagtest;
}
