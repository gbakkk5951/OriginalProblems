using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef long double Lf;
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
struct _Main {
	char num[35];
	char a[35], b[35];
	lld val;
	_Main() {
		int n, m, l1, l2;
		read(n); read(m); read(l1); read(l2);
		for (int i = l1; i >= 1; i--) {
			read(a[i]);
			val *= m;
			val += a[i];
		}
		for (int i = l2; i >= 1; i--) {
			read(b[i]);
		}
		if (l2 == 1 && b[1] == 0) {
			printf("0");
			return;
		}
		int ans = 0;;
		lld tmp;
		while (1) {
			num[1]++;
			for (int i = 1; num[i] == n; i++) {
				num[i] = 0;
				++num[i + 1];
			}
			tmp = 0;
			for (int i = l2; i >= 1; i--) {
				tmp *= m; 
				tmp += num[i];//num[i] 不是 b[i]
			}
			ans += tmp > val;
			for (int i = 1; i <= l2; i++) {
				if (b[i] != num[i]) break;
				if (i == l2) goto End;
			}
		}
		End:
		printf("%d", ans);
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
