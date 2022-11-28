#include <bits/stdc++.h>
const double eps = 1e-6;
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		long long x;
		cin >> x;
		bool P = (x > 0) 
				&& (pow((double)x, 3.0) < 3000 - eps && pow((double)x, 2.0) > 10 - eps)
				&& (pow((double)x, 2.0) > 2000 + eps || pow((double)x, 2.0) < 700 - eps);
		assert(P == (4 <= x && x <= 14));
		cout << (P ? "T" : "F") << endl;
	}
	fclose(stdout);
	return 0;
}
