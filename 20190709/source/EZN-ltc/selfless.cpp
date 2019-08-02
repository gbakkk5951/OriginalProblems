#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

inline int read(){
	int x=0,f=1;
	char p=getchar();
	while(!isdigit(p)){
		if(p=='-') f=-1;
		p=getchar();
	}
	while(isdigit(p)) x=(x<<3)+(x<<1)+p-48,p=getchar();
	return x*f;
}

const int maxn=100005,inf=1000000000;

int head[maxn],ver[maxn<<1],nxt[maxn<<1],val[maxn<<1],f[maxn],tag[maxn];
int fa[maxn][20],mini[maxn][20],maxi[maxn][20],CNT,ans,n,m,dep[maxn],tot;
struct node{
	int x,y,z;
}edge[maxn<<1];

inline int find(int x){
	if(f[x]==x) return x;
	else return f[x]=find(f[x]);
}

inline bool cmp(node a,node b){
	return a.z<b.z;
}

inline void add(int x,int y,int z){
	nxt[++tot]=head[x];
	head[x]=tot;
	ver[tot]=y;
	val[tot]=z;
}

inline void dfs(int x,int par){
	fa[x][0]=par;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==par) continue;
		dep[y]=dep[x]+1;
		maxi[y][0]=val[i];
		mini[y][0]=-inf;
		dfs(y,x);
	}
}

inline void cal(){
	for(int j=1;j<=18;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
			maxi[i][j]=max(maxi[i][j-1],maxi[fa[i][j-1]][j-1]);
			mini[i][j]=max(mini[i][j-1],mini[fa[i][j-1]][j-1]);
			if(maxi[i][j-1]>maxi[fa[i][j-1]][j-1]) mini[i][j]=max(mini[i][j],maxi[fa[i][j-1]][j-1]);
			else if(maxi[i][j-1]<maxi[fa[i][j-1]][j-1]) mini[i][j]=max(mini[i][j],maxi[i][j-1]);
		}
	}
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=18;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=18;i>=0;i--){
		if(fa[x][i]!=fa[y][i]) 
			x=fa[x][i],y=fa[y][i];
	} 
	return fa[x][0];
}

inline int qmax(int x,int y,int z){
	int ans=-inf;
	for(int i=18;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y]){
			if(maxi[x][i]!=z) ans=max(ans,maxi[x][i]);
			else ans=max(ans,mini[x][i]);
		}
	}
	return ans;
}

signed main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		edge[i].x=read();edge[i].y=read();edge[i].z=read();
	}
	sort(edge+1,edge+1+m,cmp);
	for(int i=1;i<=m;i++){
		int x=edge[i].x,y=edge[i].y,z=edge[i].z;
		if(find(x)==find(y)) continue;
		tag[i]=1;
		f[find(x)]=find(y);
		CNT+=z;
		add(x,y,z);add(y,x,z);
	}
	dep[1]=1;
	mini[1][0]=-inf;
	dfs(1,0);
	cal();
	ans=inf;
	for(int i=1;i<=m;i++){
		if(tag[i]) continue;
		int x=edge[i].x,y=edge[i].y,z=edge[i].z;
		int LCA=lca(x,y);
		int maxx=qmax(x,LCA,z);
		int maxy=qmax(y,LCA,z);
		ans=min(ans,CNT-max(maxx,maxy)+z);
	} 
	cout<<ans<<endl;
	return 0;
}
