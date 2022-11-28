#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<pli> vpli;

inline char _read() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define _read getchar

inline int read() {
	int sum = 0;
	bool f = 1;
	char ch = _read();
	while (!(ch >= '0' && ch <= '9')) {
		if (ch == '-')f = 0;
		ch = _read();
	}
	while (ch >= '0' && ch <= '9')sum = sum * 10 + ch - 48, ch = _read();
	return (f ? sum : -sum);
}

inline ll Read() {
	ll sum = 0;
	bool f = 1;
	char ch = _read();
	while (!(ch >= '0' && ch <= '9')) {
		if (ch == '-')f = 0;
		ch = _read();
	}
	while (ch >= '0' && ch <= '9')sum = sum * 10 + ch - 48, ch = _read();
	return (f ? sum : -sum);
}

#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define FOR(i, a, b) for(int i=a;i<b;++i)
#define FORD(i, a, b) for(int i=a;i<=b;++i)
#define ROF(i, a, b) for(int i=a;i>=b;--i)
#define MP(a, b) make_pair(a,b)

const ll linf = 1000000000000000000ll;
const int inf = 1000000000;
const int mod = 1000000007;

//虽然有些确实用不到，但先写着也不会有问题罢（

const int max_n = 211;

int n;
int c[max_n], col;
int g[max_n][max_n];
int t[max_n][max_n];

void dfs(int x) {
	c[x] = col;
	FOR(i, 0, n)if (c[i] == -1 && g[i][x] && g[x][i])dfs(i);
}

void solve() {
	memset(g, 0, sizeof(g));
	memset(t, 0, sizeof(t));
	memset(c, -1, sizeof(c));
	col = 0;
	n = read();
	FOR(i, 0, n)FOR(j, 0, n)g[i][j] = read();
	FOR(i, 0, n) if (c[i] == -1) {
			dfs(i);
			col++;
		}
	FOR(i, 0, n)FOR(j, 0, n)t[c[i]][c[j]] = g[i][j];
	n = col;

	FOR(i, 0, n) FOR(j, 0, n) if (!t[i][j] && !t[j][i]) {
				vi c;
				FOR(k, 0, n) if (t[i][k] && t[j][k]) {
						c.push_back(k);
					}
				if (c.size() == 0) {
					cout << "N\n";
					return;
				}
				int cnt = 0;
				for (int a:c) {
					bool f = 1;
					for (int b:c)if (b != a && !t[a][b])f = 0;
					if (f == 1)cnt++;
				}
				if (cnt != 1) {
					cout << "N\n";
					return;
				}
			}
	FOR(i, 0, n) FOR(j, 0, n) if (!t[i][j] && !t[j][i]) {
				vi c;
				FOR(k, 0, n) if (t[k][i] && t[k][j]) {
						c.push_back(k);
					}
				if (c.size() == 0) {
					cout << "N\n";
					return;
				}
				int cnt = 0;
				for (int a:c) {
					bool f = 1;
					for (int b:c)if (b != a && !t[b][a])f = 0;
					if (f == 1)cnt++;
				}
				if (cnt != 1) {
					cout << "N\n";
					return;
				}
			}

	cout << "Y\n";
}

int main() {
	fastio;
	int T = read();
	while (T--)solve();
	return 0;
}
