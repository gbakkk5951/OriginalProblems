#include<cstdio>
#include<algorithm>
#define N 100005
#define int long long
using namespace std;
const int inf=0x7ffffffffffff-233;
int n,m,h[N],nxt[N],to[N],w[N],a,b,c,fath[N],fa[N][22],ans,delt=inf,cnt=1,rt,dep[N];
bool usd[N<<1];
int maxn[N][22],minn[N][22];
struct edge{
	int fro,to,len;
}e[N<<1];
bool cmp(edge a,edge b){
	return a.len<b.len;
}
inline void add(int u,int v,int ww){
	cnt++;
	nxt[cnt]=h[u];h[u]=cnt;to[cnt]=v;w[cnt]=ww;
	cnt++;
	nxt[cnt]=h[v];h[v]=cnt;to[cnt]=u;w[cnt]=ww;
}
int find(int x){return x==fath[x]?x:fath[x]=find(fath[x]);}
inline void kruskal(){
	for(int i=1;i<=m;i++){
		int u=e[i].fro,v=e[i].to;
		int f1=find(u),f2=find(v);
		if(f1^f2){
			rt=u;
			fath[f1]=f2;
			usd[i]=1;
			add(u,v,e[i].len);
			ans+=e[i].len;
		}
	}
}
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	for(int i=h[u];i;i=nxt[i]){
		int v=to[i];
		if(v!=f){
			maxn[v][0]=w[i];
			fa[v][0]=u;
			dfs(v,u);
		}
	}
}
inline void predown(){
	for(int i=1;(1<<i)<=n;i++){
		for(int j=1;j<=n;j++){
			fa[j][i]=fa[fa[j][i-1]][i-1];
			maxn[j][i]=max(maxn[j][i-1],maxn[fa[j][i-1]][i-1]);
			minn[j][i]=max(minn[j][i-1],minn[fa[j][i-1]][i-1]);
			if(maxn[j][i-1]<maxn[fa[j][i-1]][i-1]){
				minn[j][i]=max(maxn[j][i-1],minn[j][i]);
			}
			else if(maxn[j][i-1]>maxn[fa[j][i-1]][i-1]){
				minn[j][i]=max(maxn[fa[j][i-1]][i-1],minn[j][i]);
			}
		}
	}
}
inline int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	}
	if(x==y)return x;
	for(int i=19;i>=0;i--){
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i],y=fa[y][i];
		}
	}
	return fa[x][0];
}
void print(int u){
	for(int i=1;i<dep[u];i++)putchar('-');
	printf("%lld\n",u);
	printf("%lld\n",dep[u]);
	for(int i=0;(1<<i)<=dep[u];i++)
		printf("        %lld %lld %lld  \n",i,maxn[u][i],minn[u][i]);
	for(int i=h[u];i;i=nxt[i]){
		if(to[i]!=fa[u][0])print(to[i]);
	}
}
inline int get(int x,int goal,int lim){
	int anss=-1;
	for(int i=19;i>=0;i--){
		if(dep[fa[x][i]]>=dep[goal]){
			if(maxn[x][i]<lim)anss=max(anss,maxn[x][i]);
			else if(minn[x][i]<lim)anss=max(anss,minn[x][i]);
			x=fa[x][i];
		}
	}
	return anss;
}
#undef int
int main(){
	freopen("selfless.in","r",stdin);freopen("selfless.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)fath[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&e[i].fro,&e[i].to,&e[i].len);
	}
	sort(e+1,e+m+1,cmp);
	kruskal();
	dfs(rt,0);
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++){
			minn[j][i]=-inf;
		}
	}
	predown();
	for(int i=1;i<=m;i++){
		if(!usd[i]){
			long long u=e[i].fro,v=e[i].to;
			long long fff=lca(u,v);
			long long maxn=-inf;
			maxn=max(max(maxn,get(u,fff,e[i].len)),get(v,fff,e[i].len));
			delt=min(delt,e[i].len-maxn);
		}
	}
	printf("%lld",ans+delt);
	return 0;
}
/*
3 5
1 2 3
1 2 5
2 3 4
2 3 9
1 3 3
*/
/*
5 6
1 2 1 
1 3 2 
2 4 3 
3 5 4 
3 4 3 
4 5 6 
*/
