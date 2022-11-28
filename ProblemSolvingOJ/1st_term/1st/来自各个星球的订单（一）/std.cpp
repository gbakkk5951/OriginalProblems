using namespace std;
#include <bits/stdc++.h>
int main() {
    int Tn;
    scanf("%d", &Tn);
    for (int T = 1; T <= Tn; T++) {
        int a, t;
        scanf("%d%d", &a, &t);
        printf("%.1lf\n", fabs((a * (double)t * t) / 2.0));
    }
	return 0;
}
