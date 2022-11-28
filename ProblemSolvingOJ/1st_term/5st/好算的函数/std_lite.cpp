#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int MX = 1e7;
char v[MX + 10];
lld a[MX + 10];
lld f(lld x) {
	if (x < MX) {
		if (v[x]) return a[x];
		v[x] = 1;
		return a[x] = 3 * f(max(0, (int)floor(pow(x, 0.8) - 1))) + 2 * f(x >> 1) + x;
	}
	return 3 * f(max(0, (int)floor(pow(x, 0.8) - 1))) + 2 * f(x >> 1) + x;
}
int main() {
	int T, x;
	cin >> T;
	while (T--) {
		cin >> x;
		printf("%lld ", f(x));
	}
	return 0;
}
