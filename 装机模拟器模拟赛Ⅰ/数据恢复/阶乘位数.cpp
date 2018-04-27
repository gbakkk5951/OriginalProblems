int main(){}
#include<cstdio>
#include<cmath>

const double eps=1e-8;
const double pi=acos(-1);
struct _Main{
int T;
int n,temp;
_Main(){
	scanf("%d",&T);
	int i;
	double a,b,c;
	for(i=0;i<T;i++){
		scanf("%d",&n);
		b=ceil((double)eps+(0.5*log((double)2.0*pi*n)+n*log(n)-n)/log(10));
		if(n<=1){
			printf("1\n");
		}else{
			printf("%d\n",(int)b);
		}
	}
}	
}cdvs2552;
