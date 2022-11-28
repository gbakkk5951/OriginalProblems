#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e6 + 10;;
int a[MXN];
int n, k;
int fact[15];//阶乘
void move(int n, int &remain) {
	int i;
	for (i = n - 1; i >= 1 && remain; --i) {
		if (a[i] < a[i + 1]) {
			//数出有几个比它大的
			int j = i + 1;
			while (j < n && a[j + 1] > a[i]) ++j;
			//若全逆序后仍然remain >= 0 则直接逆序，否则 + 1，然后往回走
			if (n - i <= 12 && (j - i) * (long long)fact[n - i] <= remain) {
				remain -= (j - i) * fact[n - i];
				for (int k = i; k < j; ++k) {
					swap(a[k], a[k + 1]);
				}
			} else {
				int times = 0;
				--remain;
				if (n - i <= 12) {
					times = remain / fact[n - i];
					remain -= times * fact[n - i];
				}
				int pos = n - ((j - times) - i - 1);
				for (int l = i + 1, r = n; l < r; ++l, --r) {
					swap(a[l], a[r]);
				}
				swap(a[i], a[pos]);
				int k = pos;
				for (; a[k - 1] > a[k] && k > i + 1; --k) swap(a[k], a[k - 1]);
				break;
			}
		}
	
	}
	if (i && remain) { // "往回走"，尝试
		++i;
		i = max(i, n - 12);
		for (; i < n && remain; ++i) {
			if (int times = remain / fact[n - i]) { //times 表示能增加几个 (n - i)!
				remain -= times * fact[n - i];
				int k = i + times;
				swap(a[i], a[k]);
				for (; a[k - 1] > a[k] && k > i + 1; --k) swap(a[k], a[k - 1]);
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
			scanf("%d", &a[i]);
		}
		if (n <= 12) {
			k %= fact[n];
		}
		if (k) move(n, k);
		if (k) {//变成了全逆序
			--k;
			for (int i = 1; i <= n; ++i) {
				a[i] = i;
			}
			if (k) move(n, k);//再来一次
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
	return 0;
}
