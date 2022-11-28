#include <bits/stdc++.h>
using namespace std;
namespace Archaeology {
const int maxn = 1e3 + 5;
char memory[maxn];
int s[maxn];
int n, m;
bool warning;
bool check(int p, int x) {
	if (p < 0 || p >= s[n]) {
		return false;
	}
	if (s[x] > p || p >= s[x + 1]) {
		warning = true;
	}
	return true;
}
int memset(int x0, int y0, int v, int c) {
	int p = s[x0] + y0;
	for(int i = 0; i < c; ++i) {
		if (!check(p + i, x0)) {
			return 0;
		}
	}
	::memset(memory + p, v, c); // ::表示最外层的命名空间
	return 1;
}
int strcpy(int x0, int y0, int x1, int y1) {
	int p0 = s[x0] + y0, p1 = s[x1] + y1;
	int sl = p0, dl = p1, sr, dr; //dl表示destination left, dr 表示destination right; sl, sr表示source left/right
	for (sr = sl, dr = dl; ; ++sr, ++dr) { //条件为空表示无条件执行
		if (check(sr, x0) && check(dr, x1)) {
			if (memory[sr] == 0) break;
		} else {
			return -1;
		}
	}
	if (dr < sl || sr < dl) {
		::strcpy(memory + dl, memory + sl);//注意顺序
		return 1;
	}
	return 0;
}
int strlen(int x0, int y0) {
	int p = s[x0] + y0, len = 0;
	while (1) {
		if (check(p, x0)) {
			if (memory[p] == 0) {
				break;
			}
			++len;
			++p;
		} else {
			return -1;
		}
	}
	assert(len == ::strlen(&memory[s[x0] + y0]));// 检测是否正确，可以删掉
	return len;
}
ostream& coutw() {//在输出前自动加上w，ostream表示输出流，cout是输出流的一种，返回值是cout
	return cout << (warning ? "w" : "");
}

}
int main() {
	using namespace Archaeology;
	ios::sync_with_stdio(false);
	cin >> n;
	
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		s[i] += s[i - 1];
		assert(s[i] <= 1000);//用来检测数据合法性，可以删掉
	}
	if (s[n] > 1000) while(1);//用来检测数据合法性，可以删掉
	for (int i = 0, t; i < s[n]; ++i) {
		cin >> t; //因为memory是char类型，所以可以用int类型的t作为中介
		memory[i] = t;
	}
	cin >> m;
	for (int i = 1, op, a, b, c, d; i <= m; ++i) {
		warning = false;
		cin >> op;
		switch (op) {
			case 0: {
				cin >> a >> b >> c >> d;
				if (memset(a, b, c, d)) {
					coutw() << "true" << endl; //coutw()的返回值是cout
				} else {
					cout << "overflow" << endl;
				}
				break;
			}
			case 1: {
				cin >> a >> b >> c >> d;
				int ret = strcpy(a, b, c, d);
				if (ret == 1) {
					coutw() << "true" << endl;
				} else
				if (ret == 0) {
					cout << "overwrite" << endl;
				} else { //ret == -1 
					cout << "overflow" << endl;
				}
				break;
			}
			case 2: {
				cin >> a >> b;
				int ret = strlen(a, b);
				if (ret == -1) {
					cout << "overflow" << endl;
				} else {
					coutw() << ret << endl;
				}
				break;
			}
		}
	}
	return 0;
}
