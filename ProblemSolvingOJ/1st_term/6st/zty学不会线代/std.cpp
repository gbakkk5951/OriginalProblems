#include <bits/stdc++.h>
using namespace std;
namespace my {
typedef double lf;
typedef long double Lf;
const lf eps = 1e-8;
int a[10][10];
int b[10][10];
int c[10][10];
int d[10][10];
void readitem(int &a, int, int) {
	cin >> a;
	assert(0 <= a && a <= 20);
}
void printitem(int &a, int, int) {
	cout << a << " ";
}
void endline() {
	cout << endl;
}
void empty() {}
void frame(int a[10][10], int n, int m, void (*f)(int &, int, int), void (*endline) () = empty) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			f(a[i][j], i, j);
		}
		endline();
	}
}
void read(int a[10][10], int n, int m) {
	frame(a, n, m, readitem);
}
void print(int a[10][10], int n, int m) {
	frame(a, n, m, printitem, endline);
}
void row(Lf a[10][10], int n1, int n2, int m, void (*f) (Lf &a, Lf &b)) {
	for (int i = 0; i < m; ++i) {
		f(a[n1][i], a[n2][i]);
	}
}
Lf e[10][10];
template <Lf dst[10][10]>
	void copy(int &value, int n, int m) {
		dst[n][m] = value;
	}
Lf ratio;
void add(Lf &src, Lf &dst) {
	dst += src * ratio;
}
void mul(int a[][10], int b[][10], int c[][10], int n, int m, int l) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < l; ++j) {
			int tmp = 0;
			for (int k = 0; k < m; ++k) {
				tmp += a[i][k] * b[k][j];
			}
			c[i][j] = tmp;
		}
	}
}
long long getdet(int a[10][10], int n) {
	int m = n;
	frame(a, n, m, copy<e>);
	int sign = 1;
	for (int i = 0; i < n; ++i) {
		int cho = i;
		while (cho < n && fabs(e[cho][i]) < eps) ++cho;
		if (cho == n) return 0;
		if (cho != i) row(e, cho, i, m, swap<Lf>), sign = -sign;
		for (int j = i + 1; j < n; ++j) {
			if (fabs(e[j][i]) > eps) {
				ratio = -e[j][i] / e[i][i];
				row(e, i, j, m, add);
			}
		}
	}
	Lf ret = sign;
	for (int i = 0; i < n; ++i) ret *= e[i][i];
	
	return (long long) round(ret);
}
}
int main() {
	using namespace my;
	int r, n, m, l;
	cin >> r;
	assert(1 <= r && r <= 10);
	read(a, r, r);
	cout << getdet(a, r) << endl;
	cin >> n >> m >> l;
	assert(1 <= min(min(n, m), l) && max(max(n, m), l) <= 10);
	read(b, n, m);
	read(c, m, l);
	mul(b, c, d, n, m, l);
	print(d, n, l);
	return 0;
}
