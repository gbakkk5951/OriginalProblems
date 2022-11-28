#include <bits/stdc++.h>
using namespace std;
namespace my {
const int maxn = 102;
int a[maxn];
int max(int n) {
	if (n == 1) {
		return a[n];
	}
	return ::max(max(n - 1), a[n]);
}
}
int main() {
	using namespace my;
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	cout << max(n);
	return 0;
}
