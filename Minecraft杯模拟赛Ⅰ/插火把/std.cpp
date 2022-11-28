using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<algorithm>
struct _Main{
template<typename Type>
	void read(Type &a){
		char t,f=1;
		while(!isdigit(t=getchar())){
			if(t=='-')f=-1;
		}
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}a*=f;
	}
long long even[2505][2505];
long long odd[2505][2505];	
int inline oddx(int x,int y){
	return (x+y)/2;
}
int inline oddy(int x,int y){
	return (mx/2)+(x>y?((x-y+1)/2):((x-y)/2));
}
int inline evenx(int x,int y){
	return (x+y)/2;
}
int inline eveny(int x,int y){
	return (mx+1)/2+(x-y)/2;
}

void inline change(long long arr[2505][2505],int a,int b,int c,int d,long long val){
	int x1,x2,y1,y2;
	x1=min(a,b);x2=max(a,b);y1=min(c,d);y2=max(c,d);
	x1=max(1,x1);x2=min(mx,x2);y1=max(1,y1);y2=min(mx,y2);
	arr[x2][y2]+=val;
	arr[x1-1][y2]-=val;
	arr[x2][y1-1]-=val;
	arr[x1-1][y1-1]+=val;
}


int n,m;
int mx;
_Main(){
	int i,j;
	int ans=0;
	long long r,l,d,tmp;
	read(n);read(m);
	mx=max(n,m);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			read(l);read(r);
			if(l==0)continue;
			if((i+j)&1){
				change(odd,oddx(i,j)-(r-1)/2,oddx(i,j)+(r-1)/2,oddy(i,j)-(r-1)/2,oddy(i,j)+(r-1)/2,l);
				if(r!=1)change(even,evenx(i-1,j)-(r-2)/2,evenx(i+1,j)+(r-2)/2,
									eveny(i,j-1)+(r-2)/2,eveny(i,j+1)-(r-2)/2,l);
			}else{
				change(even,evenx(i,j)-(r-1)/2,evenx(i,j)+(r-1)/2,eveny(i,j)-(r-1)/2,eveny(i,j)+(r-1)/2,l);
				if(r!=1)change(odd,oddx(i-1,j)-(r-2)/2,oddx(i+1,j)+(r-2)/2,
							       oddy(i,j-1)+(r-2)/2,oddy(i,j+1)-(r-2)/2,l);
			}
		}
	}
	for(i=mx;i>=1;i--){
		for(j=mx;j>=1;j--){
			even[i][j]+=even[i+1][j]+even[i][j+1]-even[i+1][j+1];
			odd[i][j]+=odd[i+1][j]+odd[i][j+1]-odd[i+1][j+1];
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			read(d);
			if((i+j)&1){
				tmp=odd[oddx(i,j)][oddy(i,j)];
			}else{
				tmp=even[evenx(i,j)][eveny(i,j)];
			}
			if(tmp<=d)ans++;
		}
	}
	printf("%d",ans);
}

	
	
	
	
	
	
	
}torch;
