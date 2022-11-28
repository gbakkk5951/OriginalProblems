#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 998244353;
// answer = k * com[(m - 1) + (n + 1) - 1 + 1][n + 1] + c * com[(m - 1) + (n + 1) - 1][n];
ll fastpower(ll base, ll pow) {
	ll ret = 1;
	while (pow) {
		if (pow & 1) ret = ret * base % p;
		if (pow >>= 1) base = base * base % p;
	}
	return ret;
}
int main() {
    int n, m, k, c;
    cin >> n >> m >> k >> c;
    int from = m - 1 +( n + 1) - 1;
    int choose = n;
	ll tmp = 1;
	for (int i = from - choose + 1; i <= from; ++i) tmp = tmp * i % p;
	ll rev = 1;
	for (int i = 2; i <= choose + 1; ++i) rev = rev * i % p;
	rev = fastpower(rev, p - 2);
    cout << (rev * (tmp * (from + 1) % p) % p * k 
			+ rev * (choose + 1) % p * tmp % p * c) % p;
}

