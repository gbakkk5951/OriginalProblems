#include<bits/stdc++.h>
using namespace std;
const int maxn=2000010;
int n,m,head,tail,tot,top;
int pre[maxn],nxt[maxn],val[maxn];
int change(char c)
{
	if(c=='s') return 0;
	if(c=='h') return 1;
}
inline void addh(char c){pre[head]=++tot;nxt[tot]=head;val[tot]=change(c);head=tot;}
inline void addt(char c){nxt[tail]=++tot,pre[tot]=tail;val[tot]=change(c);tail=tot;}
void calc()
{
	int res=0;
	for(int i=head;i;i=nxt[i])
	{
		int top=0,num=0,cnt=0;
		for(int j=i;j;j=nxt[j])
		{
			if(val[j]==0) top++;
			else if(val[j]==1) 
			{
				if(top) num++,top--;
				else break;
			} 
			else cnt++;
			if(!top) res=max(res,num*2+cnt);
		}
	}
	printf("%d\n",res);
}
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	head=1;
	for(int i=1;i<=n;i++) 
	{
		char c;cin>>c;addt(c);
	}
	calc();
	for(int i=1;i<=m;i++)
	{
		int op;char c;cin>>op>>c;
		if(op==1) addh(c);
		else addt(c);
		calc();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
