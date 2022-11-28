using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<algorithm>
#include<bitset>
#include<vector>
#include<cstring>
#include<iostream>
#define inf 0x3f3f3f3f
struct World{
	vector<int>portal;
	int tme;
}world[205];
bool vis[3005];
int head[3005];
int nxt[200010],to[200010],val[200010];
int eidx;
int dis[3005];
template<typename Type>
	void read(Type &a){
		char t,f=1;
		while(!isdigit(t=getchar())){
			if(t=='-')f=-1;
		}
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
		a*=f;			
	}

void inline add(int a,int b,int c){
	eidx++;
	nxt[eidx]=head[a];
	head[a]=eidx;
	to[eidx]=b;
	val[eidx]=c;
}

void dfs(int nd=0){
	vis[nd]=1;
	int i;
	for(i=head[nd];i;i=nxt[i]){
		if(!vis[to[i]]){
			dfs(to[i]);
		}
	}
}
struct Node{
	int x[3][2];
	int delta;
	int tme;
	void readpair(int a){
		int i;
		for(i=0;i<3;i++){
			read(x[i][a]);
		}
	}
	void fake(){
		int i;
		for(i=0;i<3;i++){
			x[i][1]=x[i][0];
		}
		tme=-inf;
		delta=0;
	}
}node[3005];
int n,m;
int pre[3005];
int pree[3005];
bool vis2[3005];
bool vis3[3005];

struct _Main{
	bool change[3005];	
	int n,m;
	_Main(){
		int i,j,k;
		vector<int>::iterator it;
		read(n);read(m);
		n++;
		node[0].readpair(0);
		node[0].fake();
		world[node[0].x[0][0]].portal.push_back(0);
		node[n].readpair(0);
		node[n].fake();
		world[node[n].x[0][0]].portal.push_back(n);
		for(i=1;i<=m;i++){
			read(world[i].tme);
		}
		for(i=1;i<n;i++){
			node[i].readpair(0);
			node[i].readpair(1);
			read(node[i].tme);
			read(node[i].delta);
			world[node[i].x[0][0]].portal.push_back(i);
		}
		for(i=0;i<=n;i++){
			it=world[node[i].x[0][1]].portal.begin();
			for(;it!=world[node[i].x[0][1]].portal.end();it++){
				add(i,*it,node[i].delta+world[node[i].x[0][1]].tme*(abs(node[i].x[1][1]-node[*it].x[1][0])+abs(node[i].x[2][1]-node[*it].x[2][0])) );
			}
		}
		for(i=1;i<=m;i++){
			if(world[i].portal.size()>52){
				cerr<<"WaData"<<endl;
			}
		}
		
		dfs();
		if(!vis[n]){
			printf("YouNeedOpPermission");
			return;
		}else if(world[node[n].x[0][0]].tme<0){
			printf("NegativeInfinity");
			return;
		}
		solve();
		printf("%d",dis[n]);		
	}
	~_Main(){
		fclose(stdout);
	}
	void solve(){
		int i,j,k,t;
		bool flag;
		memset(dis,63,sizeof(dis));
		memset(vis,0,sizeof(vis));
		memset(pre,255,sizeof(pre));
		change[0]=1;
		dis[0]=0;
		while(1){
			flag=false;
			for(i=0;i<=n;i++){
				if(!change[i])continue;
				change[i]=0;
				if(dis[i]<=node[i].tme)pre[i]=-1;
				for(j=head[i];j;j=nxt[j]){
					t=max(node[i].tme,dis[i])+val[j];
					t=max(t,node[to[j]].tme);
					if(world[node[i].x[0][1]].tme<0){
						t=node[to[j]].tme;
					}
					if(t<dis[to[j]]){
						pre[to[j]]=i;
						pree[to[j]]=j;
						dis[to[j]]=t;
						change[to[j]]=1;
						flag=true;
					}
				}
			}
			if(!flag)return;
			breakloop();
		}
	}
	void breakloop(){
		int i,j,k,mn;
		memset(vis2,0,sizeof(vis2));
		memset(vis3,0,sizeof(vis3));
		for(i=0;i<=n;i++){
			for(k=i;k!=-1;k=pre[k]){
				if(vis2[k]){
					break;
				}
				vis2[k]=1;
			}
			if(k==-1 || vis3[k])goto EndFor;
			mn=dis[pre[k]]+val[pree[k]]-node[k].tme;
			
			for(j=pre[k];j!=k;j=pre[j]){
				mn=min(mn,dis[pre[j]]+val[pree[j]]-node[j].tme);
			}
			if(mn<=0)goto EndFor;
			dis[k]-=mn;
			for(j=pre[k];j!=k;j=pre[j]){
				dis[j]-=mn;
			}
			EndFor:
			for(k=i;k!=-1;k=pre[k]){
				if(vis3[k])break;
				vis3[k]=1;
			}	
		}		
	}
}portal;
