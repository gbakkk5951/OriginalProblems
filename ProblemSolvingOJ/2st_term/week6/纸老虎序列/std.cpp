#include <bits/stdc++.h>
using namespace std;
const int MXL = 1e7 + 10;
const int MXN = 55;
char s[MXL];//贴着高地址用
int top = MXL - 2;
int start[MXN];//起点
char tmp[20];
int main() {
	cin >> tmp;
	int sl = strlen(tmp);
	for (int i = 0; i < sl; ++i) {
		s[top--] = tmp[sl - i - 1];
	}
	start[0] = top + 1;
	int n, m, id, pos;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> pos;
		int len = MXL - top - 2;
		int dl = (len + 4) / 5;//新增部份长度
		for (int beg = top + 1 + ((pos + dl - 1)) % len, i = 0, obeg = top + 1; i < dl; --beg, ++i) {
			if (beg < obeg) beg = MXL - 2;
			s[top--] = s[beg];
		}
		start[i] = top + 1;
	}
	for (int i = 1; i <= m; ++i) {
		cin >> id;
		puts(s + start[id]);
	}
	return 0;
}
