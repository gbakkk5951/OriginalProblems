#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;
	char ch;
	for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
	if(ch=='-') f=0,ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f?x:-x;
}
int n,tot,res;
int f[5000010];
string txt,s;
struct point 
{
	int son[2],fail,len;
	bool vis;
}tire[7000010];
inline void build()
{
	int now=0,l=s.length();
	for(int i=0;i<l;++i)
	{
		if(!tire[now].son[s[i]-'0'])
			tire[now].son[s[i]-'0']=++tot;
		now=tire[now].son[s[i]-'0'];
	}
	tire[now].vis=1;
	tire[now].len=l;
}
inline void get_fail()
{
	queue<int> q;
	for(int i=0;i<=1;++i)
	{
		if(tire[0].son[i])
		{
			tire[tire[0].son[i]].fail=0;
			q.push(tire[0].son[i]);
		}
	}
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i=0;i<=1;++i)
		{
			if(tire[now].son[i])
			{
				tire[tire[now].son[i]].fail=tire[tire[now].fail].son[i];
				q.push(tire[now].son[i]);
			}
			else 
				tire[now].son[i]=tire[tire[now].fail].son[i];
		}
	}
}
inline void query()
{
	int now=0,l=txt.length();
	for(int i=0;i<l;++i)
	{
		now=tire[now].son[txt[i]-'0'];
		if(i) f[i]=f[i-1];
		for(int t=now;t;t=tire[t].fail)
		{
			if(tire[t].vis)
			{
				int u=(i-tire[t].len>=0)?i-tire[t].len:0;
				f[i]=max(f[i],f[u]+1);
			}
		}
	}
}
signed main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	n=read();
	cin>>txt;
	for(int i=1;i<=n;++i)
	{
		cin>>s;
		build();
	}
	get_fail();
	query();
	printf("%lld\n",f[txt.length()-1]);
	fclose(stdin);fclose(stdout);
return 0;
}
