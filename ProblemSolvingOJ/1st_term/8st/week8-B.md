
### 1. 考察知识：二叉树

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的

这种二叉树的存储方式叫作堆式存储，有很多可以利用的性质（比如编号直接 / 2 下取整（或者右移1位）就能得到其parent结点）

记得要看数据范围，用long long，
我们用h(x)表示结点x的编号

我们画图可以发现 a < b 则有 h(a) <= h(b)
若每次将h(x)最大的那个点向上移动一步，则必然不会超过他们的LCA最近公共组先(相关信息见题目的提示部份)
而且两者之间的距离会减少，所以不断重复直到两者重合，此时答案便是向上移动步数之和

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
	int Qn;
	long long a, b;
	cin >> Qn;
	for (int Q = 1; Q <= Qn; ++Q) {
		cin >> a >> b;
		int cnt = 0;
		while (a != b) {
			if (a < b) swap(a, b);
			a >>= 1;
			++cnt;
		}
		printf("Case #%d: %d\n", Q, cnt);
	}
	return 0;
}

```


**二**
作者：邓振霄
lga和lgb表示a和b的深度，
将较深的移动到和另外一个相同深度后，
同步向上移动，直到会合

```C++
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

int main()
{
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        ll p = a, q = b;
        int lga = 0, lgb = 0, ans = 0;
        while (p > 1)
            p >>= 1, ++lga;
        while (q > 1)
            q >>= 1, ++lgb;
        if (lga > lgb)
            swap(a, b), swap(lga, lgb);
        ans += lgb - lga;
        while (lgb > lga)
            b >>= 1, --lgb;
        while (a != b)
            a >>= 1, b >>= 1, ans += 2;
        printf("Case #%d: %d\n", i, ans);
    };
    return 0;
}
```
