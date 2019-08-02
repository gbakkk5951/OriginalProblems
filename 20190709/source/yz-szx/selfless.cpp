#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<cstring>
#include<queue>
#define rg register
using namespace std;
#define int long long
inline int read(){
	rg char ch=getchar();
	rg int x=0,f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int head[100010],ver[400010],nxt[400010],edge[400020],tot;
inline void add(int x,int y,int z){
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}
struct node{
	int x,y,val;
}a[100010];
int vis[100010],fa[100010];
int n,m;
int f[100010][20],maxn[100010][20],minn[100010][20],dep[100010];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool cmp(struct node &x,struct node &y){
	return x.val<y.val;
}
void dfs(int x){
	for(int i=1;i<=19;++i){
		f[x][i]=f[f[x][i-1]][i-1];
		maxn[x][i]=maxn[x][i-1];
		minn[x][i]=minn[x][i-1];
		if(maxn[f[x][i-1]][i-1]>maxn[x][i]) minn[x][i]=maxn[x][i],maxn[x][i]=maxn[f[x][i-1]][i-1];
		else if(maxn[f[x][i-1]][i-1]<maxn[x][i]) minn[x][i]=max(minn[x][i],maxn[f[x][i-1]][i-1]);
		minn[x][i]=max(minn[x][i],minn[f[x][i-1]][i-1]);
//		if(f[x][i])
//		cout<<x<<" "<<" "<<i<<" "<<f[x][i]<<" "<<maxn[x][i]<<" "<<minn[x][i]<<endl;
	}
	for(int y,i=head[x];i;i=nxt[i]){
		y=ver[i];
		if(y==f[x][0]) continue;
		f[y][0]=x;
		maxn[y][0]=edge[i];
		dep[y]=dep[x]+1;
		dfs(y);
	}
}
int query(int x,int y,int val){
//	cout<<x<<" "<<y<<endl;
	int ans=0;
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;~i;--i){
		if(dep[f[x][i]]>=dep[y]){
//			cout<<x<<" "<<f[x][i]<<" "<<maxn[x][i]<<" "<<minn[x][i]<<endl;
			if(maxn[x][i]<val) ans=max(ans,maxn[x][i]);
			else ans=max(ans,minn[x][i]);
			x=f[x][i];
		}
	}
	if(x==y) return ans;
	for(int i=19;~i;--i){
		if(f[x][i]!=f[y][i]){
			if(maxn[x][i]<val) ans=max(ans,maxn[x][i]);
			else ans=max(ans,minn[x][i]);
			if(maxn[y][i]<val) ans=max(ans,maxn[y][i]);
			else ans=max(ans,minn[y][i]);
			x=f[x][i];y=f[y][i];
		}
	}
	if(maxn[x][0]<val) ans=max(ans,maxn[x][0]);
	else ans=max(ans,minn[x][0]);
	if(maxn[y][0]<val) ans=max(ans,maxn[y][0]);
	else ans=max(ans,minn[y][0]);
	return ans;
}
signed main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		a[i].x=read(),a[i].y=read(),a[i].val=read();
	}
	for(int i=1;i<=n;++i) fa[i]=i;
	sort(a+1,a+1+m,cmp);
//	for(int i=1;i<=m;++i) cout<<a[i].x<<" "<<a[i].y<<" "<<a[i].val<<endl;
//	cout<<"-----"<<endl;
	int num=0,sum=0;
	for(int x,y,i=1;i<=m;++i){
		x=find(a[i].x);y=find(a[i].y);
		if(x!=y){
			sum+=a[i].val;
			++num;
			fa[x]=y;
			vis[i]=1;
			add(a[i].x,a[i].y,a[i].val);
			add(a[i].y,a[i].x,a[i].val);
			if(num==n-1) break;
		}
	}
	dep[1]=1;
	dfs(1);
	int ans=0x3f3f3f3f;
	for(int to,i=1;i<=m;++i){
		if(vis[i]) continue;
		to=query(a[i].x,a[i].y,a[i].val);
//		cout<<i<<" "<<to<<" "<<a[i].val<<" "<<a[i].x<<" "<<a[i].y<<" "<<endl;
		if(to){
			ans=min(ans,a[i].val-to);
		}
	}
	cout<<sum+ans<<endl;
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
/*
hack:
4 5
1 2 2
2 3 3
3 4 4
1 4 4
2 4 4
*/
