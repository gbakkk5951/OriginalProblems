using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXP = 17, MXN = 100010;

struct LS {
	inline int operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	inline int operator [] (int a) {
		return a << 1 | 1;
	}
}rs;

lld pow[17];
int arr[MXN];
struct Node {
	int cnt[17][2];
	int sum[17];
};

void merge(Node &dst, Node &a, Node &b) {
	int t;
	for (int i = 0; i < MXP; i++) {
		t = a.sum[i];//不存的话若dst == a会挂
		dst.sum[i] = t ^ b.sum[i];
		for (int I = 0; I < 2; I++) {
			dst.cnt[i][I] = a.cnt[i][I] + b.cnt[i][I ^ t];
		}
	}
}
struct SegTree {
	Node node[270000];
	void setval(Node &a, int val) {
		int t;
		for (int i = 0; i < MXP; i++) {
			a.cnt[i][t = val & 1] = 1;
			a.cnt[i][t ^ 1] = 0;
			a.sum[i] = t;
			val >>= 1;
		}
	}
	void build(int nd, int nl, int nr) {
		if (nl == nr) {
			setval(node[nd], arr[nl]);
			return;
		}
		int mid = nl + nr >> 1;
		build(ls[nd], nl, mid);
		build(rs[nd], mid + 1, nr);
		merge(node[nd], node[ls[nd]], node[rs[nd]]);
	}
	
	void change(int nd, int nl, int nr, int pos, int val) {
		if (nl == nr) {
			setval(node[nd], val);
			return;
		}
		int mid = nl + nr >> 1;
		if (pos <= mid) {
			change(ls[nd], nl, mid, pos, val);
		} else {
			change(rs[nd], mid + 1, nr, pos, val);
		}
		merge(node[nd], node[ls[nd]], node[rs[nd]]);
	}
	void query(int nd, int nl, int nr, int l, int r, int &idx, Node *arr[]) {
		if (l <= nl && nr <= r) {
			arr[++idx] = &node[nd];
			return;
		}
		int mid = nl + nr >> 1;
		if (l <= mid) {
			query(ls[nd], nl, mid, l, r, idx, arr);
		}
		if (r > mid) {
			query(rs[nd], mid + 1, nr, l, r, idx, arr);
		}
	}
}tree;
Node *ansarr[45];
Node ans;
int idx;
lld calc(Node &dst) {
	lld ret = 0;
	for (int i = 0; i < MXP; i++) {
		ret += pow[i] * (dst.cnt[i][0] + 1) * dst.cnt[i][1];
	}
	return ret;
}
struct _Main {
	int n, Qn;
	void prepro() {
		pow[0] = 1;
		for (int i = 1; i < MXP; i++) {
			pow[i] = pow[i - 1] << 1;
		}
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
		}
		tree.build(1, 1, n);
	}
	lld query(int l, int r) {
		int idx = 0;
		tree.query(1, 1, n, l, r, idx, ansarr);
		ans = *ansarr[1];
		for (int i = 2; i <= idx; i++) {
			merge(ans, ans, *ansarr[i]); //i写成1了 
		}
		return calc(ans);
	}
	void solve() {
		int op, a, b;
		for (int Q = 1; Q <= Qn; Q++){
			read(op); read(a); read(b);
			if (op == 1) {
				printf("%lld\n", query(a, b));
			} else {
				tree.change(1, 1, n, a, b);
			}
		}
	}
	_Main() {
		prepro();
		solve();
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
}nano;
}
