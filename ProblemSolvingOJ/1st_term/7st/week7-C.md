
### 1. 考察知识：循环队列

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，由于是早期版本，命名和模板中的并不一致

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
struct Queue {
	int arr[maxn], n, qh, qt;
	/*有效范围[0, n]这里的n是指输入的n*/
	void init(int n) {
		qh = 0; qt = 0;
		this->n = n + 1;
	}
	bool empty() {/*重合为空*/
		return qh == qt;
	}
	bool full() {/*错开为满, n == 1即输入的n == 0时，既是空的又是满的，不需要特判*/
		return (qt + 1 == n ? 0 : qt + 1) == qh;/*这里的n是输入的n再加1*/
	}
	void insert(int value) {
		assert(!full());
		arr[qt++] = value;
		qt = qt == n ? 0 : qt;/*这里的n是输入的n再加1*/
	}
	int pop() {
		assert(!empty());
		int v = arr[qh];
		++qh;
		qh = qh == n ? 0 : qh;/*这里的n是输入的n再加1*/
		return v;
	}

}q;
int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	q.init(n);
	while (m--) {
		int op, x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			if (!q.full()) {
				q.insert(x);
			}
		} else {
			if (!q.empty()) {
				cout << q.pop() << endl;
			}
		}
	}
	return 0;
}

```


**二**
作者：胡皓明
以MaxSize为循环节的写法
用cnt记录已用的数量
```C++
#include <bits/stdc++.h>
using namespace std;
namespace MyQueue {
	const int MaxSize = 5e5 + 10; //在第七周作业的C题中，你必须使用该框架，并且不得修改本常量，也不得用任何方式，去明显增加队列的容量
	struct queue {
		int item[MaxSize], //存储元素的数组 
		limit, //容量限制
		head, //队首下标
		tail; //队尾下标
		//本题需要你实现一个循环利用空间的队列
		//你并不需要增加其他数据成员，也不需要在item中写入非队列元素的数据，也不需要全局变量或者什么静态局部变量就能够实现以下几个功能
		//但如果你想不到怎么做，可以增加其他数据成员或全局变量, 但不能明显增加队列容量
		int cnt;
		void init(int limit) {//初始化为一个容量限制为limit的队列
			head = -1;
			tail = 0;
			cnt = 0;
			this->limit = limit;//如果不需要，可以修改乃至删除这句
		}
		bool empty() {//探测是否队列为空
			return cnt == 0;
		}
		bool full() {//探测队列是否为满
			return cnt == limit;
		}
		void insert(int value) {//在队尾插入一个元素
			if(!full())
			{
				head++;
				head %= MaxSize;
				item[head] = value;
				cnt++;
			}
		}
		int pop() {//弹出队首，并将原来的队首的元素作为返回值
			int val = -1;
			if(!empty())
			{
				val = item[tail];
				tail++;
				tail %= MaxSize;
				cnt--;
			}
			return val;
		}

	};
}
int main() {
	int n, m;
	ios::sync_with_stdio(false);
	cin >> n >> m;
	using MyQueue::queue;
	queue q;
	q.init(n);
	while (m--) {
		int op, x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			if (!q.full()) {
				q.insert(x);
			}
		} else {
			if (!q.empty()) {
				cout << q.pop() << endl;
			}
		}
	}
	return 0;
}
```
