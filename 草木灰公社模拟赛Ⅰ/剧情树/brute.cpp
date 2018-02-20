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
	int val[MAXN];
	int f[MAXN];
	int h[MAXN];
	int s[MAXN][2];
	int head[MAXN];
	int eidx;
	void insert(int fa, int s, int v) {
		val[s] = v;
		f[s] = fa;
		eidx++;
		s[eidx][NXT] = head[fa];
		s[eidx][DST] = s;
		head[fa] = eidx;
	}
	
	
	_Main() {
	int i, j, k;
	int Q, Qn;
	int oper, a, b, c;
	read(Qn);
	for (Q = 1; Q <= Qn; Q++) {
		read(oper); read(a);
		switch (oper) {
			case 1: {
				read(b); read(c);	
				insert(a, b, c);	
			}
			case 2: {
				del(a);
			}
			case 3: {
				ask(a);
			}
		}
	}
	
	
}


	
}plot;

