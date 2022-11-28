#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define R register int
const int N=100005,M=400005;
using namespace std;
typedef long long LL;
struct line{
    int l, r, w;
}l[(M)/2];
struct edge{
    int to,w,next;
}e[M];
int n,m,num,top,lca,tmp;int st[N],p[N],d[N],flag[N],used[M];int fa[N][18], maxs[N][18], mini[N][18];LL ans, sum;
inline int g(){
	int x=0;char p=getchar();
	while(p<'0'||p>'9')p=getchar();
	while(p>='0'&&p<='9')x=x*10+p-'0',p=getchar();
	return x; 
}
inline bool cmp(line a, line b){return a.w < b.w;}
inline void add(int x, int y, int z){e[++num].to = y;e[num].w = z;e[num].next = p[x];p[x] = num;}
inline int find(int x){
    st[++top]=x;while(x!=fa[x][0])st[++top]=(x=fa[x][0]);
    while(top)fa[st[top--]][0]=x;
    return x;
}
void init(){n=g(),m=g();for(R i=1;i<=m;++i)l[i].l=g(),l[i].r=g(),l[i].w=g();}
void kruskal(){
    int x,y,fx,fy;sort(l+1,l+m+1,cmp);
    for (int i=1;i<=n;++i)fa[i][0]=i;
    for(R i=1;i<=m;++i){
        x=l[i].l,y=l[i].r;fx=find(x),fy=find(y);
        if(fx==fy)continue;fa[fx][0]=fy;add(x,y,l[i].w),add(y,x,l[i].w);
        used[i]=1;sum+=l[i].w;
    }
}
void bfs(){
    fa[1][0]=0;queue<int>q;q.push(1);flag[1]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(R i=p[x];i;i= e[i].next){
            int k=e[i].to;
            if (!flag[k]){flag[k]=1;d[k]=d[x]+1;fa[k][0]=x;maxs[k][0]=e[i].w;q.push(k);}
        }
    }
}
void pre_work(){
    for(R i=1;i<=17;++i)
    	for(R j=1;j<=n;++j)
    		if(d[j]>=(1<<i)){
        		fa[j][i]=fa[fa[j][i-1]][i-1];maxs[j][i]=max(maxs[j][i-1],maxs[fa[j][i-1]][i-1]);mini[j][i]=max(mini[j][i-1], mini[fa[j][i-1]][i-1]);
        		if (maxs[j][i-1]>maxs[fa[j][i-1]][i-1]&&mini[j][i]<maxs[fa[j][i-1]][i-1])mini[j][i]=maxs[fa[j][i-1]][i-1];
        		else if(maxs[j][i-1]<maxs[fa[j][i-1]][i-1]&&mini[j][i]<maxs[j][i-1])mini[j][i]=maxs[j][i-1];
    }
}
inline int get(int x,int y,int last){
    if (d[x]>d[y])swap(x,y);int l=x, r=y,now=0;
    for(R mid=d[y]-d[x],i=0;mid;++i,mid>>=1)
    if(mid&1)r=fa[r][i];
	if(l==r)lca=l;
    else{
        for(R i=17;i>= 0;i--){if(fa[l][i]==fa[r][i])continue;l=fa[l][i],r=fa[r][i];}
        lca = fa[r][0];
    }
    l=x,r=y;
    for(R i=17;i>=0;i--){
        if(d[l]-d[lca]>=(1<<i)){
            if(maxs[l][i]!=last)now=max(now,maxs[l][i]);
            else now=max(now, mini[l][i]);l=fa[l][i];
        }
        if(d[r]-d[lca]>=(1<<i)){
            if(maxs[r][i]!=last)now=max(now,maxs[r][i]);
            else now=max(now,mini[r][i]);
	r=fa[r][i];
        }
    }
    return now;
}
inline void solve(){
    kruskal();bfs();pre_work();
    for(R i = 1;i <= m;++i)
    if(!used[i]){
        tmp=get(l[i].l,l[i].r,l[i].w);
        if(ans==0&&tmp!=l[i].w)ans=sum-tmp+l[i].w;
        if(tmp<l[i].w &&sum-tmp+l[i].w<ans)ans=sum-tmp+l[i].w;
    }
    printf("%lld\n", ans);
}
signed main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out",'w',stdout);
    init();solve();fclose(stdout);return 0;
}
