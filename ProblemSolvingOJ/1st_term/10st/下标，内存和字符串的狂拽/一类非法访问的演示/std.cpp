#include <iostream>
#include <cstdio>
using namespace std;
int tmp = 0;
int size[1005];
int n, m, total, op, x, y, v, c, countd, x2, y2, x3, y3, x4, y4, x5, y5, tempx, tempy;
bool flag = true, flagg = true, flaggg = true;
int a[1005][1005];
int main() {
	scanf("%d", &y);
	int i;
	for (i = 0; y > size[i] - 1; ++i) {
		y -= size[i];
		printf("i = %d\n", i);
		fflush(stdout);
	}
	printf("%d", y);
}
