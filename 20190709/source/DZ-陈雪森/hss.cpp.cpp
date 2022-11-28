#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
#define N 1000010
int n,m;
struct node{ 
    char c;
    int b;	
}e[N];
queue<node>q1;
queue<node>q2;
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m); 
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		cin>>e[i].c;
		if(e[i].c=='s')
		{
			node y=q2.front();
			if(q2.size()&&i<y.b)
			{
				ans++;
				q2.pop();
			}
			else
			{
			 e[i].b=i;
			 q1.push(e[i]);
		    }
		}
		if(e[i].c=='h')
		{
			node x=q1.front();
			if(q1.size()&&x.b<i)
			{
				ans++;
				q1.pop();
			}
			else
			{
			 e[i].b=i;
			 q2.push(e[i]);
			}
		}
	}
	int a;
	char k;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>k;
	}
	printf("%d",ans*2);
	return 0;
}
