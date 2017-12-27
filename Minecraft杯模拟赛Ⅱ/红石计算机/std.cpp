using namespace std;
int main(){}
#include<cstdio>
#include<bitset>
#include<iostream>
typedef bitset<155> Num;

struct Graph{
	int head[150010];//2*k*n
	int from[6000010],nxt[6000010],to[6000010];
	int ind[150010];
	int eidx;
	void inline add(int a,int b){
		eidx++;
		ind[b]++;
		nxt[eidx]=head[a];
		head[a]=eidx;
		to[eidx]=b;
		from[eidx]=a;
	}
}G[2];

struct _Main{
	bool del[150010];
	bool vis[150010];
	int dfn[150010],dfncnt;
	int low[150010];
	int stk[150010],stkcnt;
	bool instk[150010];
	int rev[150010];
	Num res;
	Num	ans[505];
	int n,m,bitlen;
	char oper;
	int a,b;
	int eidx;
	void addedge(int a,int b,char oper,char re){
		switch ( oper ){
			case '|' :{
				if(re){
					G[0].add(a,b|1);
				}else{
					G[0].add(a|1,a);
				}
				break;
			}
			case '^' :{
				if(re){
					G[0].add(a,b|1);
					G[0].add(a|1,b);
				}else{
					G[0].add(a,b);
					G[0].add(a|1,b|1);
				}
				break;
			}
			case '&' :{
				if(re){
					G[0].add(a,a|1);
				}else{
					G[0].add(a|1,b);
				}
				break;
			}
		}
	}
	void tarjan(int nd){
		stk[stkcnt++]=nd;
		instk[nd]=1;
		low[nd]=dfn[nd]=++dfncnt;
		int i;
		for(i=G[0].head[nd];i;i=G[0].nxt[i]){
			if(!dfn[G[0].to[i]]){
				tarjan(G[0].to[i]);
			}
			if(instk[G[0].to[i]]){
				low[nd]=min(low[nd],low[G[0].to[i]]);
			}
		}
		if(low[nd]==dfn[nd]){
			do{
				low[stk[stkcnt-1]]=dfn[nd];
				instk[stk[stkcnt-1]]=0;
			}while(stk[--stkcnt]!=nd);
		}
	}
	void deldfs(int nd){
		if(del[nd])return;
		del[nd]=1;
		int i;
		for(i=G[1].head[nd];i;i=G[1].nxt[i]){
			deldfs(G[1].to[i]);
		}
	}
	void topodfs(int nd){
		int i;
		if(del[nd]||vis[nd])return;
		vis[nd]=1;
		deldfs(rev[nd]);
		for(i=G[1].head[nd];i;i=G[1].nxt[i]){
			G[1].ind[G[1].to[i]]--;
			if(G[1].ind[G[1].to[i]]==0){
				topodfs(G[1].to[i]);
			}
		}
	}
	_Main(){
		std::ios::sync_with_stdio(false);
		cin>>n>>m>>bitlen;
		int i,j,t;
		for(i=1;i<=m;i++){
			cin>>a>>oper>>b>>res;
			a--;b--;
			for(j=0;j<bitlen;j++){
				addedge((a*bitlen+j)<<1,(b*bitlen+j)<<1,oper,res[j]);
				addedge((b*bitlen+j)<<1,(a*bitlen+j)<<1,oper,res[j]);
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<bitlen;j++){
				t=(i*bitlen+j)<<1;
				if(!dfn[t]){
					tarjan(t);
				}	
				if(!dfn[t|1]){
					tarjan(t|1);
				}
				if(low[t]==low[t|1]){
					printf("No");
					return;
				}
				rev[low[t]]=low[t|1];
				rev[low[t|1]]=low[t];				
			}
		}
		for(i=1;i<=G[0].eidx;i++){
			if(low[G[0].from[i]]!=low[G[0].to[i]]){
				G[1].add(low[G[0].to[i]],low[G[0].from[i]]);
			}
		}
		for(i=0;i<2*n*bitlen;i++){
			if(!vis[low[i]]&&low[i]==dfn[i]&&!del[low[i]]&&G[1].ind[low[i]]==0){
				deldfs(rev[low[i]]);
				topodfs(low[i]);
			}
		}
		for(i=0;i<2*n*bitlen;i++){
			if(!del[low[i]]){
				ans[(i>>1)/bitlen][(i>>1)%bitlen]=(i&1);
			}
		}
		for(i=0;i<n;i++){
			for(j=bitlen-1;j>=0;j--){
				cout<<ans[i][j];
			}
			cout<<endl;
		}
		fclose(stdout);
	}
	
	
	
}rsputer;

