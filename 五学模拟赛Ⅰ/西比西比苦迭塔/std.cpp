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
const int MXN = 2e5 + 10;
struct _Main {
	int match[MXN];
	char str[MXN];
	int stk[MXN];
	int top;
	int n;
	int idx;
	int head[MXN];
	int edge[MXN][2];
	int eidx;
	int lh[MXN];
	int le[MXN][2];
	int dep[MXN]; // chain length , fork is 0
	int scnt;
	int depidx;
	int anyhead, ae[MXN][2], aidx;
	void inline add(int a, int b) {
		++eidx;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}

	int lidx = 0;
	char del[MXN];
	void inline ladd(int a) {
		++lidx;
		le[lidx][DST] = a;
		le[lidx][NXT] = lh[dep[a]];
		lh[dep[a]] = lidx;
		depidx = max(dep[a], depidx);
		++aidx;
		ae[aidx][DST] = a;
		ae[aidx][NXT] = anyhead;
		anyhead = aidx;
	}
	void break_tree(int nd) {
		for (int e = head[nd], t; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!head[t]) {
				++scnt;
			} else {
				ladd(t);
			}
		}
	}
	void dfs(int nd) {
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			dfs(edge[e][DST]);
		}
		if (edge[head[nd]][NXT]) {//forked
			dep[nd] = 0;
		} else
		if (head[nd]) {//chain
			dep[nd] = dep[edge[head[nd]][DST]] + 1;
		}
	}
	inline void lpop(int t) {
		del[t] = 1;
		lh[dep[t]] = le[lh[dep[t]]][NXT];
	}
	int anypop(int not_to_be) {
		int t = 0;
		while (anyhead) {
			t = ae[anyhead][DST];
			anyhead = ae[anyhead][NXT];
			if (!del[t] && t != not_to_be ) {
				break;
			} else {
				t = -1;
			}
		}
		return t;
	}
	_Main() {
		while (cin >> n) {
			anyhead = aidx = eidx = idx = lidx = scnt = top = 0;
			depidx = -1;
			cin >> (str + 1);
			for (int i = 1; i <= n; i++) {
				switch (str[i]) {
					case '2': {
						stk[++top] = i; 
						break;
					}
					case '0': {
						if (top) {
							match[match[i] = stk[top--]] = i;
						}
						break;
					}
				}
			}
			top = 0;
			for (int i = 1; i <= n; i++) if (match[i]) {
				if (match[i] > i) {
					++idx;
					add(stk[top], idx);//stk[0] == 0
					stk[++top] = idx;
				} else {
					--top;
				}
		//		printf("match[%d] = %d\n", i, match[i]);
			}
			dfs(0);
			ladd(0);
			int ans = 0, a, b;
			while (depidx >= 0) {
				a = le[lh[depidx]][DST];
				lpop(a);
				b = anypop(a);
				if (b == -1) {
					if (scnt) {
						--scnt;
						ans ++;
					}
					break_tree(a);
				} else {
					lpop(b);
					break_tree(a);
					break_tree(b);
					ans ++;
				}
				while (depidx >= 0 && lh[depidx] == 0) --depidx;
			}
			ans += scnt >> 1;
			printf("%d\n", ans);
			memset(head, 0, (n + 1) * sizeof(int));
			memset(lh, 0, (n + 1) * sizeof(int));
			memset(del, 0, (n + 1) * sizeof(char));
			memset(match, 0, (n + 1) * sizeof(int));
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
