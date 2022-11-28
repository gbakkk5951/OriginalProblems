
### 1. 考察知识：
阶乘与排列，算法构造



### 2. 优秀代码
**一**
作者：胡祖熠
代码最简洁的，
但原代码在小数据时复杂度可达 $$ 12 ^3 $$
比如
13 993773479
13 2 1 3 5 10 9 4 7 6 12 8 11
可以使得while里的for进入次数达到2502次
不过由于数据组数的限制，以及每次循环的时间很短所以可以通过本题
我进行了优化,虽然复杂度依旧，但常数小了，总体常数变为约1/2，只考虑for的话，变为1/3到1/4

while (k) {
    找到最长的 升序后缀，
    若贡献不超过k - 1的
    将其变为降序（贡献为 长度! - 1）
    否则 什么都不干
    next_permutation 生成一个更长的升序序列，或者报告整个序列为降序，则手动赋值整个序列为升序    
}


```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, k, temp[13];
long long cnt;
int main() {
	cin >> t;
	temp[0] = 0;
	temp[1] = 1;
	for (int i = 2; i <= 12; i++) {
		temp[i] = temp[i - 1] * i;
	}
	while (t--) {
		cin >> n >> k;
		int p[n + 1];
		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
		}
		if (n <= 12) {
			k = k % temp[n];
		}
		while (k) {
			int d = 1;
			int e = min(13, n);
			for (int i = n - 1; i >= n - e + 1; i--) {
				++cnt;
				if (p[i] < p[i + 1] && d < 12 && temp[d + 1] - 1 <= k) {
					d++;
				} else {
					if (k >= temp[d] - 1) k -= temp[d] - 1;
					else break;
					reverse(p + i + 1, p + i + d + 1);
					break;
				}
			}
			if (k > 0) {
				if (!next_permutation(p + 1, p + n + 1)) {
					for (int i = 1; i <= n; i++) {
						p[i] = i;
					}
				}
				--k;
			}
		}
		for (int i = 1; i <= n; i++) {
			printf("%d ", p[i]);
		}
		cout << endl;
	}
	cerr << "cnt is " << cnt << endl;
}


```


**二**
作者：张浩宇
即提示中靠后的那种思路
复杂度单次为 min(n, 12)^2 + n
但由于及实际执行的命令数较多，有很多swap和判断（并且最多需要2轮）
导致在本题的数据要求下并没有明显优势，或许把k的范围开到10^36会能拉开差距
加上读入优化可以271ms

```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e6 + 10;;
int a[MXN];
int n, k;
int fact[15];//阶乘
void move(int n, int &remain) {
	int i;
	for (i = n - 1; i >= 1 && remain; --i) {
		if (a[i] < a[i + 1]) {
			//数出有几个比它大的
			int j = i + 1;
			while (j < n && a[j + 1] > a[i]) ++j;
			//若全逆序后仍然remain >= 0 则直接逆序，否则 + 1，然后往回走
			if (n - i <= 12 && (j - i) * (long long)fact[n - i] <= remain) {
				remain -= (j - i) * fact[n - i];
				for (int k = i; k < j; ++k) {
					swap(a[k], a[k + 1]);
				}
			} else {
				int times = 0;
				--remain;
				if (n - i <= 12) {
					times = remain / fact[n - i];
					remain -= times * fact[n - i];
				}
				int pos = n - ((j - times) - i - 1);
				for (int l = i + 1, r = n; l < r; ++l, --r) {
					swap(a[l], a[r]);
				}
				swap(a[i], a[pos]);
				int k = pos;
				for (; a[k - 1] > a[k] && k > i + 1; --k) swap(a[k], a[k - 1]);
				break;
			}
		}
	}
	if (i && remain) { // "往回走"
		++i;
		i = max(i, n - 12);
		for (; i < n && remain; ++i) {
			if (int times = remain / fact[n - i]) { //times 表示能增加几个 (n - i)!
				remain -= times * fact[n - i];
				int k = i + times;
				swap(a[i], a[k]);
				for (; a[k - 1] > a[k] && k > i + 1; --k) swap(a[k], a[k - 1]);
			}
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		fact[0] = 1;
		for (int i = 1; i <= 12; ++i) {
			fact[i] = fact[i - 1] * i;
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		if (n <= 12) {
			k %= fact[n];
		}
		if (k) move(n, k);
		if (k) {//变成了全逆序
			--k;
			for (int i = 1; i <= n; ++i) {
				a[i] = i;
			}
			if (k) move(n, k);//再来一次
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
	return 0;
}


```

**三**
作者：李鸿毅
运行最敏捷的一份提交
196ms
```C++
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 2e6 + 5 , M = 999999;
int list[N] , Count;
ll factorial[13] = {1};
void read(int& x)
{
    x = 0;
    char a = getchar();
    while(a < '0' || a > '9')
        a = getchar();
    while(a >= '0' && a <= '9')
    {
        x = x * 10 + a - '0';
        a = getchar();
    }
    return;
}
void print(int x)
{
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(int a , int b)
{
    return a > b;
}
void reverse(int l , int r)//将下标从l到r的数组反转
{
    while(r - l >= 1)
    {
        swap(list[l] , list[r]);
        l++;
        r--;
    }
    return;
}
int find_successor(int l , int r , int n)//在下标从1到n的降序数组中找n的直接后继,返回后继的下标
{
    int mid = (l + r) / 2;
    while(r - l > 1)
    {
        if(list[mid] > n)
            l = mid;
        else
            r = mid;
        mid = (l + r) / 2;
    }
    if(list[r] > n)
        return r;
    else
        return l;
}
void work(int n)
{
    if(Count == 0)
        return;
    int len , cur , l , r , min = n , mid , num , flag = 1;
    for(len = 12 ; factorial[len] > Count ; len--);
        cur = n - len;
    l = cur + 1;
    while(l < n)
    {
        r = l + 1;
        num = 0;
        while(r <= n)
        {
            if(list[r] < list[l])
                num++;
            r++;
        }
        Count += num * factorial[n - l];
        l++;
    }
    Count -= factorial[len] - 1;
    sort(list + cur + 1 , list + n + 1 , cmp);
    if(list[cur] < list[cur + 1])
    {
        r = find_successor(cur , n , list[cur]);
        while(r > cur && Count >= factorial[len])
        {
            swap(list[cur] , list[r]);
            Count -= factorial[len];
            r--;
        }
        if(r > cur)
        {
            swap(list[r] , list[cur]);
            reverse(cur + 1 , n);
            Count--;
            flag = 0;
        }
    }
    if(flag == 1)
    {if(Count == 0)
        return;
    for(cur; cur >= 1 && list[cur] < list[cur - 1] ; cur--);
    if(cur == 1)
    {
        reverse(1 , n);
        Count--;
    }
    else
    {
        r = find_successor(cur , n , list[cur - 1]);
        swap(list[cur - 1] , list[r]);
        Count--;
        reverse(cur , n);
    }}
    if(Count == 0)
        return;
    min = n;
    for(len = 12 ; factorial[len] > Count ; len--);
    cur = n - len;
    while(cur != n && Count != 0)
    {
        r = cur + 1;
        while(Count >= factorial[len] && r != cur)
        {
            swap(list[cur] , list[r]);
            r++;
            Count -= factorial[len];
        }
        cur++;
        len--;
    }
    return;
}
int main()
{
    for(int i = 1 ; i <= 12 ; i++)
        factorial[i] = i * factorial[i - 1];
    int T , n , tmp;
    read(T);
    while(T--)
    {
        read(n);
        read(Count);
        for(int i = 1 ; i <= n ; i++)
            read(list[i]);
        if(n <= 12)
            while(Count >= factorial[n])
                Count -= factorial[n];
        work(n);
        for(int i = 1 ; i <= n ; i++)
        {
            print(list[i]);
            putchar(' ');
        }
        printf("\n");
    }
    return 0;
}

```