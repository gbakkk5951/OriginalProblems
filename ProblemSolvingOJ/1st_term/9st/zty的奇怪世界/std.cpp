#include <bits/stdc++.h>
using namespace std;
const int MXN = 502;
char getcode[255];
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};
class World {
private:
	int n;
	struct List {
		List *link[4];
		char linked[4];
		int x, y;
	}node[MXN][MXN];

	char todel;
	List *zty_tile;
	bool legal(int x, int y) {
		return min(x, y) >= 1 && max(x, y) <= n;
	}
	void link(int x, int y) {
		for (int i = 0; i < 4; ++i) {
			if (!node[x][y].linked[i]) {
				int xx = x + dx[i], yy = y + dy[i];
//				if (legal(xx, yy)) {
					node[x][y].link[i] = &node[xx][yy];
					node[x][y].linked[i] = 1;
					node[xx][yy].link[i ^ 2] = &node[x][y];
					node[xx][yy].linked[i ^ 2] = 1;
					node[xx][yy].x = yy;
					node[xx][yy].y = xx;
//				}
			}
		}
	}
public:
	void init(int n) {
		this->n = n;
		for (int i = 1; i <= n; i++) {
			node[i][1].linked[1] = node[i][n].linked[3] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			node[n][i].linked[0] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			node[1][i].linked[2] = 1;
		}
		link(1, 1);
		zty_tile = &node[1][1];
		node[1][1].x = node[1][1].y = 1;
	}
	void move(int dir) {
		if (!zty_tile->link[dir]) return;
		if (todel) {
			todel = 0;
			for (int i = 0; i < 4; ++i) {
				if (zty_tile->link[i]) zty_tile->link[i]->link[i ^ 2] = zty_tile->link[i ^ 2];
			}
		}
		zty_tile = zty_tile->link[dir];
		link(zty_tile->y, zty_tile->x);
	}
	void del() {
		todel = 1;
	}
	void print() {
		printf("(%d, %d)\n", zty_tile->x, zty_tile->y);
	}
}the_world;
int main() {
	getcode['W'] = 0;
	getcode['A'] = 1;
	getcode['S'] = 2;
	getcode['D'] = 3;
	int n, Qn;
	scanf("%d", &n);
	the_world.init(n);
	scanf("%d", &Qn);
	char op;
	for (int Q = 1; Q <= Qn; ++Q) {
		while (!isalpha(op = getchar()));
		if (op == 'B') {
			the_world.del();
		} else
		if (op == 'P') {
			the_world.print();
		} else {
			the_world.move(getcode[op]);
		}
	}
	return 0;
}
