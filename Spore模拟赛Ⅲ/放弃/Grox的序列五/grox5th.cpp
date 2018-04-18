using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const int MXN = 100010;
struct _Main {
lld fastpower(lld base, lld pow, lld mod = 1e18) {
	lld ret = 1;
	while (pow) {
		ret = (pow & 1) ? ret * base % mod : ret;
		base = (pow >>= 1) ? base * base % mod : base;
	}
	return ret;
}

lld exgcd(lld a, lld b, lld &x, lld &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	lld g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

char ns[1010];
char add;
lld pn, mn;

lld phi;
lld k, p;
lld fact[10], fpow[10];
int fcnt;
lld f[MXN], fr[MXN], cnt[MXN];
lld getcom(lld n, lld m, lld p, lld mod) {
	return f[n] * fr[m] % mod * fr[n - m] % mod
		 * fastpower(p, cnt[n] - cnt[m] - cnt[n - m]) % mod;
}
lld calc(lld p, lld mod) {
	lld ret = 0;
	f[0] = fr[0] = 1;
	for (int i = 1; i <= k; i++) {
		lld t = i;
		cnt[i] = cnt[i - 1];
		while (t % p == 0) {
			cnt[i]++;
			t /= p;
		}
		lld x, y;
		f[i] = f[i - 1] * t % mod;
		exgcd(t, mod, x, y);
		fr[i] = fr[i - 1] * x % mod;
	}
	lld mul = 1, pow;
	for (int i = 1; i <= k; i++) {
		
		mul = mul * (mn - i + 1) % mod;
		pow = (((pn - i) % phi ) + phi ) % phi + (add * phi);
		printf("ans += %lld * 2^(%lld) * com(%d, %d) = %lld\n", mul, pow, k - 1, i - 1, fastpower(2,  pow, mod) * mul % mod
			* getcom(k - 1, i - 1, p, mod) % mod);
		ret = (ret + fastpower(2,  pow, mod) * mul % mod
			* getcom(k - 1, i - 1, p, mod)
		) % mod;
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
lld r[10], m[10];
void merge(int, int i) {
	lld delta = r[i] - r[0];
	lld x, y;
	lld g = exgcd(m[0], m[i], x, y);
	r[0] = x * delta / g % (m[i] / g) * m[0] + r[0];
	m[0] = m[i] / g * m[0];
	r[0] %= m[0];
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
			printf("%lld", (fastpower(2, pn) - 1));
			return;
		}
		for (int i = 0; i < fcnt; i++) {
			m[i] = fastpower(fact[i], fpow[i]);
			r[i] = calc(fact[i], m[i]);
		}
		for (int i = 1; i < fcnt; i++) {
			merge(0, i);
		}
		r[0] += r[0] < 0 ? m[0] : 0;
		printf("%lld", r[0]);
	}
}grox5th;
}
