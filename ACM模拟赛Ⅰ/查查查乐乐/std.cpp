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
const int MXN = 1e7 + 10;
typedef __int128 L;
struct _Main {
	int a[MXN], l[MXN], r[MXN], stk[MXN];
	L s[MXN], ls[MXN], rs[MXN];
	int n;
	L ans;
	_Main() {
		read(n);
		for (int i = 1; i <= n; i++) {
			read(a[i]);
			s[i] = s[i - 1] + a[i];
			ls[i] = ls[i - 1] + s[i];
		}
		for (int i = n; i >= 1; i--) {
			rs[i] = rs[i + 1] + s[n] - s[i - 1];
		}
		int top = -1;
		a[0] = -INF;
		stk[++top] = 0;
		a[n + 1] = -INF + 1;
		for (int i = 1, top = -1; i <= n + 1; i++) {
			while (a[stk[top]] >= a[i]) {
				r[stk[top--]] = i - 1;
			}
			l[i] = stk[top] + 1;
			stk[++top] = i;
		}
		L tmp;
		for (int i = 1; i <= n; i++) {
			tmp = (i - l[i] + 1) * (r[i] - i + 1) * a[i];
			if (l[i] < i) tmp += (r[i] - i + 1) * (rs[l[i]] - (rs[i] + (s[n] - s[i - 1]) * (i - l[i])));
			if (r[i] > i) tmp += (i - l[i] + 1) * (ls[r[i]] - (ls[i] + s[i] * (r[i] - i)));
			ans += a[i] * tmp;
		}
		print(ans);
	}
	
	void print(L a) {
		static char stk[47];
		int top = -1, f = a < 0;
		if (a == 0) putchar('0'); else
		while (a) {
			stk[++top] = abs(a % 10) + '0';
			a /= 10;
		}
		if (f) putchar('-');
		while (top != -1) {
			putchar(stk[top--]);
		}
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
