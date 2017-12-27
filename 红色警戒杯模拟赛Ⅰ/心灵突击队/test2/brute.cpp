using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
int sq;int base;
int l[2055],r[2055];
int xmin,ymin,xmax,ymax;

struct LeftSon{
	int inline  operator [](const int &a){
		return a<<1;
	}
}lson;
struct Right{
	int inline  operator [](const int &a){
		return a<<1|1;
	}
}rson;

struct Dis{
	int inline operator () (const int &a,const int &b){
		return abs(a-b)+1;
	}
}dis;
void build(int nd=1,int s=0,int t=base-1){
	l[nd]=s;r[nd]=t;
	if(s!=t){
		build(lson[nd],s,(s+t)>>1);
		build(rson[nd],((s+t)>>1)+1,t);
	}
}
struct Size{
	int inline  operator [](const int &a){
		return dis(r[a],l[a]);
	}
}size;


long long arr[1050][1050]; 


struct Map{

long long query(int x1,int x2,int y1,int y2){
	x1-=xmin;x2-=xmin;y1-=ymin;y2-=ymin;
	long long ans=0;
	int i,j;
	for(i=x1;i<=x2;i++){
		for(j=y1;j<=y2;j++){
			ans+=arr[i][j];
		}
	}
	return ans;
}		
	
void change(int x1,int x2,int y1,int y2,long long val){
	x1-=xmin;x2-=xmin;y1-=ymin;y2-=ymin;
	x1=max(0,x1);x2=min(dis(xmin,xmax),x2);
	y1=max(0,y1);y2=min(dis(ymin,ymax),y2);	
	if(x1>x2 || y1>y2)return;
	int i,j;
	for(i=x1;i<=x2;i++){
		for(j=y1;j<=y2;j++){
			arr[i][j]+=val;
		}
	}

	
}	
	
	
}map;






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
		}
		a*=f;
	}

_Main(){
	int n,T;
	read(T);
	
	read(xmin);read(ymin);read(xmax);read(ymax);
	n=max(dis(xmin,xmax),dis(ymin,ymax));
	int i;
	for(i=0;(1<<i)<(n+3);i++);
	base=(1<<i);sq=sqrt(base);
	int a,b,c,d,e;int op;
	build();
	while(T--){
		read(op);
		if(op==0){
			read(a);read(b);read(c);read(d);
			printf("%lld\n",map.query(a,c,b,d));
		}else if(op==1){
			read(a);read(b);read(c);read(d);
			map.change(a-c+1,a+c-1,b-c+1,b+c-1,d);
			map.change(a-c+2,a+c-2,b+c,b+c,(d+3)/4);
			map.change(a-c+2,a+c-2,b-c,b-c,(d+3)/4);
			map.change(a-c,a-c,b-c+2,b+c-2,(d+3)/4);
			map.change(a+c,a+c,b-c+2,b+c-2,(d+3)/4);	
		}else{
			read(a);read(b);read(c);read(d);read(e);
			map.change(a,c,b,d,-e);
		}
	}
	
	
	
}	
	
	
}block;

