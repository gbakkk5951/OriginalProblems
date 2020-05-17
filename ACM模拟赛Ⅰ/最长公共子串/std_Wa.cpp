using namespace std;
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
#include "lcs.h"
int get_lcs(int len, int A[]);


/*
int org[105];
int N;
int calls;
int get_lcs(int len, int A[]) {
	++calls;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < len - 1; j++ ) {
			if (A[j] == org[i] && A[j + 1] == org[i + 1]) {
				return 2;
			}
		}
	}
	return 0;
}
*/


namespace ACM {
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
const int MXN = 105;
struct _Main {
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
	int n;
	int *res;
	int arr[MXN];
	int r[MXN], l[MXN];
	int lh, rh;
	int A[MXN];
	//不区分
	int div(int nd, int nl, int nr) {// already have
		if (nl == nr) {
			return arr[nl];
		} else {
			int mid = nl + nr >> 1;
			int f1 = test(nd, nl, mid);
			if (f1 == 0) {
				f1 = div(nd, mid + 1, nr);
			}
			return f1;
		}
	}
	int test(int nd, int nl, int nr) {// not sure
		if (nr - nl + 1 >= 50) {
			int mid = nr + nl >> 1;
			int f1 = test(nd, nl, mid);
			if (f1 == 0) {
				f1 = test(nd, mid + 1, nr);
			}
			return f1;
		} else {
			int cnt = 0;
			A[cnt++] = nd;
			for (int i = nl; i <= nr; i++) {
				A[cnt++] = arr[i];
				A[cnt++] = nd;
			}
			if (get_lcs(cnt, A) > 1) {
				return div(nd, nl, nr);
			}
		}
		return 0;
	}
	//区分左右的初始化
	void initdiv(int nd, int nl, int nr) {
		if (nr == nl) {
			A[0] = nd;
			A[1] = arr[nl];
			if (get_lcs(2, A) > 1) {
				r[1] = arr[nl];
			} else {
				l[1] = arr[nl];
			}
		} else {
			int mid = nr + nl >> 1;
			inittest(nd, nl, mid);
			if (!l[1] && !r[1]) {
				initdiv(nd, mid + 1, nr);
			} else if (l[1] && r[1]) {
				return;
			} else {
				inittest(nd, mid + 1, nr);
			}
		} 
	}
	void inittest(int nd, int nl, int nr) {
		if (nr - nl + 1 >= 50) {
			int mid = nr + nl >> 1;
			inittest(nd, nl, mid);
			if (!l[1] || !r[1]) {
				inittest(nd, mid + 1, nr);
			}
		} else {
			int cnt = 0;
			A[cnt++] = nd;
			for (int i = nl; i <= nr; i++) {
				A[cnt++] = arr[i];
				A[cnt++] = nd;
			}
			if (get_lcs(cnt, A) > 1) {
				initdiv(nd, nl, nr);
			}
		}
	}
	void erase(int nd) {
		if (nd) for (int i = 1; i <= n; i++) {
			if (arr[i] == nd) {
				swap(arr[i], arr[n--]);
				break;
			}
		}
	}
	void init() {
		erase(1);
		initdiv(1, 1, n);
		r[lh = l[1]] = 1;
		l[rh = r[1]] = 1;
		if (lh) erase(lh);
		if (rh) erase(rh);
	}
	void solve() {
		int tmp;
		if (n == 1) {
			res[0] = 1;
			return;
		}
		for (int i = 1; i <= n; i++) {
			arr[i] = i;
		}
		init();
		while (n) {
			if (n == 1 && (lh == 0 || rh == 0)) {
				if (rh == 0) {
					r[l[lh] = arr[1]] = lh;
					lh = 0;
				} else {
					tmp = rh;
					l[r[rh] = arr[1]] = rh;
					rh = 0;
				}
				erase(arr[1]);
			} else
			if (lh) {
				tmp = lh;
				r[lh = l[lh] = test(lh, 1, n)] = tmp;
				erase(lh);
			} else
			if (rh) {
				tmp = rh;
				l[rh = r[rh] = test(rh, 1, n)] = tmp;
				erase(rh);
			}
		}
		int nd;
		for (nd = 1; l[nd]; nd = l[nd]);
		for (int i = 0 ; nd; nd = r[nd], i++) {
			res[i] = nd;
		}
	}

	void main(int n_, int res_[]) {
		n = n_;
		res = res_;
		solve();
	} 
}a;
}
void find_permutation (int n, int res[]) {
	ACM::a.main(n, res);
}

/*

int output[105];
int main() {
	srand(time(0));
	int n = 100;
	N = n;
	for (int i = 0; i < n; i++) {
		org[i] = i + 1;
	}
	for (int i = 1; i < n; i++) {
		swap(org[i], org[rand() % (i + 1)]);
	}
	find_permutation(n, output);
	for (int i = 0; i < n; i++) {
		if (org[i] != output[i]) printf("%d ", org[i]);
	}
	
	printf("%d\n", calls);
}*/
