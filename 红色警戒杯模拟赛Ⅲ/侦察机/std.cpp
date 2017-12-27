using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<queue>
#include<cstring>
#include<functional>
#include<vector>
namespace Protector{
int overflow;
struct _Main{
	struct Edge{
		int dst,val;
		bool friend operator > (const Edge &a,const Edge &b){
			return a.val>b.val;
		}
	};
	priority_queue<Edge,vector<Edge>,greater<Edge> >heap;
	template<typename Type>
		void read(Type &a){
			char t;
			while(!isdigit(t=getchar()));
			a=t-'0';
			while( isdigit(t=getchar())){
				a*=10;a+=t-'0';
			}
		}
	int n,m;
	int degree[100010];
	int head[100010];
	int ans;
	int dis[100010];
	int nxt[400010],to[400010],val[400010];
	int eidx;
	int map[23][23];
	void inline add(int a,int b,int c){
		eidx++;
		nxt[eidx]=head[a];
		head[a]=eidx;
		to[eidx]=b;
		val[eidx]=c;
	}
	
	int list[23],listidx;
	void dijkstra(int src){
		memset(dis,63,sizeof(dis));
		dis[src]=0;
		int nd,i;Edge tmp;
		heap.push((Edge){src,0});
		while(!heap.empty()){
			tmp=heap.top();
			heap.pop();
			nd=tmp.dst;
			if(dis[nd]==tmp.val){
				for(i=head[nd];i;i=nxt[i]){
					if(dis[nd]+val[i]<dis[to[i]]){
						dis[to[i]]=dis[nd]+val[i];
						heap.push((Edge){to[i],dis[to[i]]});
					}
				}
			}
		}
	}
	int dp[1050010];
	_Main(){
		int a,b,c;
		int i,j,k;
		int I;
		read(n);read(m);
		if(m==n-1){
			for(i=1;i<=m;i++){
				read(overflow);read(overflow);read(a);
				ans+=a;
			}
			ans<<=1;
			goto EndMain;
		}
		for(i=1;i<=m;i++){
			read(a);read(b);read(c);
			ans+=c;
			degree[a]++;degree[b]++;
			add(a,b,c);add(b,a,c);
		}
		for(i=1;i<=n;i++){
			if(degree[i]&1){
				listidx++;
				list[listidx]=i;
			}
		}
		for(i=1;i<=listidx;i++){
			dijkstra(list[i]);
			for(j=1;j<=listidx;j++){
				map[i][j]=dis[list[j]];
			}
		}
		memset(dp,63,sizeof(dp));
		dp[0]=0;
		for(I=0;I<((1<<listidx)-1);I++)if(dp[I]<0x3f3f3f3f){
			for(i=0;i<listidx;i++){
				if(!(I&(1<<i))){
					for(j=i+1;j<listidx;j++){
						if(!(I&(1<<j))){
							dp[I|(1<<j)|(1<<i)]=min(dp[I|(1<<j)|(1<<i)],dp[I]+map[i+1][j+1]);
						}
					}
					break;
				}
			}
		}
		ans+=dp[(1<<listidx)-1];
		
		EndMain:
			printf("1\n%d",ans);
			fclose(stdout);
	}
	
}spyplane;

}
