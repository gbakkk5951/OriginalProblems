#include <bits/stdc++.h>
using namespace std;
const int MXN = 23;
int b[MXN][MXN];
int cho[MXN];
int n;
int used[MXN];
int ans;
bool test(int a, int now) {
	return a >= now || used[a];
}
void dfs(int now) {
	if (now == n + 1) {
		++ans;
		return;
	}
	int flag = 1;
	if (!used[now]) dfs(now + 1);
	for (int j = 1; j <= n; ++j) if (used[j]) {
		if (!test(b[j][now], now) || !test(b[now][j], now)) {
			flag = 0;
			break;
		}
	}
	if (flag != 0) {
		for (int j = 1; j <= n; ++j) if (used[j]) {
			if (!used[b[now][j]]) {
				used[b[now][j]] = now;
			}
			if (!used[b[j][now]]) {
				used[b[j][now]] = now;
			}
		}
		if (used[now] == 0) used[now] = now;
		dfs(now + 1);
		if (used[now] == now) used[now] = 0;
		for (int j = 1; j <= n; ++j) if (used[j] >= now) {
			used[j] = 0;
		}
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> b[i][j];
		}
	}
	dfs(1);
	cout << ans - 1;
	return 0;
}

