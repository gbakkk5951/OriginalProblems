using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cmath>
namespace Protector{


struct _Main{

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
	int n;
	int x[5005][2];
	int head[5005];
	int edge[5005][2];
	int eidx;
	int residx;
	int res[5005];
	void inline add(int a,int b){
		eidx++;
		edge[eidx][1]=head[a];
		head[a]=eidx;
		edge[eidx][0]=b;
	}
	void dfs(int nd=1){
		residx++;
		res[residx]=nd;
		int i;
		for(i=head[nd];i;i=edge[i][1]){
			dfs(edge[i][0]);
		}
	}
	int inline pf(int a){
		return a*a;
	}
	int inline getdis1(int a,int b){
		return (int)ceil(sqrt((double) pf(x[a][0]-x[b][0])+pf(x[a][1]-x[b][1])));
	}
	int inline getdis2(int a,int b){
		return abs(x[a][0]-x[b][0])+
	}
	int dis[5005];
	int from[5005];
	bool vis[5005];
	_Main(){
		int i,j,k,t;
		read(n);
		for(i=1;i<=n;i++){
			read(x[i][0]);read(x[i][1]);
		}
		memset(dis,63,sizeof(dis));
		dis[1]=0;
		for(i=2;i<=n;i++){
			k=-1;
			for(j=1;j<=n;j++)if(!vis[j]){
				if(k==-1 ||	dis[j] < dis[k] ){
					k=j;
				}
			}
			vis[k]=1;
			for(j=1;j<=n;j++){
				if((t=dis[k]+getdis(k,j))<dis[j]){
					dis[j]=t;
					from[j]=k;
				}
			}
		}
		for(i=2;i<=n;i++){
			add(from[i],i);
		}
		dfs();res[n+1]=1;
		
		for(i=1;i<=n+1;i++){
			printf("%d ",res[i]);
		}
	}
	
	
}nomadism;


}
