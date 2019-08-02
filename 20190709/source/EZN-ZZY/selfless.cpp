#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int num=1;
int ans=0;
struct node1{
	int from;
	int to;
	int dis;
}a[200010];
struct node2{
	int to;
	int next;
	int dis;
}road[200010];
int head[100010];
int fa[100010];
int vis[200010];
int deep[100010],pre[100010][20],maxn[100010][20],second[100010][20];//最大和严格次大 
bool com(const node1 &x,const node1 &y){
	return x.dis<y.dis;
}
void built(int from,int to,int dis){
	road[++num].next=head[from];
	road[num].to=to;
	road[num].dis=dis;
	head[from]=num;
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void kruskal(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int x=a[i].from;
		int y=a[i].to;
		int z=a[i].dis;
		int fx=find(x);
		int fy=find(y);
		if(fx==fy)continue;
		vis[i]=1;
		built(x,y,z);
		built(y,x,z);
		ans+=z;
		fa[fx]=fy;
		cnt++;
		if(cnt==n-1)break; 
	}
}
void dfs(int x,int fa){
	deep[x]=deep[fa]+1;
	pre[x][0]=fa;
	for(int i=1;i<=18;i++){
		pre[x][i]=pre[pre[x][i-1]][i-1];
		maxn[x][i]=max(maxn[x][i-1],maxn[pre[x][i-1]][i-1]);
	}
	for(int i=1;i<=18;i++){
		int k[4];
		k[0]=maxn[x][i-1];
		k[1]=second[x][i-1];
		k[2]=maxn[pre[x][i-1]][i-1];
		k[3]=second[pre[x][i-1]][i-1];
		for(int j=0;j<=3;j++){
			if(k[j]<maxn[x][i]&&k[j]>second[x][i])second[x][i]=k[j];
		}
	}
	for(int i=head[x];i;i=road[i].next){
		int y=road[i].to;
		if(y==fa)continue;
		maxn[y][0]=road[i].dis;
		second[y][0]=-1e9;
	}
}
int solve(int x,int y,int flag){
	if(deep[x]<deep[y])swap(x,y);
	int kk=deep[x]-deep[y];
	int ans1=0,ans2=0;
	for(int i=0;i<=18;i++){
		if((kk>>i)&1){
			if(maxn[x][i]>ans1){
				ans1=maxn[x][i];
			}
			else if(maxn[x][i]<ans1&&maxn[x][i]>ans2){
				ans2=maxn[i][i];
			}
			if(second[x][i]>ans2){
				ans2=second[x][i];
			}
			x=pre[x][i];
		}
	}
	if(x==y)return flag==1?ans1:ans2;
	for(int i=18;i>=0;i--){
		if(pre[x][i]!=pre[y][i]){
			int k[4];
			k[0]=maxn[x][i];
			k[1]=second[x][i];
			k[2]=maxn[y][i];
			k[3]=second[y][i];
			ans1=max(ans1,max(k[0],k[2]));
			for(int j=0;j<=3;j++){
				if(k[j]<ans1&&k[j]>ans2)ans2=k[j];
			}
			x=pre[x][i];
			y=pre[y][i];
		}
	}
	int k[4];
	k[0]=maxn[x][0];
	k[1]=second[x][0];
	k[2]=maxn[y][0];
	k[3]=second[y][0];
	ans1=max(ans1,max(k[0],k[2]));
	for(int i=0;i<=3;i++){
		if(k[i]<ans1&&k[i]>ans2)ans2=k[i];
	}
	return flag==1?ans1:ans2;
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	memset(head,0,sizeof(head));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		a[i].from=u;
		a[i].to=v;
		a[i].dis=c;
	}
	sort(a+1,a+m+1,com);
	memset(vis,0,sizeof(vis));
	kruskal();
	dfs(1,1);
	int cnt=1e9;
	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		int x=a[i].from;
		int y=a[i].to;
		if(solve(x,y,1)==a[i].dis){
			cnt=min(cnt,a[i].dis-solve(x,y,2));
		}
		else{
			cnt=min(cnt,a[i].dis-solve(x,y,1));
		}
	}
	printf("%d\n",ans+cnt);
	return 0;
}
