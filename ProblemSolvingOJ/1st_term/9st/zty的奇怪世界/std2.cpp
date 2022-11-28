struct Node {
	Node *l, *r, *u, *d;
	int x, y;
}node[maxn][maxn];
int n;
void init() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			Node *nd = &node[i][j];
		}
	}
}
