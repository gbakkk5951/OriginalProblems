#include <bits/stdc++.h>
using namespace std;
int bits[2][128];
int main() {
	scanf("%d", &n);
	int it = 0;
	int op, l, r, x, ans;
	while (n--) {
		scanf("%d", &op);
		switch(op) {
			case 1: 
				scanf("%d", &x);
				x &= 127;
				for (int i = 0; i < 128; ++i, ++x, x&= 127) {
					bits[it ^ 1][i] = bits[it][x];
				}
				it ^= 1;
				break;
			case 2:
				ans = 0;
				for (int i = 0; i < 16; ++i) {
					ans |= bits[it][i] << i;
				}
				printf("%X\n", ans);
				break;
			case 3: 
				scanf("%d%d", &l, &r);
				for (int i = l; i <= r; ++i) {
					bits[it][i] ^= 1;
				}
				break;
		}
	}
	return 0;
}
