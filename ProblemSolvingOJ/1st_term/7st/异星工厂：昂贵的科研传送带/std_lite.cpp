#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
struct Queue {
	int arr[maxn], n, qh, qt;
	/*有效范围[0, n]这里的n是指输入的n*/
	void init(int n) {
		qh = 0; qt = 0;
		this->n = n + 1;
	}
	bool empty() {/*重合为空*/
		return qh == qt;
	}
	bool full() {/*错开为满, n == 1即输入的n == 0时，既是空的又是满的*/
		return (qt + 1 == n ? 0 : qt + 1) == qh;
	}
	void insert(int value) {
		assert(!full());
		arr[qt++] = value;
		qt = qt == n ? 0 : qt;
	}
	int pop() {
		assert(!empty());
		int v = arr[qh];
		++qh;
		qh = qh == n ? 0 : qh;
		return v;
	}

}q;
int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	q.init(n);
	while (m--) {
		int op, x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			if (!q.full()) {
				q.insert(x);
			}
		} else {
			if (!q.empty()) {
				cout << q.pop() << endl;
			}
		}
	}
	return 0;
}
