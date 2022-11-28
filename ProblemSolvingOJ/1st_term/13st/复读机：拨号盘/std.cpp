#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e5 + 10;
int number[MXN], d[MXN];
int n;
template <typename Type>
	void read(Type &a) {
		int t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}
void calc() {
	memset(number + 1, 0, n * sizeof(int));
	int ans = 0;
	read(n);
	for (int i = 1; i <= n; ++i) read(d[i]);
    int idx = 0;
	for (int i = 1; i <= n; ++i) if (!number[i]) {
	    int begin = idx + 1;
		int nd = i;
		while (!number[nd]) {
			number[nd] = ++idx; 
			nd = d[nd];
		}
		if (number[nd] >= begin) {
			ans += idx - number[nd] + 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		ans -= d[d[i]] == i;
	}
	printf("%c\n", ans ? 'N' : 'Y');
}
int main() {
	int T;
	read(T);
	while (T--) calc();
	return 0;
}

