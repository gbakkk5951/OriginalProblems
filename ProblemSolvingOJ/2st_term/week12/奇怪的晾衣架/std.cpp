#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n;
int l[maxn], r[maxn];
int child[maxn];
vector<int> id[maxn];

void dfs(int x, int h) {
	if (x) {
		id[h].push_back(x);
		dfs(l[x], h + 1);
		dfs(r[x], h);
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
		child[l[i]] = 1;
		child[r[i]] = 1;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (child[i] == 0) {
			assert(++cnt == 1);
			dfs(i, 1);
		}
	}
	for (int i = 1; id[i].size(); ++i) {
		for (auto j : id[i]) {
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}
