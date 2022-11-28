#include <bits/stdc++.h>
using namespace std;
const int maxn = 2.1e6 + 10;
char s[maxn];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		int ans = 0;
		int j;
		for (j = 0; s[j] == '0'; ++j);//删除前导0
		for (; s[j]; ++j) {//数1
			ans += 1 + s[j] - '0';
		}
		printf("%d\n", ans - !!ans);
	}
	return 0;
}
