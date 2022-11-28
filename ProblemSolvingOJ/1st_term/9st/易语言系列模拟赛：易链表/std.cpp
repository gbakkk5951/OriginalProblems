#include <bits/stdc++.h>
using namespace std;
namespace myList {
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;
//在给出其定义之前，只能声明和使用其指针


/*To Do*/
/*书写更多函数以实现本题的要求*/

struct List {
private:
	struct ListItem;//声明之后会有一个命名为List的struct
	typedef ListItem Li; //给ListItem起了一个别名Li
	struct ListItem {//本行不能用别名
		int Index;
		/*To Do*/
		/*增加更多的数据成员以实现题目要求*/
		/*你必须用指针来实现链表的连接*/
		Li *prev, *next;
		int data;
		int belong;
		char del;
		
	}Pool[PoolSize];//内存池，避免频繁申请内存导致效率降低
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
	void Link(Li *l, Li *r) {//节省判断
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
template <typename Type1, typename Type2, typename Type3>
	void ep(Type1 &dst, Type2 ifvalue, Type3 newvalue) {
		if (dst == (Type1)ifvalue) dst = (Type1)newvalue;
	}
public:
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
		return 1 <= id && id <= Index && !Pool[id].del; //顺序不能变
	}
	void Delete(int id) {
		if (!Check_id_Legal(id)) return;
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
}list;
}
int main() {
	/*To Do*/
	/*书写更多代码以实现本题的要求*/
	using myList::list;
	int n, c, m, op, x, id, nid;
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> c;
		for (int j = 1; j <= c; ++j) {
			list.TailInsert(i);
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
