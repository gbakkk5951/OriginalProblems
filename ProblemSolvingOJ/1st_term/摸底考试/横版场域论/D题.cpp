using namespace std;
#include <bits/stdc++.h>
const int MXN = 1e5 + 10;
enum classmates {job, dir};
char cm[MXN][2];
int main() {
	int now = 0;
	int n, m, t;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> t;
		cm[i][dir] = t;
		cin.ignore();
		cin >> cm[i][job];
	}
	int d, p;
	for (int i = 1; i <= m; ++i) {
		cin >> d >> p;
		now = ((now + ((d ^ cm[now][dir]) ? 1 : -1) * p) % n + n) % n;
		cout << cm[now][job] << endl;
	}
	return 0;
}
