#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1e6 + 10;
struct element { // 2 * (max - min) > int 卡一下
	int value;
	lld diff;
	bool operator < (const element &b) const {
		if (abs(diff) != abs (b.diff)) {
			return abs(diff) < abs (b.diff);
		}
		return diff > b.diff;
	}
}arr[maxn];
template <typename type>
void read(type &a) {
	int f = 0, t;
	while (!isdigit(t = getchar())) {
		f |= t == '-';
	} 
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10; a += t - '0';
	}
	a = f ? -a : a;
}
int org[maxn];
int main() {
	int n, k;
	lld median;
	lld sum = 0;
	read(n); read(k);
	for (int i = 1; i <= n; ++i) {
		read(org[i]);
	}
	int mid = (n + 1) / 2;
	nth_element(org + 1, org + mid, org + n + 1);
	median = org[mid];
	if (!(n & 1)) {
		nth_element(org + mid + 1, org + mid + 1, org + n + 1);
		median += org[mid + 1];
	} else {
		median <<= 1;
	}
	for (int i = 1; i <= n; ++i) {
		arr[i] = (element) {org[i], org[i] * 2LL - median};
	}
	nth_element(arr + 1, arr + k, arr + n + 1);
	for (int i = 1; i <= k; ++i) {
		sum += arr[i].value;
	}
	printf("%lld", sum);
	return 0;
}
