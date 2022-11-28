#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn];
typedef long long lld;
lld ans[maxn][maxn];
int n;
priority_queue<int, vector<int>, greater<int> > bigger;
priority_queue<int> smaller;
void print() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j + i - 1 <= n; ++j) {
			printf("%lld\n", ans[i][j]);
		}
	}
}
template <typename type>
void clear(type &a) {
	while (!a.empty()) a.pop();
}
template <typename src_type, typename dst_type>
void move(src_type &src, dst_type &dst) {
	dst.push(src.top());
	src.pop();
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		clear(bigger);
		clear(smaller);
		lld sum = 0;
		for (int j = i; j <= n; ++j) {
			smaller.push(a[j]);
			if (bigger.size() < (j - i + 2) / 2) {
				sum += smaller.top();
				move(smaller, bigger);
			}
			if (!smaller.empty() && smaller.top() > bigger.top()) {
				sum += -bigger.top() + smaller.top();
				move(smaller, bigger);
				move(bigger, smaller);
			}
			ans[j - i + 1][i] = sum;
		}
	}
	print();
	return 0;
}
