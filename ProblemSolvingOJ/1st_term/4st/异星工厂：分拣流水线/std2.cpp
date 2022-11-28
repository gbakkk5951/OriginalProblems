#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;//定义一个常量，1e5表示1 * 10^5是浮点数，会被自动转化为整数
char S[mxn], C[mxn], D[mxn];
int cn, dn;
long long A, atmp;
double B, btmp;
double tofloat(int l, int r) {//如果用memcpy+临时数组可能会更短
	double ret;
	char t = 0;// '\0' == 0
	swap(S[r + 1], t);
	ret = atof(S + l);//也可以使用 ret = atof(&S[l]);
	swap(S[r + 1], t);
	return ret;
}
int main() {
	cin >> S;
	for (int l = 0, r; S[l]; l = r + 1) {//条件S[l]是当且仅当S[l] == 0即‘\0’时，循环结束
		char t = S[l];
		r = l;//区间的右端点
		bool dot = false;//是否有小数点
		if ('a' <= t && t <= 'z') {
			D[dn++] = t - 'a' + 'A';//不用担心char数值溢出，因为系统会自动转化为int进行运算
		} else
		if ('A' <= t && t <= 'Z') {
			C[cn++] = t - 'A' + 'a';
		} else {
			dot = t == '.';
			while ((t = S[r + 1]) && ('0' <= t && t <= '9'|| t == '.')) dot |= t == '.', ++r;
			if (dot) {
				B += tofloat(l, r);
			} else {
				A += tofloat(l, r);// double的精度足够10^6以内的整数
			}
		}
	}
	//全局变量默认就都是0,所以可以省略C[cn] = D[dn] = 0;（如果不确定请不要省略对末尾赋值为'\0'）
	printf("%lld\n%.2lf\n%s\n%s", A, B, C, D);
	return 0;
}
