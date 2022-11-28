#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;//定义一个常量，1e5表示1 * 10^5是浮点数，会被自动转化为整数
char S[mxn], C[mxn], D[mxn];
int cn, dn;
long long A, atmp;
double B, btmp;
char tmp[mxn];//临时字符
void getsub(int l, int r, char src[], char dst[]) {//取出src字符串从l到r的子串，并存在tmp处（从tmp[0]开始用）
	memcpy(dst, src + l, (r - l + 1) * sizeof(char));//如果src和dst是一个数组(哪怕以指针形式传递并且没有重叠)，必须用memmove不然会出错
	dst[r - l + 1] = '\0';//如果用字符串处理函数，必须有这个结尾标志位，'\0' == 0
}
int toint(int l, int r) {//几种方法选一种即可,l表示该数在字符串中的左端点的下标，r表示右端点的下标（闭区间）
	getsub(l, r, S, tmp);
	int ret;//这里没有初始化，是因为sscanf不受该变量初值的影响
	//方法一
	sscanf(tmp, "%d", &ret);
	//方法二
	ret = 0;//必须初始化为0
	for (int i = 0; tmp[i]; ++i) {
		ret *= 10;
		ret += tmp[i] - '0';
	}
	//方法三
	stringstream s1(tmp);
	s1 >> ret;
	//方法四
	istringstream s2(tmp);
	s2 >> ret;
	//方法五
	ret = atoi(tmp); //ASCII to integer
	//
	return ret;
}
double tofloat(int l, int r) {//几种方法选一种即可,l表示该数在字符串中的左端点的下标，r表示右端点的下标（闭区间）
	getsub(l, r, S, tmp);
	double ret;//这里没有初始化，是因为sscanf不受该变量初值的影响
	//方法一
	sscanf(tmp, "%lf", &ret);//读入时lf和f是不同的，输出时lf和f都可
	//方法二
	ret = 0;//必须初始化为0
	bool dot = false;
	double factor = 0.1;
	for (int i = 0; tmp[i]; ++i) {
		if (tmp[i] == '.') {
			dot = 1;//赋值一个非0数值,相当于赋值true
			continue;
		}
		if (!dot) {
			ret *= 10;
			ret += tmp[i] - '0';
		} else {
			ret += (tmp[i] - '0') * factor;
			factor /= 10.0;
		}
	}
	//方法三
	stringstream s1(tmp);
	s1 >> ret;
	//方法四
	istringstream s2(tmp);
	s2 >> ret;
	//方法五
	ret = atof(tmp); //ASCII to floating number, 类型是double
	//
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
				A += toint(l, r);
			}
		}
	}
	//如果逐字符输出不需要下面这两句, 这样是为了利用%s输出字符串
	C[cn] = 0;
	D[dn] = '\0';// '\0' 就是 0 
	
	/*方法一
	C[cn + 1] = '\n';
	printf("%lld\n%.2lf\n%s%s", A, B, C, D);
	*/
	/*方法二
	printf("%lld\n%.2lf\n%s\n%s", A, B, C, D);//注意%lld
	*/
	//方法三
	printf(
R"(%lld
%.2lf
%s
%s)", A, B, C, D);//注意%lld
	return 0;
}
