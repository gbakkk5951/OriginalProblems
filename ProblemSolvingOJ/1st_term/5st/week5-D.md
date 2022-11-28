
### 1. 考察知识：递推数列

思路如下：
我们用一个数列F[i]表示从i开始的字符串长度
遇到0则设置F[i]为0
若非0则F[i] = F[i + 1] + 1
特别地，把最F[n]设置为 -inf, 即一个绝对值很大的负数
定义F[i] < 0 表示 overflow

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，比较简单粗暴
```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 10;
int s[MXN];
int len[MXN];
int n;
int main() {
	cin >> n;
	len[n] = -2147483648;
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
	}
	for (int i = n - 1; i >= 0; --i) {
		len[i] = s[i] ? len[i + 1] + 1 : 0;
	}
	for (int i = 0; i < n; ++i) {
		if (len[i] < 0) {
			cout << "overflow" << endl;
		} else {
			cout << len[i] << endl;
		}
	}
	return 0;
}

```


**二**
作者：胡皓明
跑得非常快，用-1表示overflow，
遇到第一个0会结束连续的-1的区域
```C++
#include <cstdio>
#include <cstring>
int n, str[200100], ans[200100];
int main()
{
	memset(ans, -1, sizeof(ans));
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &str[i]);
	for(int i = n; i >= 1; i--)
	{
		if(str[i] == 0)
		{
			ans[i] = 0;
			continue;
		}
		if(ans[i + 1] == -1)
			continue;
		ans[i] = ans[i + 1] + 1;
	}
	for(int i = 1; i <= n; i++)
	{
		if(ans[i] == -1)
			printf("overflow\n");
		else
			printf("%d\n", ans[i]);
	}
	return 0;
}
```
