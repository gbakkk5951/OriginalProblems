#include<cstdio>
int n;
int to[1000005];
bool vis[1000005];
int stack[1000005],top;
bool instack[1000005];
int con=0,rings[1000005];
void search(int now){
	if(vis[now]){
		if(!instack[now]) return ;
		int tmp=top;
		int ans=0;
		while(stack[tmp]!=now){
			--tmp; ans++;
		}
		rings[++con]=ans;
		return ; 
	}
	stack[top++] = now;
	instack[now] = true;
	vis[now] = true;
	search(to[now]);
	--top,instack[now]=false;
	stack[top]=0;
	return ;
}

long long gcd(long long a, long long b){
	if(!b) return a;
	else return gcd(b, a%b);
}

bool notprime[1000005];
int prime[1000005],primeMax[1000005],pcnt=0;
int firstP[1000005];
void eul(int maxi){
	for(int i=2;i<=maxi;i++){
		if(!notprime[i]){
			firstP[i]=pcnt;
			prime[pcnt++]=i;
		}
		for(int j=0;j<pcnt;j++){
			if(i*prime[j]>maxi) break;
			notprime[i*prime[j]]=true;
			firstP[i*prime[j]]=j;
			if(i%prime[j]==0) break;
		}
	}
	return ;
}

const int mod=998244353;
long long qpow(long long base, long long k){
	long long ans=1;
	for(long long now=base;k;k>>=1){
		if(k&1) ans = ans * now % mod;
		now=(now*now)%mod;
	}
	return ans;
}

int main(){
	int T;
	scanf("%d",&T);
	eul(1000000);
//	T==3?puts("1\n5\n6"):puts("2\n4");
	while(T--){
		scanf("%d",&n);
		con = 0;
		for(int i=0;i<=n;i++) vis[i]=false,primeMax[i]=0;
		for(int i=1;i<=n;i++) scanf("%d",&to[i]);
		for(int i=1;i<=n;i++) if(!vis[i]) search(i);
		for(int i=1;i<=con;i++){
			int tmp=rings[i];
			int cnt,now=-1;
//			if(tmp) continue;
			while(tmp!=1){
				if(firstP[tmp]!=now) cnt=0,now=firstP[tmp];
				++cnt;
				if(primeMax[now]<cnt) primeMax[now]=cnt;
				tmp/=prime[now];
			}
		}
		long long ans=1;
		for(int i=0;i<=n;i++){
			if(primeMax[i]){
				ans = ans * qpow(prime[i], primeMax[i]) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
