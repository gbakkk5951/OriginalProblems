using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstring>
/*
#include<bitset>
bitset<10000010>iscom*/
bool iscom[10000010];//is composite
int sq;
int mx;
int gcd_arr[3205][3205];
int decom[10000010][3];
int prime[670010];
int mindiv[10000010];

int pidx;
const int daymod=28800;

struct _Main{
void getprime(){
	int i,j,t;
	for(i=2;i<=mx;i++){
		if(!iscom[i]){
			prime[pidx++]=i;
			mindiv[i]=i;
		}
		for(j=0;j<pidx && (t=i*prime[j]) <=mx;j++){
			iscom[t]=1;
			mindiv[t]=prime[j];
			if(!(i%prime[j]))break;
		}
	}
}	
	
template<typename Type>
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}
void ini(){
	int i,j,p;
	mx=(int)1e7+1;
	sq=(int)sqrt(mx)+1;
	getprime();
	for(i=0;i<=sq;i++){
		gcd_arr[0][i]=i;
	}
	for(i=0;i<=sq;i++){
		gcd_arr[i][0]=i;
	}
	for(i=1;i<=sq;i++){
		for(j=1;j<=sq;j++){
			gcd_arr[i][j]=gcd_arr[j%i][i];
		}
	}
	decom[1][0]=decom[1][1]=decom[1][2]=1;
	for(i=2;i<=mx;i++){
		p=mindiv[i];
		memcpy(decom[i],decom[i/p],sizeof(decom[i]));
		if(decom[i][0]*p<=sq){
			decom[i][0]*=p;
		}else if(decom[i][1]*p<=sq){
			decom[i][1]*=p;
		}else{
			decom[i][2]*=p;
		}
	}
	
}	
	
int gcd(int a,int b){
	int ans=1,d,t;
	int i;
	for(i=0;i<3;i++){
		t=decom[a][i];
		if(t<=sq){
			d=gcd_arr[t][b%t];
		}else if(b%t==0){
			d=t;
		}else{
			d=1;
		}
		ans*=d;
		b/=d;
	}
	return ans;
}	
long long day_t[3],tick_t[3];
_Main(){
	int i;
	int q;int a;int b;
	long long ans;

	ini();
	read(q);
	for(i=1;i<=q;i++){
		read(a);read(b);
		ans=(long long)a/gcd(a,b)*b;
		day_t[i&1]^=ans/daymod;
		day_t[2]+=ans/daymod;
		tick_t[i&1]^=ans%daymod;
		tick_t[2]+=ans%daymod;
	}
	printf("%lld %lld\n",day_t[1],tick_t[1]);
	printf("%lld %lld\n",day_t[0],tick_t[0]);
	printf("%lld %lld\n",day_t[2],tick_t[2]);
	fclose(stdout);
}
	
	
	
	
}redstoneclock;





