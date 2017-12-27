using namespace std;
int main(){}
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
int head[2005];
int to[4005];
int nxt[4005];
double dp[2005];
double p[2005];
double dmg[2005];
double arr[2005];

double ans;
struct _Main{

int eidx;
void getdp(int nd,int from){
	int i;int cnt;double sum;
	for(i=head[nd];i;i=nxt[i])if(to[i]!=from){
		getdp(to[i],nd);
	}
	for(i=head[nd],cnt=0;i;i=nxt[i])if(to[i]!=from){
		arr[cnt++]=dp[to[i]];
	}
	sort(arr,arr+cnt,greater<double>());
	for(i=0,sum=0,dp[nd]=0;i<cnt;i++){
		sum+=arr[i];
		dp[nd]=max(dp[nd],sum*(p[nd]+(1.0-p[nd])/(i+1.0)));
	}
	if(cnt && m==0)dp[nd]=sum*(p[nd]+(1.0-p[nd])/(cnt));
	dp[nd]+=dmg[nd];
}
void inline add(int a,int b){
	eidx++;
	nxt[eidx]=head[a];
	head[a]=eidx;
	to[eidx]=b;
}
double eps;
int n,m,e;
_Main(){
	freopen("prism.out","w",stdout);
    freopen("prism.in","r",stdin);		
	int a,b;int i,j,k;
	scanf("%d%d%d%lf",&n,&m,&e,&eps);
	for(i=0;i<e;i++){
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	for(i=1;i<=n;i++){
		scanf("%lf",&dmg[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%lf",&p[i]);
	}
	int tmp;
	for(i=1;i<=n;i++){
		getdp(i,0);
		if(dp[i]>ans){
			tmp=i;
		}
		ans=max(ans,dp[i]);
	}
	ans+=eps;
	printf("%.0lf",ans);
}
	
	
	
	
	
}prism;
