using namespace std;
#include <bits/stdc++.h>
char s[20];
int main() {
	int Tn;
	cin >> Tn;
	for (int T = 1; T <= Tn; ++T) {
		char out = 'Y';
		cin >> s;
		int l = 0, r = strlen(s) - 1;
		assert(r <= 17);
		while (s[l] == '0' && l <= r) ++l;
		while (l < r) {
			if (s[l] != s[r]) {
				out = 'N';
				break;
			}
			++l; --r;
		}
		cout << out << endl;
	}
	return 0;
}
