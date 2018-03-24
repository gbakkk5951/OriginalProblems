using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
inline lld mul(lld a, lld b, lld mod) {//assert a < mod && b < mod
	lld ret = ((a * b) - (lld)((double)a / mod * b) * mod) % mod;
	return ret < 0 ? ret + mod : ret;
}
lld fastpower(lld base, lld pow, lld mod) {
	lld ret = 1;
	while (pow) {
		if (pow & 1) {
			ret = mul(ret, base, mod);
		}
		if (pow >>= 1) {
			base = mul(base, base, mod);
		}
	}
	return ret;
}
const lld p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
char miller(lld num) {
	lld pow, t;
	for (int i = 0; i < 9 && p[i] < num; i++) {
		pow = num - 1;
		while (1) {
			t = fastpower(p[i], pow, num);
			if (t == 1) {
				if (!(pow & 1)) {
					pow >>= 1;
				} else {
					break;
				}
			} else if (t == num - 1) {
				break;
			} else {
				return 0;
			}
		}
	}
	return 1;
}
struct _Main {
	_Main() {
		int n, g, sum = 0;
		lld k, b, t = k * g + b;
		scanf("%d%d%lld%lld", &n, &g, &k, &b);
		t = k * g + b;
		for (int i = g; i < g + n; i++, t += k) {
			sum += miller(t);
			printf("%d\n", sum);
		}
	}
}passwd;
}
