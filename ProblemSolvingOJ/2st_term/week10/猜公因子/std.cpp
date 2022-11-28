#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
const int tries = 50;
int n, m, limit; 
int a[maxn];
int ans = 1;
void test(int factor) {
	if (factor <= ans || factor > limit) return;
	int count = 0;
	for (int i = 1; ; ++i) {
		if (a[i] % factor == 0) {
			if (++count == m) {
				ans = factor;
				return;
			}
		} else
		if (n - i + count < m) {
			return;
		}
	}
}
int main() {
	srand(time(0));
	cin >> n >> m >> limit;
	if (m == 0) {
		cout << limit;
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		swap(a[i], a[rand() % i + 1]);
	}
	for (int i = 1; i <= tries && i <= (n - m + 1) && ans < limit; ++i) {
		int mx = min((int)sqrt(a[i] + 0.5), limit);
		for (int j = 1; j <= mx; ++j) {//´Ó1¿ªÊ¼ 
			if (a[i] % j == 0)  {
				test(j);
				test(a[i] / j);
			}
		}
	}
	cout << ans;
	return 0;
}
