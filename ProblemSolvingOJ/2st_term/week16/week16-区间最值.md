
### 1. 考察知识：

考虑增量构造法，

假设已经对[L, R]完成了计算

那么计算[L, R+1]仅需要考虑第R+1个元素是应该放入较小的集合，还是较大的集合

那么有4种情况

(1)如果放入较大的集合，且较大集合的size还没有+1,那么需要把较大集合中最小的元素转移到较小的集河。

(2)如果放入较大集合，且较大集合的size+1了，那么就不需要转移

(3)如果放入较小集合，且较大集合size+1了，那么需要将较小集合的最大元素转移到最大集合

(4)如果放入较小集合，且较大集合size不变，那么就不需要转移

为了减少分类讨论，我们可以在每次新加入的元素时，运行以下步骤

（1）把新元素放入较小的集合

（2）若较大集合的size+1则将最小集合的最大元素转移到最大集合

（3）若最小集合的最大元素（如果存在）大于最大元素的最小元素，则交换两个元素

堆（可以用priority_queue），可以用O(log)的时间处理加入元素，删除最值，用O(1)的时间查看最值

大根堆只维护最大值，小根堆只维护最小值

所以我们枚举左端点，对于每个左端点枚举右端点逐步移动。

时间复杂度O(n^2logn)

空间 O(n^2) 即存储答案的复杂度

### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn];
typedef long long lld;
lld ans[maxn][maxn];
int n;
priority_queue<int, vector<int>, greater<int> > bigger;//堆默认是大根堆，其用小于运算判断，你将小于改成大于，那么大根堆就变成了小根堆
priority_queue<int> smaller;//较小的一半元素所在的集合，由于要提取最大值，故为默认的大根堆
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
template <typename src_type, typename dst_type>//懒得写类型，直接让编译器自动识别
void move(src_type &src, dst_type &dst) {//将src中的top元素转移到dst中
	dst.push(src.top());
	src.pop();
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {//枚举左端点
		clear(bigger);//不要忘了
		clear(smaller);
		lld sum = 0;
		for (int j = i; j <= n; ++j) {//枚举右端点
			smaller.push(a[j]);//先认为它是小的
			if (bigger.size() < (j - i + 2) / 2) {//较大的集合size+1了，扩充较大的堆
				sum += smaller.top();
				move(smaller, bigger);
			}
			if (!smaller.empty() && smaller.top() > bigger.top()) {//交换两个堆中的最值，其实就是新加入的元素将bigger集合中最小的顶替掉了
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


```
