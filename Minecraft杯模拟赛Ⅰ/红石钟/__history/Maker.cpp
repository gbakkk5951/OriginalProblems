using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
struct _Main{
	int lim,alph;
template<typename Type>
	void shuffle(Type *beg,int size){
		int i;
		for(i=1;i<size;i++){
			swap(beg[rand()%(i+1)],beg[i]);
		}
	}
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
int randsym(){
	return (rand()&1)?-1:1;
}

string arr[100010];

void make(){
	int i,j,k;int I;int l,m;int n;int g;
	int a,b,c,d;
	int maxpos;int xmin,xmax,ymin,ymax;

	for(I=0;I<2;I++){
		file="redstoneclock"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		if(I==0){
			xmax=1000000;
			n=600000;
			cout<<n<<endl;
			for(i=1;i<=n;i++){
				cout<<lrand()%xmax+1<<" "<<lrand()%xmax+1<<endl;
			}
		}else{
			xmax=10000000;
			n=3000000;
			cout<<n<<endl;
			for(i=1;i<=n;i++){
				cout<<lrand()%xmax+1<<" "<<lrand()%xmax+1<<endl;
			}			
			
		}
		
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<2;I++){
		cerr<<I<<endl;
		cmd="std.exe > redstoneclock"+to_string(I)+".out < redstoneclock"+to_string(I)+".in";
		system(cmd.c_str());
	}
}	
	
_Main(){
	getprime();
	srand(time(0));
//	make();
	run();
}
	
	
}Maker;
