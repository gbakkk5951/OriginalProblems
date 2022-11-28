#include <bits/stdc++.h>
using namespace std;
int t, n, k, temp[13];
int bestk;
long long bestcnt;
int ans[20];
int orgp[20];
int main() {
//	cin >> t;
	t = 100000000;
	temp[0] = 0;
	temp[1] = 1;
	for (int i = 2; i <= 12; i++) {
		temp[i] = temp[i - 1] * i;
	}
	srand(time(0));
	while (t--) {
		if (t % 10000 == 0) {
			printf("Best k = %d, Best cnt = %lld\n", bestk, bestcnt);
			for (int i = 1; i <= n; ++i) {
				printf("%d ", ans[i]);
			}
			printf("\n");
			fflush(stdout);
		}
//		cin >> n >> k;
		n = 13; k = rand() % (int)1e9 + 1;
		int p[n + 1];
		int mid = n / 2 + 1;
		int head = n, tail = 1;
		
		for (int i = 1; i <= n; i++) {
			p[i] = (i & 1) ? head-- : tail++;
		}
		
		for (int i = 2; i <= n; ++i) {
			swap(p[i], p[rand() % i + 1]);
		}
		memcpy(orgp, p, sizeof(p));
		if (n <= 12) {
			k = k % temp[n];
		}
		int orgk = k;
		long long cnt = 0;
		while (k) {
			int d = 1;
			int e = min(13, n);
			for (int i = n - 1; i >= n - e + 1; i--) {
				++cnt;
				if (p[i] < p[i + 1]) {
					d++;
				} else {
					if (k >= temp[d]) k -= temp[d] - 1;
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
		if (cnt > bestcnt) {
			bestcnt = cnt;
			bestk = orgk;
			memcpy(ans, orgp, sizeof(orgp));
		}
	//	for (int i = 1; i <= n; i++) {
	//		printf("%d ", p[i]);
	//	}
	//	cout << endl;
	}
}

