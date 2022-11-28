
### 1. 考察知识：

就按照提示里的性质来优化就行

注意long long


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long lld;
const lld mod = 998244353; 
int ans[maxn];
int main() {
	int Qn, last, index;
	scanf("%d", &Qn);
	ans[last = 1] = 1;
	for (int Q = 1; Q <= Qn; ++Q) {
		scanf("%d", &index);
		while (last < index) {
			++last;
			lld tmp = last;
			for (int st = 2, ed, d; st <= last; st = ed + 1) {
				ed = last / (d = last / st);
				tmp = (tmp + (ed - st + 1LL) * ans[d]) % mod;
			}
			ans[last] = tmp;
		}
		printf("%d\n", index > 0 ? ans[index] : index);
	}
	return 0;
}


```
