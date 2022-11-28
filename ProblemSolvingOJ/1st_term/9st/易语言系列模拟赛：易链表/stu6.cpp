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
		node[n][0].next = NULL;
		node[n][0].last = NULL;
		tail[n] = NULL;
		for(int i = 1; i <= Ci; i++)
		{
			if(i == 1)
			{
				node[n][i].last = node[n][i].next = NULL;   //如果只有一个，前后指针为NULL 
				node[n][i].id = node[n][i].remark = count;
				d[count] = &node[n][i];
				count++;
			}
			if(Ci > 1) node[n][1].next = &node[n][2];     //两个及以上，补上1的右指针 
			if(i > 1 && i < Ci)      //中间指针 
			{
				node[n][i].last = &node[n][i - 1];
				node[n][i].next = &node[n][i + 1];
				node[n][i].id = node[n][i].remark = count;
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
				(p -> last) -> next = p -> next;
				(p -> next) -> last = p -> last;	
			}
			if(p -> last != NULL && p -> next == NULL)  //后指针为空 
			{
				(p -> last) -> next = NULL;
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
				(p -> next) -> last = NULL;
			}
			if(p -> next == NULL && p -> last == NULL)  //删除后，整个不存在，0点指向空 
			{
				for(int i = 1; i <= n; i++)
				{
					if(node[i][0].next == p)
					{
						node[i][0].next = NULL;
						tail[i] = NULL;
						break;
					}
				}
			}
		}
		if(Id < 1000005) d[Id] = NULL;	//清楚Id的位置（已被删除） 
	} 
	void insertHead(int nid)
	{
		Node *p = node[nid][0].next;
		c[nid]++;   //存到下一个位置上; 
		if(p != NULL)
		{
			p -> last = &node[nid][c[nid]];
			node[nid][c[nid]].next = p;
			node[nid][0].next = &node[nid][c[nid]];
			node[nid][c[nid]].last = NULL;
			d[count] = &node[nid][c[nid]];
		}
		if(p == NULL)
		{
			node[nid][c[nid]].next = node[nid][c[nid]].last = NULL;
			node[nid][0].next = &node[nid][c[nid]];
			d[count] = &node[nid][c[nid]];
		}
		node[nid][c[nid]].id = node[nid][c[nid]].remark = count;
		count ++;
	}
	void insertTail(int nid)
	{
		Node *p = tail[nid];
		c[nid] ++;
		if(p != NULL)
		{
			p -> next = &node[nid][c[nid]];
			node[nid][c[nid]].next = NULL;
			node[nid][c[nid]].last = p;
			tail[nid] = &node[nid][c[nid]];
		}
		else  //序列为空，直接添加 
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
			if(y > 0 && y < 1000000) l.change(y, z);
		}
		else
		{
			scanf("%d", &y);
			if(x == 1)
			{
				if(y > 0 && y < 1000000) l.print(y);
				else printf("NULL NULL NULL\n");
			}
			if(x == 2)
			{
				if(y > 0 && y < 1000000) l.Delete(n, y);
			}
			if(x == 3)
			{
				if(y > 0 && y < 1000000) l.insertHead(y);
			}
			if(x == 4)
			{
				if(y > 0 && y < 1000000) l.insertTail(y);
			}
		} 	
	}	
}
