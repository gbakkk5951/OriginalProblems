
### 1. 考察知识：读入一行字符串，汉诺塔，以及对编号的确定

思路如下：
```
读入n；//cin和scanf会自动跳过空行和空格来试图匹配
用三个char数组或string读入三个平台的名字
读入n个积木的名字
调用汉诺塔函数（A，B，C，N）

汉诺塔函数（起点，目标，借助，n）
若n==1
    移动起点平台的最上面一个积木到目标平台，并输出
否则
    调用汉诺塔函数（起点，借助，目标，n-1）//从起点平台借助目标平台移到借助平台
    移动起点平台的最上面一个积木到目标平台，并输出
    调用汉诺塔函数（借助，目标，起点，n-1）//从借助平台借助来源平台移目标平台
```


### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，比较简单粗暴，没有利用汉诺塔的数学性质来确定积木的编号
top[i]表示第i个平台的积木数量
woodId[i][j]表示第i个平台从下往上数第j个积木的编号
++a 和 a++ 是有区别的
```c++
#include <bits/stdc++.h>
using namespace std;
string platformName[3], woodName[10];
int woodId[3][10];
int top[3];
int n;
void move(int src, int dst) {
	cout << "Move " << woodName[woodId[src][top[src]]] << " from " << platformName[src] << " to " << platformName[dst] << '.' << endl;
	woodId[dst][++top[dst]] = woodId[src][top[src]--];
}
void hanoi(int src, int dst, int helper, int amount) {
	if (amount > 1) {
		hanoi(src, helper, dst, amount - 1);
	}
	move(src, dst);
	if (amount > 1) {
		hanoi(helper, dst, src, amount - 1);
	}
}
int main() {
	memset(top, -1, sizeof(top));
	cin >> n;
	cin.ignore();
	for (int i = 0; i < 3; ++i) getline(cin, platformName[i]);
	for (int i = 0; i < n; ++i) getline(cin, woodName[i]), woodId[0][++top[0]] = i;
	hanoi(0, 1, 2, n);
	return 0;
}
```


**二**
作者：邓振霄
很好地利用了汉诺塔的规律，直接得出积木的编号，而不需要模拟积木的移动。
```C++
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
int n;
string tow[4], dsk[20];

void print(int cur, int src, int dst) {
  cout << "Move " << dsk[cur] << " from " << tow[src] << " to " << tow[dst]
       << ".\n";
}

void move(int src, int dst, int mid, int cur) {
  if (cur == n)
    print(cur, src, dst);
  else {
    move(src, mid, dst, cur + 1);
    print(cur, src, dst);
    move(mid, dst, src, cur + 1);
  };
}

int main() {
  scanf("%d", &n);
  getchar();
  for (int i = 1; i <= 3; ++i)
    getline(cin, tow[i]);
  for (int i = 1; i <= n; ++i)
    getline(cin, dsk[i]);
  move(1, 2, 3, 1);
  return 0;
}
```
