
### 1. 考察知识：
本题是根据书面作业题目改编

设计贪心策略即可

按照提示里的来做就行

由题目可知，如果一个元素不会被pop，那么就不需要被push，直接删掉

策略：

删去无效的push之后

尽可能使多的元素被直接放在底部这样它的代价为2

并设法令其余代价为4

对于一个push，如果有空位置，则放到空位置上（总代价为2）

如果没有，则放到其前一个元素的上方（总代价为4）

对于一个pop如果其位于栈底则将其上方的元素（如果有）pop到另一个栈

（优先非空）

然后弹出该元素

对于已经被移动过的元素，其弹出时必然位于栈顶



### 2. 优秀代码
**一**
作者：张浩宇

首先，计算出有多少元素需要压栈，不会被出队的元素直接丢弃
对于一次压栈，若有空位，直接占领
   若没有，压到其前一个元素上（必然存在且位于一个逆序栈的栈顶）

对于一次弹栈
if(上方有元素){则将其上方的元素移动到另一个栈}
  优先弹到非空的栈，没有再弹到空栈
}
将其弹出
若位于栈底部，则空栈数量+1

```c++
#include <bits/stdc++.h>
const int maxn = 4e6 + 10;
int n;
int m;
int empty;
int ans;
char s[maxn], bottom[maxn];//bottom[i]表示i号元素是否在底部，无论是直接在底部还是被移动到底部
int main() {
	scanf("%d%d%s", &n, &m, s);
	empty = n;
	int valid_number = 0;
	int in_stack = 0;
	for (int i = 0; i < m; ++i) {//删去无效的push
		if (s[i] == '0') {
			++in_stack;
		} else {
			if (in_stack) {
				--in_stack;
				++valid_number;
			}
		}
	}
	int pushed = 0, poped = 0;
	for (int i = 0; i < m; ++i) {
		if (s[i] == '0') {//加入
			if (pushed < valid_number) {
				if (empty) {//有空位
					--empty;
					bottom[++pushed] = 1;
					ans += 2;
				} else {//放到其前一个元素的头顶上
					bottom[++pushed] = 0;
					ans += 4;
				}
			}
		} else {
			if (poped < pushed) {
				empty += bottom[++poped];//新弹出的元素是否在底部
			}
		}
		if (poped < pushed) {
			if (empty == n) {//没办法把刚pop过的元素头顶上的元素放到非空的栈上
				empty = n - 1;
				bottom[pushed] = 1;//两项都要有
			}
		}
	}
	std::cout << ans;
	return 0;
}


```
