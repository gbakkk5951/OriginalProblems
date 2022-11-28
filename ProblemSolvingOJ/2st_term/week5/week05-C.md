
### 1. 考察知识： 贪心策略、类似放缩的优化？




### 2. 优秀代码
**一**
作者：张浩宇

若 l < r :
则有  a_l + a_r < k  当且仅当 a_l + l右侧的最小值 < k
则有  a_l + a_r >= k  当且仅当 a_l + l右侧的最大值 >= k
首先比较位数
同位数，从高位（左）到低位（右）尽可能大/小

```c++
#include <bits/stdc++.h>
using namespace std;
template <typename Type>
void read(Type &a) {//读入优化，可以不看
	int t;
	while (!isdigit(t = getchar()));
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10; a += t - '0';
	}
}
char stk[33];
void write(int a) {//输出优化，可以不看
	int d;
	while (a) {
		d = a / 10;
		stk[++stk[0]] = '0' + a - d * 10;
		a = d;
	}
	if (!stk[0]) {
		putchar('0');
	} else {
		do {
			putchar(stk[stk[0]--]);
		} while (stk[0]);
	}
}
int num[(int)1e6 + 10];
int n;
int scale;
void output(int begin) {
	while (!num[begin]) ++begin;
	for (int i = begin; i <= n; ++i) {
		write(num[i]);
		putchar(' ');
	}
}
void getmax() {
	int apos, bpos, avalue, bvalue;
	//判断是否存在进位 a + b >= scale;
	int flag = 0;
	int mx = num[n];//不是0, 可以造数据卡
	for (int i = n - 1; i >= 1; --i) {//找到能进位的最靠右的左侧元素的位置
		if (num[i] + mx >= scale) {
			apos = i;
			avalue = num[apos];
			flag = 1;
			break;
		}
		mx = max(mx, num[i]);
	}
	if (flag == 1) {//存在进位
		for (int j = n; 1; --j) {//找到对应的最靠右的右元素的位置
			if (num[j] + avalue >= scale) {
				bpos = j;
				bvalue = num[j];
				break;
			}
		}
		//尝试(1) + (k - 1), 这样左侧的元素1不会减少，右侧会减少
		int first1, lastk_1;
		for (first1 = 1; first1 <= n; first1++) {//最靠左的1
			if (num[first1] == 1) {
				break;
			}
		}
		for (lastk_1 = n; lastk_1; --lastk_1) {//最靠右的k-1
			if (num[lastk_1] == scale - 1) {
				break;
			}
		}
		if (first1 < lastk_1 && lastk_1 > apos) {//比较 lastk_1 和 apos，是因为变小的元素越靠右，结果越大
			apos = first1;
			bpos = lastk_1;
			avalue = 1;
			bvalue = scale - 1;
		}
		num[apos] = 1;
		num[bpos] = (avalue + bvalue) - scale;
		output(1);
	} else { //必然少1位，则前两项相加可以使得结果最大化（因为首位比其他方案都大）
		apos = 1, bpos = 2;
		avalue = num[apos], bvalue = num[bpos];
		num[bpos] += num[apos];
		output(2);
	}
	num[apos] = avalue, num[bpos] = bvalue;
}
void getmin() {
	int pos;
	if (num[2] == 0) {//尝试减少2位以上，将第一位和右侧的某个相加
		for (int j = n; ; --j) {//尽可能靠右的相加的不进位元素
			if (num[j] + num[1] < scale) {
				pos = j;
				break;
			}
		}
		if (pos > 2) {//至少能砍2位
			num[pos] += num[1];
			output(3);
			return;	
		}
	}
	//最靠左的不相邻的不进位的一对, 且左则的右邻居 < 左侧
	pos = 0;
	int mn = num[n];//不是inf
	for (int i = n - 2; i; --i) {//判断是否存在，并找到左侧元素位置
		if (num[i] > num[i + 1] && num[i] + mn < scale) {
			pos = i;
		}
		mn = min(num[i + 1], mn);
	}
	if (pos) {//存在，找到实际的右元素的位置
		int pos2;
		for (int j = n; ; --j) {
			if (num[j] + num[pos] < scale) {
				pos2 = j;
				break;
			}
		}
		num[pos2] += num[pos];
		for (int i = pos; i >= 2; --i) {
			num[i] = num[i - 1];
		}
		output(2);
		return;
	}	
	//尽可能靠右的一对 相加不进位
	pos = 0;
	mn = num[n];//不是inf
	for (int i = n - 1; i; --i) {//判断是否存在，并找到左侧元素位置
		if (num[i] + mn < scale) {
			pos = i;
			break;
		} else {
			mn = min(num[i], mn);
		}
	}
	if (pos) {//存在，找到实际的右元素的位置
		int pos2;
		for (int j = n; ; --j) {
			if (num[j] + num[pos] < scale) {
				pos2 = j;
				break;
			}
		}
		num[pos2] += num[pos];
		for (int i = pos; i >= 2; --i) {
			num[i] = num[i - 1];
		}
		output(2);
	} else { //必然进位，则第一位 >= 1, 所以我们选第一位为1（相加后第一位恰=1）, 第一位和第二位相加必然令第二位减少
	    //且若第一位本来就是1,那么其他位必然都是k-1, 第一位和第二位相加后第二为变成0最小
	    //若第一位本来>1则必选第一位，那么要令第二位尽可能小，所以选第一位和第二位
		num[2] = (num[1] + num[2]) - scale;
		num[1] = 1;
		output(1);
	}
}
int main() {
	read(n); read(scale);
	for (int i = 1; i <= n; ++i) read(num[i]);
	getmax();
	printf("\n");
	getmin();
	return 0;
}


```
