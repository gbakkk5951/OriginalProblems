using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
namespace OI {
const int MXN = 100010;
const int CHANGE = 1, INS = 2, DEL = 3;
struct Splay {
	vector<int> data;
	void build(int arr[], int l, int r) {
		data.resize(r - l + 1);
		for (int i = l; i <= r; i++) {
			data[i] = arr[i];
		}
	}
	void erase(int pos) {
		data.erase(data.begin() + pos);
	}
	void insert(int pos, int v) {
		data.insert(data.begin() + pos, v);
	}
	void change(int pos, int v) {
		data[pos] = v;
	}
	int findside(int v, int side) {
		int add = 1, beg = 1, end = data.size();
		if (side) {
			add = -1;
			beg = data.size() - 1;
			end = 0;
		}
		for (int i = beg; i != end; i += add) {
			if (data[i] == v) {
				return i;
			}
		}
		return 0;
	}
}tree;

struct _Main {
	int arr[MXN];
	void ask() {
		if (cnt[0]) {
			if (!(tree.findside(0, 0) & 1) || !(tree.findside(0, 1))) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		} else 
		if (cnt[1]) {
			if ((n & 1) || !(tree.findside(1, 0) & 1) || !((n - tree.findside(1, 1) + 1) & 1)) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		} else {
			printf("%c\n", (char)(n & 1) + '0');
		}
	}
	int cnt[101];
	int n;
	_Main() {
		freopen("brute6.in", "r", stdin);
		int op, Qn, pos, val;
		read(n); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
			cnt[arr[i]]++;
		}
		arr[0] = 2;
		tree.build(arr, 0, n);
		ask();
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); read(pos);
			if (op == CHANGE) {
				read(val);
				--cnt[tree.data[pos]];
				tree.change(pos, val);
				++cnt[val];
			} else if (op == INS) {
				read(val);
				tree.insert(pos, val);
				++cnt[val];
				++n;
			} else if(op == DEL) {
				--cnt[tree.data[pos]];
				tree.erase(pos);
				--n;
			}
			ask();
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
}eaw;
}
