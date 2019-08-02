//
//  main.cpp
//  selfless
//
//  Created by gengyf on 2019/7/9.
//  Copyright ? 2019 yifan Geng. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
#define M 200010
#define inf 2147483647000
struct edge1{
    int u,v;
    ll w;
}e1[M];
struct edge2{
    int from,to,nxt;
    ll dis;
}e2[N*2];
int head[N],f[N],deep[N];
int fa[N][20];
ll maxx[N][20],minn[N][20];
bool check[M];
int n,m,cnt;
ll tot,ans=inf;
bool cmp(edge1 x,edge1 y){
    return x.w<y.w;
}
inline void add(int from,int to,ll w){
    e2[++cnt].to=to;e2[cnt].dis=w;e2[cnt].nxt=head[from];head[from]=cnt;
}
inline int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
inline void kruskal(){
    sort(e1+1,e1+m+1,cmp);
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=m;i++){
        int u=find(e1[i].u);
        int v=find(e1[i].v);
        ll w=e1[i].w;
        if(u!=v){
            f[u]=v;tot+=w;
            add(e1[i].u,e1[i].v,w);add(e1[i].v,e1[i].u,w);
            check[i]=1;
        }
    }
}
inline void dfs(int x,int f){
    fa[x][0]=f;
    for(int i=head[x];i;i=e2[i].nxt){
        int y=e2[i].to;
        if(y!=f){
            deep[y]=deep[x]+1;
            maxx[y][0]=e2[i].dis;
            minn[y][0]=-inf;
            dfs(y,x);
        }
    }
}
inline void calc(){
    for(int i=1;i<=20;i++)
        for(int j=1;j<=n;j++){
            int k=fa[j][i-1];
            fa[j][i]=fa[k][i-1];
            maxx[j][i]=max(maxx[j][i-1],maxx[k][i-1]);
            minn[j][i]=min(minn[j][i-1],minn[k][i-1]);
            if(maxx[j][i-1]>maxx[k][i-1])minn[j][i]=max(minn[j][i],maxx[k][i-1]);
            else if(maxx[j][i-1]<maxx[k][i-1])minn[j][i]=max(minn[j][i],maxx[j][i-1]);
        }
}
inline int lca(int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    for(int i=20;i>=0;i--){
        if(deep[fa[y][i]]>=deep[x])
            y=fa[y][i];
    }
    if(x==y)return x;
    for(int i=20;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
ll qmax(int x,int y,ll w){
    ll tmp=-inf;
    for(int i=20;i>=0;i--){
        if(deep[fa[x][i]]>=deep[y]){
            if(w!=maxx[x][i])tmp=max(tmp,maxx[x][i]);
            else tmp=max(tmp,minn[x][i]);
            x=fa[x][i];
        }
    }
    return tmp;
}
int main() {
    freopen("selfless.in", "r", stdin);
    freopen("selfless.out", "w", stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%lld",&e1[i].u,&e1[i].v,&e1[i].w);
    }
    kruskal();
    minn[1][0]=-inf;
    deep[1]=1;
    dfs(1,0);calc();
    for(int i=1;i<=m;i++){
        if(!check[i]){
            int u=e1[i].u,v=e1[i].v,z=lca(u,v);
            ll w=e1[i].w,maxu=qmax(u,z,w),maxv=qmax(v,z,w);
            ans=min(ans,tot-max(maxu,maxv)+w);
        }
    }
    printf("%lld",ans);
    fclose(stdin);fclose(stdout);
    return 0;
}
