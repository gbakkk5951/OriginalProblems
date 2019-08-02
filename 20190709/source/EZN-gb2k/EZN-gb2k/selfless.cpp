#include<cstdio>
#include<cstring>
#include<algorithm>
#define ls ch[0][k]
#define rs ch[1][k]
#define which(k) (ch[1][fa[k]]==k)
#define isroot(k) (ch[0][fa[k]]!=k&&ch[1][fa[k]]!=k)
int read()
{
    char ch=getchar();
    int x=0;
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
int Max(int x,int y)
{
    return x>y?x:y;
}
int ch[2][401000],fa[401000];
int key[401000],sum[401000],lazy[401000];
void pushdown(int k)
{
    if(lazy[k])
    {
        lazy[k]=0;
        int tmp=ls;
        ls=rs;
        rs=tmp;
        lazy[ls]^=1;
        lazy[rs]^=1;
    }
}
void maintain(int k)
{
    sum[k]=Max(Max(sum[ls],key[k]),sum[rs]);
}
void Rotate(int k)
{
    int y=fa[k];
    if(!isroot(y))
        ch[which(y)][fa[y]]=k;
    bool d=which(k);
    fa[k]=fa[y];
    fa[y]=k;
    ch[d][y]=ch[!d][k];
    fa[ch[d][y]]=y;
    ch[!d][k]=y;
    maintain(y);
    maintain(k);
}
int stk[401000],tp=0;
void splay(int k)
{
    while(!isroot(k))
    {
        stk[++tp]=k;
        k=fa[k];
    }
    stk[++tp]=k;
    int qaq=fa[k];
    while(tp)
        pushdown(stk[tp--]);
    k=stk[1];
    while(fa[k]!=qaq)
    {
        int y=fa[k];
        if(!isroot(y))
            Rotate(which(k)^which(y)?k:y);
        Rotate(k);
    }
}
void access(int k)
{
    for(register int x=k,y=0;x;y=x,x=fa[x])
    {
        splay(x);
        ch[1][x]=y;
        maintain(x);
    }
}
void makeroot(int k)
{
    access(k);
    splay(k);
    lazy[k]^=1;
}
int getroot(int k)
{
    access(k);
    splay(k);
    while(ls)
        k=ls;
    return k;
}
void split(int x,int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y)
{
    makeroot(x);
    fa[x]=y;
}
int Find(int k,int x)
{
    int tmp=0;
    if(key[k]<x)
        tmp=key[k];
    if(sum[ls]<x)
        tmp=tmp>sum[ls]?tmp:sum[ls];
    else
    {
        int y=Find(ls,x);
        tmp=tmp>y?tmp:y;
    }
    if(sum[rs]<x)
        tmp=tmp>sum[rs]?tmp:sum[rs];
    else
    {
        int y=Find(rs,x);
        tmp=tmp>y?tmp:y;
    }
    return tmp;
}
struct edge
{
    int x,y,w;
    friend bool operator <(edge a,edge b)
    {
        return a.w<b.w;
    }
}e[300100];
bool used[300100];
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	int n,m;
    long long Sum=0,ans=1e18;
    n=read();
    m=read();
    for(int i=1;i<=m;++i)
    {
        e[i].x=read();
        e[i].y=read();
        e[i].w=read();
    }
    std::sort(e+1,e+1+m);
    for(int i=1;i<=m;++i)
    {
        key[n+i]=sum[n+i]=e[i].w;
        makeroot(e[i].x);
        if(getroot(e[i].y)!=e[i].x)
        {
            used[i]=1;
            link(e[i].x,n+i);
            link(e[i].y,n+i);
            Sum+=e[i].w;
        }
    }
    for(int i=1;i<=m;++i)
        if(!used[i])
        {
            split(e[i].x,e[i].y);
            int t=Find(e[i].y,e[i].w);
            ans=ans<Sum+key[n+i]-t?ans:Sum+key[n+i]-t;
        }
    printf("%lld\n",ans);
    return 0;
}
