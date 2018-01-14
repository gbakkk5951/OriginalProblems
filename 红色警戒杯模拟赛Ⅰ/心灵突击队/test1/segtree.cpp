using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
int sq;int base;
int l[2055],r[2055];


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



struct SumTree{
long long sig[2055];
long long val[2055];
void inline pushsig(int nd){
	if(sig[nd]){
		sig[lson[nd]]+=sig[nd];
		sig[rson[nd]]+=sig[nd];
		val[lson[nd]]+=sig[nd]*size[lson[nd]];
		val[rson[nd]]+=sig[nd]*size[rson[nd]];		
		sig[nd]=0;
	}
}
	
long long query(int ql,int qr,int nd=1)	{

	if(l[nd]>qr || r[nd]<ql)return 0;
	if(ql<=l[nd] && r[nd]<=qr)return val[nd];
	pushsig(nd);
	return query(ql,qr,lson[nd])+query(ql,qr,rson[nd]);
}
void change(int ql,int qr,long long add,int nd=1){
	if(l[nd]>qr || r[nd]<ql)return;
	if(ql<=l[nd] && r[nd]<=qr){
		val[nd]+=add*(size[nd]);
		sig[nd]+=add;
	}else{
		pushsig(nd);
		change(ql,qr,add,lson[nd]);
		change(ql,qr,add,rson[nd]);
		val[nd]=val[lson[nd]]+val[rson[nd]];
	}
}

}tree;



struct Map{
SumTree sqtree[35];
SumTree rowtree[1005];
SumTree sigtree[35];

long long query(int x1,int x2,int y1,int y2){
	long long ans=0;int pos=y1/sq;
	int i;
	if(y1%sq){
		for(i=y1;i<(pos+1)*sq && i<=y2;i++){
			ans+=rowtree[i].query(x1,x2);
//			printf("ans+=row[%d](%d,%d)=%d\n",i,x1,x2,rowtree[i].query(x1,x2));
		}
//		printf("[1]ans=%lld+%lld\n",ans,sigtree[pos].query(x1,x2)*min((pos+1)*sq-y1,dis(y1,y2)));
		ans+=sigtree[pos].query(x1,x2)*min((pos+1)*sq-y1,dis(y1,y2));
		pos++;
	}
	while((pos+1)*sq<=y2+1){
		ans+=sqtree[pos].query(x1,x2);
		ans+=sigtree[pos].query(x1,x2)*sq;
//		printf("[0]ans+=%lld +%lld \n",sqtree[pos].query(x1,x2),sigtree[pos].query(x1,x2)*sq);
		pos++;
	}
	if(pos*sq<=y2){
		for(i=pos*sq;i<=y2;i++){
			ans+=rowtree[i].query(x1,x2);
//			printf("ans+=row[%d](%d,%d)=%d\n",i,x1,x2,rowtree[i].query(x1,x2));
		}
		ans+=sigtree[pos].query(x1,x2)*dis(y2,pos*sq);
//		printf("[2]ans=%lld+[%d]%lld*%d\n",ans,pos,sigtree[pos].query(x1,x2),dis(y2,pos*sq));
	}
//	printf("----------");
	return ans;
}		
	
void change(int x1,int x2,int y1,int y2,long long val){
	int pos=y1/sq;
	int i;
	if(y1%sq){
		for(i=y1;i<(pos+1)*sq && i<=y2;i++){
			rowtree[i].change(x1,x2,val);
//			printf("row[%d](%d,%d)+=%d\n",i,x1,x2,val);
		}
		sqtree[pos].change(x1,x2,val*min((pos+1)*sq-y1,dis(y1,y2)));
		
		pos++;
	}
	while((pos+1)*sq<=y2+1){
		sigtree[pos].change(x1,x2,val);
//		printf("sig[%d](%d,%d)+=%d\n",pos,x1,x2,val);
		pos++;
	}
	if(pos*sq<=y2){
		for(i=pos*sq;i<=y2;i++){
//			printf("row[%d](%d,%d)+=%d\n",i,x1,x2,val);
			rowtree[i].change(x1,x2,val);
		}
		sqtree[pos].change(x1,x2,val*dis(y2,pos*sq));
//		printf("Sqtree[%d].add(%d,%d)=%d\n",pos,x1,x2,val*dis(y2,pos*sq));
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
	read(T);read(n);
	int i;
	for(i=0;(1<<i)<(n+3);i++);
	base=(1<<i);sq=sqrt(base);
	int a,b,c,d,e,f,g;int op;
	build();
	while(T--){
		read(op);
		if(op==1){
			read(a);read(b);read(c);read(d);read(e);
			map.change(a,b,c,d,e);
		}else{
			read(a);read(b);read(c);read(d);
			printf("%lld\n",map.query(a,b,c,d));
		}
	}
	
	
	
}	
	
	
}block;

