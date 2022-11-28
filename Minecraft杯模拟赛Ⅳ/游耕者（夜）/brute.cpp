using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
namespace Protector{
struct _Main{
	
	bool vis[3010];
	int dis[3010];
	int x[3010][2];
	int inline getdis(int a,int b){
		return abs(x[a][0]-x[b][0])+abs(x[a][1]-x[b][1]);
	}
	long long ans;
	_Main(){
		int n;
		int i,j,k;
		
		memset(dis,63,sizeof(dis));
		scanf("%d",&n);
		for(i=1;i<=n;i++){
			scanf("%d%d",x[i],x[i]+1);
		}
		dis[1]=0;
		for(i=1;i<=n;i++){
			for(j=1,k=-1;j<=n;j++)if(!vis[j]){
				if(k==-1 || dis[j]<dis[k]){
					k=j;
				}
			}
			ans+=dis[k];
			vis[k]=1;
			for(j=1;j<=n;j++){
				dis[j]=min(dis[j],getdis(k,j));
			}
		}
		printf("%lld",ans);
	}
	
}nomadism_night;	
	
	
	
	
	
}
