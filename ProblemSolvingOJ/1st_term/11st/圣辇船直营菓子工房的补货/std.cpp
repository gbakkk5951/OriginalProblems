#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const lld mod = 998244353;
lld ans;
int x;	
int cnt;
void search(int i, int rem) {
	++cnt;
	if (rem < i || i > x) return;
	search(i + 1, rem);
	ans += rem -= i;
	search(i, rem);
}
int main() {
	cin >> x;
	ans = x;
	search(1, x);
	cout << ans % mod;
	cout << endl << cnt;
	return 0;
}
