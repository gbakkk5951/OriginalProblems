#include <bits/stdc++.h>
using namespace std;
using l = long;
char s[3][105];
l slen[37];
void print(int n, l begin, l len) {
	len = min(len, slen[n] - begin + 1);
	if (n <= 2) {
		for (int i = 1; i <= len; ++i) {
			putchar(s[n][begin + i - 1]);
		}
		return;
	} else 
	if (begin + len <= slen[n - 2]) {
		print(n - 2, begin, len);
	} else
	if (begin > slen[n - 2]) {
		print(n - 1, begin - slen[n - 2], len);
	} else {
		print(n - 2, begin, len);
		print(n - 1, 1, len - (slen[n - 2] - begin + 1));
	}
	
}
int main() {
	int Qn;
	scanf("%s%s%d", s[1] + 1, s[2] + 1, &Qn);
	slen[1] = strlen(s[1] + 1);
	slen[2] = strlen(s[2] + 1);
	for (int i = 3; i <= 35; ++i) {
		slen[i] = slen[i - 1] + slen[i - 2];
	}
	for (int Q = 1; Q <= Qn; ++Q) {
		int n, k;
		scanf("%d%d", &n, &k);
		print(n, k, 10);
		putchar('\n');
	}
	return 0;
}
