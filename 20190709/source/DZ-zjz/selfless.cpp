#include<iostream>
#include<cstdio>
#define regin register int
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;
int n,m;
int ans=500000000,sum;
struct edg
{
	int u,v,c;
} eg[201000];

bool comp(edg a,edg b)
{
	return a.c<b.c;
}

bool v[201000];
int fa[101000];
inline int get(int a)
{
	return fa[a]==a? a:fa[a]=get(fa[a]);
}

int tot,head[101000],nex[201000],ver[201000],edge[201000];
inline void add(int a,int b,int c)
{
	ver[++tot]=b;nex[tot]=head[a];edge[tot]=c;head[a]=tot;
}

int d[101000],father[101000][20],mx[101000][20],me[101000][20];
inline void dfs(int s,int f)
{
	//cout<<f<<"	"<<s<<endl;
	for(regin i=head[s];i;i=nex[i])
	{
		if(ver[i]==f) continue;
		int y=ver[i],z=edge[i];
		d[y]=d[s]+1;
		father[y][0]=s;
		mx[y][0]=z;
		dfs(ver[i],s);
	}
}

inline int lca(int a,int b)
{
	if(d[a]<d[b]) swap(a,b);
	for(regin i=19;i>=0;i--)
	{
		if(d[father[a][i]]>=d[b]) a=father[a][i];
	}
	if(a==b) return a;
	for(regin i=19;i>=0;i--)
	{
		if(father[a][i]!=father[b][i]) a=father[a][i],b=father[b][i];
	}
	return father[a][0];
}

inline int qmax(int x,int y,int z)
{
	int an=0;
	for(regin i=19;i>=0;i--)
	{
		if(d[father[x][i]]>=d[y])
		{
			if(z==mx[x][i]) an=max(an,me[x][i]);
			else an=max(an,mx[x][i]);
			x=father[x][i];
		}
	}
	return an;
}
int main ()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(regin i=1;i<=n;i++) fa[i]=i;
	for(regin i=1;i<=m;i++)
	{
		scanf("%d%d%d",&eg[i].u,&eg[i].v,&eg[i].c);
	}
	sort(eg+1,eg+1+m,comp);
	int k=0;
	for(regin i=1;i<=m;i++)
	{
		if(k==n-1) break;
		int x=get(eg[i].u),y=get(eg[i].v);
		if(x==y) continue;
		k++;
		fa[x]=y;
		v[i]=1;
		sum+=eg[i].c;
		add(eg[i].u,eg[i].v,eg[i].c);
		add(eg[i].v,eg[i].u,eg[i].c);
	}
	//cout<<sum<<endl;
	d[1]=1;
	dfs(1,0);
	for(regin i=1;i<=19;i++)
	{
		for(regin j=1;j<=n;j++)
		{
			father[j][i]=father[father[j][i-1]][i-1];
			int ff=father[j][i-1];
			mx[j][i]=max(mx[j][i-1],mx[ff][i-1]);
			if(mx[j][i-1]>mx[ff][i-1]) me[j][i]=max(me[j][i],mx[ff][i-1]);
			else if(mx[j][i-1]<mx[ff][i-1]) me[j][i]=max(me[j][i],mx[j][i-1]);
		}
	}
	for(regin i=1;i<=m;i++)
	{
		if(v[i]) continue;
		int x=eg[i].u,y=eg[i].v,z=eg[i].c;
		int lc=lca(x,y);
		//cout<<x<<"	"<<y<<"		"<<lc<<endl;
		int m1=qmax(x,lc,z),m2=qmax(y,lc,z);
		ans=min(ans,sum+eg[i].c-max(m1,m2));
		//cout<<eg[i].c<<"	"<<m1<<"	"<<m2<<"	"<<ans<<endl;
	}
	printf("%d\n",ans);
	return 0;
}
