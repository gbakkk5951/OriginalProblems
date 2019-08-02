#include<bits/stdc++.h>
using namespace std;
int n,m,bcj[200010],x[5010][5010],vis[10010],val=0,v2,ans,flag;
int find(int a){
	if(bcj[a]==a)return a;
	return bcj[a]=find(bcj[a]);
}
struct line{
		int a;
		int b;
		int cost;
		bool visit;
	}m1[200010];
bool cmp(line a,line b){
	return a.cost<b.cost;
}	
void dfs(int st,int now){
	if(x[now][st]&&m1[x[now][st]].visit){
		vis[x[now][st]]=1;
		flag=1;
	}
	else{
	for(int a=1;a<=m;a++){
		if(vis[x[now][a]]==0&&flag==0&&m1[a].visit){
			vis[x[now][a]]=1;
			dfs(st,m1[x[now][a]].b);
			vis[x[now][a]]=0;
		}
		
		}	
	}
	
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int a=1;a<=m;a++){
		scanf("%d%d%d",&m1[a].a,&m1[a].b,&m1[a].cost);
		x[m1[a].a][m1[a].b]=x[m1[a].b][m1[a].a]=a;
	}
	for(int a=1;a<=m;a++)bcj[a]=a;
	sort(m1+1,m1+m+1,cmp);
	for(int a=1;a<=m;a++){
		if(find(m1[a].a)!=find(m1[a].b)){
			bcj[find(m1[a].a)]=bcj[find(m1[a].b)];
			m1[a].visit=true;
			val+=m1[a].cost;
		}
	}
	
	ans=0x7fffffff;
	for(int a=1;a<=m;a++){
		if(m1[a].visit==false){
			v2=val+m1[a].cost;
			memset(vis,0,sizeof(vis));
			flag=0;
			dfs(m1[a].b,m1[a].a);
			
			for(int b=1;b<=m;b++){
				if(b!=a&&vis[b]){
					ans=min(ans,v2-m1[b].cost);
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}

