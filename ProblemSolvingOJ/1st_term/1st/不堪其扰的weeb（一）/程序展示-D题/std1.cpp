using namespace std;
#include <bits/stdc++.h>
char s[89];
int main() {
	int Tn;
	cin >> Tn;
	char c;
	for (int T = 1; T <= Tn; T++) {
		cin >> c;
		int cnt = 0;
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 10; j++) {
				if (i <= j && j <= i + 2 || 10 - i - 1 <= j && j <= 10 - i + 1) {
					s[cnt++] = c;
				} else {
					s[cnt++] = ' ';
				}
			}
			s[cnt++] = '\n';
		}
		s[cnt++] = '\0';
		cout << s;
	}
	return 0;
}

