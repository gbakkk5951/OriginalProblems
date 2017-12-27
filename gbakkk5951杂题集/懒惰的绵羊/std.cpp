int main(){}
using namespace std;
#include<cstdio>
#include<cctype>
#include<algorithm>
void read(int &a){
	char t;
	while(!isdigit(t=getchar()));
	a=t-'0';
	while(isdigit(t=getchar())){
		a*=10;
		a+=t-'0';
	}
}
int high;
int n,q,t;
int tl[300010];
int ans[300010];
struct _Main{
void updata(int low){
	for(high;high>=low;high--){
		if(high+tl[high]>n){
			ans[high]=1;
		}else{
			ans[high]=ans[high+tl[high]]+1;
		}
	}
}	
int s[2];long long sum;
_Main(){
	int i,j,k;int a,b,c;
	read(n);read(q);read(t);
	for(i=0;i<=n;i++){
		read(tl[i]);
	}
	high=n;
	switch(t){
		case 1:{
			for(i=1;i<=q;i++){
				read(a);
				switch(a){
					case 1:{
						read(b);read(c);
						tl[b]=c;
						high=max(high,b);
						break;
					}
					case 2:{
						read(b);
						if(b<=n){
							updata(b);
							s[i&1]^=ans[b];	
							sum+=ans[b];
						}
						break;
					}
				}
			}
			printf("%d %d %lld",s[1],s[0],sum);
			break;
		}
		case 2:{
			for(i=1;i<=q;i++){
				read(a);
				switch(a){
					case 1:{
						read(b);read(c);
						tl[b]=c;
						high=max(high,b);						
						break;
					}
					case 2:{
						read(b);
						if(b<=n){
							updata(b);
							printf("%d\n",ans[b]);
						}else{
							printf("0\n");
						}
						break;
					}
				}				
			}		
			break;
		}
	}

	fclose(stdout);
	
	
}	
	
	
	
}ezoj1026;
