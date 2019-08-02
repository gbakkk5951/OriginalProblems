#include<bits/stdc++.h>
#define N 110000
#define M 201000
#define INF 2147483647000000
#define ll long long
using namespace std;
struct edge{
    ll u,v,d;
    ll nxt;
}e[M<<1],e1[M<<1];
bool b[M<<1];
ll tot=0,n,m;
ll head[M],fa[N];
ll f[N][20],maxi[N][20],mini[N][20],dep[N];
inline void read(ll &x){
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
}
inline void add(ll u,ll v,ll d){
    e[++tot].u=u,e[tot].v=v,e[tot].d=d,e[tot].nxt=head[u],head[u]=tot;
    e[++tot].u=v,e[tot].v=u,e[tot].d=d,e[tot].nxt=head[v],head[v]=tot;
}
inline void dfs(ll u,ll fa){
    f[u][0]=fa;
    for(ll i=head[u];i;i=e[i].nxt){
        ll v=e[i].v;
        if(v==fa)continue;
        dep[v]=dep[u]+1ll;
        maxi[v][0]=e[i].d;
        mini[v][0]=-INF;
        dfs(v,u);
    }
}
inline void cal(){
    for(ll i=1;i<20;++i)
        for(ll j=1;j<=n;++j){
            f[j][i]=f[f[j][i-1]][i-1];
            maxi[j][i]=max(maxi[j][i-1],maxi[f[j][i-1]][i-1]);
            mini[j][i]=max(mini[j][i-1],mini[f[j][i-1]][i-1]);
            if(maxi[j][i-1]>maxi[f[j][i-1]][i-1]) mini[j][i]=max(mini[j][i],maxi[f[j][i-1]][i-1]);
            else if(maxi[j][i-1]<maxi[f[j][i-1]][i-1]) mini[j][i]=max(mini[j][i],maxi[j][i-1]);
        }
}
inline ll LCA(ll x,ll y){
    if(dep[x]<dep[y])swap(x,y);
    for(ll i=19;i>=0;--i)
        if(dep[f[x][i]]>=dep[y])
            x=f[x][i];
    if(x==y) return x;
    for(ll i=19;i>=0;--i)
        if(f[x][i]^f[y][i])
            x=f[x][i],y=f[y][i];
    return f[x][0];
}
inline ll qmax(ll u,ll v,ll maxx){
    ll Ans=-INF;
    for(ll i=19;i>=0;--i){
        if(dep[f[u][i]]>=dep[v]){
            if(maxx!=maxi[u][i])Ans=max(Ans,maxi[u][i]);
            else Ans=max(Ans,mini[u][i]);
            u=f[u][i];
        }
    }
    return Ans;
}
inline bool cmp1(edge x,edge y){
    return x.d<y.d;
}
inline ll find(ll x){
    if(fa[x]==x) return fa[x];
    else return fa[x]=find(fa[x]);
}
int main()
{
    freopen("selfless.in","r",stdin);
    freopen("selfless.out","w",stdout);
    read(n),read(m);
    for(ll i=1;i<=m;++i)
        read(e1[i].u),read(e1[i].v),read(e1[i].d);
    sort(e1+1,e1+m+1,cmp1);
    for(ll i=1;i<=n;++i)
        fa[i]=i;
    ll cnt=0;
    for(ll i=1;i<=m;++i){
        ll Fu=find(e1[i].u);
        ll Fv=find(e1[i].v);
        if(Fu!=Fv){
            cnt+=e1[i].d;
            fa[Fu]=Fv;
            add(e1[i].u,e1[i].v,e1[i].d);
            b[i]=true;
        }
    }
    mini[1][0]=-INF;
    dep[1]=1;
    dfs(1,-1);
    cal();
    ll ans=INF;
    for(ll i=1;i<=m;++i){
        if(!b[i]){
            ll u=e1[i].u;
            ll v=e1[i].v;
            ll d=e1[i].d;
            ll lca=LCA(u,v);
            ll maxu=qmax(u,lca,d);
            ll maxv=qmax(v,lca,d);
            ans=min(ans,cnt-max(maxu,maxv)+d);
        }
    }
    printf("%lld\n",ans);
    // system("pause");
    return 0;
}