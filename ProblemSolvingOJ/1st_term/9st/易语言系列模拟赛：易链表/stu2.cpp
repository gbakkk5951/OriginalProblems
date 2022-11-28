#include <bits/stdc++.h>
using namespace std;
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
int DELETE = 1000000001;
int Index = 0, n;
const int PoolSize = MaxN * MaxC + MaxM;
struct ListItem;//声明之后会有一个命名为List的struct
typedef ListItem Li; //给ListItem起了一个别名Li
//在给出其定义之前，只能声明和使用其指针

Li *Head[MaxN], *Tail[MaxN];//

struct ListItem {//本行不能用别名
	int value;
	int nid;
	ListItem * prev;
	ListItem * next;
	/*增加更多的数据成员以实现题目要求*/
	/*你必须用指针来实现链表的连接*/	
}Pool[PoolSize];//内存池，避免频繁申请内存导致效率降低

Li *GetNewListItem(int nid) {//你必须用这个函数来申请一个新的表项
	//静态变量只会初始化1次，auto表示自动匹配类型，需要C++11及以上。如果你认为有必要可以把该静态局部变量改为全局变量
	//如果你吧Index当作一个类/结构体的数据成员，那么删掉auto和static加上int
	++Index;
	Li * NewOne = &Pool[Index];
	NewOne-> nid = nid;
	NewOne-> value = Index;
	NewOne-> prev = NULL;
	NewOne-> next = NULL;
	//这里的编号和池的下标是同步的，可以直接通过Pool[i]来得到第i号表项, &Pool[i] 或 (Pool + i) 表示指向第i号表项的指针
	//如果你认为有必要，可以在这里增加一些初始化代码，也可以增加本函数的参数
	return NewOne;
}
void inserthead(int nid){
	if (nid < 1 || nid > n){
	    return;
	}
	GetNewListItem(nid);
	if (Head[nid]->next == NULL){
		Head[nid]->next = Tail[nid]->prev = &Pool[Index];
	}
	else {
		(Pool+Index)->next = Head[nid]->next;
		Head[nid]->next->prev = &Pool[Index];
		Head[nid]->next = &Pool[Index];
	}
}
void inserttail(int nid){
	if (nid < 1 || nid > n){
	    return;
	}
	GetNewListItem(nid);
	if (Tail[nid]->prev == NULL){
		Head[nid]->next = Tail[nid]->prev = &Pool[Index];
	}
	else {
	    (Pool+Index)->prev = Tail[nid]->prev;
		Tail[nid]->prev->next = &Pool[Index];
		Tail[nid]->prev = &Pool[Index];
	}
}
void print(int id){
	if (id < 1 || id > Index){
		printf("NULL NULL NULL\n");
	}
	else if ((Pool + id)->value == DELETE){
			printf("NULL NULL NULL\n");
	}
	else if ((Pool + id)->next == NULL && (Pool + id)->prev == NULL){
			printf("NULL %d NULL\n", (Pool + id)->value);
	}
	else if ((Pool + id)->next == NULL && (Pool + id)->prev != NULL){
		printf("%d %d NULL\n", (Pool + id)->prev->value, (Pool + id)->value);
	}
	else if ((Pool + id)->next != NULL && (Pool + id)->prev == NULL){
		printf("NULL %d %d\n", (Pool + id)->value, (Pool + id)->next->value);
	}
	else{
		printf("%d %d %d\n", (Pool + id)->prev->value, (Pool + id)->value, (Pool + id)->next->value);
	}
}
void deletenode(int id){
	if (id < 1 || id > Index){
		return;
	}
	else if ((Pool+id)->prev == NULL && (Pool+id)->next == NULL) {
		if (Head[(Pool + id) -> nid]->next != NULL){
			Head[(Pool + id) -> nid]->next = NULL;
			Tail[(Pool + id) -> nid]->prev = NULL;
			(Pool + id)->value = DELETE;
	    }
	    else {
	    	return;
		}
    }
	else if ((Pool+id)->prev == NULL && (Pool+id)->next != NULL){
		Head[(Pool+id)->nid]->next = (Pool+id)->next;
		(Pool+id)->next->prev = NULL;
		(Pool+id)->next = NULL;
		(Pool + id)->value = DELETE;
	}
	else if ((Pool+id)->prev != NULL && (Pool+id)->next == NULL){
		Tail[(Pool+id)->nid]->prev = (Pool+id)->prev;
		(Pool+id)->prev->next = NULL;
		(Pool+id)->prev = NULL;
		(Pool + id)->value = DELETE;
	}
	else {
		(Pool+id)->prev->next = (Pool+id)->next;
		(Pool+id)->next->prev = (Pool+id)->prev;
		(Pool+id)->next = NULL;
		(Pool+id)->prev = NULL;
		(Pool + id)->value = DELETE;
	}
}
void update(int id, int idx){
	if (id < 1 || id > Index) return;
	else if ((Pool+id)->value == DELETE) {
			return;
	}
	else{
		Pool[id].value = idx;
	}
}
/*To Do*/
/*书写更多函数以实现本题的要求, 你也可以把Pool以及GetNewListItem包装到一个新的结构体/类中*/
/*如果你把ListItem的定义也移入了，那么head和tail以及typedef和提前声明的strut ListItem;也要移入*/


int main() {
	int m, op, nid[505], id, NID, x;
	scanf("%d", &n);
	for (int i = 0; i < MaxN; i++){
		Head[i] = (Li*)malloc(sizeof(Li));
		Tail[i] = (Li*)malloc(sizeof(Li));
	}
	for(int i = 0; i < MaxN; i++){
    Head[i]->next = NULL;
    Head[i]->prev = NULL;
    Tail[i]->next = NULL;
    Tail[i]->prev = NULL; 
}
	for (int i = 1; i <= n; i++){
		cin >> nid[i];
		for (int j = 1; j <= nid[i]; j++){
			inserttail(i);
		}
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		scanf("%d", &op);
		switch(op){
		case 1:
			scanf("%d", &id);
			print(id);
			break;
		case 2:
			scanf("%d", &id);
			deletenode(id);
		    break;
		case 3:
			scanf("%d", &NID);
			inserthead(NID);
		    break;
		case 4:
			scanf("%d", &NID);
			inserttail(NID);
		    break;
		case 5:
			scanf("%d %d", &id, &x);
			update(id, x);
		break;
	    }
	}
	return 0;
}
