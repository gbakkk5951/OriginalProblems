#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 300005
#define R register
using namespace std;
int n,m,ch[N][2],par[N],sta[N],rev[N],mx[N],cmx[N],fa[N],cnt;
int fi(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=fi(fa[x]);
}
long long ans=1926081719260817,sum;
struct ccf
{
	int to,fr,w;
}e[N];
bool cmp(ccf a,ccf b){return a.w<b.w;}
inline int rd()
{
	char p=getchar();int x=0;
	while(p>'9'||p<'0')p=getchar();
	while(p>='0'&&p<='9')x=x*10+p-'0',p=getchar();
	return x;
}
int chk(int x){return ch[par[x]][1]==x;}
int get(int x){return ch[par[x]][0]==x||ch[par[x]][1]==x;}
void filp(int x)
{
	swap(ch[x][0],ch[x][1]);
	rev[x]^=1;
}
int getmax(int a,int b){return e[a].w>e[b].w?a:b;}
void pushup(int x)
{
	int l=ch[x][0],r=ch[x][1];
	if(e[mx[l]].w>e[mx[r]].w)mx[x]=mx[l],cmx[x]=getmax(mx[r],cmx[l]);
	else if(e[mx[r]].w>e[mx[l]].w)mx[x]=mx[r],cmx[x]=getmax(mx[l],cmx[r]);
	else mx[x]=mx[l],cmx[x]=getmax(cmx[l],cmx[r]);
	if(e[x].w>e[mx[x]].w)cmx[x]=mx[x],mx[x]=x;
	else if(e[x].w!=e[mx[x]].w&&e[x].w>e[cmx[x]].w)cmx[x]=x;
}
void zhuan(int x)
{
	int y=par[x],z=par[y],k=chk(x),w=ch[x][k^1];
	if(get(y))ch[z][chk(y)]=x;
	ch[y][k]=w;ch[x][k^1]=y;
	if(w)par[w]=y;par[x]=z;par[y]=x;
	pushup(y);
}
void pushdown(int x)
{
	if(!rev[x])return;
	rev[x]=0;
	if(ch[x][0])filp(ch[x][0]);
	if(ch[x][1])filp(ch[x][1]);
}
void splay(int x)
{
	int y=x,top=0;sta[++top]=y;
	while(get(y))sta[++top]=y=par[y];
	while(top)pushdown(sta[top--]);
	while(get(x))
	{
		int y=par[x];
		if(get(y))
		{
			if(chk(x)==chk(y))zhuan(y);
			else zhuan(x);	
		}
		zhuan(x);
	}
	pushup(x);
}
inline void Access(int x)
{
	for(R int y=0;x;y=x,x=par[x])
	{
		splay(x);
		ch[x][1]=y;
		pushup(x);
	}
}
inline int findroot(int x)
{
	Access(x);
	splay(x);
	while(ch[x][0])pushdown(x),x=ch[x][0];
	splay(x);
	return x;
}
inline void makeroot(int x){Access(x);splay(x);filp(x);}
inline void split(int x,int y){makeroot(x);Access(y);splay(y);}
inline void link(int x,int y)
{
	makeroot(x);
	par[x]=y;
}
bool vis[N];
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	R int x,y,z;
	n=rd();m=rd();
	for(R int i=1;i<=n;i++)fa[i]=i;
	for(R int i=1;i<=m;i++)
	{
		x=rd();y=rd();z=rd();
		e[i+n].to=y;
		e[i+n].fr=x;
		e[i+n].w=z;
	}
	sort(e+n+1,e+n+m+1,cmp);
	for(R int i=1;i<=m;i++)
	{
		x=e[i+n].fr;y=e[i+n].to;
		if(fi(x)==fi(y))continue;
		fa[fi(x)]=fi(y);
		sum+=e[i+n].w;
		cnt++;
		link(x,i+n);link(i+n,y);
		vis[i]=true;
		if(cnt==n-1)break;
	}
	for(R int i=1;i<=m;i++)
	{
		if(vis[i])continue;
		x=e[i+n].fr;y=e[i+n].to;
		split(x,y);
		if(cmx[y]==0)continue;
		if(e[mx[y]].w==e[i+n].w)ans=min(sum+e[i+n].w-e[cmx[y]].w,ans);
		else ans=min(sum+e[i+n].w-e[mx[y]].w,ans);
	}
	printf("%lld\n",ans);
	return 0;
}
