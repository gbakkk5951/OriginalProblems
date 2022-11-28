using namespace std;
#include <bits/stdc++.h>
int main() {
	int Tn;
	cin >> Tn;
	for (int T = 1; T <= Tn; T++) {
		long long x;
		cin >> x;
		cout << (4 <= x && x <= 14 ? "T" : "F");
	}
	return 0;
}
