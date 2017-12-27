using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>

struct _Main{
bool small;	
int prime[200];
int cnt;bool vis[200];
void getprime(){
	int i,j;
	for(i=2;i<=150;i++){
		if(!vis[i]){
			prime[cnt++]=i;
		}
		for(j=0;j<cnt && i*prime[j] <=150;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
	
int lrand(){
	return (rand()<<15) | rand();	
}
string file,cmd;
string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}
int gap[2005];
void make(){
	int i,j,k;int I;int l,m;int n;int lim;int g;
	int hp,hpmx,atk,atkmx,hpadd;int block;int e;
	int x1,x2,y1,y2;
	for(I=0;I<20;I++){
		file="commando"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		m=10000;
		n=1000;
		printf("%d %d\n",m,n);
		for(i=0;i<m;i++){
			if(rand()&1){
				x1=lrand()%n;
				x2=x1+lrand()%(n-x1+1);
				y1=lrand()%n;
				y2=y1+lrand()%(n-y1+1);				
				printf("1 %d %d %d %d %d\n",x1,x2,y1,y2,1);
			}else{
				x1=lrand()%n;
				x2=x1+lrand()%(n-x1+1);
				y1=lrand()%n;
				y2=y1+lrand()%(n-y1+1);				
				printf("0 %d %d %d %d\n",x1,x2,y1,y2);				
			}
			
		}
		
		fclose(stdout);
	}
	
	
	
}
int totcnt;
void run(){
	int I;
	cmd="output"+to_string(totcnt/20)+".res";
	freopen(cmd.c_str(),"w",stdout);
	for(I=0;I<20;I++){
		
		cerr<<"["<<I+totcnt<<"]"<<endl;
		
		cmd="segtree.exe > segtree"+to_string(I)+".out < commando"+to_string(I)+".in";
		system(cmd.c_str());		
		cmd="brute.exe > brute"+to_string(I)+".out < commando"+to_string(I)+".in";
		system(cmd.c_str());
		cmd="fc brute"+to_string(I)+".out  segtree"+to_string(I)+".out";
		system(cmd.c_str());
	}
	cerr<<"请按任意键继续. . . "<<endl;
	totcnt+=25;
}
	
_Main(){
	getprime();
small=false;
srand(time(0));
while(1){
	make();
	run();	
	getchar();
}
	

}	
	
	
}Maker;
