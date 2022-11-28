#include<bits/stdc++.h>
using namespace std;
struct node
{
	int pos;
	node *nxt,*pre;
}*he1,*tl1,*he2,*tl2;
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		if(ch=='s')
		{
			if(!he1)
			{
				he1=new node();
				he1->pos=i;
			}
			else if(!tl1)
			{
				tl1=new node();
				tl1->pos=i;
				he1->nxt=tl1;
				tl1->pre=he1;
			}
			else
			{
				node* t=new node();
				t->pos=tl1->pos;
				tl1->pre->nxt=t;
				t->pre=tl1->pre;
				t->nxt=tl1;
				tl1->pre=t;
				tl1->pos=i;
			}
		}
		else if(ch=='h')
		{
			if(!he2)
			{
				he2=new node();
				he2->pos=i;
			}
			else if(!tl2)
			{
				tl2=new node();
				tl2->pos=i;
				he2->nxt=tl2;
				tl2->pre=he2;
			}
			else
			{
				node* t=new node();
				t->pos=tl2->pos;
				tl2->pre->nxt=t;
				t->pre=tl2->pre;
				t->nxt=tl2;
				tl2->pre=t;
				tl2->pos=i;
			}
		}
	};
	int lans=0,rans=0,ans=0;
	node *nows=he1,*nowh=he2;
	while(nowh&&nows)
	{
		int st=nows->pos,end=0;
		while(nowh&&(nowh->pos<nows->pos))nowh=nowh->nxt;
		if(nowh)
		{
			while(nowh&&nows&&(nows->pos<nowh->pos))
			{
				end=max(end,nowh->pos);
				nows=nows->nxt,nowh=nowh->nxt;
			}
		}
		if(st<=2)lans=end-st+1;
		ans=max(ans,end-st+1);
	}
	nows=tl1,nowh=tl2;
	int st=nowh->pos,end=n;
	while(nows&&nows->pos>nowh->pos)nows=nows->pre;
	if(nows)
	{
		while(nowh&&nows&&(nows->pos<nowh->pos))
		{
			end=min(end,nows->pos);
			nows=nows->pre,nowh=nowh->pre;
		}
	}
	if(st>=n-1)rans=st-end+1;
	printf("%d\n",ans);
	int front=1,back=n;
	for(int i=1;i<=m;i++)
	{
		int p;
		char ch;
		scanf("%d %c",&p,&ch);
		if(n<=5000)
		{
			if(p==1)
			{
				if(ch=='s')
				{
					node *t=new node();
					t->pos=he1->pos;
					he1->pos=--front;
					he1->nxt->pre=t;
					t->nxt=he1->nxt;
					t->pre=he1;
					he1->nxt=t;
				}
				else if(ch=='h')
				{
					node *t=new node();
					t->pos=he2->pos;
					he2->pos=--front;
					he2->nxt->pre=t;
					t->nxt=he2->nxt;
					t->pre=he2;
					he2->nxt=t;
				}
				else front--;
			}
			else
			{
				if(ch=='h')
				{
					node* t=new node();
					t->pos=tl2->pos;
					t->pre=tl2->pre;
					tl2->pre->nxt=t;
					tl2->pos=++back;
					t->nxt=tl2;
					tl2->pre=t;
				}
				else if(ch=='s')
				{
					node* t=new node();
					t->pos=tl1->pos;
					t->pre=tl1->pre;
					tl1->pre->nxt=t;
					tl1->pos=++back;
					t->nxt=tl1;
					tl1->pre=t;
				}
				else back++;
			}
			node *nows=he1,*nowh=he2;
			while(nowh&&nows)
			{
				int st=nows->pos,end=0;
				while(nowh&&(nowh->pos<nows->pos))nowh=nowh->nxt;
				if(nowh)
				{
					while(nowh&&nows&&(nows->pos<nowh->pos))
					{
						end=max(end,nowh->pos);
						nows=nows->nxt,nowh=nowh->nxt;
					}
				}
				if(st<=2)lans=end-st+1;
				ans=max(ans,end-st+1);
			}
		}
		else{
			if(p==1)
			{
				if(he1->pos>he2->pos&&ch=='s') //hs*** adds
				{
					lans+=2,ans=max(ans,lans);
					node *t=new node();
					t->pos=he1->pos;
					he1->pos=--front;
					he1->nxt->pre=t;
					t->nxt=he1->nxt;
					t->pre=he1;
					he1->nxt=t;
				}
				else if(he1->pos>he2->pos&&ch=='h')//hs*** addh
				{
					lans=0;
					node *t=new node();
					t->pos=he2->pos;
					he2->pos=--front;
					he2->nxt->pre=t;
					t->nxt=he2->nxt;
					t->pre=he2;
					he2->nxt=t;
				}
				else if(he1->pos<he2->pos&&ch=='h')//sh*** addh
				{
					node *t=new node();
					t->pos=he2->pos;
					he2->pos=--front;
					he2->nxt->pre=t;
					t->nxt=he2->nxt;
					t->pre=he2;
					he2->nxt=t;
				}
				else if(he1->pos<he2->pos&&ch=='h')//sh*** adds
				{
					lans=0;
					node *t=new node();
					t->pos=he1->pos;
					he1->pos=--front;
					he1->nxt->pre=t;
					t->nxt=he1->nxt;
					t->pre=he1;
					he1->nxt=t;
				}
				else if(ch=='S')front--;
			}
			else
			{
				if(tl1->pos>tl2->pos&&ch=='h')//***hs addh
				{
					rans+=2;
					ans=max(ans,rans);
					node* t=new node();
					t->pos=tl2->pos;
					t->pre=tl2->pre;
					tl2->pre->nxt=t;
					tl2->pos=++back;
					t->nxt=tl2;
					tl2->pre=t;
				}
				else if(tl1->pos>tl2->pos&&ch=='s')//***hs adds
				{
					rans=0;
				}
			}
		}
		printf("%d\n",ans);
	} 
	return 0;
}
