
### 1. 考察知识：因数分解、置换、环长、lcm（最小公倍数）


lcm(a, b) % mod 不一定等于 lcm(a % mod, b % mod)
而如果环长分别为 4 3 7 11 13 17 19 23 29 31 37 41 43 .... 会导致lcm非常大，不能用定长的整数存

### 2. 优秀代码
**一**
作者：张浩宇
比较简洁
标记的同时就进行了数据的清空


```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 5;
int mx[MXN];//最大指数
int nxt[MXN];//下一个位置
const long long MOD = 998244353;
int getlen(int nd) {//计算nd所在的环的长度，并将环上点均标记
	int ret = 0;
	while (nxt[nd]) {//nxt == 0 表示已经访问过， 否则表示下一个元素
		int *org = &nxt[nd];
		nd = *org;
		*org = 0;
		++ret;
	}
	return ret;
}
void div(int n) {
	for (int i = 2; i * i <= n; ++i) {//因为被分解的数总和为n，故不需要根号优化，当然可以加上，但只是减少常数
		if (n % i == 0) {//由于我们从2开始从小到大枚举，所以必然是质数先去分解它，读者可以自行证明
			int c = 0;
			do {
				++c;
				n /= i;
			} while (n % i == 0);
			mx[i] = max(mx[i], c);
		}
	}
	mx[n] = max(mx[n], 1);//带根号优化的必须有这句话
}
int main() {
	int n, Tn;
	scanf("%d", &Tn);
	while (Tn--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &nxt[i]);
		}
		for (int i = 1; i <= n; ++i) {
			if (nxt[i]) {//没被统计过
				div(getlen(i));
			}
		}
		long long prod = 1;//product 乘积
		for (int i = 1; i <= n; ++i) {
			while(mx[i]) {
				prod = prod * i % MOD;
				--mx[i]; 
			}
		}
		printf("%lld\n", prod);
	}
	return 0;
}


```
