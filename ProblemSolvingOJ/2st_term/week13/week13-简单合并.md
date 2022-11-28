
### 1. 考察知识：
堆可以动态维护最值，最值删除，插入值

由于每个序列都是有序的，故每个序列只需要有1个元素在堆中即可

priority_queue 默认是大根堆，

可以通过指定比较器来改变

也可以将权值取负

pair比较大小，先比first，相同再比second

### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
template <typename type>
void read(type &a) {
	int t, f = 0;
	while (!isdigit(t = getchar())) {
		f |= t == '-';
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a = f ? -a : a;
}
template <typename type>
void write(type a) {
	char out[35];
	int index = 35;
	out[--index] = 0;
	out[--index] = '\n';
	if (a < 0) {
		putchar('-');
		a = -a;
	}
	if (a) {
		do {
			out[--index] = a % 10 + '0';
		} while(a /= 10);
	} else {
		out[--index] = '0';
	}
	do {
		putchar(out[index]);
	} while(out[++index]);
}
int n;
const int maxn = 1e6 + 200;
int arr[maxn];
int end[maxn];
typedef std::pair<int, int> pii;
int head[maxn];

std::priority_queue<pii> h;
void push(int bel) {
	if (head[bel] > end[bel]) return;
	h.push((pii) {-arr[head[bel]], bel});
	++head[bel];
}
int pop() {
	int bel = h.top().second;
	int ret = -h.top().first;
	h.pop();
	push(bel);
	return ret;
}
int main() {
	int m;
	read(n); read(m);
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		read(s);
		head[i] = end[i - 1] + 1;
		end[i] = end[i - 1] + s;
		for (int j = head[i]; j <= end[i]; ++j) {
			read(arr[j]);
		}
		int flag = arr[head[i]] > arr[end[i]];
		if (flag) for (int x = head[i], j = end[i]; x < j; ++x, --j) {
			std::swap(arr[x], arr[j]);
		}
		push(i);
	}
	for (int i = 1; i <= m; ++i) {
		write(pop());
	}
	return 0;
}


```
