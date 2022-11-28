using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<set>
set<long long> tree;

struct _Main{
	
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
long long llrand(){
	return  (long long)((long long)rand()<<47) ^ ((long long)lrand()<<30) | lrand();
}
string file,cmd;
string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}
long long mod[10]={
	(long long)1e9+7,(long long)1e9+9,233333339LL,49935623LL,499356653LL,(long long)1e9+7,(long long)1e9+7,
	(long long)1e9+9,933181336LL,150119970LL
};
int arr[200];
int str[200];
char map[40][40];
void make(){
	tree.clear();
	int i,j,k;int I;int l,m;int n;
	long long a,b,c,d,e,f,g;
	int ndcnt;long long time;
	long long ra[100],rb[100];
	int qcnt,ccnt;
	for(I=0;I<10;I++){
		file="chrono"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		//定棋盘 
		if(I<3){
			n=100;m=100;
		}else if(I<6){
			n=1000;m=1000;
		}else if(I==6){
			n=1;m=1000000;
		}else{
			n=rand()%100000;
			m=1000000/n;
		}
		cout<<n<<" "<<m<<" ";
		//定点数 
		if(I<3){
			ndcnt=6+I;
		}else if(I<9){
			ndcnt=200-rand()%30;
		}else if(I==9){
			ndcnt=200;
		}
		cout<<ndcnt<<" "<<mod[I]<<endl;
		for(i=1;i<=ndcnt;i++){
			if(I==2 || I==5){
				a=2*i%n+1;b=i*3%m+1;
			}else if(I!=9){
				a=lrand()%n+1;b=lrand()%m+1;
			}else{
				if(i==2){
					a=a;b=b;
				}else{
					a=lrand()%n+1;b=lrand()%m+1;
				}
			}
			cout<<a<<" "<<b<<" ";
			do{
				time=llrand()%(I<3?200:(long long)1e18);
			}while(tree.find(time)!=tree.end());
			tree.insert(time);
			cout<<time<<" ";
			c=1+rand()%ndcnt;
			if(I!=9)c=1+rand()%min(ndcnt,10);
			cout<<c<<" ";
			for(j=1;j<=c;j++){
				if(j==c){
					cout<<ndcnt<<" ";
				}else{
					cout<<1+rand()%ndcnt<<" ";
				}
			}
			cout<<endl;
		}
		
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<10;I++){
		cmd="std.exe > chrono"+to_string(I)+".out < chrono"+to_string(I)+".in";
		system(cmd.c_str());
	}
}
	
_Main(){
	getprime();
	srand(time(0));
	make();
	run();
}	
	
	
}Maker;
