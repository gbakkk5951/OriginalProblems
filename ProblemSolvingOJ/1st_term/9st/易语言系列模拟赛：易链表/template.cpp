#include <bits/stdc++.h>
using namespace std;
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;
struct ListItem;//声明之后会有一个命名为List的struct
typedef ListItem Li; //给ListItem起了一个别名Li
//在给出其定义之前，只能声明和使用其指针

Li *Head[MaxN], *Tail[MaxN];//

struct ListItem {//本行不能用别名
	int Index;
	/*To Do*/
	/*增加更多的数据成员以实现题目要求*/
	/*你必须用指针来实现链表的连接*/
	
	
}Pool[PoolSize];//内存池，避免频繁申请内存导致效率降低

Li *GetNewListItem() {//你必须用这个函数来申请一个新的表项
	static auto Index = 0;//静态变量只会初始化1次，auto表示自动匹配类型，需要C++11及以上。如果你认为有必要可以把该静态局部变量改为全局变量
	//如果你吧Index当作一个类/结构体的数据成员，那么删掉auto和static加上int
	++Index;
	Li * NewOne = &Pool[Index];
	NewOne->Index = Index;//这里的编号和池的下标是同步的，可以直接通过Pool[i]来得到第i号表项, &Pool[i] 或 (Pool + i) 表示指向第i号表项的指针
	//如果你认为有必要，可以在这里增加一些初始化代码，也可以增加本函数的参数
	NewOne->data = Index;
	return NewOne;
}
/*To Do*/
/*书写更多函数以实现本题的要求, 你也可以把Pool以及GetNewListItem包装到一个新的结构体/类中*/
/*如果你把ListItem的定义也移入了，那么head和tail以及typedef和提前声明的strut ListItem;也要移入*/


int main() {
	/*To Do*/
	/*书写更多代码以实现本题的要求*/
	
	return 0;
}
