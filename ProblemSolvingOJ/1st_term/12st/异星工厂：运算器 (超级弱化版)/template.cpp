/* to do 请补全头文件，如果你的编译器支持，可以使用万能头文件*/
using namespace std;
namespace my_calculator {
const int MXN = 2e5 + 10;
int runtime_error;// 0 表示没发生问题, 1 表示有问题
/*b = 0表示默认参数值，可以在调用的时侯不填，但为了能够被通用的函数指针指向，必须要有2个int参数*/
int positive(int a, int b = 0) {
	return a;
}
int negative(int a, int b = 0) {
	return -a;
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
/* to do 补全以下5个函数, 计算部份直接调用C++对应的算术符号即可*/
int reverse(int a, int b = 0) {// ~ 运算
	/*to do*/
}
int module(int a, int b) { // % 运算
	/*to do*/
}
int plus(int a, int b) {
	/*to do*/
}
int minus(int a, int b) {
	/*to do*/
}
int less(int a, int b) {
	/*to do*/
}
int greater(int a, int b) {
	/*to do*/
}

// enum 中的名字其实是int，如果没有赋值，则值为上一个+1,特别的如果第一个值没有赋值，则为0
// 里面的名字可以直接用，更多信息可参考
// https://www.runoob.com/w3cnote/cpp-enum-intro.html
// 无需修改
enum operators {
	Positive, //值为0
	Negative, //值为1
	Reverse, //值为2
	Multiply,
	Divideby,
	Module,
	Plus,
	Minus,
	Less,
	Greater,
	LeftBracket = '9' + 1,// 这里可以不赋值，只是为了演示
	RightBracket //值为 '9' + 2
};
// 类型为(指向(返回值为int，参数为两个int的函数)的指针)的数组
// 无需修改
int (*opt[]) (int, int) = { //这里的 opt 才是这个数组的名字, 有初始化列表的数组可以省略最高维度的大小
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
int getid(int position) {//传入参数为infix的下标
	/*to do 补全区分加减和正负的if的条件*/
	switch(infix[position]) { //这里的break可省
		case '+' :
			if (/*to do*/) {
				return Plus;
			} else {
				return Positive;
			}
		case '-' :
			if (/*to do*/) {
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
		default  : // 数字直接返回原编码, char其实是8位版本的int
			return infix[position];
	}
}
int associativity[256];
int priority[256];
int single[256];
enum {
	LeftAssociative = 0,
	RightAssociative = 1
};
int postfix[MXN], pn;// pn表示结果数组加入新 符号/数 的下标, 可以将存储后缀表达式的数组看作一个队列，中缀转后缀时，不断加入队尾，计算时不断从中取出队头
void infix_to_postfix() {
	/*to do 将infix中的表达式，转化为中缀表达式，为了计算方便，请使用getid()来转化编码*/
}
int calculate() {
	/*to do 计算postfix数组中的后缀表达式*/
}
void init() {
	associativity[Negative] = associativity[Positive] = associativity[Reverse] = RightAssociative;
	//左结合用0表示，而全局变量默认为0
	single[Negative] = single[Positive] = single[Reverse] = 1;
	priority[LeftBracket] = priority[RightBracket] = 1;
	/*to do 仿照上述代码对优先级的赋值，完成对其他符号的优先级赋值*/
	/*数字一方面因为全局变量初始为0,另一方面也因为数字的优先级用不到，所以不用赋值*/
	
}
void clear() {
	runtime_error = 0;
	pn = 0;
}
void main() {//实际上的main，不需要修改
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
int main() {//形式上的main
	my_calculator::main();
	return 0;
}
