

### 1. 考察知识：代数转化、对类型范围的把握
long long 的范围在 -2^63 到 2^63-1，x^3可能会爆long long
所以要么利用double精度较低但范围大的特点，
要么进行一些手动代数转化。
思路如下：
```
读入T
while (T--)
{
  读入x
  判断x是否满足条件
  输出
}
```


### 2. 优秀代码
**一**
作者：张浩宇
值得你学习的地方: 
double虽然精度不如long long，但表示的范围很大，可以用来和一些不会遇到精度问题的比较小的数做大小的判断
assert(P == (4 <= x && x <= 14)); 
其实是将所有条件手动计算后，直接得出x在区间[4, 14]时为T；
```c++
#include <bits/stdc++.h>
const double eps = 1e-6;
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		long long x;
		cin >> x;
		bool P = (x > 0) 
				&& (pow((double)x, 3.0) < 3000 - eps && pow((double)x, 2.0) > 10 - eps)
				&& (pow((double)x, 2.0) > 2000 + eps || pow((double)x, 2.0) < 700 - eps);
		assert(P == (4 <= x && x <= 14));
		cout << (P ? "T" : "F") << endl;
	}
	fclose(stdout);
	return 0;
}
```

**二**
作者：龚至诚
值得你学习的地方: 
对每个命题进行了转化
```c++
#include <iostream>
using namespace std;

int main()
{
	long long x, T, i;
	char ans[1000];
	cin >> T;
	for (i = 0; i < T; i++)
	{
		cin >> x;
		if (x > 0 && (x >= 4 && x <= 14) && (x <= 26 || x >= 45))
			ans[i] = 'T';
		else ans[i] = 'F';
	}
	for (i = 0; i < T; i++)
		cout << ans[i] << endl;
	return 0;
}

```
**三**
作者：陈荣锴
值得你学习的地方: 
采取判断为F的情况
前两个if筛掉了会爆long long的情况
```c++
#include <iostream>
using namespace std;
int T;
long long x;
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> x;
        bool ok = 1;
        if (x <= 0)
            ok = 0;
        if (x > 3000)
            ok = 0;
        else
        {
            if (x * x * x >= 3000 || x * x < 10)
                ok = 0;
            if (x * x <= 2000 && x * x >= 700)
                ok = 0;
        }
        puts(ok ? "T" : "F");
    }
    return 0;
}
```