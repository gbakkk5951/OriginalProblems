using namespace std;
int main(){}
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cmath>

namespace Protector{
	const double pi=acos(-1.0);
struct Sig{
	double val;char neg;
};	
struct Node{
	Sig sig[2];double deg;char rev;
	void ini(){
		memset(this,0,sizeof(Node));
	}
};
struct Lson{
	int inline operator [] (int a){
		return a<<1;
	}
}lson;
struct Rson{
	int inline operator [] (int a){
		return a<<1|1;
	}
}rson;
struct SegTree{
	Node node[270000];
	int n,base;
	int range[270000][2];
	void build(){
		int i;
		for(i=base;i<(base<<1);i++){
			range[i][0]=range[i][1]=i-base+1;
		}
		for(i=base-1;i;i--){
			range[i][0]=range[lson[i]][0];
			range[i][1]=range[rson[i]][1];
		}
	}
	void change(int nl,int nr,const Node &agr,int nd=1){
		if(nl>range[nd][1] || nr<range[nd][0])return;
		if(nl<=range[nd][0] && nr>=range[nd][1]){
			subchange(nd,agr);
			return ;
		}
		push(nd);
		change(nl,nr,agr,lson[nd]);
		change(nl,nr,agr,rson[nd]);
	}
	void subchange(int dst,const Node &src){
		int i;
		double x,y;
		//swp
		if(src.rev){
			swap(node[dst].sig[0],node[dst].sig[1]);
			node[dst].rev^=1;
			node[dst].deg*=-1.0;
		}
		//neg
		for(i=0;i<2;i++){
			if(src.sig[i].neg){
				node[dst].deg*=-1.0;
				node[dst].sig[i].neg^=1;
				node[dst].sig[i].val*=-1.0;
			}
		}
		//rot
		if(fabs(src.deg)>1e-6 ){
			double nx=node[dst].sig[0].val,ny=node[dst].sig[1].val;
			x=nx*cos(src.deg/180.0*pi)+ny*(-sin(src.deg/180.0*pi));
			y=nx*sin(src.deg/180.0*pi)+ny*cos(src.deg/180.0*pi);
			node[dst].sig[0].val=x;
			node[dst].sig[1].val=y;
			node[dst].deg+=src.deg;
		}
		//add
		for(i=0;i<2;i++){
			node[dst].sig[i].val+=src.sig[i].val;
		}
	}
	
	void inline push(int nd){
		subchange(lson[nd],node[nd]);
		subchange(rson[nd],node[nd]);
		node[nd].ini();
	}
	
	void print(int nd=1){
		if(range[nd][0]>n)return;
		if(range[nd][0]==range[nd][1]){
			printf("%.2lf %.2lf \n",node[nd].sig[0].val,node[nd].sig[1].val);
			return;
		}
		push(nd);
		print(lson[nd]);
		print(rson[nd]);
	}
}tree;

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
	int n,m;
	_Main(){
		int i,j,k;
		char oper[5];
		double agr[5];
		int a,b,c;
		Node config;
		read(n);read(m);
		tree.n=n;
		for(tree.base=1;tree.base<(n+2);tree.base<<=1);
		tree.build();
		for(i=0;i<n;i++){
			for(j=0;j<2;j++){
				scanf("%lf",&tree.node[tree.base+i].sig[j].val);
			}
		}
		
		for(i=0;i<m;i++){
			scanf("%s",oper);
			config.ini();
			read(a);read(b);
			switch(oper[0]){
				case '0':{
					for(j=0;j<=0;j++){
						scanf("%lf",agr+j);
					}
					config.sig[0].val=agr[0];
					break;
				}		
				case '1':{
					for(j=1;j<=1;j++){
						scanf("%lf",agr+j);
					}
					config.sig[1].val=agr[1];
					break;
				}
				case '2' :{
					config.sig[1].neg=1;
					break;
				}
				case '3' :{
					config.sig[0].neg=1;					
					break;
				}
				case '4' :{
					config.rev=1;						
					break;
				}
				case '5': {
				    config.rev=1;	
				    config.sig[0].neg=1;
				    config.sig[1].neg=1;
					break;
				}
				case '6' :{
					scanf("%lf",&config.deg);
					break;
				}
			}
			tree.change(a,b,config);
		}
		tree.print();
	}
	
}GalaxyBattleship;




}
