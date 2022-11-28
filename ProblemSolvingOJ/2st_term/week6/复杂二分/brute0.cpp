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
int solve(int l, int r) {
	// l is calculated, and minimal
	while (l < r) {
		swap(a[rand() % (r - (l + 1) + 1) + (l + 1)], a[r]);
		int eqn = 1, ln = l + 1;
		lld lsum = 0;
		for (int i = l + 1; i < r; ++i) {
			if (a[i] < a[r]) {
				lsum += a[i];
				swap(a[i], a[ln++]);
//				if (L - lsum < 0) break;// 卡一下这个错误优化？
			} else
			if (a[i] == a[r]) {
				++eqn;
			}
		}
		if (L - lsum >= 0) {
			L -= lsum;
			int obeg = ln;
			l = ln - 1;
			for (int i = ln; i <= r; ++i) {
				if (a[i] == a[r]) {
					swap(a[i], a[ln++]);
				}
			}
			while (obeg < ln && L - a[obeg] >= 0) {
				l = obeg;
				L -= a[obeg];
				++obeg;
			}
			if (obeg < ln) {
				r = l;
			}
		} else {
			r = ln - 1;
		}
	}
	return r;
}
int main() {
	cin >> n >> A >> B >> C >> MOD >> L;
	int non_positive_count = 0;
	for (int i = 1; i <= n; ++i) {
		a[i] = get_random();
		if (a[i] <= 0) {
			L -= a[i];
			++non_positive_count;
			--i;
			--n;
		}
	}
	if (L < 0) cout << 0;
	else cout << non_positive_count + solve(0, n);
	return 0;
}
