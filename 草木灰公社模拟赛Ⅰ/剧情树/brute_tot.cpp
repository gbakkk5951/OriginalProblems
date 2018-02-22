using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
const int 
	MAXN = 100010,
	NXT = 1,
	DST = 0
;
struct _Main {
	template <typename Type>
		void read(Type &a) {
			char t;
			while (!isdigit(t = getchar()));
			a = t - '0';
			while ( isdigit(t = getchar())) {
				a *= 10;
				a += t - '0';
			}
		} 
	int s[MAXN][2];
	int head[MAXN];
	int eidx;
	int out[MAXN];
	int f[MAXN];
	int h[MAXN];
	int val[MAXN];
	void add(int f, int _s) {
		eidx++;
		s[eidx][DST] = _s;
		s[eidx][NXT] = head[f];
		head[f] = eidx;
	}
	int getlcp(int a, int b) {
		int ret = 0;
		while (a && b && val[a] == val[b]) {
			ret++;
			a = f[a];
			b = f[b];
		}
		if (val[a] == val[b]) {
			ret++;
		}
		return ret;
	}
	void insert(int _f, int s, int v) {
		add(_f, s);
		out[_f]++;
		f[s] = _f;
		val[s] = v;
		h[s] = h[_f] + 1;
	}
	int ask(int nd) {
		int lcp = 0;
		for (int i = 0; i <= mx; i++) {
			if (out[i] == 0 && i != nd && h[i] != 0) {
				lcp = max(lcp, getlcp(i, nd));
				/*if (lcp == 3) {
					printf("i = %d\n", i);
				}*/
			}
		}
		return h[nd] - lcp;
	}
	void del(int nd) {
		if (nd == 0) {
			return;
		}
//		printf("del %d\n", del);
		int t;
		h[nd] = 0;
		for (int i = head[nd]; i; i = s[i][NXT]) {
			if (f[(t = s[i][DST])] == nd) {
				del(t);
			}
		}
		out[f[nd]]--;
		f[nd] = -1;
	}
	int mx;
	_Main() {
//		freopen("data0.in", "r", stdin);
		int i, j, k;
		int Q, Qn;
		int oper, a, b, c;
		read(Qn);
		insert(0, 0, 0);
		for (Q = 1; Q <= Qn; Q++) {
		
			read(oper); read(a);
			mx = max(mx, a);
			switch (oper) {
				case 1: {
					read(b); read(c);	
					mx = max(mx, b);
					insert(a, b, c);
					break;	
				}
				case 2: {
					del(a);
					break;
				}
				case 3: {
					printf("%d\n", ask(a));
					break;
				}
			}
		}
		
	
}


	
}plot;

