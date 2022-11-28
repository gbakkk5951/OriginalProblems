using namespace std;
#include <bits/stdc++.h>
int main() {
	int Tn;
	cin >> Tn;
	char c;
	for (int T = 1; T <= Tn; T++) {
		cin >> c;
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 10; j++) {
				if (i <= j && j <= i + 2 || 10 - i - 1 <= j && j <= 10 - i + 1) {
					cout << c;
				} else {
					cout << ' ';
				}
			}
			cout << endl;
		}
	}
	return 0;
}

