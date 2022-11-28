
### 1. 考察知识：二叉搜索树

一个有右子树的节点的后继，必然在右子树的最左侧


### 2. 优秀代码
**一**
作者：张浩宇
子树用数组表示，可以方便访问，直接用0/1寻址
这里记录了parent节点的指针

```c++
#include <bits/stdc++.h>
using namespace std;
struct Node {
	int value, cnt;
	Node *f, *s[2];
	Node(int value, Node *f) {//构造函数
		this->f = f;
		this->value = value;
		cnt = 1;
		s[0] = s[1] = nullptr;//之前不小心写成了s[0] = s[0] = nullptr
	}
};

class Tree {
	Node *root = nullptr;
	void swapdata(Node *a, Node *b) {
		swap(a->value, b->value);
		swap(a->cnt, b->cnt);
	}
	void print(Node *nd) {
		printf("%d ", nd->value);
		for (int i = 0; i < 2; ++i) {
			if (nd->s[i]) print(nd->s[i]);
		}
	}
public:// public表示外部可以调用，class默认权限为private，struct默认为public
	void erase(int v) {
		Node *nd = root;
		while (nd) {
			if (nd->value == v) {
				if (--nd->cnt) break;
				if (nd->s[0] && nd->s[1]) {//两个kid，找到后继交换数据
					Node *succ = nd->s[1];
					while (succ->s[0]) succ = succ->s[0];
					swapdata(succ, nd);
					nd = succ;
				}
				// one or zero kid
				Node *s = nd->s[!!nd->s[1]];
				if (nd->f) nd->f->s[nd == nd->f->s[1]] = s;
				else root = s;
				if (s) s->f = nd->f;
				delete nd;
				break;
			} else {
				nd = nd->s[nd->value < v];
			}
		}
	}
	void insert(int v) {
		if (!root) {
			root = new Node(v, nullptr);
			return;
		}
		Node *nd = root;
		while (1) {
			if (nd->value == v) {
				++nd->cnt;
				return;
			}
			int spo = v > nd->value;
			if (nd->s[spo]) {
				nd = nd->s[spo];
			} else {
				nd->s[spo] = new Node(v, nd);
				return;
			}
		}
	}
	void print() {
		if (root) print(root);
		printf("\n");
	}
}tree;

int main() {
	int M;
	cin >> M;
	for (; M--; ) {
		int op, x;
		cin >> op;
		switch (op) {
			case 0 : {
				tree.print();
				break;
			}
			case 1 : {
				cin >> x;
				tree.insert(x);
				break;
			}
			case 2 : {
				cin >> x;
				tree.erase(x);
				break;
			}
			default : {
				throw "Wrong input";
			}
		}
	}
	return 0;
}


```

**二**
作者：张明轩


```c++
#include <bits/stdc++.h>
using namespace std;
struct node{
    int c, val;
    node* left, *right;
    node(int a, int b){left = NULL; right = NULL; c = a; val = b;}
    node(){left = NULL; right = NULL; c = 1;}
};
node* root = NULL;
node*& find(node*& t)
{
    if (!t->left) return t;
    else return find(t->left);
}
void insert(node*& t, int x) 
{
    if (t == NULL) {t = new node(1, x); return;}
    if (t->val == x) {t->c++; return;}
    if (x < t->val) insert(t->left, x);
    else if (x > t->val) insert(t->right, x);
}
void erase(node*& t, int x)
{
    if (t == NULL) return;
    if (t->val == x){
        t->c--;
        if (t->c <= 0){
            if (!t->left && !t->right) t = NULL; 
            else if (t->left && t->right){
                swap(find(t->right)->c, t->c);
                swap(find(t->right)->val, t->val);//交换后删破坏树的结构，此处不会再比较大小，所以可以
                erase(find(t->right), find(t->right)->val);
            }
            else{
                if (t->left) t = t->left;
                else t = t->right;
            }
        }
        return;
    }
    else if (x < t->val) erase(t->left, x);
    else erase(t->right, x);
}
void print(node* t)
{
    if (!t) return;
    cout << t->val << " ";
    print(t->left);
    print(t->right);
}
int main()
{
    int n, op, x;
    cin >> n;
    while(n--){
        cin >> op;
        if (op == 1){
            cin >> x;
            insert(root, x);
        }
        else if (op == 2){
            cin >> x;
            erase(root, x);
        }
        else{
            print(root);
            cout << endl;
        }
   }
}
```

**三**
作者：胡皓明


```c++
#include <cstdio>
struct node{
	node *lson, *rson;
	int val, cnt;
	node(int v)
	{
		lson = rson = NULL;
		val = v;
		cnt = 1;
	}
};
node* root;
int m;
void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
void dfs(node* u)
{
	if(u == NULL)
		return;
	printf("%d ", u -> val);
	dfs(u -> lson);
	dfs(u -> rson);
}
void insert(node* &u, int v)
{
	if(u == NULL)
	{
		u = new node(v);
		return;
	}
	if(u -> val < v)
		insert(u -> rson, v);
	else if(u -> val == v)
	{
		u -> cnt ++;
		return;
	}
	else
		insert(u -> lson, v);
}
void rmnode(node* &u)
{
	if(u -> lson == NULL && u -> rson == NULL)
	{
		node* tmp = u;
		u = NULL;
		delete tmp;
	}
	else if(u -> lson != NULL)
	{
		if(u -> rson == NULL)
		{
			node* tmp = u;
			u = u -> lson;
			delete tmp;
		}
		else
		{
			node* v = u -> rson;
			node* fa = u;
			while(v -> lson != NULL)
			{
				fa = v;
				v = v -> lson;
			}
			swap(u -> cnt, v -> cnt);
			swap(u -> val, v -> val);
			rmnode(v);
			if(fa == u)
				fa -> rson = v;
			else
				fa -> lson = v;
		}
	}
	else
	{
		node* tmp = u;
		u = u -> rson;
		delete tmp;
	}
}
void delet(node* &u, int v)
{
	if(u == NULL)
		return;
	if(u -> val == v)
	{
		u -> cnt --;
		if(u -> cnt == 0)
			rmnode(u);
		return;
	}
	if(u -> val < v)
		delet(u -> rson, v);
	else
		delet(u -> lson, v);
}
int main()
{
	root = NULL;
	scanf("%d", &m);
	int op, val;
	while(m--)
	{
		scanf("%d", &op);
		if(op == 0)
		{
			dfs(root);
			printf("\n");
		}
		else
		{
			scanf("%d", &val);
			if(op == 1)
				insert(root, val);
			else
				delet(root, val);
		}
	}
	return 0;
}
```

**四**
作者：徐沐杰


```c++
#include<cstdio>
#include<algorithm>
struct node{
	int cnt,idx;
	node *ls,*rs;
	node(int cnt=0,int idx=0,node* ls=NULL,node *rs=NULL){
		this->cnt=cnt,this->idx=idx;
		this->ls=ls,this->rs=rs;
	}
}*root=NULL;
void insert(node* &tree,int s){
	if(tree==NULL) return (void) (tree=new node(1,s));
	if(tree->idx==s) return (void) (++(tree->cnt));
	return s<tree->idx?insert(tree->ls,s):insert(tree->rs,s);
}
node** digleft(node* &tree){
	return tree->ls!=NULL?digleft(tree->ls):(&tree);
}
node** findnxt(node* &tree){
	return digleft(tree->rs);
}
void erase(node* &tree,int s){
	if(tree==NULL) return ;
	if(tree->idx==s){
		if(tree->cnt>1)
			return (void) (--tree->cnt);
		if(tree->ls!=NULL&&tree->rs!=NULL){
			node **tmp=findnxt(tree);
			std::swap(tree->idx,(*tmp)->idx);
			std::swap(tree->cnt,(*tmp)->cnt);
			return erase(*tmp,s);
		}
		else return (void) (tree->ls==NULL?(tree=tree->rs):(tree=tree->ls));
	}
	else return s<tree->idx?erase(tree->ls,s):erase(tree->rs,s);
}
void view(node* tree){
	if(!tree) return;
	printf("%d ",tree->idx);
	return view(tree->ls),view(tree->rs);
}
int main(){
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d",&opt);
		switch(opt){
			case 0:{
				view(root);
				puts("");
				break;
			}
			case 1:{
				int s;
				scanf("%d",&s);
				insert(root,s);
				break;
			}
			case 2:{
				int s;
				scanf("%d",&s);
				erase(root,s);
				break;
			}
		}
	}
	return 0;
}
```

**五**
作者：陈楚安


```c++
#include <bits/stdc++.h>
using namespace std;
const int M = 1e5;
int a[M + 5];
int c;
int root;
int lt[M + 5];
int rt[M + 5];
int val[M + 5];
int cnt[M + 5];
void insert(int &o, int x)
{
	if(!o)
	{
		o = ++c;
		val[o] = x;
		cnt[o]++;
		return;
	}
	if(x == val[o])
	{
		cnt[o]++;
		return;
	}
	if(x < val[o])
	{
		insert(lt[o], x);
	}
	else if(x > val[o])
	{
		insert(rt[o], x);
	}
}
int &min(int &o)
{
	if(lt[o])
		return min(lt[o]);
	return o;
}
void del(int &o, int x)
{
	//cout << "1\n";
	if(!o)
		return;
	if(val[o] == x)
	{
		//cout << "1\n";
		if(cnt[o] > 1)
		{
			cnt[o]--;
			return;
		}
		//cout << "1\n";
		if(!lt[o] && !rt[o])
		{
			o = 0;
			//cout << "1\n";
            return;
		}
		else if(!lt[o])
		{
			o = rt[o];
			return;
		}
		else if(!rt[o])
		{
			o = lt[o];
			return;
		}
		else
		{
		    swap(val[o], val[min(rt[o])]);
			swap(cnt[o], cnt[min(rt[o])]);
			del(min(rt[o]), x);
		}
	}
	if(val[o] < x) 
		del(rt[o], x);
	if(val[o] > x)
		del(lt[o], x);
}
void print(int &o)
{
	if(!o)
		return;
	printf("%d ", val[o]);
	print(lt[o]);
	print(rt[o]);
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int opt, x;
		scanf("%d", &opt);
		if(opt == 0)
		{
			print(root);
			printf("\n");
		}
		if(opt == 1)
		{
			scanf("%d", &x);
			insert(root, x);
		}
		if(opt == 2)
		{
			scanf("%d", &x);
			del(root, x);
		}
	}
	return 0;
}
```