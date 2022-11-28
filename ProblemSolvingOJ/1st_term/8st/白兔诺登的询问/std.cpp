#include <bits/stdc++.h>
using namespace std;
int main() {
	int Qn;
	long long a, b;
	cin >> Qn;
	for (int Q = 1; Q <= Qn; ++Q) {
		cin >> a >> b;
		int cnt = 0;
		while (a != b) {
			if (a < b) swap(a, b);
			a >>= 1;
			++cnt;
		}
		printf("Case #%d: %d\n", Q, cnt);
	}
	return 0;
}
