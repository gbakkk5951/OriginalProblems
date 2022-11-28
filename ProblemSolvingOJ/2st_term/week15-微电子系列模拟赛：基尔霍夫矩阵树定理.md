
### 1. 考察知识：
根结点必然是先序遍历中的第一个，

而在中序遍历中，其左子树的结点都在其左侧，右子树同理

故其可以递归处理


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
template <typename type>
void read(type &a) {
    int t, f = 0;
    while (!isdigit(t = getchar())) {
        f |= t == '-';
    }
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
    a = f ? -a : a;
}
template <typename type>
void write(type a) {
    char out[35];
    int index = 35;
    out[--index] = 0;
    out[--index] = ' ';
    if (a < 0) {
        putchar('-');
        a = -a;
    }
    if (a) {
        do {
            out[--index] = a % 10 + '0';
        } while(a /= 10);
    } else {
        out[--index] = '0';
    }
    do {
        putchar(out[index]);
    } while(out[++index]);
}
const int maxn = 1e6 + 10;
int position[maxn];//位置
int pre[maxn];//前序
int in[maxn];//中序
int n;
int post[maxn];//后序
void get(int l, int r) {//对应的中序遍历的区间
	static int index = 0;//静态局部变量，相当于一个只有该函数能用的全局变量，表示前序遍历用到哪里了
	if (l > r) return;
	int cho = l;
	int now = pre[++index];
	int p = position[now];
	get(l, p - 1);
	get(p + 1, r);
	write(now);
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(pre[i]);
	}
	for (int i = 1; i <= n; ++i) {
		read(in[i]);
		position[in[i]] = i;
	}
	get(1, n);
	return 0;
}

```
