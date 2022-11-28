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
#include<bitset>

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
typedef bitset<155>Num;
Num arr[505],ans;

void make(){
	int i,j,k;int I;int n,m;
	int a,b,c,d;
	int oper;

	for(I=11;I<12;I++){
		cerr<<I<<endl;
		outfile="rsputer_extra"+to_string(I)+".in";
		ofstream output(outfile.c_str());
		/*
		if(I<2){
			n=I*20;
		}else if(I<6){
			n=30+I*4;
		}else{
			n=I*20+120;
		}
		if(I<6){
			m=I*50;
		}else{
			m=(I+1)*500;
		}
		if(I<6){
			k=1;
		}else if(I<10){
			k=I*5;
		}else{
			k=55+I*5;
		}
		*/
//		n=500;m=500;k=5;
		n=500;m=100;k=5;
		output<<n<<" "<<m<<" "<<k<<endl;
		for(i=1;i<=n;i++){
			for(j=0;j<k;j++){
				arr[i][j]=rand()&1;
			}
		}
		
		for(i=1;i<=m;i++){
			oper=rand()%3;
			a=rand()%n+1;b=rand()%n+1;
			if(oper==0){
				output<<a<<" ^ "<<b<<" ";
				ans=arr[a]^arr[b];
			}else if(oper==1){
				output<<a<<" | "<<b<<" ";
				ans=arr[a]|arr[b];			
			}else{
				output<<a<<" & "<<b<<" ";
				ans=arr[a]&arr[b];					
			}
			for(j=k-1;j>=0;j--){
				output<<((I!=2 && I!=8 && I!=18)?ans[j]:(rand()&1));
			}
			output<<endl;				
		}		


		
		
		
		output.close();
	}
	
	
	
}
	
void run(){
	int I;
	for(I=11;I<12;I++){
		cerr<<I<<endl;
		cmd="std.exe > rsputer_extra"+to_string(I)+".out < rsputer_extra"+to_string(I)+".in";
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
