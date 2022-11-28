
### 1. 考察知识：卡特兰数/递推

可以直接设计递推
可以使用卡特兰数
可以用组合数求卡特兰数（多种方式）


### 2. 优秀代码
**一**
作者：张浩宇
组合数求卡特兰数

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e9 + 7;
int c[(int)1e4 + 10][(int)5e3 + 10];

int main(){
	int n;
	cin >> n;
	for (int i = 0; i <= n * 2; ++i) {
	    c[i][0] = 1;
	    for (int j = 1; j <= min(i, 5000); ++j) {
	        c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	        c[i][j] -= c[i][j] >= N ? N : 0;
	    }
	}
	cout << ((c[2 * n][n] - c[2 * n][n + 1]) % N + N) % N;
	return 0;
} 

```

**二**
作者：张明轩
求卡特兰数

```c++
#include <iostream>
using namespace std;
const long long mod = 1e9 + 7;
long long h[5005] = {1, 1};
int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= i; ++j){
            h[i] += h[j - 1] * h[i - j];
            h[i] %= mod;
        }
    cout << h[n] % mod;
}

```
**三**
作者：李成蹊
记忆化搜索

```c++
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;
int a[5005][5005];
int f(int save, int money)
{
    if (a[save][money] != 0)
    {
        return a[save][money];
    }
    else if (save == 0)
        return 1;
    else if (money == 0)
    {
        return f(save - 1, 1);
    }
    else
    {
        a[save][money] = f(save, money - 1) + f(save - 1, money + 1);
        a[save][money] = (a[save][money] >= 1000000007) ? a[save][money] % (1000000007) : a[save][money];
        return a[save][money];
    }
}
int main()
{
    int n;
    cin >> n;

    cout << f(n, 0);
}


```


**四**
作者：张浩宇
加速了的组合数求卡特兰数
```c++
using namespace std;
int main() {}
#include <bits/stdc++.h>

namespace OI {
typedef long long lld;
const lld MOD = 1e9 + 7, PHI = 1e9 + 6;
const int MXN = 1e4 + 10;
struct _Main {
    lld fastpow(lld base, lld pow) {
        lld ret = 1;
        while (pow) {
            if (pow & 1) ret = ret * base % MOD;
            if (pow >>= 1) base = base * base % MOD;
        }
        return ret;
    }
    lld com(int n, int m) {
        return f[n] * fastpow(f[m], PHI - 1) % MOD * fastpow(f[n - m], PHI - 1) % MOD;
    }
    int f[MXN];
    _Main() {
        int n;
        scanf("%d", &n);
        f[0] = 1;
        for (lld i = 1; i <= (n << 1); i++) {
            f[i] = f[i - 1] * (lld )i % MOD;
        }
        printf("%lld", (com(2 * n, n) * fastpow(n + 1, PHI - 1)) % MOD);
    }
}std;
}

```
