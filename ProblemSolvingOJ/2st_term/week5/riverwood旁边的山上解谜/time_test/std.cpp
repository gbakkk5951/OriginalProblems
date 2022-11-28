#include <bits/stdc++.h>
using namespace std;
char stk[33];
void output(int x) {
	int d;
	while (x) {
		d = x / 10;
		stk[++stk[0]] = '0' + x - d * 10;
		x = d;
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
