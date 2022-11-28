#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e6 + 10;;
int a[MXN];
int n, k;
int fact[15];
//#define DEBUG
void move(int n, int &rem) {
	int i;
	for (i = n - 1; i >= 1 && rem; --i) {
		if (a[i] < a[i + 1]) {
			//数出有几个比它大的
			int j = i + 1;
			while (j < n && a[j + 1] > a[i]) ++j;
			//若全逆序后仍然rem >= 0 则直接逆序，否则 + 1，然后回滚
			if (n - i <= 12 && (j - i) * (long long)fact[n - i] <= rem) {
				rem -= (j - i) * fact[n - i];
				for (int k = i; k < j; ++k) {
					swap(a[k], a[k + 1]);
				}
			} else {
				int times = 0;
				--rem;
				if (n - i <= 12) {
					times = rem / fact[n - i];
					rem -= times * fact[n - i];
				}
				int pos = j - times;
				for (int l = i + 1, r = n; l < r; ++l, --r) {
					swap(a[l], a[r]);
					if (l == pos) {
						pos = r;
					} else
					if (r == pos) {
						pos = l;
					}
				}
				swap(a[i], a[pos]);
				int k = pos;
				for (; k < n && a[k + 1] < a[k]; ++k) swap(a[k], a[k + 1]);
				for (; k > i + 1 && a[k - 1] > a[k]; --k) swap(a[k], a[k - 1]);
	//			swap(a[i], a[j - times]);
	//			sort(a + i + 1, a + n + 1);
				break;
			}
		}
		#ifdef DEBUG
		printf("i = %d, rem = %d a = \n", i, rem);
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
		#endif
	}
		#ifdef DEBUG
		printf("\n");
		printf("[Mid]i = %d, rem = %d a = \n", i, rem);
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
		#endif
	if (i && rem) {
		++i;
		for (; i < n && rem; ++i) {
			int times = 0;
			if (n - i <= 12) {
				times = rem / fact[n - i];
			}
			if (times) {
				rem -= times * fact[n - i];
				swap(a[i], a[i + times]);
				sort(a + i + 1, a + n + 1);
		#ifdef DEBUG
				printf("[2]i = %d, rem = %d, a = \n", i, rem);
				for (int i = 1; i <= n; ++i) {
					printf("%d ", a[i]);
				}
				printf("\n");
		#endif
			}
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		fact[0] = 1;
		for (int i = 1; i <= 12; ++i) {
			fact[i] = fact[i - 1] * i;
		}
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}
		if (n <= 12) {
			k %= fact[n];
		}
		if (k) move(n, k);
		if (k) {
			--k;
			for (int i = 1; i <= n; ++i) {
				a[i] = i;
			}
			if (k) move(n, k);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
	return 0;
}
