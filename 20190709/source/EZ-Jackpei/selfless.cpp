#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
#define R register int
using namespace std;
#define ull unsigned long long
#define ll long long
#define pause (for(R i=1;i<=10000000000;++i))
#define IN freopen("NOIPAK++.in","r",stdin)
#define OUT freopen("out.out","w",stdout)
namespace Fread {
	static char B[1<<15],*S=B,*D=B;
#ifndef JACK
	#define getchar() (S==D&&(D=(S=B)+fread(B,1,1<<15,stdin),S==D)?EOF:*S++)
#endif
	inline int g() {
		R ret=0,fix=1; register char ch; while(!isdigit(ch=getchar())) fix=ch=='-'?-1:fix;
		if(ch==EOF) return EOF; do ret=ret*10+(ch^48); while(isdigit(ch=getchar())); return ret*fix;
	} inline bool isempty(const char& ch) {return (ch<=36||ch>=127);}
	inline void gs(char* s) {
		register char ch; while(isempty(ch=getchar()));
		do *s++=ch; while(!isempty(ch=getchar()));
	}
}using Fread::g; using Fread::gs; const int N=100010;
struct node{int u,v,w;bool operator <(const node & y) const { return w<y.w;}}a[600010];
struct edge{int v,w,nxt;}e[N<<2];
int n,m,cnt,mx,mmx,mn=0x3f3f3f3f,ans,tot; 
int fir[N],f[N][20],h[N][20][2],fa[N],d[N]; bool tr[N<<2];
inline void add(int u,int v,int w) {e[++cnt].v=v,e[cnt].nxt=fir[u],e[cnt].w=w,fir[u]=cnt;}
inline void ins(int u,int v,int w) {add(u,v,w),add(v,u,w);}
inline int getf(int x) {return x==fa[x]?x:fa[x]=getf(fa[x]);}
inline void dfs(int u,int fa) {
	for(R i=fir[u];i;i=e[i].nxt) {
		R v=e[i].v; if(v==fa) continue;
		f[v][0]=u,h[v][0][0]=e[i].w,d[v]=d[u]+1;
		for(R i=1;d[v]>=(1<<i);++i) {
			f[v][i]=f[f[v][i-1]][i-1]; 
			h[v][i][0]=max(h[v][i-1][0],h[f[v][i-1]][i-1][0]);
			//cout<<u<<" "<<f[u][0]<<endl;
			if(h[v][i-1][0]==h[f[v][i-1]][i-1][0]) 
				h[v][i][1]=max(h[v][i-1][1],h[f[v][i-1]][i-1][1]);
			else {
				h[v][i][1]=min(h[v][i-1][0],h[f[v][i-1]][i-1][0]);
				h[v][i][1]=max(h[v][i-1][1],h[v][i][1]);
				h[v][i][1]=max(h[v][i][1],h[f[v][i-1]][i-1][1]);
			}
		}
		dfs(v,u);
	}
}
inline int lca(int u,int v) {
	if(d[u]<d[v]) swap(u,v); R lim=log2(d[u])+1; 
	for(R j=lim;j>=0;--j) if(d[f[u][j]]>=d[v]) u=f[u][j];
	if(u==v) return u; 
	for(R j=lim;j>=0;--j) if(f[u][j]!=f[v][j]) u=f[u][j],v=f[v][j];
	return f[u][0];
}
inline void calc(int u,int fa,int w) {
	mx=0,mmx=0; R lim=log2(d[u]-d[fa])+1;
	for(R i=lim;i>=0;--i) if(d[u]-d[fa]>=(1<<i)){
		if(h[u][i][1]>mx) mmx=mx,mx=h[u][i][0];
		mx=max(h[u][i][0],mx); mmx=max(mmx,h[u][i][1]),u=f[u][i];
	} if(mx!=w) mn=min(mn,w-mx); else mn=min(mn,w-mmx);
}
signed main() {
	freopen("selfless.in","r",stdin); freopen("selfless.out","w",stdout);
	n=g(),m=g(); for(R i=1;i<=n;++i) fa[i]=i;
	for(R i=1;i<=m;++i) a[i].u=g(),a[i].v=g(),a[i].w=g();
	sort(a+1,a+m+1);
	for(R i=1;i<=m&&tot<n;++i) {
		R uf=getf(a[i].u),vf=getf(a[i].v);
		if(uf==vf) continue;
		fa[uf]=vf; ans+=a[i].w; tr[i]=true;
		ins(a[i].u,a[i].v,a[i].w); ++tot;
	}
	dfs(1,0); 
	for(R i=1;i<=m;++i) if(!tr[i]) {
		R L=lca(a[i].u,a[i].v); 
		calc(a[i].u,L,a[i].w);
		calc(a[i].v,L,a[i].w);
	} printf("%lld\n",ans+mn);
}
