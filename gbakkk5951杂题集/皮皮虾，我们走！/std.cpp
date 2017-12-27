#include<cstdio>
#include<cstring>
int main(){}
const long long mod=1000000000;
struct _Main{
long long dp[65][65][65];
int mx;
int bit[70];
long long mem[70][70];
int cnt; 
long long n;
void getdp(){
	int i,j,k,l,m;
	for(j=0;j<=mx;j++){
		dp[j][j][j]=1;
		for(i=0;i<j;i++){
			for(k=i;k<j;k++){
				for(l=i;l<=k;l++){
					for(m=l;m<=k;m++){
						dp[i][j][k]+=dp[i][j-1][l]*dp[m][j-1][k];
						dp[i][j][k]%=mod;
					}
				}
			}
		}
	}
}

_Main(){
	scanf("%lld",&n);
	int i,j,k,l;long long ans;
	for(i=0,cnt=0;n>>i;i++){
		if((n>>i)&1){
			bit[cnt++]=i;
		}
		mx=i;
	}
	getdp();
	for(i=0;i<=mx;i++){
		mem[cnt][i]=1;
	}
	for(i=cnt-1;i>=0;i--){
		for(j=0;j<=bit[i];j++){
			ans=0;
			for(k=j;k<=bit[i];k++){
				for(l=k;l<=bit[i];l++){
					ans=(ans+dp[k][bit[i]][l]*mem[i+1][l])%mod;
				}	
			}
			mem[i][j]=ans;
		}
	}
	
	ans=mem[0][0];
	//ans=dfs(0,0);
	printf("%lld",ans);
}
/*
long long dfs(int pos,int low){

	if(mem[pos][low]) return mem[pos][low]-1;
	if(pos==cnt)return 1;
	int i,j;
	long long ans=0;
	for(i=low;i<=bit[pos];i++){
		for(j=low;j<=bit[pos];j++){
			ans+=dp[i][bit[pos]][j]*dfs(pos+1,j)%mod;
			ans%=mod;
		}
	}
	mem[pos][low]=ans+1;
	return ans;
}
*/
}ezoj1010;
