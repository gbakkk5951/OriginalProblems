#include <bits/stdc++.h>
struct Node
{
	int id, remark; //id:编号  remark:备注
	Node *last, *next;
};
int c[505]; //c[nid]可记录子程序最后一个变量的位置；
Node *d[500000]; //记录每个id对应的位置 
Node *tail[505];
Node *head[505];   //记录每个数组的尾部 
int count = 1; //count为增加项的编号和备注 
Node node[500000]; 
struct list
{
	void init(int n, int Ci)  //node[n][0]用来占位，单向指向第一个元素； 
	{
		head[n] = NULL;
		tail[n] = NULL;         //初始化尾部指针，此时里边没有元素; 
		for(int i = 1; i <= Ci; i++)       //第i个链表，依次读取Ci个元素; 
		{
			if(i == 1)          
			{
				node[count].last = node[count].next = NULL;     //如果只有一个，前后指针为NULL
				node[count].id = node[count].remark = count;    //编号和备注赋值 
				d[count] = &node[count];   //记录位置 
				head[n] = &node[count];      
				count++;
			}
			if(Ci > 1) node[count - 1].next = &node[count];     //两个及以上，补上1的右指针 
			if(i > 1 && i < Ci)      //中间指针 
			{
				node[count].last = &node[count - 1];          //分别指向前和后 
				node[count].next = &node[count + 1];
				node[count].id = node[count].remark = count;  //编号和备注赋值 
				d[count] = &node[count];
				count++;
			}
			if(i == Ci && Ci > 1)  //结尾指针，后指针为NULL 
			{
				node[count].last = &node[count - 1];
				node[count].next = NULL;
				node[count].id = node[count].remark = count;
				d[count] = &node[count];
				count ++;
			}		
		}
		if(Ci > 0) 
		{
		    tail[n] = &node[count - 1]; 
			node[count - 1].next = NULL;             //0指针的next指向1，如果没有，指向NULL
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
					if(head[i] == p)    //将该链表的0指针指向NULL 
					{
						head[i] = p -> next; 
						break;
					}
				} 	
				(p -> next) -> last = NULL;   //后一项的左指针清除 
			}
			if(p -> next == NULL && p -> last == NULL)  //删除后，整个不存在，0点指向空 
			{
				for(int i = 1; i <= n; i++)
				{
					if(head[i] == p)
					{
						head[i] = NULL;
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
		Node *p = head[nid];   //找到nid链表的第一个元素，或空 
		//c[nid]++;   //存到下一个位置上; 
		if(p != NULL)   //链表本身有元素 
		{
			p -> last = &node[count];          //p和p后面的指针互相指 
			node[count].next = p;
			head[nid] = &node[count];    //不为空只需要改0指针; 
			node[count].last = NULL;
			d[count] = &node[count];  //记录这个新增的位置 
		}
		if(p == NULL)
		{
			node[count].next = node[count].last = NULL;
			head[nid] = &node[count];
			d[count] = &node[count];
			tail[nid] = &node[count];       //为空时需要改尾巴 
		}
		node[count].id = node[count].remark = count;
		count ++;
	}
	void insertTail(int nid)
	{
		Node *p = tail[nid];
		//c[nid]++;
		if(p != NULL)
		{
			p -> next = &node[count];   //两个互相连接 
			node[count].last = p;
			node[count].next = NULL;
			tail[nid] = &node[count];
		}
		if(p == NULL)  //序列为空，直接添加 
		{
			node[count].last = node[count].next = NULL; //一个元素，头尾指针都为NULL 
			tail[nid] = &node[count];   //尾标记指向该元素 
			head[nid] = &node[count];  //0指针指向该元素 
		}
		node[count].id = node[count].remark = count;
		d[count] = &node[count];
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
		std::cerr << " i = " << i << std::endl;
		fflush(stderr);
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
				if(y > 0 && y < 1000000) l.Delete(n, y);    //删除编号为y的元素 
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
