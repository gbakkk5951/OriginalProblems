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
struct _Main {
	unsigned pow[34];
	_Main() {
		freopen("chart.out", "w", stdout);
		pow[0] = 1u;
		for (int i = 1; i < 34; i++) {
			pow[i] = pow[i - 1] * 10u;
		}
		unsigned bina, dst = (1LLU << 30);
		int sum = 1;
		
		printf("const int sum[]={1");
		for (unsigned i = 1; i != dst; i++) {
			bina = 0;
			for (unsigned j = 0, tmp = i; tmp; j++, tmp >>= 1) {
				bina += (tmp & 1) * pow[j];
			}
			sum += (bina & i) == i;
			if (i % 160000 == 0) {
				printf(",%d", sum);
			}
		}
		printf("};");
		freopen("CON", "w", stdout);
		printf("till %u sum = %d\n", dst - 1u, sum);
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
