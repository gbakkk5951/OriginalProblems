#include <bits/stdc++.h>
using namespace std;
template <typename Type>
void read(Type &a) {
	int t;
	while (!isdigit(t = getchar()));
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10; a += t - '0';
	}
}
char stk[33];
void write(int a) {
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
//	putchar('\n');
}
void getmax() {
	int apos, bpos, avalue, bvalue;
	//exists a + b >= scale;
	int flag = 0;
	int mx = num[n];//不是0, 可以造数据卡
	for (int i = n - 1; i >= 1; --i) {
		if (num[i] + mx >= scale) {
			apos = i;
			avalue = num[apos];
			flag = 1;
			break;
		} 
		mx = max(mx, num[i]);
	}
	
	
	if (flag == 1) {
		for (int j = n; 1; --j) {
			if (num[j] + avalue >= scale) {
				bpos = j;
				bvalue = num[j];
				break;
			}
		}
		//尝试(1) + (k - 1), 
		int first1, lastk_1;
		for (first1 = 1; first1 <= n; first1++) {
			if (num[first1] == 1) {
				break;
			}
		}
		for (lastk_1 = n; lastk_1; --lastk_1) {
			if (num[lastk_1] == scale - 1) {
				break;
			}
		}
		if (first1 < lastk_1 && lastk_1 > apos) {//要不要卡一下没判的？
			apos = first1;
			bpos = lastk_1;
			avalue = 1;
			bvalue = scale - 1;
		}
		
		
		num[apos] = 1;
		num[bpos] = (avalue + bvalue) - scale;
//		cerr << "Case A" << endl;
		output(1);
	} else { 
		//not exists
		apos = 1, bpos = 2;
		avalue = num[apos], bvalue = num[bpos];
		num[bpos] += num[apos];
//		cerr << "Case B" << endl;
		output(2);
	}
	num[apos] = avalue, num[bpos] = bvalue;
}
void getmin() {
	//前导0
	int pos;
	if (num[2] == 0) {
		for (int j = n; ; --j) {
			if (num[j] + num[1] < scale) {
				pos = j;
				break;
			}
		}
		if (pos > 2) {
			num[pos] += num[1];
//			cerr << "Case C" << endl;
			output(3);
			return;	
		}
	}
	//最靠左的不相邻的不进位的一对, 且左则的右邻居 < 左侧
	
	pos = 0;
	int mn = num[n];//不是inf
	for (int i = n - 2; i; --i) {
//		printf("i = %d, num = %d, mn = %d\n", i, num[i], mn);
		if (num[i] > num[i + 1] && num[i] + mn < scale) {
			pos = i;
			
		}
		mn = min(num[i + 1], mn);
	}
	
	if (pos) {
//		printf("pos = %d\n", pos); 
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
//		cout << "Case F" << endl;
		output(2);
		return;
	}
	
	//尽可能靠右的一对 相加不进位
	pos = 0;
	mn = num[n];//不是inf
	for (int i = n - 1; i; --i) {
		if (num[i] + mn < scale) {
			pos = i;
			break;
		} else {
			mn = min(num[i], mn);
		}
	}
	if (pos) {
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
//		cerr << "Case D" << endl;
		output(2);
	} else { //必然进位
		num[2] = (num[1] + num[2]) - scale;
		num[1] = 1;
	//	cerr << "Case E" << endl;
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

