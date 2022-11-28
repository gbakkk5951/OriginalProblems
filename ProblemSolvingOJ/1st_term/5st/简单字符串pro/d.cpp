#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 10;
int s[MXN];
int len[MXN];
int n;
int main() {
	cin >> n;
	len[n] = -2147483648;
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
	}
	for (int i = n - 1; i >= 0; --i) {
		len[i] = s[i] ? len[i + 1] + 1 : 0;
	}
	for (int i = 0; i < n; ++i) {
		if (len[i] < 0) {
			cout << "overflow" << endl;
		} else {
			cout << len[i] << endl;
		}
	}
	return 0;
}
