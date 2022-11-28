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
#include <cassert>
namespace OI {
inline int lb(int a) {
	return a & (-a);
}
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
typedef complex<lf> com;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MX = 1e7;
const int MXN = MX + 10;
typedef pair<int, int> p;
struct _Main {
	p a[MXN];
	_Main() {
		freopen("a.in", "w", stdout);
		for (int i = 1; i <= MX; i++) {
			printf("%d ", rand());
		}
		fclose(stdout);;
		lf ta = clock();
		cerr << "Writing finished" << endl;
		freopen("a.in", "r", stdin);
		for (int i = 1; i <= MX; i++) {
			a[i].second = i;
			read(a[i].first);
		}
		lf tb = clock();
		sort (a + 1, a + MX + 1);
		cerr << ((tb - ta) / CLOCKS_PER_SEC);
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
