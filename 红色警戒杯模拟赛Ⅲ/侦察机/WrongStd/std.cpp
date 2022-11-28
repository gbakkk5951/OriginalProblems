using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>

struct _Main{
template<typename Type>
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}
int nxt[10010],to[10010],val[10010];
int eidx;int degree[1010];

int head[1010];
int n,m;	
void inline add(int a,int b,int c){
	eidx++;
	nxt[eidx]=head[a];
	head[a]=eidx;
	to[eidx]=b;
	val[eidx]=c;
	degree[a]++;
}
bool vis[1010];
long long dis[1010];
void dijkstra(int nd){
	memset(dis,63,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[nd]=0;
	int i,j,chose;
	for(i=2;i<=n;i++){
		for(j=1,chose=-1;j<=n;j++){
			if(!vis[j] && (chose==-1||dis[j]<dis[chose])){
				chose=j;
			}
		}
		vis[chose]=1;
		for(j=head[chose];j;j=nxt[j]){
			dis[to[j]]=min(dis[to[j]],dis[chose]+val[j]);
		}
	}
}


int mmp[310],mmpidx;
long long sum;
long long mmpdis[305][305];
_Main(){
	memset(lx,128,sizeof(lx));
	int i,j;int a,b,c;
	long long tmp;
	read(n);read(m);read(a);read(b);
	degree[a]++;degree[b]++;
	for(i=1;i<=m;i++){
		read(a);read(b);read(c);
		sum+=c;
		if((m<=2000 && n<=1000)|| n<=300){
			add(a,b,c);add(b,a,c);
		}
	}
/*	if(m==n-1){
		printf("%lld",sum*2LL);
		return ;
	}else if(!((m<=2000 && n<=1000)|| n<=300)){
		printf("%lld",sum);
		return ;
	}
*/	for(i=1;i<=n;i++){
		if(degree[i]&1){
			mmp[++mmpidx]=i;
		}
	}
	for(i=1;i<=mmpidx;i++){
		dijkstra(mmp[i]);
		for(j=1;j<=mmpidx;j++)if(j!=i){
			mmpdis[i][j]=-dis[mmp[j]];
			lx[i]=max(lx[i],mmpdis[i][j]);
		}
	}
	km();
	for(i=1,tmp=0;i<=mmpidx;i++){
		if(lx[i]+ly[i]>(-1e14))
		tmp+=lx[i]+ly[i];
		printf("link %d %d %lld\n",i,linkx[i],mmpdis[i][linkx[i]]);
	}
	
//	printf("tmp=%lld\n",tmp);
	printf("%lld",sum-tmp/2);
}
long long mndelta;
bool visx[305],visy[305];
int linkx[305],linky[305];
long long lx[305],ly[305];
bool dfs(int s){
	int i;
	long long t;
	visx[s]=1;
	for(i=1;i<=mmpidx;i++)if(!visy[i]){
		t=lx[s]+ly[i]-mmpdis[s][i];
		if(t==0){
			visy[i]=1;
			if(linky[i]==0 || dfs(linky[i])){
				linkx[s]=i;linky[i]=s;
				return true;
			}
		}else if(t>0){
			mndelta=min(mndelta,t);
		}
	}
	
	return false;
}

void km(){
	int i,j;
	for(i=1;i<=mmpidx;i++){
		while(1){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			mndelta=(long long)1e11;
			if(dfs(i))break;
			for(j=1;j<=mmpidx;j++)if(visx[j]){
				lx[j]-=mndelta;
			}
			for(j=1;j<=mmpidx;j++)if(visy[j]){
				ly[j]+=mndelta;
			}
		}
		
	}
	
}	


	
}spyplane;
