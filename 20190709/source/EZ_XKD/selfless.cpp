#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=100009;
const int maxm=200009;
const ll INF=9999999999999999;
inline int read(){
	int ret=0,fix=1;char ch;
	while(!isdigit(ch=getchar()))fix=ch=='-'?-1:fix;
	do ret=(ret<<1)+(ret<<3)+ch-'0';
	while(isdigit(ch=getchar()));
	return ret*fix;
}
int n,m;
struct node{
	int u,v,nxt;
	ll w;
}t[maxm<<1],e[maxn<<1];
int head[maxn],cnt;
ll tot=0;
inline void add(int u,int v,ll w){
	e[++cnt].u=u;e[cnt].v=v;e[cnt].w=w;e[cnt].nxt=head[u];head[u]=cnt;
}
ll st[maxn][20],maxi[maxn][20],mini[maxn][20],dep[maxn];
void dfs(int x,int fa){
	st[x][0]=fa;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].v;
		if(y==fa)continue;
		dep[y]=dep[x]+1;
		maxi[y][0]=e[i].w;
		mini[y][0]=-INF;
		dfs(y,x);
	}
}
void cal(){
	for(int i=1;i<=18;i++)
	for(int j=1;j<=n;j++){
		st[j][i]=st[st[j][i-1]][i-1];
		maxi[j][i]=max(maxi[j][i-1],maxi[st[j][i-1]][i-1]);
		mini[j][i]=max(mini[j][i-1],mini[st[j][i-1]][i-1]);
		if(maxi[j][i-1]>maxi[st[j][i-1]][i-1])mini[j][i]=max(mini[j][i],maxi[st[j][i-1]][i-1]);
		else if(maxi[j][i-1]<maxi[st[j][i-1]][i-1])mini[j][i]=max(mini[j][i],maxi[j][i-1]);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=18;i>=0;i--)
	if(dep[st[x][i]]>=dep[y])x=st[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)
	if(st[x][i]!=st[y][i])x=st[x][i],y=st[y][i];
	return st[x][0];
}
ll qmax(int u,int v,int maxx){
	ll ans=-INF;
	for(int i=18;i>=0;i--){
		if(dep[st[u][i]]>=dep[v]){
			if(maxx!=maxi[u][i])ans=max(ans,maxi[u][i]);
			else ans=max(ans,mini[u][i]);
			u=st[u][i];
		}
	}
	return ans;
}
bool cmp(node a,node b){
	return a.w<b.w;
}
int fa[maxn];
inline int find(int x){
	while(x!=fa[x])x=fa[x]=fa[fa[x]];
	return x;	
}
bool b[maxm<<1];ll sum=0;
void kru(){
	sort(t+1,t+m+1,cmp);
	for(int i=1;i<=m;i++){
		int u=find(t[i].u),v=find(t[i].v);
		if(u==v)continue;
		sum+=t[i].w;
		fa[u]=v;
		add(t[i].u,t[i].v,t[i].w);
		add(t[i].v,t[i].u,t[i].w);
		b[i]=1;
	}
}
ll ans=INF;
void sol(){
	for(int i=1;i<=m;i++){
		if(b[i])continue;
		int u=t[i].u,v=t[i].v,w=t[i].w;
		int f=lca(u,v);
		ll maxu=qmax(u,f,w);
		ll maxv=qmax(v,f,w);
		ans=min(ans,sum-max(maxu,maxv)+w);
	}
	printf("%lld",ans);
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		t[i].u=read();t[i].v=read();t[i].w=read();	
	}
	kru();
	mini[1][0]=-INF;
	dep[1]=1;
	dfs(1,-1);
	cal();
	sol();
}
