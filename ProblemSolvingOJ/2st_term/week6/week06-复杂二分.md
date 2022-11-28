
### 1. 考察知识：
先特殊处理负数和0

使用nth_element的思想

随机选择一个元素x，将序列划分为3部份，（1）小于x的，（2）等于x的，（3）大于x的


### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L;
int n, m;
lld get_random() {
	return A = C + (A * B) % MOD;
}
int a[maxn];
int solve(int l, int r) {
	// l is calculated, and minimal
	while (l < r) {
		swap(a[rand() % (r - (l + 1) + 1) + (l + 1)], a[r]);//a[r]位置存储被选中的元素
		int eqn = 1, ln = l + 1;
		lld lsum = 0;
		for (int i = l + 1; i < r; ++i) {
			if (a[i] < a[r]) {
				lsum += a[i];//小于的和
				swap(a[i], a[ln++]);
				//if (L - lsum < 0) break; 卡一下这个错误优化？
			} else
			if (a[i] == a[r]) {
				++eqn;//等于的数量
			}
		}// [l, ln - 1] 是小于选中元素的
		if (L - lsum >= 0) {//部分（1）可以全吃下
			L -= lsum;
			int obeg = ln;//相等区间地左侧
			l = ln - 1;
			for (int i = ln; i <= r; ++i) {
				if (a[i] == a[r]) {
					swap(a[i], a[ln++]);
				}
			}//现在 [obeg, ln - 1] 是相等的元素
			while (obeg < ln && L - a[obeg] >= 0) {//不断吃掉等于的部分
				l = obeg;
				L -= a[obeg];
				++obeg;
			}
			if (obeg < ln) {//无法全部吃下相等的
				r = l;
			}
		} else {//递归进入部分（1）小于被选中元素的部分
			r = ln - 1;
		}
	}
	return r;
}
int main() {
	cin >> n >> A >> B >> C >> MOD >> L;
	int non_positive_count = 0;
	for (int i = 1; i <= n; ++i) {
		a[i] = get_random();
		if (a[i] <= 0) {//单独处理非正数
			L -= a[i];
			++non_positive_count;
			--i;
			--n;
		}
	}
	if (L < 0) cout << 0;
	else cout << non_positive_count + solve(0, n);
	return 0;
}


```
