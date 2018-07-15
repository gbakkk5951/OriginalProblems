using namespace std;
#include<fstream>
#include<cstdlib>
#define AC 0
#define WA 1
const double EPS = 1e-2 + 1e-6;
bool equal(double a, double b) {
    return a < b + EPS && a > b - EPS; 
}
const int MXN = 1e5 + 10, MXM = 2e5 + 10;
const int DST = 0, NXT = 1;
char vis[MXN];
char bel;
int head[MXN], edge[MXM << 1][2], eidx;
void add(int a, int b) {
	eidx++;
	edge[eidx][DST] = b;
	edge[eidx][NXT] = head[a];
	head[a] = eidx;
}

void mark(int nd) {
	vis[nd] = 1;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		vis[edge[e][DST]] = 1;
	}
}
int main(int argc, char *args[]) {
    ifstream f_in(args[1]);
	ifstream f_out(args[2]);
	ifstream f_user(args[3]);
    double u_ans, std_ans;
	int i, j, k;
	int a, b;
	int n, m;
	int cnt = -1;
	int stdcnt;
	f_in >> n >> m;
	for (int i = 1; i <= n; i++) {
		f_in >> bel;
	}
	for (int i = 1; i <= m; i++) {
		f_in >> a >> b;
		add(a, b); add(b, a);
	}
	f_out >> stdcnt;
	f_user >> cnt;
	if (cnt != stdcnt) return WA;
	for (int i = 1; i <= cnt; i++) {
		f_user >> a;
		if (1 <= a && a <= n) {
			mark(a);
		} else {
			return WA;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			return WA;
		}
	}
    return AC;  
}  




















