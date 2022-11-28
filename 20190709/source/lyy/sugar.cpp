#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
struct node
{
	int to[2],fail,num;
}tr[5000005];
int n,ans,tot,nn=-1;
int w[100005],v[10000005];
string s,k;
void add(int x)
{
	int now=0;
	for(int i=0;i<s.length();i++)
	{
		if(tr[now].to[s[i]-'0'])now=tr[now].to[s[i]-'0'];
		else tr[now].to[s[i]-'0']=++tot,now=tot;
	}
	tr[now].num=x;
}
void fuck()
{
	queue<int>q;
	for(int i=0;i<=1;i++)if(tr[0].to[i])q.push(tr[0].to[i]);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<=1;i++)
		{
			int g=tr[u].to[i];
			if(tr[u].to[i])
			{
			tr[g].fail=tr[tr[u].fail].to[i];q.push(g);
		}
			else tr[u].to[i]=tr[tr[u].fail].to[i];
		}
	}
}
void fuckyou()
{
	int now=0;
	for(int i=0;i<k.length();i++)
	{
		now=tr[now].to[k[i]-'0'];
		for(int j=now;j;j=tr[j].fail)
		  if(tr[j].num)v[i]=min(v[i],w[tr[j].num]);
	}
}
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	memset(v,0x3f,sizeof(v));
	cin>>n;
	cin>>k;
	for(int i=1;i<=n;i++)cin>>s,add(i),w[i]=s.length();
	fuck();
	fuckyou();
	for(int i=0;i<k.length();i++)if(i-v[i]+1>nn)ans++,nn=i;
	cout<<ans<<endl;
	return 0;
}
