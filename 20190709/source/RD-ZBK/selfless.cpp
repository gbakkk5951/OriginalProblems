#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+50;
int n,m,fa[N],ver[N*2],edge[N*2],nxt[N*2],head[N],tot,d[N],f[18][N],ma[18][N],ma2[18][N],ans=1e9,sum=0;
struct node{
	int x,y,z;bool flag;
	void init(){scanf("%d%d%d",&x,&y,&z);}
	bool friend operator <(node a,node b){return a.z<b.z;}
}e[2*N];
void add(int x,int y,int z){ver[++tot]=y;edge[tot]=z;nxt[tot]=head[x];head[x]=tot;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void change(int &m1,int &m2,int mm1,int mm2){
	if(mm1>m1)m1=mm1;
	else if(mm1!=m1&&mm1>m2)m2=mm1;
	if(mm2!=m1&&mm2>m2)m2=mm2;
}
void pre(int x,int fa){
	d[x]=d[fa]+1;
	for(int i=1;i<18;i++){
		int y=f[i-1][x];
		f[i][x]=f[i-1][y];
		ma[i][x]=ma[i-1][x];ma2[i][x]=ma2[i-1][x];
		change(ma[i][x],ma2[i][x],ma[i-1][y],ma2[i-1][y]);
	}
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa)continue;
		ma[0][y]=edge[i];f[0][y]=x;
		pre(y,x);
	}
}
int ask(int x,int y,int z){
	if(d[x]<d[y])swap(x,y);
	int maxn=-5e8,maxn2=-1e9;
	for(int i=17;i>=0;i--)if(d[x]-(1<<i)>=d[y]){
		change(maxn,maxn2,ma[i][x],ma2[i][x]);
		x=f[i][x];
	}
	if(x==y){
		if(maxn<z)return z-maxn;
		return z-maxn2;
	}
	for(int i=17;i>=0;i--)if(f[i][x]!=f[i][y]){
		change(maxn,maxn2,ma[i][x],ma2[i][x]);
		change(maxn,maxn2,ma[i][y],ma2[i][y]);
		x=f[i][x];y=f[i][y];
	}
	change(maxn,maxn2,ma[0][x],ma2[0][x]);
	change(maxn,maxn2,ma[0][y],ma2[0][y]);
	if(maxn<z)return z-maxn;
	return z-maxn2;
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)e[i].init();
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++){
		int x=e[i].x,y=e[i].y,z=e[i].z;
		int fx=find(x),fy=find(y);
		if(fx==fy)continue;
		fa[fx]=fy;e[i].flag=1;sum+=e[i].z;
		add(x,y,z);add(y,x,z);
	}
	memset(ma2,0xcf,sizeof(ma2));
	pre(1,0);
	for(int i=1;i<=m;i++)
		if(!e[i].flag)ans=min(ans,ask(e[i].x,e[i].y,e[i].z));
	printf("%d\n",sum+ans);
	return 0;
}
