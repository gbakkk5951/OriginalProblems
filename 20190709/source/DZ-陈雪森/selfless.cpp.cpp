#include<iostream>
#include<algorithm>
#include<cstdio>
#define N 100010
#define M 400010
#define INF 2147483647000000
#define ll long long
using namespace std;
struct edge
{
    ll x,y,z,nxt;
}g[N<<1];
ll head[N],fa[N],tot,n,m;
ll bz[N][20],maxn[N][20],minn[N][20],deep[N];
inline void add(ll x,ll y,ll z)
{
    g[++tot].x=x,g[tot].y=y,g[tot].z=z,g[tot].nxt=head[x],head[x]=tot;
}
inline bool cmp(edge x,edge y)
{
    return x.z<y.z;
}
inline void dfs(ll u,ll fa)
{
    bz[u][0]=fa;
    for(ll i=head[u];i;i=g[i].nxt)
    {
        ll v=g[i].y;
        if(v==fa)continue;
        deep[v]=deep[u]+1;
        maxn[v][0]=g[i].z;
        minn[v][0]=-INF;
        dfs(v,u);
    }
}
inline void calc()
{
    for(ll i=1;i<=18;++i)
        for(ll j=1;j<=n;++j)
        {
            bz[j][i]=bz[bz[j][i-1]][i-1];
            maxn[j][i]=max(maxn[j][i-1],maxn[bz[j][i-1]][i-1]);
            minn[j][i]=max(minn[j][i-1],minn[bz[j][i-1]][i-1]);
            if(maxn[j][i-1]>maxn[bz[j][i-1]][i-1])
				minn[j][i]=max(minn[j][i],maxn[bz[j][i-1]][i-1]);
            else if(maxn[j][i-1]<maxn[bz[j][i-1]][i-1])
					minn[j][i]=max(minn[j][i],maxn[j][i-1]);
        }
}

inline ll LCA(ll x,ll y)
{
    if(deep[x]<deep[y])swap(x,y);
    for(ll i=18;i>=0;--i)
        if(deep[bz[x][i]]>=deep[y])
            x=bz[x][i];
    if(x==y)return x;
    for(ll i=18;i>=0;--i)
        if(bz[x][i]^bz[y][i])
            x=bz[x][i],y=bz[y][i];
    return bz[x][0];
}
inline ll qmax(ll x,ll y,ll maxx)
{
    ll ans=-INF;
    for(ll i=18;i>=0;--i)
    {
        if(deep[bz[x][i]]>=deep[y])
        {
            if(maxx!=maxn[x][i])
				ans=max(ans,maxn[x][i]);
            else ans=max(ans,minn[x][i]);
            x=bz[x][i];
        }
    }
    return ans;
}
edge a[M<<1];
inline ll get(ll x)
{
    if(x==fa[x])return x;
    return fa[x]=get(fa[x]);
}
bool v[M<<1];
int main()
{
    freopen("selfless.in","r",stdin);
    freopen("selfless.out","w",stdout);
	scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=m;++i)
        scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].z);
    sort(a+1,a+m+1,cmp);
    for(ll i=1;i<=n;++i)
        fa[i]=i;
    ll cnt=0;
    for(ll i=1;i<=m;++i)
    {
        ll x=get(a[i].x);
        ll y=get(a[i].y);
        if(x!=y)
        {
            cnt+=a[i].z;
            fa[x]=y;
            add(a[i].x,a[i].y,a[i].z);
            add(a[i].y,a[i].x,a[i].z);
            v[i]=true;
        }
    }
    minn[1][0]=-INF;
    deep[1]=1;
    dfs(1,-1);
    calc();
    ll ans=INF;
    for(ll i=1;i<=m;++i)
        if(!v[i])
        {
            ll x=a[i].x;
            ll y=a[i].y;
            ll z=a[i].z;
            ll lca=LCA(x,y);
            ll maxu=qmax(x,lca,z);
            ll maxv=qmax(y,lca,z);
            ans=min(ans,cnt-max(maxu,maxv)+z);
        }
    printf("%lld",ans);
    return 0;
}
