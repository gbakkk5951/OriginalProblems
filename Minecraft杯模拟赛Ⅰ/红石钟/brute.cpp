using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstring>

const long long mod=(long long)1e7;


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

	
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

long long tick_t[2];
_Main(){
	long long i;
	long long n;
	long long a;
	long long ans;

	read(n);read(a);

	for(i=1;i<=n;i++){
		ans=(long long)i/gcd(i,a)*a;
		tick_t[1]^=ans;
		a=(a+10007LL)%mod+1;
		ans=(long long)i/gcd(i,a)*a;
		tick_t[0]^=ans;
		a=(a*a+1LL)%mod+1;
	}
	printf("%lld\n",tick_t[1]);
	printf("%lld\n",tick_t[0]);
	fclose(stdout);
}
	
	
	
	
}redstoneclock;





