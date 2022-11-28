#include<bits/stdc++.h>
using namespace std;
#define st 2700000
inline int read()
{
	int x=0,f=1;
	char ch;
	for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
	if(ch=='-') f=0,ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f?x:-x;
}
int n,m,t,cur,lst,res,x,ans,str;
int nxt[3000010],frm[3000010];
int a[3000010],sum[3000010];
char s[2000010],ch;
inline void work()
{
	res=0,ans=0,str=0;
	memset(sum,0,sizeof(sum));
	if(!a[nxt[st]]) res=max(res,1),ans=1,str=1;
	
	if(a[nxt[st]]==1) ++sum[nxt[st]];
	
	for(int i=nxt[nxt[st]];i!=-1;i=nxt[i])
	{
		sum[i]=sum[frm[i]];
		if(!a[i])
			++ans,++str;
		if(a[i]==1)
			++sum[i];
		if(a[i]==2)
		{
			if(sum[i])
			{
				--sum[i];
				ans+=2;
				if(a[i+1]!=2&&sum[i])
				{
					ans-=str;
				}
			}
			else
				ans=0,str=0;
		}
		res=max(res,ans);
	}
	printf("%d\n",res);
}
signed main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	n=read(),m=read();
	cin>>s;
	memset(nxt,-1,sizeof(nxt));
	cur=lst=strlen(s)-1;
	nxt[st]=0;
	frm[0]=st;
	for(int i=0;i<=cur;++i)	
	{
		if(s[i]=='s') a[i]=1;
		if(s[i]=='h') a[i]=2;
		if(i!=cur) nxt[i]=i+1;
		if(i) frm[i]=i-1;
	}
	work();
	for(int i=1;i<=m;++i)
	{
		t=read();
		cin>>ch;
		if(ch=='s') x=1;
		if(ch=='h') x=2;
		if(ch=='S') x=0;
		a[++cur]=x;
		if(t==1)
		{
			nxt[cur]=nxt[st];
			frm[nxt[st]]=cur;
			nxt[st]=cur;
			frm[cur]=st;
		}
		else
		{
			nxt[lst]=cur;
			frm[cur]=lst;
			++lst;
		}
		work();
	}
	fclose(stdin);fclose(stdout);
return 0;
}
