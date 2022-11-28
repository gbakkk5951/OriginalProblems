
### 1. 考察知识：对字符串的划分，大小写转化，以及从文本中读入数
字符本身是用数进行编码的，可以搜索“ASCII码”进一步了解
'a'-'z', '0'-'9', 'A'-'Z'这三组**分别**是一个连续的区间，
我们有以下操作
假设s是一个string或一个char数组，我们要处理下标为i处的字符
```c++
char t = s[i];
if ('a' <= t && t <= 'z') {
    ...//t是小写字母
}
if ('A' <= t && t <= 'Z') {
    ...//t是大写字母
}
if ('0' <= t && t <= '9') {
    ...//t是数字
}
if ('a' <= t && t <= 'z' || 'Z' <= t && t <= 'Z') {
    ...//t是字母
}
char t2 = t + 'a' - 'A'; //大写转小写
char t3 = t - 'A' + 'a'; //小写转大写
int a1 = t - '0'; //单个字符转数

```
或者
```c++
char t = s[i];
if (islower(t)) {
    ...//t是小写字母
}
if (isupper(t)) {
    ...//t是大写字母
}
if (isdigit(t)) {
    ...//t是数字
}
if (isalpha(t)) {
    ...//t是字母
}
char t2 = tolower(t); //大写或小写 转小写
char t3 = toupper(t); //大写或小写 转大写
int a1 = t - '0'; //单个字符转数

```
思路如下：
```
读入字符串S，（由于只有1行，而且没有空格，直接cin >> s; 或scanf("%s", s); 即可）
```


### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的，真的没有想到很多同学写起来很困难（/表情_躬匠）
```c++
#include <bits/stdc++.h>
using namespace std;
string S;
long long A;
double B, tmp;
string C;
string D;
int main() {
	cin >> S;
	for (int l = 0, r; l < S.length(); l = r + 1) {
		r = l;
		bool dot = S[r] == '.';
		if (isalpha(S[l])) {
			if (isupper(S[l])) {
				C += (char) tolower(S[l]); //string 直接在末尾追加字符
			} else {
				D = D + (char) toupper(S[l]); //string 直接在末尾追加字符，只是为了展示两种写法才用的不同运算符
			}
			continue;
		} else {
			while (r + 1 < S.length() && !isalpha(S[r + 1])) { //划出这个数的区间[l, r]
				dot |= S[++r] == '.';
			}
			istringstream is(S.substr(l, r - l + 1));
			is >> tmp; // double的精度足够6位整数，所以可以通用一个tmp，当然也可以分别开一个变量
			if (dot) {
				B += tmp;
			} else {
				A += tmp;
			}
		}
	}
	cout << A << endl << setiosflags(ios::fixed) << setprecision(2) << B << endl << C << endl << D;
	return 0;
}
```


**二**
作者：张浩宇
使用char数组完成，里面包含了很多种方法，所以其实并不长，**不要害怕！**, 三是精简版
```C++
#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;//定义一个常量，1e5表示1 * 10^5，是浮点数，会被自动转化为整数
char S[mxn], C[mxn], D[mxn];
int cn, dn;
long long A, atmp;
double B, btmp;
char tmp[10];//临时字符 由题目约定，10恰好够
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
		ret += ret * 10 + tmp[i] - '0';
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
	double factor = 1;
	for (int i = 0; tmp[i]; ++i) {
		if (tmp[i] == '.') {
		    dot = 1;
		} else {
		    ret = dot ? ret + (tmp[i] - '0') * (factor /= 10.0) : ret * 10 + tmp[i] - '0'; // ? : 是c语言的三目运算符
		    /*相当于
		    if (dot) {
                ret = ret + (tmp[i] - '0') * (factor /= 10.0); 
                // (factor /= 10.0)
                // 表示 factor = factor / 10.0; 并将修改后的factor作为值参与运算
            } else {
                ret = ret * 10 + tmp[i] - '0';
            }
		    */
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
			while ((t = S[r]) && ('0' <= t && t <= '9'|| t == '.')) {
			    dot |= t == '.';
			    ++r;
			}
			--r;
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
	printf("%lld\n%.2lf\n%s%s", A, B, C, D);//注意%lld
	*/
	/*方法二
	printf("%lld\n%.2lf\n%s\n%s", A, B, C, D);//注意%lld
	*/
	//方法三 rawstring, 会包含换行，c++11开始提供的特性
	printf(
R"(%lld
%.2lf
%s
%s)", A, B, C, D);//注意%lld
	return 0;
}
```
**三**
作者：张浩宇
二的精简版
```C++
#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;//定义一个常量，1e5表示1 * 10^5是浮点数，会被自动转化为整数
char S[mxn], C[mxn], D[mxn];
int cn, dn;
long long A, atmp;
double B, btmp;
double tofloat(int l, int r) {//如果用memcpy+临时数组可能会更短
	double ret;
	char t = S[r + 1];//也可以用swap : char t = 0; swap(S[r + 1], t);
	S[r + 1] = 0;// '\0' == 0
	ret = atof(S + l);//也可以使用 ret = atof(&S[l]); 如果不愿意用库函数，可以使用二、tofloat()的方法二
	S[r + 1] = t;//也可以swap
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
			while ((t = S[r]) && ('0' <= t && t <= '9'|| t == '.')) {
			    dot |= t == '.';
			    ++r;
			}
			--r;
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
```
**四**
作者：朱宇博
```c++
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <iomanip>
using namespace std;
const int N = 1000000 + 5;
char s[N];
long long A;
double B;
string C, D;
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    bool flag = 0;
    int l = -1, dightLen = 0;
    double tep = 0;

    for (int i = 0; i <= len; i++)
    {
        if (s[i] == '.' || isdigit(s[i]))
        {
          l = (l == -1) ? i : l;
          dightLen = dightLen + 1;
          if (s[i] == '.') flag = true;
        }
        else {
          if (dightLen) {
            char c = s[l + dightLen];
            s[l + dightLen] = 0;
            sscanf(s + l, "%lf", &tep);
            if (!flag) A += tep;
            else B += tep;
            s[l + dightLen] = c;
            dightLen = 0;
            l = -1;
            flag = false;
          }

          if (islower(s[i])) D += toupper(s[i]);
          else if (isupper(s[i])) C += tolower(s[i]);
        }
    }
    cout << A << endl << setiosflags(ios::fixed) << setprecision(2) << B << endl << C << endl << D;
    return 0;
}
```
**五**
作者：徐沐杰
```c++
#include<cstdio>
#include<cstring>
char s[100005];
char ans1[100005], ans2[100005];
int cnt1, cnt2;
long long ansNum1 = 0;
double ansNum2 = 0.0;
long long currentState = 0, integer = 0;
double floating = 0, floatBase = 1.0;

void checkout(){
	if(currentState == 0){
		ansNum1 += integer;
	}
	else{
		ansNum2 += integer + floating;
	}
	integer = 0;
	floating = 0;
	floatBase = 1.0;
	currentState = 0;
	return ;
}

int main(){
	scanf("%s", s);
	int slen = strlen(s);
	for(int i = 0; i < slen; i++){
		if(s[i] == '.'){
			currentState = 1;
		}
		if(s[i] >= '0' && s[i] <= '9'){
			if(currentState == 1){
				floatBase /= 10.0;
				floating += (s[i] - '0') * floatBase;
			}
			else integer = integer * 10 + s[i] - '0'; 
		}
		if(s[i] >= 'a'&&s[i] <= 'z'){
			checkout();
			ans2[cnt2++] = s[i] - 'a' + 'A';
		}
		if(s[i] >= 'A'&&s[i] <= 'Z'){
			checkout();
			ans1[cnt1++] = s[i] - 'A' + 'a';
		}
	}
	checkout();
	printf("%lld\n%.2lf\n%s\n%s", ansNum1, ansNum2, ans1, ans2);
	return 0;
}

```