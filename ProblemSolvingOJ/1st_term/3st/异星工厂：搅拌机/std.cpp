using namespace std;
#include <bits/stdc++.h>
const int maxn = 21;
int n, m, Qn;
int block[maxn][maxn], temp[maxn][maxn];
const char error[] = "Invalid arguments!";
void print() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << block[i][j] << " ";
		}
		cout << endl;
	}
}
int main() {
	int op, a, b, Qn;
	cin >> n >> m >> Qn;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> block[i][j];
		}
	}
	for (int Q = 1; Q <= Qn; ++Q) {
		cin >> op;
		switch(op) {
			case 1: {
				cin >> a >> b;
				if (1 <= min(a, b) && max(a, b) <= n) {
					for (int i = 1; i <= m; i++) {
						swap(block[a][i], block[b][i]);
					}
					print();
				} else {
					cout << error << endl;
				}
				break;
			}
			case 2: {
				cin >> a >> b;
				if (1 <= min(a, b) && max(a, b) <= m) {
					for (int i = 1; i <= n; i++) {
						swap(block[i][a], block[i][b]);
					}
					print();
				} else {
					cout << error << endl;
				}
				break;
			}
			case 3: {
				for (int i = 1; i <= n; ++i) {
					for (int j = 1; j <= m; ++j) {
						temp[j][n - i + 1] = block[i][j];
					}
				}
				memcpy(block, temp, sizeof(temp));
				swap(n, m);
				print();
				break;
			}
		}
	}
	return 0;
}
