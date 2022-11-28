using namespace std;
#include <bits/stdc++.h>
string S;
int count(int l, int r, const string &t) {
	string sub = S.substr(l, r - l + 1);
	int ret = 0;
	for (size_t pos = 0; ; ++pos) {
		if ((pos = sub.find(t, pos)) != string::npos) {
			++ret;
		} else {
			break;
		}
	}
	return ret;
}
int m;
int main() {
	ios::sync_with_stdio(false);
	int l, r;
	string t;
	cin >> S;
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> l >> r >> t;
		cout << count(l - 1, r - 1, t) << endl;
	}
	return 0;
}
