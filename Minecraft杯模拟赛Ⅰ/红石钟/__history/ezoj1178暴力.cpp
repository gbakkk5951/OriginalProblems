#include<cstdio>
#include<cctype>
int main(){}
template<typename Type>		
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}	
	const int mod=28800;
struct _Main{
	int q;
	long long t1,t2;
	long long gcd(long long a,long long b){
		return b?gcd(b,a%b):a;
	}
	long long sum[2];
	_Main(){
		freopen("redstoneclock0.in","r",stdin);
		read(q);
		int i;
		long long lcm;
		for(i=1;i<=q;i++){
			read(t1);read(t2);	
			lcm=t1/gcd(t1,t2)*t2;
			sum[0]+=lcm%mod;
			sum[1]+=lcm/mod;
		}
		printf("%lld %lld",sum[1],sum[0]);
	}
	
}brute;	
