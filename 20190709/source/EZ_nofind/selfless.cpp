#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int maxm=200010;
const int inf=5010;
struct Edge
{
	int u,v,w;
}E[maxm];
struct edge
{
	int to,nxt,dis;
}e[maxn<<1];
int n,m,cnt,tot,ans,t;
int head[maxn],f[maxn],dep[maxn];
int fa[maxn][30],maxx[maxn][30],minn[maxn][30];
bool check[maxm];
bool cmp(Edge a,Edge b){return a.w<b.w;}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void add(int u,int v,int w)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	e[cnt].dis=w;
}
void k()
{
	for(int i=1;i<=n;i++) f[i]=i;
	sort(E+1,E+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int x=E[i].u,y=E[i].v;
		if(find(x)==find(y)) continue;
		f[find(x)]=find(y);tot+=E[i].w;
		check[i]=1;add(x,y,E[i].w);add(y,x,E[i].w);
	}
}
void dfs(int x,int pre)
{
	fa[x][0]=pre;dep[x]=dep[pre]+1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==pre) continue;
		maxx[y][0]=e[i].dis;minn[y][0]=-inf;
		dfs(y,x);
	}
}
void calc()
{
	for(int i=1;i<=t;i++)
	{
		for(int x=1;x<=n;x++)
		{
			fa[x][i]=fa[fa[x][i-1]][i-1];
			maxx[x][i]=max(maxx[x][i-1],maxx[fa[x][i-1]][i-1]);
			minn[x][i]=max(minn[x][i-1],minn[fa[x][i-1]][i-1]);
			if(maxx[x][i-1]<maxx[fa[x][i-1]][i-1]) minn[x][i]=max(minn[x][i],maxx[x][i-1]);
			else if(maxx[x][i-1]>maxx[fa[x][i-1]][i-1]) minn[x][i]=max(minn[x][i],maxx[fa[x][i-1]][i-1]);
		}		
	}
}
int lca(int x,int y)
{
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=t;i>=0;i--) if(dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if(x==y) return x;
	for(int i=t;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int get(int x,int y,int w)
{
	int res=0;
	for(int i=t;i>=0;i--)
	{
		if(dep[fa[x][i]]>=dep[y]) 
		{
			if(maxx[x][i]!=w) res=max(res,maxx[x][i]);
			else res=max(res,minn[x][i]);
			x=fa[x][i];
		}
	}
	res=max(res,maxx[x][0]==w?minn[x][0]:maxx[x][0]);
	return res;
}
void solve()
{
	for(int i=1;i<=m;i++)
	{
		if(check[i]) continue;
		int x=E[i].u,y=E[i].v,z=lca(x,y);//printf("%d %d %d\n",x,y,z);
		int maxu=get(x,z,E[i].w),maxv=get(y,z,E[i].w);//printf("%d %d\n",maxu,maxv);
		ans=min(ans,tot-max(maxu,maxv)+E[i].w);
	}
	printf("%d",ans);
}
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);t=(int)log2(n)+1;ans=inf*n+10;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	k();
	maxx[1][0]=0,minn[1][0]=-inf;dfs(1,0);calc();
	solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
