
### 1. 考察知识：位运算

### 2. 优秀代码
**一**
作者：张浩宇
精简版，解释见二
```c++
#include <bits/stdc++.h>
using namespace std;
typedef __uint128_t u;
u a;
u mask[129];
template <typename Type>
void read(Type &a) {
	char t, f = 1;
	while (!isdigit(t = getchar())) {
		if (t == '-') f = -1;
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a *= f;
}
int main() {
	for (int i = 1; i <= 128; ++i) {//有i个1的掩码
		mask[i] = mask[i - 1] << 1 | 1;
	}
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		int op, x;
		read(op);
		if (op == 1) {
			read(x);
        		a = a >> x | (128 - x);
		} else
		if (op == 2) {
			printf("%X\n", (unsigned short) a);
		} else
		if (op == 3) {
			int l, r;
			read(l); read(r);
			a ^= mask[r - l + 1] << l;
		}
	}
	return 0;
}
```
**二**
作者：张浩宇
助教自己写的


```c++
#include <bits/stdc++.h>
using namespace std;
typedef __uint128_t u;
u a;
u mask[129];
u getmask(int bits) {//也可以用这个函数 
	return bits == 128 ? ~(u)0 : ((u)1 << bits) - 1;
}
template <typename Type>
void read(Type &a) {
	char t, f = 1;
	while (!isdigit(t = getchar())) {
		if (t == '-') f = -1;
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a *= f;
}
int main() {
	assert(mask[0] == getmask(0));
	for (int i = 1; i <= 128; ++i) {//有i个1的掩码
		mask[i] = mask[i - 1] << 1 | 1;
		assert(mask[i] == getmask(i)); //两者等价
	}
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		int op;
		read(op);
		if (op == 1) {
			int x;
			read(x);
			/* 以下代码也可以运行，无需对x进行取模，因为128位整数位移的时侯，a << b, 会自动取b的低7位，即 b mod 128（数学意义上）
    	        		a = a >> x | (128 - x);
    			    continue;
			*/
			x = x & mask[7]; /*等价于 x = (x % 128 + 128) % 128*/
			a = a >> x | a << (mask[7] ^ x) << 1; // mask[7] ^ x 相当于 127 - x， 而我们要实现 128 - x，所以再补上一个 << 1
			/*或者
			a = a >> x | (a << (128 - x));
			a = a >> x ^ a << (mask[7] ^ x) << 1;
			a = a >> x ^ a << (127 - x) << 1;
			但不能是
			a = a >> x ^ (a << (128 - x));
			因为x == 0时会挂(此时a << 128 等价于 a << 0)
			
			优先级：先算位移，再异或,或
			*/
		} else
		if (op == 2) {
			printf("%X\n", (int) (a & mask[16]));
			/* 或者
			printf("%X\n", (int) (unsigned short) a); // (int) 可省略
			*/
		} else
		if (op == 3) {
			int l, r;
			read(l); read(r);
			/* 或者
			    a ^= mask[r - l + 1] << l;
			    continue;
			*/
			++r;
			a ^= mask[r] ^ mask[l];
		} else {
			cerr << "Wrong op" << endl;
		}
	}
	return 0;
}



```


**三**
作者：邓振霄
成功实现了加强版，即使用两个整数拼成一个大整数

```C++
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <cstring>
typedef unsigned long long ull;
using namespace std;

ull exp[200];

template <typename Type>
void read(Type &a) {
    char t, f = 1;
    while (!isdigit(t = getchar())) {
        if (t == '-') f = -1;
    }
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
    a *= f;
}


int main()
{
    int N;
    read(N);
    ull high = 0, low = 0,nhigh,nlow;
    exp[0] = 1;
    for (int i = 1; i <= 63; ++i)
        exp[i] = exp[i - 1] << 1;
    int op,x,l,r;
    while (N--) {
        read(op);
        if (op == 1) {
            read(x);
            x = (x % 128 + 128);
            x = x >= 128 ? x - 128 : x;
            if (x == 64)
                nhigh = low, nlow = high;
            else if (x < 64)
                nhigh = (((low & ((exp[x]) - 1)) << (64 - x)) | (high >> x)), nlow = ((low >> x) | ((high & ((exp[x]) - 1)) << (64 - x)));
            else
                x -= 64, nlow = (high >> x) | ((low & ((exp[x]) - 1)) << (64 - x)), nhigh = (low >> x) | ((high & ((exp[x]) - 1)) << (64 - x));
            high = nhigh, low = nlow;
        } else if (op == 2) {
            ull ans = low & (exp[16] - 1);
            printf("%X\n",ans);    
        } else {
            read(l);read(r);
            ++r;
            if (l + 1 <= 64) {
                if (r <= 64) {
                    low ^= exp[r] - exp[l];
                } else {
                    low ^= (exp[64]) - exp[l];
                    r -= 64;
                    high ^= exp[r] - exp[0];
                };
            } else {
                l -= 64, r -= 64;
                high ^= exp[r] - exp[l];
            };
        };
    };
    return 0;
}
```
