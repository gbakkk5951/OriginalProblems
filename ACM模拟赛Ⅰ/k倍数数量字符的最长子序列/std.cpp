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
typedef pair<int, int> p;
const int MXN = 1e6 + 10;
struct _Main {
	priority_queue<p, vector<p>, greater<p> > heap; 
	
	int cnt[MXN], needcnt[MXN], arr[MXN];
	int n, m;
	int len;
	_Main() {
		int l = 0, r = 1;
		int mx = 1;
		read(n); read(m);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
			mx = max(mx, arr[i]);
			++cnt[arr[i]];
		}
		for (int i = 1; i <= mx; i++) {
			len += needcnt[i] = cnt[i] / 3 * 3;
		}
		printf("%d\n", len);
		int nd, pos;
		
		while (1) {
			while (r < n && cnt[arr[r]] - 1 >= needcnt[arr[r]]) {
				++r;
				heap.push((p) {arr[r], r});
			}
			while (!heap.empty()) {
				nd = heap.top().first;
				pos = heap.top().second;
				if (pos > l && needcnt[nd] > 0) {
					printf("%d ", nd);
					break;
				}
				heap.pop();
			}
			if (heap.empty()) break;
			heap.pop();
			--needcnt[nd];
			for (int i = l + 1; l <= pos; i++) {
				--cnt[arr[i]];
			}
			l = pos;
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
