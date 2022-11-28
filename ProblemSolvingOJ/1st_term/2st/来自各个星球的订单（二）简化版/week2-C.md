
### 1. 考察知识：min, max, swap或其手动实现（可选）， 几何

思路如下：
```
读入T
while (T--)
{
  读入8个坐标，并按照一定顺序存储
  进行算法1或算法2
  算法1
  找出顶边最高的矩形，判断另一个矩形的顶边是否与相交。
  算法2
  求两个矩形中心在x和y分别的距离，如果均小于等于两者在该方向的边长/2则相交（可以通过将表达式左右*2,消去/2）

}
```


### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，用的是题目给出的思路
用了enum, 常量字符串。初始化的"[Intersect] = ", 其实可以删掉，只是为了增加可读性减少BUG
enum的项目默认为从0开始计数的整数，可以手动赋值，允许一个数值对应多个名字。"Type"可以省略 末尾的";"不能省略
```c++
#include <bits/stdc++.h>
using namespace std;
enum Type {Intersect, NotIntersect};
char const *Output[] = {[Intersect] = "Intersection Found\n", [NotIntersect] = "Intersection Not Found\n"};
int xl[2], xr[2], yl[2], yr[2];
int main() {
	int Tn;
	cin >> Tn;
	for (int T = 1; T <= Tn; T++) {
		for (int I = 0; I < 2; ++I) {//Rectangle ID
			cin >> xl[I] >> yl[I] >> xr[I] >> yr[I];
			if (xl[I] > xr[I]) swap(xl[I], xr[I]);
			if (yl[I] > yr[I]) swap(yl[I], yr[I]);
		}
		int ID = yr[1] > yr[0]; // Highest
		if (yr[ID ^ 1] < yl[ID] || xr[ID ^ 1] < xl[ID] || xr[ID] < xl[ID ^ 1]) {
			cout << Output[NotIntersect];
		} else {
			cout << Output[Intersect];
		}
		
	}
	return 0;
}
```
关于enum
```c++
enum {a, b, c = 0, d = -2, e, f};
```
数值a=0, b=1, c=0, d=-2, e=-1, f=0;

**二**
作者：毛子钰
值得你学习的地方: 算法二（约去了/2）很好利用了几何特征，使得代码很好写
虽然我没学过python，但可以看懂
```python
T = int(input())
while T:
    T -= 1
    pos = ()
    pos = input().split()
    zx  = abs(int(pos[0]) + int(pos[2]) - int(pos[4]) - int(pos[6]))
    x   = abs(int(pos[0]) - int(pos[2])) + abs(int(pos[4]) - int(pos[6]))
    zy  = abs(int(pos[1]) + int(pos[3]) - int(pos[5]) - int(pos[7]))
    y   = abs(int(pos[1]) - int(pos[3])) + abs(int(pos[5]) - int(pos[7]))
    if zx <= x and zy <= y:
        print("Intersection Found")
    else:
        print("Intersection Not Found")

```
**三**
作者：陈星宇
比较难读懂，但比较巧妙，

```c++
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); i++)

const int inf = 1000000000;
int xMax, xMin, yMax, yMin;

void solve() {
	xMax = yMax = inf;
	xMin = yMin = -inf;
	FOR(i, 0, 2) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		xMax = min(xMax, max(a, c));
		xMin = max(xMin, min(a, c));
		yMax = min(yMax, max(b, d));
		yMin = max(yMin, min(b, d));
	}
	cout << "Intersection" << (((xMax >= xMin) && (yMax >= yMin)) ? " " : " Not ") << "Found\n";
}

int main() {
	int T;
	cin >> T;
	while (T--)solve();
	return 0;
}
```

