using namespace std;
int main(){}
#include<cstdio>
#include<cctype>

template<typename Type>
	void read(Type &a){
		char t,f=1;
		while(!isdigit(t=getchar())){
			if(t=='-')f=-1;
		}
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
		a*=f;
	}
struct _Main{
long long arr[1020][1020];
_Main(){
	int T,n;long long ans;
	int op,a,b,c,d,e;
	read(T);read(n);
	int i,j;
	while(T--){
		read(op);
		if(op==1){
			read(a);read(b);read(c);read(d);read(e);
			for(i=a;i<=b;i++){
				for(j=c;j<=d;j++){
					arr[i][j]+=e;
				}
			}
		}else{
			read(a);read(b);read(c);read(d);
			ans=0;
			for(i=a;i<=b;i++){
				for(j=c;j<=d;j++){
					ans+=arr[i][j];
				}
			}
			printf("%lld\n",ans);
		}
		
		
	}
	
}	
	
	
	
}BruteForce;
