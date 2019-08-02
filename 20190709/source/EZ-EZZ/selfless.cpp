#include<bits/stdc++.h>
#define N 101000
#define M 201000
#define INF 2147483647000000
#define ll long long
using namespace std;
struct ziji{ll u,v,d,nxt;}G[N<<1],A[M<<1];ll cnt=0ll;
ll tot=0,head[N],n,m,Father[N],Ans=INF;bool B[M<<1];
inline void add(ll u,ll v,ll d){
    G[++tot].u=u,G[tot].v=v,G[tot].d=d,G[tot].nxt=head[u],head[u]=tot;
    G[++tot].u=v,G[tot].v=u,G[tot].d=d,G[tot].nxt=head[v],head[v]=tot;
}
ll bz[N][19],maxi[N][19],mini[N][19],deep[N];
inline void dfs(ll u,ll fa){
    bz[u][0]=fa;
    for(register ll i=head[u];i;i=G[i].nxt){
        ll v=G[i].v;if(v==fa)continue;
        deep[v]=deep[u]+1ll;maxi[v][0]=G[i].d;
        mini[v][0]=-INF;dfs(v,u);
    }
}
inline void cal(){
    for(register ll i=1;i<=18;i++){
        for(register ll j=1;j<=n;j++){
            bz[j][i]=bz[bz[j][i-1]][i-1];
            maxi[j][i]=max(maxi[j][i-1],maxi[bz[j][i-1]][i-1]);
            mini[j][i]=max(mini[j][i-1],mini[bz[j][i-1]][i-1]);
            if(maxi[j][i-1]>maxi[bz[j][i-1]][i-1])
                mini[j][i]=max(mini[j][i],maxi[bz[j][i-1]][i-1]);
            else if(maxi[j][i-1]<maxi[bz[j][i-1]][i-1])
                mini[j][i]=max(mini[j][i],maxi[j][i-1]);
        }
    }
}
inline ll LCA(ll x,ll y){
    if(deep[x]<deep[y]) swap(x,y);
    for(ll i=18;i>=0;--i)
        if(deep[bz[x][i]]>=deep[y]) x=bz[x][i];
    if(x==y)return x;
    for(ll i=18;i>=0;i--)
        if(bz[x][i]^bz[y][i]) x=bz[x][i],y=bz[y][i];
    return bz[x][0];
}
inline ll qmax(ll u,ll v,ll maxx){
    ll Ans=-INF;
    for(register ll i=18;i>=0;i--){
        if(deep[bz[u][i]]>=deep[v]){
            if(maxx!=maxi[u][i])Ans=max(Ans,maxi[u][i]);
            else Ans=max(Ans,mini[u][i]);
            u=bz[u][i];
        }
    }
    return Ans;
}
inline ll read(){
    ll x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
    return x;
}
inline bool cmp(ziji x,ziji y){return x.d<y.d;}
inline ll find(ll x){
    return (x==Father[x])?x:Father[x]=find(Father[x]);
}
int main(){
    freopen("selfless.in","r",stdin);
    freopen("selfless.out","w",stdout);
    n=read();m=read();
    for(register ll i=1;i<=m;i++)
        A[i].u=read(),A[i].v=read(),A[i].d=read();
    sort(A+1,A+m+1,cmp);
    for(register ll i=1;i<=n;i++) Father[i]=i;
    for(register ll i=1;i<=m;i++){
        ll root=find(A[i].u),root1=find(A[i].v);
        if(root!=root1)
            cnt+=A[i].d,Father[root]=root1,
            add(A[i].u,A[i].v,A[i].d),B[i]=true;
    }
    mini[1][0]=-INF;deep[1]=1;dfs(1,-1);cal();
    for(register ll i=1;i<=m;i++){
        if(!B[i]){
            ll u=A[i].u,v=A[i].v,d=A[i].d,lca=LCA(u,v),
            maxu=qmax(u,lca,d),maxv=qmax(v,lca,d);
            Ans=min(Ans,cnt-max(maxu,maxv)+d);
        }
    }
    printf("%lld",Ans);
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
