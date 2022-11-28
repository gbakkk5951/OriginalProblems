#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
using namespace std;
typedef long long lt;

lt read()
{
    lt f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=400010;
lt n,m,ans;
struct node{int u,v;lt dis;}edge[maxn];
struct node2{lt v,dis,nxt;}E[maxn];
int head[maxn],tot;
int fa[maxn];
bool judge[maxn];//判断是否是最小生成树的边
int gra[maxn][18],dep[maxn];
lt fir[maxn][18],sec[maxn][18];


bool cmp(node a,node b){return a.dis<b.dis;}

void add(int u,int v,lt dis)
{
    E[++tot].nxt=head[u];
    E[tot].v=v;
    E[tot].dis=dis;
    head[u]=tot; 
}

int find(int x)
{
    if(x==fa[x]) return x;
    else return fa[x]=find(fa[x]);
}

lt kruskal()
{
    int num=0; lt len=0;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int u=edge[i].u,v=edge[i].v;lt dis=edge[i].dis;
        int fu=find(u),fv=find(v);
        if(fu!=fv)
        {
            fa[fu]=fv;  judge[i]=true;
            num++;  len+=dis; 
            add(u,v,dis); add(v,u,dis);
            if(num==n-1) break; 
        } 
    }
    return len;
}

void dfs(int u,int pa)
{
    for(int i=head[u];i;i=E[i].nxt)
    {
        int v=E[i].v;
        if(v==pa) continue;
        dep[v]=dep[u]+1; gra[v][0]=u; 
        fir[v][0]=E[i].dis; sec[v][0]=-1e9;
        dfs(v,u);
    }
}

void work()
{
    for(int i=1;(1<<i)<=n;i++)
    for(int u=1;u<=n;u++)
    {
        gra[u][i]=gra[ gra[u][i-1] ][i-1];
        fir[u][i]=max(fir[u][i-1],fir[ gra[u][i-1] ][i-1]);
        sec[u][i]=max(sec[u][i-1],sec[ gra[u][i-1] ][i-1]);
        
        if(fir[u][i-1]>fir[ gra[u][i-1] ][i-1])
        sec[u][i]=max(fir[ gra[u][i-1] ][i-1],sec[u][i]);
        else if(fir[u][i-1]<fir[ gra[u][i-1] ][i-1])
        sec[u][i]=max(fir[u][i-1],sec[u][i]);
       
    }
}

int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    int d=dep[u]-dep[v];
    
    for(int i=0;(1<<i)<=d;i++)
    if((1<<i)&d) u=gra[u][i];
    
    if(u==v) return u;
    for(int i=(int)log(n);i>=0;i--)
    {
        if(gra[u][i]!=gra[v][i])
        u=gra[u][i],v=gra[v][i];
    }
    return gra[u][0];
}

lt qmax(int u,int v,lt dis)
{
    lt tp=-1e9;
    for(int i=1;(1<<i)<=n;i++)//倍增思想
    {
        
        if(dep[ gra[u][i] ]>=dep[v])
        {
            if(dis==fir[u][i]) tp=max(tp,sec[u][i]);
            else tp=max(tp,fir[u][i]);
        }
    }
    return tp;
}

int main()
{
    freopen("selfless.in","r",stdin);
    freopen("selfless.out","w",stdout);
	n=read();m=read();
    for(int i=1;i<=m;i++)
    edge[i].u=read(),edge[i].v=read(),edge[i].dis=read();
    
    sort(edge+1,edge+1+m,cmp);
    ans=kruskal();//先求最小生成树

    dfs(1,-1);
    work();
    
    lt add=1e9;
    for(int i=1;i<=m;i++)
    {
        if(judge[i])continue;
        int u=edge[i].u,v=edge[i].v;lt dis=edge[i].dis;
        int LCA=lca(u,v);
        lt maxu=qmax(u,LCA,dis);
        lt maxv=qmax(v,LCA,dis);
        add=min(add,dis-max(maxu,maxv));
    }
    
    cout<<ans+add;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

