#include <bits/stdc++.h>
using namespace std;
int main() {
	freopen("data.in", "w", stdout);
	int cho = 1;
	long double ans = 0;
	for (int i = 1; i <= 99; ++i) {
		if (pow((long double)i, 5.0) * (100 - i) > ans) {
			ans = pow((long double)i, 5.0) * (100 - i);
			cho = i;
		}
	}
//	printf("%d\n%Lf\n", cho, ans);
	printf("1\n100 %d\n", (int) (6.1e8 + 601));
	cho = 98;
	for (int i = 1; i <= cho; ++i) {
		printf("%d ", (int) (1e8 + i * 2 + 1));
	}
	for (int i = cho + 1; i <= 99; ++i) {
		printf("%d ", (int) (1.1e8 + i * 2 + 1));
	}
	printf("%d ", (int) (1.1e8 + 400 * 2 + 1));
}
