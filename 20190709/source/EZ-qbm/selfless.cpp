#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
#define N 400040
#define M 900090
#define ll long long
using namespace std;
struct node{
	ll u,v,w;
	ll next;
}g[N<<1],a[M<<1];
ll n,m,tot,head[N],bz[N][19],maxx[N][19],minn[N][19],deep[N],fa[N];
bool v[M<<1],b[M<<1];
inline bool cmp(node x,node y){
    return x.w<y.w;
}
inline void dfs(ll u,ll fa){
	bz[u][0]=fa;
	for(ll i=head[u];i;i=g[i].next){
		ll v=g[i].v;
		if(v==fa) continue;
		deep[v]=deep[u]+1ll;
		maxx[v][0]=g[i].w;
		minn[v][0]=-INF;
		dfs(v,u); 
	}
}
inline ll find(ll x){
	if(x!=fa[x])
	fa[x]=find(fa[x]);
	return fa[x];
}
inline void add(ll u,ll v,ll w){
	g[++tot].u=u,g[tot].v=v,g[tot].w=w;g[tot].next=head[u],head[u]=tot;
	g[++tot].u=v,g[tot].v=u,g[tot].w=w;g[tot].next=head[v],head[v]=tot;
}
inline void cal(){
	for(ll i=1;i<=18;i++)
	for(ll j=1;j<=n;j++){
		bz[j][i]=bz[bz[j][i-1]][i-1];
		maxx[j][i]=max(maxx[j][i-1],maxx[bz[j][i-1]][i-1]);
		minn[j][i]=max(minn[j][i-1],minn[bz[j][i-1]][i-1]);
		if(maxx[j][i-1]>maxx[bz[j][i-1]][i-1])
		minn[j][i]=max(minn[j][i],maxx[bz[j][i-1]][i-1]);
		else if(maxx[j][i-1]<maxx[bz[j][i-1]][i-1])
		minn[j][i]=max(minn[j][i],maxx[j][i-1]);
	}
}
inline ll LCA(ll x,ll y){
	if(deep[x]<deep[y]) swap(x,y);
	for(ll i=18;i>=0;i--)
	if(deep[bz[x][i]]>=deep[y])
	x=bz[x][i];
	if(x==y) return x;
	for(ll i=18;i>=0;i--)
	if(bz[x][i]^bz[y][i])
	x=bz[x][i],y=bz[y][i];
	return bz[x][0];
}
inline ll qmax(ll u,ll v,ll w){
	ll ans=-INF;
	for(ll i=18;i>=0;i--){
		if(deep[bz[u][i]]>=deep[v]){
			if(w!=maxx[u][i])
			ans=max(ans,maxx[u][i]);
			else
			ans=max(ans,minn[u][i]);
			u=bz[u][i];
		}
	}
	return ans;
}
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++)
	scanf("%lld%lld%lld",&a[i].u,&a[i].v,&a[i].w);
	sort(a+1,a+m+1,cmp);
	for(ll i=1;i<=n;i++) fa[i]=i;
	ll cnt=0ll;
	for(ll i=1;i<=m;i++){
		ll r1=find(a[i].u),r2=find(a[i].v);
		if(r1!=r2){
			cnt+=a[i].w;
			fa[r1]=r2;
			add(a[i].u,a[i].v,a[i].w);
			b[i]=true;
		}
	}
	minn[1][0]=-INF;
	deep[1]=1;
	dfs(1,-1);
	cal();
	ll ans=INF;
	for(ll i=1;i<=m;i++){
		if(!b[i]){
		    ll u=a[i].u;
		    ll v=a[i].v;
		    ll w=a[i].w;
		    ll lca =LCA(u,v);
		    ll maxu=qmax(u,lca,w);
		    ll maxv=qmax(v,lca,w);
		    ans=min(ans,cnt-max(maxu,maxv)+w);
	    }
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
