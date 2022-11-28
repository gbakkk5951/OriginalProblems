#include <bits/stdc++.h>
struct Node
{
	int id, remark; //id:编号  remark:备注  now:最后一位在数组中的位置; 
	Node *last, *next;
};
int c[505]; //c[nid]可记录子程序最后一个变量的位置；
Node *d[1000005]; //记录每个id对应的位置 
Node *tail[505];   //记录每个数组的尾部 
int count = 1; //count为增加项的编号和备注 
Node node[505][10005]; 
struct list
{
	void init(int n, int Ci)  //node[n][0]用来占位，单向指向第一个元素； 
	{
		node[n][0].next = NULL; //初始化0位置 
		node[n][0].last = NULL; //初始化0位置 
		tail[n] = NULL;         //初始化尾部指针，此时里边没有元素; 
		for(int i = 1; i <= Ci; i++)       //第i个链表，依次读取Ci个元素; 
		{
			if(i == 1)          //如果只有一个，前后指针为NULL 
			{
				node[n][i].last = node[n][i].next = NULL;   
				node[n][i].id = node[n][i].remark = count;    //编号和备注赋值 
				d[count] = &node[n][i];         //记录位置 
				count++;
			}
			if(Ci > 1) node[n][1].next = &node[n][2];     //两个及以上，补上1的右指针 
			if(i > 1 && i < Ci)      //中间指针 
			{
				node[n][i].last = &node[n][i - 1];          //分别指向前和后 
				node[n][i].next = &node[n][i + 1];
				node[n][i].id = node[n][i].remark = count;  //编号和备注赋值 
				d[count] = &node[n][i];
				count++;
			}
			if(i == Ci && Ci > 1)  //结尾指针，后指针为NULL 
			{
				node[n][i].last = &node[n][i - 1];
				node[n][i].next = NULL;
				node[n][i].id = node[n][i].remark = count;
				d[count] = &node[n][i];
				count ++;
			}		
		}
		if(Ci > 0) 
		{
		    tail[n] = &node[n][Ci];              //0指针的next指向1，如果没有，指向NULL
		    node[n][0].next = &node[n][1];
		}
	}
	void print(int Id)
	{
		Node *p = NULL;
		if(Id < 1000005)
		{
			p = d[Id];   //用p取出Id编号对应的位置; 
		}
		if(p != NULL)
		{
			if(p -> last != NULL) printf("%d ", (p -> last) -> remark);
			else printf("NULL ");
			printf("%d ", p -> remark);
			if(p -> next != NULL) printf("%d\n", (p -> next) -> remark);
			else printf("NULL\n");
		}
		if(p == NULL) printf("NULL NULL NULL\n");
	}
	void Delete(int n, int Id)
	{
		Node *p = NULL;
		if(Id < 1000005)
		{
			p = d[Id];   //用p取出Id编号对应的位置; 
		}
		if(p != NULL)
		{
			if(p -> last != NULL && p -> next != NULL)  //前后指针都有 
			{
				(p -> last) -> next = p -> next;      //前后指针互相连上即可 
				(p -> next) -> last = p -> last;	
			}
			if(p -> last != NULL && p -> next == NULL)  //后指针为空 
			{
				(p -> last) -> next = NULL;   //上一个的右指针没有了 
				for(int i = 1; i <= n; i++)   //找到对应的链表 
				{
					if(tail[i] == p)    //将链表的结尾改为前一个 
					{
						tail[i] = p -> last;
						break;
					}
				} 	
			}	
			if(p -> next != NULL && p -> last == NULL)  //前指针为空 ,后指针不为空 
			{
				for(int i = 1; i <= n; i++)   //找到对应的链表 
				{
					if(node[i][0].next == p)    //将该链表的0指针指向NULL 
					{
						node[i][0].next = p -> next; 
						break;
					}
				} 	
				(p -> next) -> last = NULL;   //后一项的左指针清除 
			}
			if(p -> next == NULL && p -> last == NULL)  //删除后，整个不存在，0点指向空 
			{
				for(int i = 1; i <= n; i++)
				{
					if(node[i][0].next == p)
					{
						node[i][0].next = NULL;
						tail[i] = NULL;    //尾巴也不存在了 
						break; 
					}
				}
			}
		}
		if(Id < 1000005) d[Id] = NULL;	//清除Id的位置（已被删除） 
	} 
	void insertHead(int nid) //只能在1~n范围内添加 
	{
		Node *p = node[nid][0].next;   //找到nid链表的第一个元素，或空 
		c[nid]++;   //存到下一个位置上; 
		if(p != NULL)   //链表本身有元素 
		{
			p -> last = &node[nid][c[nid]];          //p和p后面的指针互相指 
			node[nid][c[nid]].next = p;
			node[nid][0].next = &node[nid][c[nid]];    //不为空只需要改0指针; 
			node[nid][c[nid]].last = NULL;
			d[count] = &node[nid][c[nid]];  //记录这个新增的位置 
		}
		if(p == NULL)
		{
			node[nid][c[nid]].next = node[nid][c[nid]].last = NULL;
			node[nid][0].next = &node[nid][c[nid]];
			d[count] = &node[nid][c[nid]];
			tail[nid] = &node[nid][c[nid]];       //为空时需要改尾巴 
		}
		node[nid][c[nid]].id = node[nid][c[nid]].remark = count;
		count ++;
	}
	void insertTail(int nid)
	{
		Node *p = tail[nid];
		c[nid]++;
		if(p != NULL)
		{
			p -> next = &node[nid][c[nid]];   //两个互相连接 
			node[nid][c[nid]].last = p;
			node[nid][c[nid]].next = NULL;
			tail[nid] = &node[nid][c[nid]];
		}
		if(p == NULL)  //序列为空，直接添加 
		{
			node[nid][c[nid]].last = node[nid][c[nid]].next = NULL; //一个元素，头尾指针都为NULL 
			tail[nid] = &node[nid][c[nid]];   //尾标记指向该元素 
			node[nid][0].next = &node[nid][c[nid]];   //0指针指向该元素 
		}
		node[nid][c[nid]].id = node[nid][c[nid]].remark = count;
		d[count] = &node[nid][c[nid]];
		count ++;
	}
	void change(int Id, int x)
	{
		Node *p = NULL;
		if(Id < 1000005)
		{
			p = d[Id];
		}
		if(p != NULL)
		{
			p -> remark = x;
		}
	}
};
int main()
{
	list l;
	int m, n, x, y, z; 
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
		l.init(i, c[i]);	
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++)
	{
		scanf("%d", &x);
		if(x == 5)
		{
			scanf("%d %d", &y, &z);
			if(y > 0 && y < 1000000) l.change(y, z);    //将编号为y元素的备注改为z 
		}
		else
		{
			scanf("%d", &y);
			if(x == 1)
			{
				if(y > 0 && y < 1000000) l.print(y);   //编号为y的元素前中后 
				else printf("NULL NULL NULL\n");
			}
			if(x == 2)
			{
				if(y > 0 && y <= n) l.Delete(n, y);    //删除编号为y的元素 
			}
			if(x == 3)
			{
				if(y > 0 && y <= n) l.insertHead(y);    //在y链表的头部增加 
			}
			if(x == 4)
			{
				if(y > 0 && y <= n) l.insertTail(y);   //在y链表的尾部增加 
			}
		} 	
	}	
}
