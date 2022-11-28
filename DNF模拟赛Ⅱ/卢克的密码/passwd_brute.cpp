using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
char miller(lld num) {
	for (lld i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			return 0;
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
