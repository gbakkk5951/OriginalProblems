using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<algorithm>
int n,m;
struct _Main{
	

long long lsum[2005],rsum[2005];
long long pos[2005];
long long cst[2005][2005];
long long dp[2005][2];
long long sol[2005][2];
template<typename Type>
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while(isdigit(t=getchar())){
			a*=10;
			a+=t-'0';
		}
	}
void dfs(long long iter,long long l,long long r,long long mn=1,long long mx=n){

	long long mid=(l+r)>>1;
	long long mmx=min(mx,mid-1);
	long long mmn=max(mn,sol[mid][iter^1]);
	long long i,s=mmn;
	for(i=mmn;i<=mmx;i++){
		if(dp[i][iter^1]+cst[i][mid]<=dp[s][iter^1]+cst[s][mid]){
			s=i;
		}
	}
	sol[mid][iter]=s;
	dp[mid][iter]=dp[s][iter^1]+cst[s][mid];
	if(l<=mid-1) dfs(iter,l,mid-1,mn,s);
	if(mid+1<=r) dfs(iter,mid+1,r,s,mx);
}
long long ans;
_Main(){
	long long i,j,k;long long a,b,c;long long I,J,K;long long iter=0;
	read(n);read(m);
	for(i=1;i<=n;i++){
		read(pos[i]);
	}sort(pos+1,pos+n+1);
	for(i=1;i<=n;i++){
		lsum[i]=lsum[i-1]+(i-1)*(pos[i]-pos[i-1]);
	}
	for(i=n;i>=1;i--){
		rsum[i]=rsum[i+1]+(n-i)*(pos[i+1]-pos[i]);
	}
	for(i=1;i<=n;i++){
		for(j=i+2,k=i;j<=n;j++){
			while(k+1<j && pos[j]-pos[k+1] >= pos[k+1]-pos[i]){
				k++;
			}
			cst[i][j]=rsum[i]-rsum[k]-(n-k)*(pos[k]-pos[i])
					+ lsum[j]-lsum[k+1]-(k)*(pos[j]-pos[k+1]); 
		}
	}
	for(i=1;i<=n;i++){
		dp[i][iter]=lsum[i];
	}
	for(I=2;I<=m;I++){
		iter^=1;
		dfs(iter,I,n);
	}
	
	for(i=m, ans=(int)1e8;i<=n;i++){
		if(ans>dp[i][iter]+rsum[i]){
			ans=dp[i][iter]+rsum[i];
		}
	}
	printf("%lld",ans);
	fclose(stdout);
}	

	
	
	
	
	
	
}jsk;
