
### 1. 考察知识：
代码分析、归并排序求逆序对
多关键字比较可以用pair，也可以用struct/class 自定义 operator < 
也可以直接写个函数
pair比较大小的时侯先比first，等价则比second

### 2. 优秀代码
**一**
作者：张浩宇
本题的分析思路可以用于时间复杂度的分析。
这种排序算法是我学冒泡排序的时侯误认为的算法，
后来才知道冒泡更暴力，
后来知道我想到的这种算法叫作 gnome-sort 地精排序 或者叫 侏儒排序

交换不相等的相邻两项，会使得逆序对数+1或-1，读者可以自行证明

直观地讲，这个算法的思路就是
有一个地精，它从1开始不断往右走，
在发现逆序的情况下，就把那个元素不断向左移动直到到达正确的位置，再继续向右走
直到从1走到n

我们来分析代码



首先当我们位于位置1时，由于步骤（0）if成立会直接向右弹
故步骤（1）不会发生在位置1，在位置1处的右移是不会贡献步骤（1）的执行次数的

每当发现一个逆序，其向左每移动1次，就会减少1个逆序对，又因为地精向右走回来需要相同的步数

所以为了消灭逆序走的步数为 逆序对数 * 2

步骤（0）if成立　除了一开始直接右移的１次之外，其他都是由于消灭逆序造成的

而除了步骤（0）if成立的移动之外，每次移动都要进入步骤（1）

所以为了消灭逆序执行的（1）的次数 = 逆序对数 * 2 - （步骤（0）if成立的次数 - 1）

步骤（0）if成立的次数即，从1到n依次访问，会更新多少次最小值（1号位置也算1次更新最小值）

此外为了从1走到n，也会经历n-1次右移 （其中第一次是步骤（0）if成立造成的），故贡献为 (n - 1 - 1)

而为了从n结束要到达步骤（2）还需要经历 1 次步骤（1）故贡献为 1

故总的（1）执行次数 = 逆序对数 * 2 - （步骤（0）if成立的次数 - 1） + （n - 1 - 1） + 1
= 逆序对数 * 2 +n - 步骤（0）if成立的次数(即最小值更新的次数)

```c++
#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e5 + 10;
typedef pair<int, int> p;
p arr[MXN], tmp[MXN];
long long rev;
long long mncnt;
int n;
template <typename Type>
void read(Type &a) {
	int t, f = 1;
	while (!isdigit(t = getchar())) {
		f = t == '-' ? -1 : f;
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a *= f;
}
void merge_sort(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	int tn = 0;
	int al = l, bl = mid + 1;
	while (al <= mid && bl <= r) {
		if (arr[al] < arr[bl]) {
			tmp[tn++] = arr[al];
			++al;
			rev += bl - (mid + 1);
		} else {
			tmp[tn++] = arr[bl];
			++bl;
		}
	}
	while (al <= mid) {
		tmp[tn++] = arr[al];
		++al;
		rev += bl - (mid + 1);
	}
	while (bl <= r) {
		tmp[tn++] = arr[bl];
		++bl;
	}
	memcpy(arr + l, tmp, (r - l + 1) * sizeof(p));
}
int main() { //用正、负结合数卡一下直接相加法
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(arr[i].first); read(arr[i].second);
	}
	p mn = arr[1];//第一个
	mncnt = 1;//最小值的更新次数
	for (int i = 2; i <= n; ++i) {
		if (arr[i] < mn) {
			mn = arr[i];
			++mncnt;
		}
	}
	merge_sort(1, n);
	cout << rev * 2 + n - mncnt;
}


```


**二**
作者：陈荣锴
使用了离散化+树状数组（不要求同学们掌握）求逆序对
非常简洁

计算式为 (对数 - 顺序对数) * 2 + 不更新最小值的个数

```C++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5 + 3;
int n, s[N];
long long ans;
struct Data
{
    int x, y, id;
} a[N];
bool Less(Data A, Data B)//比较函数
{
    return A.x == B.x ? A.y < B.y : A.x < B.x;
}
void Add(int x)//令x位置的值+1
{
    for (; x <= n; x += x & -x)
        s[x]++;
}
int Sum(int x)//对1到x求和
{
    int re = 0;
    for (; x; x -= x & -x)
        re += s[x];
    return re;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].x, &a[i].y), a[i].id = i;
    sort(a + 1, a + n + 1, Less);
    for (int i = 1; i <= n; ++i)
    {
        int q = Sum(a[i].id); //在我左边且比我小的数的个数
        ans += (i - 1 - q) * 2 + (q > 0);// (i - 1) - q = 对数 - 顺序对数 = 逆序对数 ;  q > 0 == 1 表示不会更新最小值
        Add(a[i].id);
    }
    printf("%lld", ans);
    return 0;
}
```

