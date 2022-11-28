#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1e5+7;
const int N2 = 1e4+7;
int n,m;
struct data
{
    int u,v,w;
    bool vis;
} p[N];
vector<int>G[N];
int per[N],maxd[N2][N2];
bool cmp(data a,data b)
{
    return a.w < b.w;
}
int Union_Find(int x)
{
    return x == per[x] ? x: per[x] = Union_Find(per[x]);
}
void kruskal()
{
    sort(p,p+m,cmp);
    for(int i=0; i<=n; i++)
    {
        G[i].clear();
        G[i].push_back(i);
        per[i]=i;
    }
    long long sum=0,k=0;
    for(int i=0; i<m; i++)
    {
        if(k==n-1)  break;
        int x1=Union_Find(p[i].u),x2=Union_Find(p[i].v);
        if(x1!=x2)
        {
            k++;
            p[i].vis=1;
            sum+=p[i].w;
            int len_x1=G[x1].size();
            int len_x2=G[x2].size();
            for(int j=0; j<len_x1; j++)
                for(int k=0; k<len_x2; k++)
                    maxd[G[x1][j]][G[x2][k]]=maxd[G[x2][k]][G[x1][j]]=p[i].w;
            per[x1]=x2;
            for(int j=0; j<len_x1; j++)
                G[x2].push_back(G[x1][j]);
        }
    }
    long long  cisum=INF;
    for(int i=0; i<m; i++)
        if(!p[i].vis)
            cisum = min(cisum, sum+p[i].w - maxd[p[i].u][p[i].v]);
    printf("%lld\n",cisum);
}
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++)
    {
        scanf("%d %d %d",&p[i].u,&p[i].v,&p[i].w);
        p[i].vis = false;
    }
    kruskal();
    return 0;
}
