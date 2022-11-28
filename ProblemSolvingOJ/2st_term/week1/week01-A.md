
### 1. 考察知识：对增长速度的把握、模拟
9的三次方是729
4 * 729 = 2916  < 9999
故4位数之后ｘ的值已经远超过了ｘ的各位数值三次方之和
由于|K| <= 10000 
故尝试到　20000之后，哪怕＋10000，ｘ的各位数三次方之和也无法达到ｘ了





### 2. 优秀代码
**一**
作者：朱宇博
十分简单暴力的优秀算法

找出 x各位三次方之和 + K == x
转化为
找出  K == x - x各位三次方之和 

直接算出20000以内所有ｘ的， x - x各位三次方之和 的值，存入vector
+10000 是为了将可能的负数映射为非负数



```c++
#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define cubic(x) ((x)*(x)*(x))
 
vector<int> numbers[20001];
 
static inline int cubicsum(int x) {
    int ret = 0;
    while(x) {
        ret += cubic(x%10);
        x /= 10;
    }
    return ret;
}
void init() {
    for(int i = 0; i < 20000; ++i) {
        int delta = i - cubicsum(i);
        if(abs(delta) <= 10000) {
            numbers[delta + 10000].push_back(i);
        }
    }
}
int main() {
    int k;
    init();
    while(scanf("%d", &k) == 1) {
        for(int i : numbers[k + 10000])
            printf("%d\n", i);
        puts("");
    }
    return 0;
}

```

**一**
作者：李昕怡

K  > 0时直接从K开始枚举，减少了枚举数量
并且预先算出来



```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int k, x, cnt, temp;
    int cube[10] = {0, 1, 8, 27, 64, 125, 216, 343, 512, 729};
    cin >> k;
    while (cin.fail() == false)
    {
        x = k > 0 ? k : 0;
        for (int i = 0; i < 5000; i++, x++)
        {
            temp = x, cnt = 0;
            while (temp != 0)
            {
                cnt += cube[temp % 10];
                temp /= 10;
            }
            if (cnt == x - k)
                cout << x << endl;
        }
        cout << endl;
        cin >> k;
    }
    return 0;
}
```
