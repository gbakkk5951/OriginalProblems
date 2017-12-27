using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<fstream>

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
	return (rand()<<16) | (rand()<<1) ^rand();	
}
long long llrand(){
	return (long long)((long long)lrand()<<32)|((long long )lrand()<<1)^rand();
}
string outfile,cmd,infile;
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

	for(I=0;I<20;I++){
		cerr<<I<<endl;
		outfile="torch"+to_string(I)+".in";
		ofstream output1(outfile.c_str());
		int n,m;
		if(I<6){
			m=30+I*10;
			n=60;
		}else if(I<10){
			n=m=120+I*20;
			n=300;
		}else if(I<16){
			n=m=I*100;
			n=1500;
		}else {
			m=300+I*100;
			n=2200;
		}
		output1<<n<<" "<<m<<endl;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				output1<<randsym()*llrand()%((long long)1e8+1)<<" ";
				if(rand()%3000<3){
					output1<<llrand()%((long long)1e5)+1<<" ";
				}else if(rand()&1){
					output1<<llrand()%((long long)n)+1<<" ";
				}else{
					output1<<llrand()%((long long)m)+1<<" ";
				}
			}
			output1<<endl;
		}
		output1.close();
		infile="_Mid_Proc_.txt";
		cmd="Maker_Answer.exe > "+infile+" < torch"+to_string(I)+".in";
		system(cmd.c_str());
		ifstream input(infile.c_str());
		ofstream output2(outfile.c_str(),ios::app);
		long long val;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				input>>val;
				output2<<val+rand()%3-1<<" ";
			}
			output2<<endl;
		}
		output2.close();
		input.close();
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<10;I++){
		cerr<<I<<endl;
		cmd="std.exe > torch"+to_string(I)+".out < torch"+to_string(I)+".in";
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
