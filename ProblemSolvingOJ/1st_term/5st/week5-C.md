
### 1. 考察知识：记忆化递归

思路如下：
我们之前学过，记忆化
我们将这个函数的x代入x=0
得到表达式F(0)=5F(0)+0 
又由于其定义域和值域均为非负整数，所以解得F(0) = 0
又由于F的定义中，自变量x总是下降的，数值比较小的部份会被大量用到
所以我们考虑
一个记忆化的递归算法。
注意，如果你用值是否为0来判断是否算过，需要特判x=0的情况

记忆化的范围不是越大越好，因为内存有限，并且太大其实会拖慢速度

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，比较简单粗暴
v数组表示是否已经计算
a数组表示计算的结果
我没有特判0,是因为在运算过程中，它会把0标记为0,并算出来
F(0)的运算过程比较诡异，但由于其值特殊，能证明其得出的结果正确
如果对递归不是很熟悉的同学，可以想一想为什么F(0)是对的


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int MX = 1e7;
char v[MX + 10];
lld a[MX + 10];
lld f(lld x) {
	if (x < MX) {
		if (v[x]) return a[x];
		v[x] = 1;
		return a[x] = 3 * f(max(0, (int)floor(pow(x, 0.8) - 1))) + 2 * f(x >> 1) + x;
	}
	return 3 * f(max(0, (int)floor(pow(x, 0.8) - 1))) + 2 * f(x >> 1) + x;
}
int main() {
	int T, x;
	cin >> T;
	while (T--) {
		cin >> x;
		printf("%lld ", f(x));
	}
	return 0;
}
```


max函数需要被比较的两个值同一类型，又由于floor返回值为浮点数，需要用(int)来转化
当然，你可以使用(long long), 但因为此处是传递的参数，而不是返回值所以用(int)也没有问题

typedef long long lld; //表示给long long一个新的代号lld，long long 依然可以征程使用。

x >> 1 表示x右移一位，对于非负整数来说，右移相当于 / 2 （下取整）

return a[x] = ...; 
这句话表示将a[x]赋值，然后将a[x]作为返回值
类似的用法有
```c++
    int b;
    float a, c;
    (a = b = c = 1.5) += 10.1;
    //结果是 
    a == 11.1;
    b == 1;
    c == 1.5;
    //运算顺序是
    c = 1.5;
    b = c;
    a = b;
    a += 10.1;
```


**二**
作者：朱宇博
利用memset将f数组初始化为-1,节约了一个是否已经计算的标记数组
注意memset是以8bit为单位赋值的
```C++
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 10000000 + 5;
ll f[N];
ll F(int x)
{
    if (x == 0) return 0;
    if (x < N && f[x] != -1) return f[x];
    if (x < N)
    f[x] = 3 * F(max((int)(pow(x, 0.8) - 1), 0)) + (ll)2 * F(0.5 * x) + x;
    else return 3 * F(max((int)(pow(x, 0.8) - 1), 0)) + (ll)2 * F(0.5 * x) + x;
    return f[x];
}
int main()
{
    memset(f, -1, sizeof(f));
    int T;
    cin >> T;
    while (T--) 
    {
        int n;
        cin >> n;
        cout << F(n) << " ";
    }
    return 0;
}
```
**三**
作者：邓振霄
跑得最快的，只用了257ms
```c++
#include <algorithm>
#include <cmath>
#include <cstdio>
typedef long long ll;
using namespace std;
const int N = 1e6;
ll f[N];

ll calc(ll x) {
  if (x <= N) {
    if (f[x] != -1)
      return f[x];
    ll ans = 3 * calc(max((ll)(pow(x, 0.8) - 1), (ll)0)) +
             2 * calc((ll)(x / 2.0)) + x;
    return f[x] = ans;
  } else
    return 3 * calc(max((ll)(pow(x, 0.8) - 1), (ll)0)) +
           2 * calc((ll)(x / 2.0)) + x;
}

int main() {
  for (int i = 1; i < N; ++i)
    f[i] = -1;
  int T;
  scanf("%d", &T);
  while (T--) {
    ll x;
    scanf("%lld", &x);
    printf("%lld ", calc(x));
  };
  return 0;
}
```