
### 1. 考察知识：递归，对律令的遵巡

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，比较简单粗暴
::max表示从最外层这个没有名字的命名空间中寻找max，由于
这个最外层中有了using namespace std; 
所以std::max也可以写作::max

main的内部，不是最外层的，所以可以用
using namespace my;
优先从my中寻找max

```c++
#include <bits/stdc++.h>
using namespace std;
namespace my {
const int maxn = 102;
int a[maxn];
int max(int n) {//表示取出a[1]到a[n]中的最大值
	if (n == 1) {
		return a[n];
	}
	return ::max(max(n - 1), a[n]);
}
}
int main() {
	using namespace my;
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	cout << max(n);
	return 0;
}

```


**二**
作者：董睿祺
通过将最大值移动到a[n]的方式算出最大值
由于律令并没有要求必须用提示的递归结构，所以这种写法也是对的
/* zhy助教第一次实现循环其实是用递归模拟循环的，用的编程语言是易语言 */

```C++
#include <iostream>
using namespace std;
int n, k = 1, a[101];
void f();
int main ()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    f();
    cout << a[n];
}
void f()
{
    if ( k <= n-1 )
    {
        if (a[k] > a[k+1])
            swap(a[k], a[k+1]);
        k++;
        f();
    }
}
```
