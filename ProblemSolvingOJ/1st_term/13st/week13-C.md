
### 1. 考察知识：关系、格
题面可以直观理解为定义了一个没有反对称性的格（若上（下）确界的元素有多个但等价则也算作唯一）
或者以一个例子理解
：x，y，z是三个符号，可以有f(x)=a, f(y)=a, f(z)=a
但此时若关系(x,y)存在于R', 即(a,a)存在于R''，则要求(y,x), (x,z), (y,z), (z,x), (z,y)也都存在于R'
由于问的是 存在S存在f，故S和f可以随便你构造，只要满足那些条件即可

（一）自反性
枚举（a,a）是否存在
（二）传递性
枚举i,j,k若(i,j), (j,k) 则要求(i,k)

（三）等价符号关系一致
当且仅当(a,b)且(b,a)时我们令f(a)=f(b)，此时传递性已经帮助我们判断了，故无需写代码

（四）上（下）确界存在且唯一
以上界为例
枚举每一对元素 i，j
 令sup为一个变量，初始为-1
 然后枚举k，若k为i j的上界 {若sup为-1或者(k, sup)属于R则令sup=k}
 k枚举结束之后
 若sup==-1则非法，否则继续
 再枚举一遍k
 若存在k， k是ij的上界 且 (sup, k)不属于R //经过前三步之后我们已经可以运用自反性、传递性和等价符号的关系一致性了
 则不合法（此时k和sup均为ij的上界，且k和sup不等价且k（以及其他小于k的ij的上界）和sup之间没有最小值）
 故sup和 k（或某个小于k的ij的上界）均为ij的上确界（且两者不等价）
 不满足唯一性

经过以上判定，若均满足，则存在合法方案，否则不存在


另外，也可以

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的

```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 52;
int r[MXN][MXN];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		int flag = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &r[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (!r[i][i]) {//反身性
				flag = 1;
				goto End;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (r[i][j]) {
					for (int k = 1; k <= n; ++k) {
						if (r[j][k] && ! r[i][k]) {//传递性
							flag = 1;
							goto End;
						}
					}
				}
				int sup = -1, inf = -1;
				for (int k = 1; k <= n; ++k) {//最紧的上下界
					if (r[k][i] && r[k][j]) {
						if (inf == -1 || r[inf][k]) {
							inf = k;
						} 
					}
					if (r[i][k] && r[j][k]) {
						if (sup == -1 || r[k][sup]) {
							sup = k;
						}
					}
				}
				if (min(sup, inf) == -1) {//不存在上/下界
					flag = 1;
					goto End;
				}
				for (int k = 1; k <= n; ++k) {//唯一性
					if (r[k][i] && r[k][j]) {
						if (!r[k][inf]) {
							flag = 1;
							goto End;
						}
					}
					if (r[i][k] && r[j][k]) {
						if (!r[sup][k]) {
							flag = 1;
							goto End;
						}
					}
				}
			}
		}
		End://跳转标记；不必要，可以用一个变量+判断来跳出
		puts(flag ? "N" : "Y"); //puts自动换行
	}
	return 0;
}


```

**二**
作者：赵烜呈
巧妙运用了对偶的性质
```c++
#include <cstdio>
#include <cstring>
int n, rel[2][55][55];
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
bool jdg()
{
	int i, j, k;
	for(i=1; i<=n; i++)
		if(rel[0][i][i] == 0)
			return false;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			for(k=1; k<=n; k++)
				if(rel[0][i][j] && rel[0][j][k] && !rel[0][i][k])
					return false;
	return true;
}
bool jdg2(int op)
{
	int i, j, k;
	int lbound;
	for(i=1; i<=n; i++)
		for(j=i+1; j<=n; j++)
		{
			lbound = -1;
			for(k=1; k<=n; k++)
				if(rel[op][i][k] && rel[op][j][k])
				{
					if(lbound == -1 || rel[0][lbound][k]) //按照下确界的定义暴力求解 
						lbound = k;
				}
			if(lbound == -1) return false;
			for(k=1; k<=n; k++)
				if(rel[op][i][k] && rel[op][j][k] && !rel[op][lbound][k] && !rel[op][k][lbound])
					return false;
		}
	return true;
}
int main()
{
	int T, i, j, k;
	T = read();
	while(T--)
	{
		memset(rel, 0, sizeof(rel));
		n = read();
		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++)
				rel[0][i][j] = read();
		if(!jdg())
		{
			printf("N\n");
			continue;
		}
		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++)
				if(rel[0][i][j] == 1)
					rel[1][j][i] = 1;//上确界转化为对偶关系的下确界 
		if(jdg2(0) && jdg2(1))
			printf("Y\n");
			else printf("N\n");
	}
	return 0;
}
```


**三**
作者：（姜凯发现的解法），张浩宇

上确界存在且唯一时，
若存在最小值，则合法

或者下确界存在且唯一时，若存在最大值，则合法

读者可以自行证明（此时若下确界不唯一则上确界也不唯一）

```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 52;
int r[MXN][MXN];
int n;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int flag = 0;
		int min_exist = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &r[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
		    if (!r[i][i]) {//反身性
				flag = 1;
				goto End;
			}
            int cnt = 0;
			for (int j = 1; j <= n; ++j) {
				if (r[i][j]) {
			        ++cnt;
					for (int k = 1; k <= n; ++k) {
						if (r[j][k] && ! r[i][k]) {//传递性
							flag = 1;
							goto End;
						}
					}
				}
               	int sup = -1;
                	for (int k = 1; k <= n; ++k) {
                		if (r[i][k] && r[j][k]) {
                			if (sup == -1 || r[k][sup]) {
                				sup = k;
                			}
                		}
                	}
                	if (sup == -1) {//不存在上界
        				flag = 1;
        				goto End;
                	}
                	for (int k = 1; k <= n; ++k) {//唯一性
                		if (r[i][k] && r[j][k]) {
                			if (!r[sup][k]) {
                				flag = 1;
                				goto End;
                			}
                		}
                	}
			}
			if (cnt == n) min_exist = 1;//存在最小值
		}
		End://跳转标记；不必要，可以用一个变量+判断来跳出
		puts(flag || !min_exist ? "N" : "Y"); //puts自动换行
	}
	return 0;
}
```