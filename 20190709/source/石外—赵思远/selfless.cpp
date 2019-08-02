#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long 
const int N=100010;
const int M=200010;
const ll INF=1e17;
using namespace std;
struct edge{
	ll from,to,dis,next;
}G[N<<1];
ll tot,head[N],n,m;
inline void add(ll u,ll v,ll w)
{
	G[++tot].dis=w;G[tot].next=head[u];
	G[tot].from=u;G[tot].to=v;
	head[u]=tot;
	return ;
}
ll bz[N][19],maxi[N][19],mini[N][19],deep[N];
inline void dfs(ll u,ll fa)
{
	bz[u][0]=fa;
	for(ll i=head[u];i;i=G[i].next)
	{
		ll t=G[i].to;
		if(t==fa) continue;
		deep[t]=deep[u]+1ll;
		maxi[t][0]=G[i].dis;
		mini[t][0]=-INF;
		dfs(t,u);
	}
	return ;
}
inline void cal()
{
	for(int i=1;i<=18;++i)
	{
		for(ll j=1;j<=n;++j)
		{
			bz[j][i]=bz[bz[j][i-1]][i-1];
			maxi[j][i]=max(maxi[j][i-1],maxi[bz[j][i-1]][i-1]);
			mini[j][i]=max(mini[j][i-1],mini[bz[j][i-1]][i-1]);
			if(maxi[j][i-1]>maxi[bz[j][i-1]][i-1])
			{
				mini[j][i]=max(mini[j][i],maxi[bz[j][i-1]][i-1]);
			}
			else if(maxi[j][i-1]<maxi[bz[j][i-1]][i-1])
			{
				mini[j][i]=max(mini[j][i],maxi[j][i-1]);
			}
		}
	}
	return ;
}
inline ll lca(ll x,ll y)
{
	if(deep[x]<deep[y])swap(x,y);
	for(ll i=18;i>=0;i--)
	{
		if(deep[bz[x][i]]>=deep[y])
		{
			x=bz[x][i];
		}
	}
	if(x==y) return x;
	for(ll i=18;i>=0;--i)
	{
		if(bz[x][i]^bz[y][i])
		{
			x=bz[x][i];y=bz[y][i];
		}
	}
	return bz[x][0];
}
inline ll qmax(ll u,ll v,ll maxx)
{
	ll res=-INF;
	for(ll i=18;i>=0;--i)
	{
		if(deep[bz[u][i]]>=deep[v])
		{
			if(maxx!=maxi[u][i])
			{
				res=max(res,maxi[u][i]);
			}
			else
			{
				res=max(res,mini[u][i]);
			}
			u=bz[u][i];
		}
	}
	return res;
}
inline bool cmp(edge x,edge y)
{
	return x.dis<y.dis;
}
edge A[M<<1];
ll u,v,w,fa[N];ll cnt;
inline ll find(ll x)
{
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x]; 
}
bool vis[M<<1];
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&A[i].from,&A[i].to,&A[i].dis);
	}
	sort(A+1,A+m+1,cmp);
	for(ll i=1;i<=n;++i) fa[i]=i;
	for(ll i=1;i<=m;++i)
	{
		u=A[i].from; v=A[i].to;w=A[i].dis;
		ll fat=find(u);
		ll fb=find(v);
		if(fat==fb) continue;
		fa[fat]=fb;
		cnt+=A[i].dis;
		add(u,v,w);add(v,u,w);
		vis[i]=1;
	}
	mini[1][0]=-INF; deep[1]=1;
	dfs(1,-1); cal();
	ll Ans=INF;
	for(ll i=1;i<=m;++i)
	{
		if(vis[i]) continue;
		u=A[i].from; v=A[i].to;
		w=A[i].dis; ll LCA=lca(u,v);
		ll maxu=qmax(u,LCA,w);
		ll maxv=qmax(v,LCA,w);
		Ans=min(Ans,cnt-max(maxu,maxv)+w);
	}
	printf("%lld\n",Ans);
	fclose(stdin);fclose(stdout);
	return 0;
 } 
