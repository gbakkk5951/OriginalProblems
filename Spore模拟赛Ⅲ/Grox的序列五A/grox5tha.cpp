using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 3010;
struct _Main {
	
lld fastpower(lld base, lld pow, lld mod = 1e18) {
	lld ret = 1;
	while (pow) {
		ret = (pow & 1) ? ret * base % mod : ret;
		base = (pow >>= 1) ? base * base % mod : base;
	}
	return ret;
}

char ns[1010];
char add;
lld pn, mn;

lld phi;
lld k, p;
lld fact[10], fpow[10];
int fcnt;

lld xishu[MXN][MXN];

lld calc() {
	lld ret = 0;
	xishu[1][1] = 1;
	for (int i = 2; i <= k; i++) {
		for (int j = 1; j <= i; j++) {
			xishu[i][j] = (j * xishu[i - 1][j] + xishu[i - 1][j - 1]) % p;
		}
	}
	/*
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			printf("%-6lld ", xishu[i][j]);
		}
		printf("\n");
	}*/
	lld mul = 1, pow;
	for (int i = 1; i <= k; i++) {
		mul = mul * (mn - i + 1) % p;
		pow = (((pn - i) % phi ) + phi ) % phi + (add * phi);
		ret = (ret + fastpower(2, pow, p) * mul % p * xishu[k][i]) % p;
	}
	return ret;
}
void getphi() {
	int rem = p;
	phi = p;
	memset(fpow, 0, sizeof(fpow));
	for (int i = 2; i * i <= rem; i++) {
		if (rem % i == 0) {
			fact[fcnt] = i;
			phi -= phi / i;
			do {
				fpow[fcnt]++;
				rem /= i;
			} while (rem % i == 0);
			fcnt++;
		}
	}
	if (rem > 1) {
		fact[fcnt] = rem;
		fpow[fcnt] = 1;
		fcnt++;
		phi -= phi / rem;
	}
}
	_Main() {
		scanf("%s%lld%lld", ns, &k, &p);
		getphi();
		for (int i = 0; ns[i]; i++) {
			mn = (mn * 10 + ns[i] - '0') % p;
			pn = pn * 10 + ns[i] - '0';
			if (pn >= phi) {
				add = 1;
				pn %= phi;
			}
		}
		if (k == 0) {
			printf("%lld", ((fastpower(2, pn) - 1) % p + p) % p);
			return;
		}
		lld ans = calc();
		printf("%lld", ans);
	}
}grox5th;
}
