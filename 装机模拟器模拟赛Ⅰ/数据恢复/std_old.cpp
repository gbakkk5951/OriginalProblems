using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
typedef double lf;
const int MXN = 500010, MXLEN = 3000010;
lld MOD[3] = {17LL << 52 | 1, (lld)1e9 + 9};
lld mul(lld a, lld b, lld mod) {
	return (a * b - (lld)((lf)a / mod * b)) % mod;
}
struct _Main {
	int n, k, len;
	char str[MXLEN];
	lld pow[MXLEN][3];
	lld rem[3], fact[3];
	_Main() {
		scanf("%d%d%d", &n, &k, &len);
		scanf("%s", str);
		srand(15657631 ^ (unsigned long long) new char);
		MOD[2] = (((rand() << 30) ^ (rand() << 15) ^ rand()) + 3) | 1;
		for (int I = 0; I < 3; I++) {
			pow[0][I] = 1;
		}
		for (int i = 1; i < k + 5; i++) {
			for (int I = 0; I < 3; I++) {
				pow[i][I] = pow[i - 1][I] * 10LL % MOD[I];
			}
		}
		for (int i = 0; i < k; i++) {
			for (int I = 0; I < 3; I++) {
				rem[I] = (rem[I] + (str[len - i - 1] - '0') * pow[i][I]) % MOD[I];
			}
		}
		for (int I = 0; I < 3; I++) {
			fact[I] = 1;
		}
		for (int i = 2; i <= n; i++) {
			for (int I = 0; I < 3; I++) {
				fact[I] = mul(fact[I], i, MOD[I]);
			}
		}
		for (int I = 0; I < 3; I++) {
			fact[I] += fact[I] < 0 ? MOD[I] : 0;
		}
		lld tmp[3];
		int ans = 0;
		for (int i = 0; i < 100000; i++) {
			memcpy(tmp, rem, sizeof(tmp));
			for (int I = 0; I < 3; I++) {
				tmp[I] += i / 1 % 10 * pow[k][I];
				tmp[I] += i / 10 % 10 * pow[k + 1][I];
				tmp[I] += i / 100 % 10 * pow[k + 2][I];
				tmp[I] += i / 1000 % 10 * pow[k + 3][I];
				tmp[I] += i / 10000 % 10 * pow[k + 4][I];
				tmp[I] %= MOD[I];
			}
			if (memcmp(tmp, fact, sizeof(tmp)) == 0) {
				ans = i;
				break;
			}
		}
		if (ans >= 10000) {
			printf("%d", ans / 10000 % 10);
		}
		if (ans >= 1000) {
			printf("%d", ans / 1000 % 10);
		}
		if (ans >= 100) {
			printf("%d", ans / 100 % 10);
		}
		if (ans >= 10) {
			printf("%d", ans / 10 % 10);
		}
		if (ans >= 1) {
			printf("%d", ans / 1 % 10);
		}
		printf("%s", str + len - k);
	}
	
}revoer;
}
