#include <bits/stdc++.h>
using namespace std;
const int maxn = 405;
char v[maxn * 2][maxn * 2];
char del[maxn * maxn];
int point[maxn * maxn];
int pn;
char s[maxn][maxn];
const int vx = 401, vy = 401;
int nx = 0, ny = 0;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == '1') {
				point[++pn] = (i << 10) | j;
			}
		}
	}
	v[vx + nx][vy + ny] = 1;
	printf("%d\n", pn);
	for (int i = 1; i <= m; ++i) {
		int d;
		scanf("%d", &d);
		nx += dx[d], ny += dy[d];
		if (pn && !v[vx + nx][vy + ny]) {//防止越界
			v[vx + nx][vy + ny] = 1;
			for (int i = 1; i <= pn; ++i) {
				int x = (point[i] >> 10) + nx, y = (point[i] & 1023) + ny;
				del[i] = s[x][y] != '1';
			}
			int l = 0;
			for (int i = 1; i <= pn; ++i) {
				if (!del[i]) {
					point[++l] = point[i];
				}
			}
			pn = l;
		}
		printf("%d\n", pn);//不是在上面的括号里
	}
	return 0;
}
