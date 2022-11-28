
### 1. 考察知识：双向链表

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的


```c++
#include <bits/stdc++.h>
using namespace std;
namespace myList {//因为list和STL中的list命名冲突，所以用一个namespace加以区分
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;// 100万 
//在给出其定义之前，只能声明和使用其指针


/*To Do*/
/*书写更多函数以实现本题的要求*/

//class类 和 struct结构体在功能上可以等价，除了struct默认访问权限为public，class为private之外
struct List {
private: //private:在该关健测后，直到下一个描述访问权限的关键词前的内容都只能被该struct/class内部的函数调用
	struct ListItem;//声明之后会有一个命名为List的struct
	typedef ListItem Li; //给ListItem起了一个别名Li
	struct ListItem {//本行不能用别名
		int Index;
		/*To Do*/
		/*增加更多的数据成员以实现题目要求*/
		/*你必须用指针来实现链表的连接*/
		Li *prev, *next; //前后指针
		int data; //备注
		int belong; //属于的链表
		char del; //是否已经被删除
		
	}Pool[PoolSize];//内存池，避免频繁申请内存导致效率降低，下标与编号相对应，可以快速取出， Pool[id]即编号为id的表项
	Li *Head[MaxN], *Tail[MaxN];//
	int Index = 0;//静态变量只会初始化1次，auto表示自动匹配类型，需要C++11及以上。如果你认为有必要可以把该静态局部变量改为全局变量
	Li *GetNewListItem(int belong) {//你必须用这个函数来申请一个新的表项
		++Index;
		Li * NewOne = &Pool[Index];
		NewOne->Index = Index;//这里的编号和池的下标是同步的，可以直接通过Pool[i]来得到第i号表项, &Pool[i] 或 (Pool + i) 表示指向第i号表项的指针
		//如果你认为有必要，可以在这里增加一些初始化代码，也可以增加本函数的参数
		NewOne->belong = belong;
		NewOne->data = Index;
		return NewOne;
	}
	void Link(Li *l, Li *r) {//节省判断， 将 l 和 r 连接， 在c++中NULL即为0, 0转化为bool类型时为false，非0为true
		if (l) l->next = r;
		if (r) r->prev = l;
	}
	
	void print(Li *nd, char endchar) {
		if (nd) {
			cout << nd->data;
		} else {
			cout << "NULL";
		}
		cout << endchar;
	}
template <typename Type1, typename Type2, typename Type3> //这里typename 表示一个不确定的类型，如果你确定两个参数类型一致，则可以少写一个，如果三个参数的类型一致，则只需要一个typename
	void ep(Type1 &dst, Type2 ifvalue, Type3 newvalue) {// Equal then rePlace, 因为P是重音，所以选用了P字母
		if (dst == (Type1) ifvalue) dst = (Type1) newvalue;// (Type1) xx 表示将xx的值转化为Type1类型
	}
public: //public:在该关健测后，直到下一个描述访问权限的关键词前的内容都可以在所有地方被调用
	void HeadInsert(int nid) {
		Li *nd = GetNewListItem(nid);
		Link(nd, Head[nid]);
		Head[nid] = nd;
		ep(Tail[nid], NULL, nd);
	}
	void TailInsert(int nid) {
		Li *nd = GetNewListItem(nid);
		Link(Tail[nid], nd);
		Tail[nid] = nd;
		ep(Head[nid], NULL, nd);
	}
	bool Check_id_Legal(int id) {
		return 1 <= id && id <= Index && !Pool[id].del; //顺序不能变，&&是短路运算符，从左到右计算，一但逻辑运算结果确定，后面的表达式不会被执行
	}
	void Delete(int id) {
		if (!Check_id_Legal(id)) return;//其实类内部的函数顺序没有严格要求，写在前面的函数可以直接调用 同一个类的写在后面的函数
		Li *nd = &Pool[id];
		nd->del = 1;
		Link(nd->prev, nd->next);
		ep(Head[nd->belong], nd, nd->next);
		ep(Tail[nd->belong], nd, nd->prev);
	}
	void Modify(int id, int x) {
		if (!Check_id_Legal(id)) return;
		Pool[id].data = x;
	}
	void Print(int id) {
		if (!Check_id_Legal(id)) {
			cout << "NULL NULL NULL" << endl;
			return;
		}
		Li *nd = &Pool[id];
		print(nd->prev, ' ');
		print(nd, ' ');
		print(nd->next, '\n');
	}
}list;// List是一个类，而 List list 的 list 称为List类的实例， list称作对象
//因为list是一个全局变量，所以其占用的空间初始均为0,所以可以省略一些初始化，
//但如果其作为非静态局部变量则需要加入初始化动作，而且由于占用空间较大，如果作为非静态局部变量很可能会爆栈，还需要动态申请内存
}
int main() {
	/*To Do*/
	/*书写更多代码以实现本题的要求*/
	using myList::list;//list是一个管理多个链表的对象
	int n, c, m, op, x, id, nid;
	ios::sync_with_stdio(false);//关闭cin和scanf的同步，以加速
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> c;
		for (int j = 1; j <= c; ++j) {
			list.TailInsert(i);//直接复用尾部插入即可， **完全没必要单独写一个初始化以实现连接！
		}
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> op;
		switch (op) {
			case 1: {
				cin >> id;
				list.Print(id);
				break;
			};
			case 2: {
				cin >> id;
				list.Delete(id);
				break;
			};
			case 3: {
				cin >> nid;
				list.HeadInsert(nid);
				break;
			};
			case 4: {
				cin >> nid;
				list.TailInsert(nid);
				break;
			};
			case 5: {
				cin >> id >> x;
				list.Modify(id, x);
				break;
			};
		}
	}
	return 0;
}


```


**二**
作者：张天昀
C语言版本，其映射表大小开小了，我已经帮他修正

```C++
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int n = 0, m = 0;
int c[505] = {};
int total = 0;

struct LinkedNode {
    int id;
    int listId;
    int value;
    struct LinkedNode *prev;
    struct LinkedNode *next;
};
struct LinkedNode *nodeMap[500 * 1000 + 500000 + 5] = {};

struct LinkedList {
    struct LinkedNode *head;
    struct LinkedNode *tail;
};
struct LinkedList list[505] = {};

struct LinkedNode *allocNewNode(int listId) {
    struct LinkedNode *node = malloc(sizeof(struct LinkedNode));
    total++;
    nodeMap[total] = node;
    node->id = total;
    node->listId = listId;
    node->value = total;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insertHead(int nid) {
    if (nid < 1 || nid > n) return;
    struct LinkedNode *node = allocNewNode(nid);
    if (list[nid].head == NULL) {
        list[nid].head = list[nid].tail = node;
    } else {
        node->next = list[nid].head;
        list[nid].head->prev = node;
        list[nid].head = node;
    }
}

void insertTail(int nid) {
    if (nid < 1 || nid > n) return;
    struct LinkedNode *node = allocNewNode(nid);
    if (list[nid].tail == NULL) {
        list[nid].head = list[nid].tail = node;
    } else {
        node->prev =list[nid].tail;
        list[nid].tail->next = node;
        list[nid].tail = node;
    }
}

void printNode(struct LinkedNode *node) {
    if (node != NULL) {
        printf("%d ", node->value);
    } else {
        printf("NULL ");
    }
}

void printNodes(int id) {
    if (id < 1 || id > total || nodeMap[id] == NULL) {
        printf("NULL NULL NULL");
    } else {
        struct LinkedNode *curr = nodeMap[id];
        struct LinkedNode *prev = curr->prev;
        struct LinkedNode *next = curr->next;
        printNode(prev);
        printNode(curr);
        printNode(next);
    }
    printf("\n");
}

void deleteNode(int id) {
    if (id < 1 || id > total) return;
    if (nodeMap[id] == NULL) return;
    
    struct LinkedNode *node = nodeMap[id];
    nodeMap[id] = NULL;
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node == list[node->listId].head) {
        list[node->listId].head = node->next;
    }
    if (node == list[node->listId].tail) {
        list[node->listId].tail = node->prev;   
    }
    free(node);
}

void updateNode(int id, int value) {
    if (id < 1 || id > total) return;
    if (nodeMap[id] != NULL) {
        nodeMap[id]->value = value;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        for (int j = 1; j <= c[i]; ++j) {
            insertTail(i);
        }
    }
    scanf("%d", &m);
    while (m--) {
        int op = 0, arg1 = 0, arg2 = 0;
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%d", &arg1);
                printNodes(arg1);
                break;
            case 2:
                scanf("%d", &arg1);
                deleteNode(arg1);
                break;
            case 3:
                scanf("%d", &arg1);
                insertHead(arg1);
                break;
            case 4:
                scanf("%d", &arg1);
                insertTail(arg1);
                break;
            case 5:
                scanf("%d%d", &arg1, &arg2);
                updateNode(arg1, arg2);
                break;
            default:
                assert(0);
        }
    }
    return 0;
}
```
**三**
作者：张天昀
C++版本
```c++
#include <cstdio>
#include <cassert>
#include <vector>
#include <unordered_map>

int n = 0, m = 0;
int c[505] = {};
int total = 0;

class LinkedNode;
std::unordered_map<int, LinkedNode*> nodeMap;

class LinkedNode {
    public:
        int id;
        int listId;
        int value;
        LinkedNode *prev;
        LinkedNode *next;
        LinkedNode(int listId) : listId(listId) { //zhy注 构造函数，即一个对象（变量）被创建时调用的函数
            //listId(listId), 表示listId调用构造函数，其参数为listId
            //对于int其等价于在这里写一行 this->listId = listId; 因为重名所以需要加this->以区分参数和数据成员
            total++;
            nodeMap[total] = this;
            id = total;
            value = total;
            prev = next = NULL;
        }
};

class LinkedList {
    public:
        LinkedNode *head;
        LinkedNode *tail;
        LinkedList() {
            head = tail = NULL;
        }
};
std::vector<LinkedList> list;

void insertHead(int nid) {
    if (nid < 1 || nid > n) return;
    LinkedNode *node = new LinkedNode(nid);
    if (list[nid].head == NULL) {
        list[nid].head = list[nid].tail = node;
    } else {
        node->next = list[nid].head;
        list[nid].head->prev = node;
        list[nid].head = node;
    }
}

void insertTail(int nid) {
    if (nid < 1 || nid > n) return;
    LinkedNode *node = new LinkedNode(nid);
    if (list[nid].tail == NULL) {
        list[nid].head = list[nid].tail = node;
    } else {
        node->prev =list[nid].tail;
        list[nid].tail->next = node;
        list[nid].tail = node;
    }
}

void printNode(LinkedNode *node) {
    if (node != NULL) {
        printf("%d ", node->value);
    } else {
        printf("NULL ");
    }
}

void printNodes(int id) {
    if (id < 1 || id > total || nodeMap.find(id) == nodeMap.end()) {
        printf("NULL NULL NULL");
    } else {
        LinkedNode *curr = nodeMap[id];
        LinkedNode *prev = curr->prev;
        LinkedNode *next = curr->next;
        printNode(prev);
        printNode(curr);
        printNode(next);
    }
    printf("\n");
}

void deleteNode(int id) {
    if (id < 1 || id > total) return;
    if (nodeMap.find(id) == nodeMap.end()) return;
    
    LinkedNode *node = nodeMap[id];
    nodeMap.erase(id);
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node == list[node->listId].head) {
        list[node->listId].head = node->next;
    }
    if (node == list[node->listId].tail) {
        list[node->listId].tail = node->prev;   
    }
    delete node;
}

void updateNode(int id, int value) {
    if (id < 1 || id > total) return;
    if (nodeMap.find(id) != nodeMap.end()) {
        nodeMap[id]->value = value;
    }
}

int main() {
    scanf("%d", &n);
    list.resize(n + 1, LinkedList());
    for (int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
        for (int j = 1; j <= c[i]; ++j) {
            insertTail(i);
        }
    }
    scanf("%d", &m);
    while (m--) {
        int op = 0, arg1 = 0, arg2 = 0;
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%d", &arg1);
                printNodes(arg1);
                break;
            case 2:
                scanf("%d", &arg1);
                deleteNode(arg1);
                break;
            case 3:
                scanf("%d", &arg1);
                insertHead(arg1);
                break;
            case 4:
                scanf("%d", &arg1);
                insertTail(arg1);
                break;
            case 5:
                scanf("%d%d", &arg1, &arg2);
                updateNode(arg1, arg2);
                break;
            default:
                assert(0);
        }
    }
    return 0;
}

```