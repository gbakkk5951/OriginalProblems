#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 5;
int mx[MXN];
int nxt[MXN];
const long long MOD = 998244353;
int getlen(int nd) {
	int ret = 0;
	while (nxt[nd]) {
		int *org = &nxt[nd];
		nd = *org;
		*org = 0;
		++ret;
	}
	return ret;
}
void div(int n) {
//	printf("div %d\n", n);
	for (int i = 2; i < n; ++i) {
		if (n % i == 0) {
			int c = 0;
			do {
				++c;
				n /= i;
			} while (n % i == 0);
			mx[i] = max(mx[i], c);
		}
	}
	mx[n] = max(mx[n], 1);
}
int main() {
	int n, Tn;
	scanf("%d", &Tn);
	while (Tn--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &nxt[i]);
		}
		for (int i = 1; i <= n; ++i) {
			if (nxt[i]) {
				div(getlen(i));
			}
		}
		long long prod = 1;
		for (int i = 1; i <= n; ++i) {
			while(mx[i]) {
				prod = prod * i % MOD;
				--mx[i];
			}
		}
		printf("%lld\n", prod);
	}
	return 0;
}
