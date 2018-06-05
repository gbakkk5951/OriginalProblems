using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <cstring>
namespace OI {
const int MXN = 3.6e3;
const int DIV = 3e5;
const unsigned MOD = 160000;
struct _Main {
	char str[40];
	int to_binary(char str[]) {
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			str[i] -= '0';
			if (str[i] > 1) {
				for (int j = i; j < len; j++) {
					str[j] = 1;
				}
				break;
			}
		}//0 1ปฏ
		int ret = 0;
		for (int i = 0; i < len; i++) {
			ret |= str[i] << len - i - 1;
		}
		return ret;
	}
	unsigned pow[34];
	_Main() {
		int Qn;
		unsigned ans, now, tmp, dst;
		read(Qn);
		pow[0] = 1u;
		for (int i = 1; i < 34; i++) {
			pow[i] = pow[i - 1] * 10u;
		}
		unsigned bina;
		for (int Q = 1; Q <= Qn; Q++) {
			scanf("%s", str);
			dst = to_binary(str);
			tmp = dst / MOD;
			now = 0;
			ans = 0;
			for (; now <= dst; now++) {
				bina = 0;
				for (unsigned i = 0; now >> i; i++) {
					bina += (now >> i & 1) * pow[i];
				}
				ans += (bina & now) == now;
			}	
			printf("%d\n", ans);
		}
		
	}
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
	}
}std;
}
