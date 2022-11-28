#include <bits/stdc++.h>
using namespace std;
const string sp = " ";
int main() {
	freopen("data_ex.in", "w", stdout);
	int Tn = 1000, n = 50;
	cout << Tn << endl;
	const int GAP = 15;
	for (int T = 1; T <= Tn; T++) {
		cout << n << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j || i == 1 || j == n || (i <= GAP && j > GAP) || (i > GAP && j > i)) {
					cout << 1 << sp;
				} else {
					cout << 0 << sp;
				}
			}
			cout << endl;
		}
	}
	return 0;
}
