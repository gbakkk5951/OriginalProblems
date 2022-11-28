#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 10;
int vis[MXN], d[MXN], stk[MXN], instk[MXN];
int top;
int n;
template <typename Type>
	void (Type &a) {
		int t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}
int main() {
	int ans = 0;
	read(n);
	for (int i = 1; i <= n; ++i) read(d[i]);
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		int nd = i;
		while (!vis[nd]) {
			vis[nd] = 1; 
			stk[instk[nd] = ++top] = nd;
			nd = d[nd];
		}
		if (instk[nd]) {
			ans += top - instk[nd] + 1;
		}
		while (top) {
			instk[stk[top--]] = 0;
		}
	}
	printf("%d", ans);
	return 0;
}
