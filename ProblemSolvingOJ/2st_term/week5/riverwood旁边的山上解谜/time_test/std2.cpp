#include <bits/stdc++.h>
using namespace std;
char stk[33];
void output(int x) {
	while (x) {
		stk[++stk[0]] = '0' + x % 10;
		x /= 10;
	}
	if (stk[0] == 0) putchar('0');
	while (stk[0]) {
		putchar(stk[stk[0]--]);
	}
}
int main() {
	for (int i = 1; i <= (int)1e7; i++) {
		output(i);
	}
	return 0;
}
