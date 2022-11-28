#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 2e7 + 10;
lld A, B, C, MOD;
lld L;
int n, m;
lld get_random() {
	return A = C + (A * B) % MOD;
}
lld a[maxn];
int main() {
	cin >> n >> A >> B >> C >> MOD >> L;
	for (int i = 1; i <= n; ++i) a[i] = get_random();
	/* to do */
	/* complete this function and the whole program */
	sort(a + 1, a + n + 1);
	lld lsum = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		lsum += a[i];
		if (lsum <= L) {
			ans = i;
		}
	}
	cout << ans;
	return 0;
}
