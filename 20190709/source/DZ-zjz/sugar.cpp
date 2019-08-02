#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define regin register int
#include<queue>
using namespace std;
int n;
char c[5001000],s[5001000];

int tot,ch[5001000][2],nu[5001000];
bool vis[5001000];
inline void make(int lc)
{
	int l=strlen(c);
	int u=0;
	for(regin i=0;i<l;i++)
	{
		int v=c[i]-'0';
		if(!ch[u][v]) ch[u][v]=++tot;
		u=ch[u][v];
	}
	nu[u]=l;
	vis[u]=1;
}

queue<int> q;
int fail[5001000],dp[5001000];
inline void bfs()
{
	for(regin i=0;i<2;i++)
	{
		if(ch[0][i]) q.push(ch[0][i]);
	}
	while(q.size())
	{
		int u=q.front();q.pop();
		for(regin i=0;i<2;i++)
		{
			if(!ch[u][i]) ch[u][i]=ch[fail[u]][i];
			else 
			{
				int v=fail[u];
				while(v>0&&ch[v][i]==0) v=fail[v];
				fail[ch[u][i]]=ch[v][i];
			}
		}
	}
}
inline void answer()
{
	int l=strlen(s);
	int u=0;
	for(regin i=0;i<l;i++)
	{
		int a=s[i]-'0';
		int v=u;
		if(v)while(v)
		{
			if(vis[v]) i>=nu[v]?dp[i]=max(dp[i],dp[i-nu[v]]+1):dp[i]++;
			v=fail[v];
		}
		else dp[i]=dp[i-1];
		u=ch[u][a];
	}
}
int main ()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s);
	for(regin i=1;i<=n;i++)
	{
		scanf("%s",c);
		make(i);
	}
	bfs();
	answer();
	printf("%d\n",dp[strlen(s)-1]);
	return 0;
}
