#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;
#define inf 2333333333333333;
const int M=2e5+5;
const int N=1e5+5;
int n,m,last[N],cnt,fa[N],deep[N],t;bool pd[N];
struct node{
	int from,to,nxt;
	long long dis;
}E[M],edge[M<<1];
bool cmp(node a,node b){
	return a.dis<b.dis;
}
int get(int x){
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
void add(int from,int to,long long dis){
	edge[++cnt].from=from;edge[cnt].to=to;edge[cnt].dis=dis;edge[cnt].nxt=last[from];last[from]=cnt;
}
struct nod{
	int fa;
	long long maxx,minn;
}f[N][19];
void dfs(int x,int fa){
	f[x][0].fa=fa;
	for(int i=last[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(y==fa) continue ;
		f[y][0].fa=x;f[y][0].maxx=edge[i].dis;
		f[y][0].minn=-inf;
		deep[y]=deep[x]+1;
		dfs(y,x);
	}
}
void cal(){
	for(int i=1;i<=t;i++){
		for(int j=1;j<=n;j++){
			f[j][i].fa=f[f[j][i-1].fa][i-1].fa;
			f[j][i].maxx=max(f[j][i-1].maxx,f[f[j][i-1].fa][i-1].maxx);
			f[j][i].minn=max(f[j][i-1].minn,f[f[j][i-1].fa][i-1].minn);
			if(f[j][i-1].maxx>f[f[j][i-1].fa][i-1].maxx) f[j][i].minn=max(f[j][i].minn,f[f[j][i-1].fa][i-1].maxx);
			else if(f[j][i-1].maxx<f[f[j][i-1].fa][i-1].maxx) f[j][i].minn=max(f[j][i].minn,f[j][i-1].maxx);
		}
	}
}
int lca(int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=t;i>=0;i--){
		if(deep[f[x][i].fa]>=deep[y]) x=f[x][i].fa;
	}
	if(x==y) return x;
	for(int i=t;i>=0;i--){
		if(f[x][i].fa!=f[y][i].fa){
			x=f[x][i].fa;y=f[y][i].fa;
		}
	}
	return f[x][0].fa;
}
long long query(int x,int y,long long dis){
	long long ans=-inf;
	for(int i=t;i>=0;i--){
		if(deep[f[x][i].fa]>=deep[y]){
			if(dis!=f[x][i].maxx) ans=max(ans,f[x][i].maxx);
			else ans=max(ans,f[x][i].minn);
			x=f[x][i].fa;
		}
	}
	return ans;
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);
	t=log(n)/log(2)+1;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&E[i].from,&E[i].to,&E[i].dis);
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	sort(E+1,E+1+m,cmp);
	long long ans=0;
	for(int i=1;i<=m;i++){
		int x=get(E[i].from),y=get(E[i].to),dis=E[i].dis;
		if(x==y) continue ;
		fa[x]=y;
		ans+=dis;
		pd[i]=1;
		add(E[i].to,E[i].from,dis);
		add(E[i].from,E[i].to,dis);
	}
	f[1][0].minn=-inf;
	deep[1]=1;
	dfs(1,-1);
	cal();
	long long res=inf;
	for(int i=1;i<=m;i++){
		if(!pd[i]){
			int x=E[i].from,y=E[i].to,anc=lca(x,y);
			long long dis=E[i].dis;
			long long maxx=query(x,anc,dis),maxy=query(y,anc,dis);
			res=min(res,ans-max(maxx,maxy)+dis);
		}
	}
	printf("%lld\n",res);
}
