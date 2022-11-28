
### 1. 考察知识：

有前导零。


若输入 等于0，则答案为0

否则

答案 = 删去前导0后的长度 + '1'的个数 - 1

如果我们删去前导0,不会把最后一个"0"删空，则不需要上述分类讨论
直接 = 删去前导0后的长度 + '1'的个数 - 1


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2.1e6 + 10;
char s[maxn];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		int ans = 0;
		int j;
		for (j = 0; s[j] == '0'; ++j);//删除前导0
		for (; s[j]; ++j) {//数1
			ans += 1 + s[j] - '0';
		}
		printf("%d\n", ans - !!ans);
	}
	return 0;
}


```
