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
int maxn,cd=1e15+7;
int n,m,num,sum,res=1e15+7;
int f[200010],lg[200010],dep[200010];
int bz[100010][21],val[100010][21],cval[100010][21];
bool miao[500010];
int head[200010],cnt;
struct point 
{
	int nxt,to,val;
}e[500010],a[500010];
inline void add(int x,int y,int z)
{
	a[++cnt].nxt=head[x];
	a[cnt].to=y;
	a[cnt].val=z;
	head[x]=cnt;
}
inline int find(int k)
{
	if(f[k]==k) return k;
	return f[k]=find(f[k]);
}
inline bool cmp(point x,point y)
{
	return x.val<y.val;
}
inline void dfs(int now,int fa,int deep,int v)
{
	dep[now]=deep;
	bz[now][0]=fa;
	val[now][0]=v;
	for(int i=1;(1<<i)<=deep;++i)
	{
		bz[now][i]=bz[bz[now][i-1]][i-1];
		val[now][i]=max(val[now][i-1],val[bz[now][i-1]][i-1]);
		cval[now][i]=max(cval[now][i-1],cval[bz[now][i-1]][i-1]);
		if(val[now][i-1]>val[bz[now][i-1]][i-1])
			cval[now][i]=max(cval[now][i],val[bz[now][i-1]][i-1]);
		if(val[now][i-1]<val[bz[now][i-1]][i-1])
			cval[now][i]=max(cval[now][i],val[now][i-1]);
	}
	for(int i=head[now];i;i=a[i].nxt)
	{
		int t=a[i].to;
		if(t==fa) continue;
		dfs(t,now,deep+1,a[i].val);
	}
}
inline void query(int x,int y,int v)
{
	int ans=0;
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y])
	{
		int d=(dep[x]-dep[y]);
		if(v^val[x][lg[d]-1])
			ans=max(ans,val[x][lg[d]-1]);
		else
			ans=max(ans,cval[x][lg[d]-1]);
		x=bz[x][lg[d]-1];
	}
	if(x==y)
	{
		res=min(res,sum-ans+v);
		return ;
	}
	for(int i=lg[dep[x]];i>=0;--i)
	{
		if(bz[x][i]^bz[y][i])
		{
			int tx=(v^val[x][i])?val[x][i]:cval[x][i];
			int ty=(v^val[y][i])?val[y][i]:cval[y][i];
			ans=max(ans,max(tx,ty));
			x=bz[x][i],y=bz[y][i];
		}
	}
	int tx=(v^val[x][0])?val[x][0]:cval[x][0];
	int ty=(v^val[y][0])?val[y][0]:cval[y][0];
	ans=max(ans,max(tx,ty));
	res=min(res,sum-ans+v);
}
signed main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		e[i].nxt=read(),e[i].to=read(),e[i].val=read();
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;++i)	f[i]=i;
	for(int i=1;i<=200010;++i)	lg[i]=lg[i>>1]+1;
	for(int i=1;i<=m;++i)
	{
		int tx=find(e[i].nxt),ty=find(e[i].to);
		if(tx!=ty)
		{
			f[tx]=ty;
			sum+=e[i].val;
			maxn=max(maxn,e[i].val); 
			miao[i]=1;
			add(e[i].nxt,e[i].to,e[i].val);
			add(e[i].to,e[i].nxt,a[i].val); 
			if(++num==n-1) break;
		}
	}
	dfs(1,0,1,0);
	for(int i=1;i<=m;++i)
	{
		if(miao[i]) continue;
		if(e[i].val-maxn>=cd) break;
		query(e[i].nxt,e[i].to,e[i].val);
		cd=res-sum;
	}
	printf("%lld\n",res);
	fclose(stdin);fclose(stdout);
return 0;
}
