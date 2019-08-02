#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int s,t,w;
}e[200001];
bool cmp(edge x,edge y)
{
	return x.w<y.w;
}
int fa[100001];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int target[200001],pre[200001],last[200001],tot,w[200001],deep[200001],
father[200001][21],zd[200001][21],cd[200001][21];
bool intree[200001];
void add(int x,int y,int z)
{
	tot++;
	target[tot]=y;
	pre[tot]=last[x];
	last[x]=tot;
	w[tot]=z;
}
void dfs(int x)
{
	for(int i=last[x];i;i=pre[i])
	{
		int to=target[i];
		if(!deep[to])
		{
			deep[to]=deep[x]+1;
			father[to][0]=x;
			zd[to][0]=w[i];
			dfs(to);
		}
	}
}
int query1(int x,int y)
{
	int ans=0;
	if(deep[x]<deep[y])swap(x,y);
	for(int k=20;k>=0;k--)if(deep[father[x][k]]>=deep[y])ans=max(ans,zd[x][k]),x=father[x][k];
	if(x==y)return ans;
	for(int k=20;k>=0;k--)if(father[x][k]!=father[y][k])ans=max(ans,max(zd[x][k],zd[y][k])),x=father[x][k],y=father[y][k];
	ans=max(ans,max(zd[x][0],zd[y][0]));
	return ans;
}
int query2(int x,int y)
{
	int ans=0,cans=0;
	if(deep[x]<deep[y])swap(x,y);
	for(int k=20;k>=0;k--)
		if(deep[father[x][k]]>=deep[y])
			cans=max(min(ans,zd[x][k]),max(cans,cd[x][k])),ans=max(ans,zd[x][k]),x=father[x][k];
	if(x==y)return cans;
	for(int k=20;k>=0;k--)
		if(father[x][k]!=father[y][k])
			cans=max(min(ans,zd[x][k]),max(cans,cd[x][k])),ans=max(ans,zd[x][k]),
			cans=max(min(ans,zd[y][k]),max(cans,cd[y][k])),ans=max(ans,zd[y][k]),
			x=father[x][k],y=father[y][k];
	cans=max(min(ans,zd[x][0]),max(cans,cd[x][0])),ans=max(ans,zd[x][0]),
	cans=max(min(ans,zd[y][0]),max(cans,cd[y][0])),ans=max(ans,zd[y][0]);
	return cans;
}
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout); 
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].s,&e[i].t,&e[i].w);
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		int s=e[i].s,t=e[i].t,c=e[i].w;
		if(find(s)!=find(t))fa[find(s)]=find(t),ans+=1ll*c,add(s,t,c),add(t,s,c),intree[i]=1;
	}
	deep[1]=1;
	dfs(1);
	for(int k=1;k<=20;k++)
		for(int i=1;i<=n;i++)
		{
			father[i][k]=father[father[i][k-1]][k-1];
			zd[i][k]=max(zd[i][k-1],zd[father[i][k-1]][k-1]);
			cd[i][k]=max(min(zd[i][k-1],zd[father[i][k-1]][k-1]),max(cd[i][k-1],cd[father[i][k-1]][k-1]));
			//printf("%d %d %d\n",i,k,father[i][k]);
		}
	int delta=1e9;
	for(int i=1;i<=m;i++)
	{
		if(intree[i])continue;
		int s=e[i].s,t=e[i].t,c=e[i].w,maxx=query1(s,t);
		
		if(maxx!=c)delta=min(delta,c-maxx);
		else
		{
			maxx=query2(s,t);
			delta=min(delta,c-maxx);
		}
	}
	printf("%lld\n",ans+delta);
	return 0;
}
