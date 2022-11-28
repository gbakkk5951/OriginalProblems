#include <bits/stdc++.h>
using namespace std;
string S;
long long A, atmp;
double B, btmp;
string C;
string D;
int main() {
	cin >> S;
	for (int l = 0, r; l < S.length(); l = r + 1) {
		r = l;
		bool dot = false;
		if (isalpha(S[l])) {
			if (isupper(S[l])) {
				C = C + (char) tolower(S[l]);
			} else {
				D = D + (char) toupper(S[l]);
			}
			continue;
		} else {
			while (r < S.length() && !isalpha(S[r])) {
				dot |= S[r] == '.';
				++r;
			}
			--r;
			if (dot) {
				istringstream is(S.substr(l, r - l + 1));
				is >> btmp;
				B += btmp;
			} else {
				istringstream is(S.substr(l, r - l + 1));
				is >> atmp;
				A += atmp;
			}
		}
	}
	cout << A << endl << setiosflags(ios::fixed) << setprecision(2) << B << endl << C << endl << D;
	return 0;
}
