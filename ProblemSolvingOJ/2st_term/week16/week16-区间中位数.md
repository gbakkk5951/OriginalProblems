
### 1. 考察知识：

堆

和区间最值类似



### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn];
int ans[maxn][maxn];
int n;
priority_queue<int, vector<int>, greater<int> > bigger;//元素数量n/2下取整，这里的n是当前枚举的区间内元素的个数，而非全局的n
priority_queue<int> smaller;//元素数量n/2上取整，这里的n是当前枚举的区间内元素的个数，而非全局的n
void print() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j + i - 1 <= n; ++j) {
			printf("%d\n", ans[i][j]);
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
		for (int j = i; j <= n; ++j) {
			smaller.push(a[j]);
			if (smaller.size() - 2 >= bigger.size() || !bigger.empty() && smaller.top() > bigger.top()) {//卡一下没判empty的
				move(smaller, bigger);
			}
			if (bigger.size() > smaller.size()) {
				move(bigger, smaller);
			}
			if ((j - i) & 1) {//长度为偶数
				ans[j - i + 1][i] = bigger.top() + smaller.top();
			} else {
				ans[j - i + 1][i] = smaller.top() * 2;
			}
		}
	}
	print();
	return 0;
}


```
