using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
namespace OI {
const int MXN = 2e5 + 10;
struct Splay {
	void build(int l, int r, int color[]) {
		arr.assign(color, color + r + 1);
	}
	vector<int> arr, tmp;
	int query(int l, int r) {
		int lst = -1, cnt = 0;
		for (int i = l; i <= r; i++) {
			if (arr[i] != lst) {
				++cnt;
				lst = arr[i];
			}
		}
		return cnt;
	}
	void mov(int l, int len, int nl) {
		tmp.assign(arr.begin() + l, arr.begin() + l + len);
		arr.erase(arr.begin() + l, arr.begin() + l + len);
		arr.insert(arr.begin() + nl, tmp.begin(), tmp.end());
	}
	
	void assign(int l, int r, int v) {
		fill(arr.begin() + l, arr.begin() + r + 1, v);
	}
	void reverse(int l, int r) {
		std::reverse(arr.begin() + l, arr.begin() + r + 1);
	}
	
	
}tree;


struct _Main {
	int n, Qn;
	int color[MXN];
	_Main() {
		int op, l, r, v, nl, len;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(color[i]);
		}
		tree.build(1, n, color);
		for (int Q = 1; Q <= Qn; Q++) {
			read(op);
			if (op == 1) {//¸³Öµ
				read(l); read(r); read(v);
				tree.assign(l, r, v);
			} else
			if (op == 2) {//rev
				read(l); read(r);
				tree.reverse(l, r);
			} else
			if (op == 3) {//mov
				read(l); read(len); read(nl);
				tree.mov(l, len, nl);
			} else { //query
				read(l); read(r);
				printf("%d\n", tree.query(l, r));
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
}canister;
}
