
### 1. 考察知识：悦读、表达式计算、栈

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
粘贴模板
直接补全代码，照着算法抄就行了，除了判-+是正负还是加减需要考虑一下
但也有不少同学照着説明实现会漏掉重要的步骤，比如没有判断栈非空
比如在尝试取出前一个字符的时侯没有判断是否是第一个字符
比如%没判断是否会Runtime Error


```c++
#include <bits/stdc++.h>
using namespace std;
namespace my_calculator {
const int MXN = 2e5 + 10;
int runtime_error; // 0 表示没发生问题, 1 表示有问题
/*b = 0表示默认参数值，可以在调用的时侯不填，但为了能够被通用的函数指针指向，必须要有2个int参数*/
int positive(int a, int b = 0) {
	return a;
}
int negative(int a, int b = 0) {
	return -a;
}
int reverse(int a, int b = 0) {
	return ~a;
}
int multiply(int a, int b) {
	return a * b;
}
int divideby(int a, int b) {
	if (b == 0) {
		runtime_error = 1;
		return 0;
	}
	return a / b;
}
int module(int a, int b) {//有好几个同学没判断是否为0,直接取模:(
	if (b == 0) {
		runtime_error = 1;
		return 0;
	}
	return a % b;
}
int plus(int a, int b) {
	return a + b;
}
int minus(int a, int b) {
	return a - b;
}
int less(int a, int b) {
	return a < b;
}
int greater(int a, int b) {
	return a > b;
}
//enum可以看作一堆int常量
enum operators {
	Positive,//值为0
	Negative, //值为1
	Reverse, //值为2
	Multiply,
	Divideby,
	Module,
	Plus,
	Minus,
	Less,
	Greater,
	LeftBracket = '9' + 1, //其实用不着特别赋值，也可以把它定义为左括号本身
	RightBracket //值为'9' + 2
};

// 类型为(指向(返回值为int，参数为两个int的函数)的指针)的数组, 这个((函数指针)数组)命名为opt
// 无需修改
// (*opt[]) 的括号不能省略，[]去掉后就变成了单个函数指针，而非指针数组

int (*opt[]) (int, int) = { //可以将[XXX] = 省略，这么写只是为了方便悦读
	[Positive] = positive, 
	[Negative] = negative, 
	[Reverse] = reverse, 
	[Multiply] = multiply, 
	[Divideby] = divideby, 
	[Module] = module, 
	[Plus] = plus, 
	[Minus] = minus,
	[Less] = less,
	[Greater] = greater
};
// opt[Greater](a, b) 等价于 greater(a, b)
// 若有
// int t = Less;
// 则
// opt[t](a, b) 等价于 less(a, b);
char infix[MXN];
int getid(int pos) {
	switch(infix[pos]) { //这里的break可省
		case '+' :
			if (pos && (isdigit(infix[pos - 1]) || infix[pos - 1] == ')')) {
			//由于单目运算符都在操作数左侧，所以一个双目运算符的左侧只可能是)或数字
			//必须把判断是否为首字符作为第一个被判断的，如果又不理解的可以复习下短路运算符
				return Plus;
			} else {
				return Positive;
			}
		case '-' :
			if (pos && (isdigit(infix[pos - 1]) || infix[pos - 1] == ')')) {
				return Minus;
			} else {
				return Negative;
			}
		case '*' :
			return Multiply;
		case '/' :
			return Divideby;
		case '%' :
			return Module;
		case '~' :
			return Reverse;
		case '<' :
			return Less;
		case '>' :
			return Greater;
		case '(' :
			return LeftBracket;
		case ')' :
			return RightBracket;
		default  : // digits
			return infix[pos];
	}
}
int associativity[256];//结合性是左结合还是右结合
int priority[256];//优先级
int single[256];//是否为单目运算符
enum {
	LeftAssociative = 0,
	RightAssociative = 1
};
int postfix[MXN], sn;
void infix_to_postfix() {//照着说明实现算法即可
	stack<int> stk;
	for (int i = 0; infix[i]; ++i) {
		int t = getid(i);
		if (isdigit(t)) {
			postfix[sn++] = t;
			continue;
		} else
		if (t == LeftBracket) {
			stk.push(t);
		} else
		if (t == RightBracket) {
			assert(!stk.empty());
			while (stk.top() != LeftBracket) {
				postfix[sn++] = stk.top();
				stk.pop();
			}
			stk.pop();
		} else {
			while (
				stk.size() &&//这个必须在前
				stk.top() != LeftBracket && (
					priority[stk.top()] < priority[t] || (
						priority[stk.top()] == priority[t] && 
						associativity[t] == LeftAssociative
					)
				)
			) {
				postfix[sn++] = stk.top();
				stk.pop();
			}
			stk.push(t);
		}
	}
	while (!stk.empty()) {//别忘了
		postfix[sn++] = stk.top();
		stk.pop();
	}
}
int calculate() {//照着説明写即可
	stack<int> stk;
	for (int i = 0, t, a, b; i < sn; ++i) {
		t = postfix[i];
		if (isdigit(t)) {
			stk.push(t - '0');
		} else
		if (single[t]) {
			assert(stk.size() >= 1);
			a = stk.top();
			stk.pop();
			stk.push(opt[t](a, 0));
		} else {
			assert(stk.size() >= 2);
			b = stk.top();
			stk.pop();
			a = stk.top();
			stk.pop();
			stk.push(opt[t](a, b));
		}
	}
	assert(stk.size() == 1);
	return stk.top();
}
void init() {
	associativity[Negative] = associativity[Positive] = associativity[Reverse] = RightAssociative;
	//左结合用0表示，而全局变量默认为0
	single[Negative] = single[Positive] = single[Reverse] = 1;
	//非单目运算符用0表示，而全局变量默认为0
	priority[LeftBracket] = priority[RightBracket] = 1;
	priority[Negative] = priority[Positive] = priority[Reverse] = 2;
	priority[Multiply] = priority[Divideby] = priority[Module] = 3;
	priority[Plus] = priority[Minus] = 4;
	priority[Greater] = priority[Less] = 5;
}
void clear() {
	runtime_error = 0;
	sn = 0;
}
void main() {
	init();
	int T;
	scanf("%d", &T);
	while (T--) {
		clear();
		scanf("%s", infix);
		infix_to_postfix();
		int t = calculate();
		if (runtime_error) {
			printf("Runtime Error\n");
		} else {
			printf("%d\n", t);
		}
	}
}

}
int main() {
	my_calculator::main();
	return 0;
}

```


**二**
作者：徐沐杰
直接在中缀表达式上算
代码是最短的，设计很精巧

```C++
#include<cstdio>
const char optr[7] = { '+','-','*','/','%','<','>' };
const int priority[7] = { 1,1,5,5,5,0,0 };//越大表示需要先计算，单目运算符优先级为8
inline int findOptr(char s) {
	for (int i = 0; i < 7; i++)
		if (optr[i] == s) return i;
	return -1;
}
char expr[200005];
int end;//注意这是全局变量
bool reSign;
int work(int start, int level) {//计算从（start位置开始，一直到第一个优先级小于等于level的左结合运算符，或右括号，或表达式末尾）这段表达式的值
	int ans = 0;
	bool flag = false;
	for (;; start = end + 1) {
		if (reSign) return 0xffffffff;//出现 x / 0 或 x % 0
		if (expr[start] <= '9' && expr[start] >= '0') {//数
			ans = expr[start] - '0', end = start;
		}
		if (~findOptr(expr[start]) || expr[start] == '~') { // ~X 在逻辑运算时等价于 X != -1
			if (flag) {//双目运算符，这些if只有一个会执行判定为真的语句
				int now = findOptr(expr[start]);
				if (priority[now] <= level) { end = start - 1; break; }
				if (expr[start] == '+') ans = ans + work(start + 1, priority[now]);
				if (expr[start] == '-') ans = ans - work(start + 1, priority[now]);
				if (expr[start] == '*') ans = ans * work(start + 1, priority[now]);
				if (expr[start] == '/') {
					int tmp = work(start + 1, priority[now]);
					if (!tmp) {
						puts("Runtime Error");
						reSign = true;
						return 0xffffffff;
					}
					ans = ans / tmp;
				}
				if (expr[start] == '%') {
					int tmp = work(start + 1, priority[now]);
					if (!tmp) {
						puts("Runtime Error");
						reSign = true;
						return 0xffffffff;
					}
					ans = ans % tmp;
				}
				if (expr[start] == '<') ans = ans < work(start + 1, priority[now]);
				if (expr[start] == '>') ans = ans > work(start + 1, priority[now]);
			}
			else {//单目运算符，这些if只有一个会执行判定为真的语句
				if (expr[start] == '+') ans = +work(start + 1, 8);
				if (expr[start] == '-') ans = -work(start + 1, 8);
				if (expr[start] == '~') ans = ~work(start + 1, 8);
			}
		}
		if (expr[start] == '(') { ans = work(start + 1, -1); ++end; }
		if (expr[start] == ')') {//
			end = start - 1; break;
		}
		if (expr[start] == '\0') {
			end = start - 1; break;
		}
		flag = true;
	}
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		reSign = false;
		scanf("%s", expr);
		int tmp = work(0, -1);
		if (!reSign) printf("%d\n", tmp);
	}
	return 0;
}
```

**三**
作者：缪天顺
代码很简洁

```C++
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>

const int N = 2e5 + 10;
char list[N], stack1[N], stack2[N];
int stackres[N];
char pr[128] = {}, as[128] = {};
int main()
{
	pr['^'] = 100;
	pr['('] = pr[')'] = 1;
	pr['$'] = pr['!'] = pr['~'] = 2;
	pr['*'] = pr['/'] = pr['%'] = 3;
	pr['+'] = pr['-'] = 4;
	pr['>'] = pr['<'] = 5;
	as['$'] = as['!'] = as['~'] = 1;

	int* res;
	int T; scanf("%d", &T);
	while (T--) {
		list[0] = '^', stack2[0] = '(';
		int cnt = 0;
		scanf("%s", list + 1);//数组从1开始用，这样list[0]可以作为哨兵结点，减少特判
		char* pt1, * pt2, ch;
		for (pt1 = list + 1; *pt1 != '\0'; ++pt1, ++cnt)
			if (*pt1 == '+' || *pt1 == '-') {
				if (pr[*(pt1 - 1)] && *(pt1 - 1) != ')')
					*pt1 = (*pt1 == '+' ? '$' : '!');
			}
		list[0] = list[cnt + 1] = '^';
		list[cnt + 2] = '\0';

		pt1 = stack1, pt2 = stack2;
		for (int i = 1; list[i] != '\0'; ++i) {
			if (!pr[list[i]])
				*(++pt1) = list[i];
			else if (list[i] == '(')
				*(++pt2) = '(';
			else if (list[i] == ')') {
				while (*pt2 != '(')
					*(++pt1) = *(pt2--);
				pt2--;
			}
			else {
				while (*pt2 != '(') {
					if (as[list[i]] && pr[*pt2] < pr[list[i]])
						*(++pt1) = *(pt2--);
					else if (!as[list[i]] && pr[*pt2] <= pr[list[i]])
						*(++pt1) = *(pt2--);
					else
						break;
				}
				*(++pt2) = list[i];
			}
		}
		*(++pt1) = '^';



		res = stackres;
		for (int i = 1; stack1[i] != '^'; ++i) {
			if (!pr[stack1[i]])
				*(++res) = stack1[i] ^ '0';
			else {
				switch (stack1[i])
				{
				case '$': break;
				case '!': *res = -(*res); break;
				case '~': *res = ~(*res); break;
				case '*': --res; *res = (*res) * (*(res + 1)); break;
				case '/':
					--res;
					if (*(res + 1))
						*res = (*res) / (*(res + 1));
					else {
						printf("Runtime Error\n");
						goto end;
					}
					break;
				case '%':
					--res;
					if (*(res + 1))
						*res = (*res) % (*(res + 1));
					else {
						printf("Runtime Error\n");
						goto end;
					}
					break;
				case '+':--res; *res = (*res) + (*(res + 1)); break;
				case '-':--res; *res = (*res) - (*(res + 1)); break;
				case '>':--res; *res = (*res) > (*(res + 1)); break;
				case '<':--res; *res = (*res) < (*(res + 1)); break;
				}
			}
		}
		printf("%d\n", *res);  //
	end:
		;
	}
	return 0;
}

```