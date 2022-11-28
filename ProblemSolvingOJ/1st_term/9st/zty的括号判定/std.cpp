#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
char s[MAXN];
char LeftChar[255], LeftofRight[255];
int main() {
	LeftChar['('] = LeftChar['['] = LeftChar['{'] = 1;
	LeftofRight[')'] = '(';
	LeftofRight[']'] = '[';
	LeftofRight['}'] = '{';
	int Tn;
	scanf("%d", &Tn);
	for (int T = 1; T <= Tn; T++) {
		stack<char> stk;
		scanf("%s", s);
		bool flag = true;
		for (int t = 0; s[t]; ++t) {
			char i = s[t];
			if (LeftChar[i]) {
				stk.push(i);
			} else {
				if (!stk.empty() && stk.top() == LeftofRight[i]) {
					stk.pop();
				} else {
					flag = false;
					break;
				}
			}
		}
		flag = flag && stk.empty();
		cout << (flag ? "Yes" : "No") << endl;
	}
	return 0;
}
