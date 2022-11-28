#include <bits/stdc++.h>
using namespace std;
int t, n, k, temp[13];
int main() {
	cin >> t;
	temp[0] = 0;
	temp[1] = 1;
	for (int i = 2; i <= 12; i++) {
		temp[i] = temp[i - 1] * i;
	}
	while (t--) {
		cin >> n >> k;
		int p[n + 1];
		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
		}
		if (n <= 12) {
			k = k % temp[n];
		}
		while (k) {
			int d = 1;
			int e = min(13, n);
			for (int i = n - 1; i >= n - e + 1; i--) {
				if (p[i] < p[i + 1] && temp[d + 1] - 1 <= k) {
					d++;
				} else {
					if (k >= temp[d] - 1) k -= temp[d] - 1;
					else break;
					reverse(p + i + 1, p + i + d + 1);
					break;
				}
			}
			if (k > 0) {
				if (!next_permutation(p + 1, p + n + 1)) {
					for (int i = 1; i <= n; i++) {
						p[i] = i;
					}
				}
				--k;
			}
		}
		for (int i = 1; i <= n; i++) {
			printf("%d ", p[i]);
		}
		cout << endl;
	}
}
