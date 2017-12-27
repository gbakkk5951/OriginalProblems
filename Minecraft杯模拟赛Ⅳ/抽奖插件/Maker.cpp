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
#include<fstream>

const string problemname="drawlots";

struct _Main{
int name[100010];	
struct Edge{
	int a,b,c;
}edge[200010];	
	
	int lim,alph;
template<typename Type>
	void shuffle(Type *beg,int size){
		int i;
		for(i=1;i<size;i++){
			swap(beg[rand()%(i+1)],beg[i]);
		}
	}
int prime[2000000];
int primecnt;bool vis[10000005];
void getprime(){
	int i,j;
	for(i=2;i<=10000000;i++){
		if(!vis[i]){
			prime[primecnt++]=i;
		}
		for(j=0;j<primecnt && i*prime[j] <=10000000;j++){
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
void shuffleedge(Edge *beg,int n,int m){
	int i;
	for(i=1;i<=n;i++){
		name[i]=i;
	}
	shuffle(name+1,n);
	shuffle(beg,m);
	for(i=0;i<m;i++){
		if(rand()&1)swap(beg[i].a,beg[i].b);
		beg[i].a=name[beg[i].a];
		beg[i].b=name[beg[i].b];
	}
}
void inline add (int a,int b,int c,int &idx){
	edge[idx].a=a;
	edge[idx].b=b;
	edge[idx].c=c;
	idx++;
}
int arr1[400010],arr2[400010];
char type[4000010];
int mod=1e5+1;
void make(){
	int I;
	int i,j,k;
	int A,B,C;
	int N,M,Q,K;
	int t;
	for(I=0;I<10;I++){
		outfile=problemname+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		A=lrand()%(int)(1e9)+1;
		B=prime[primecnt-I*(rand()%100+1)];
		C=prime[primecnt-I*(rand()%107+1)];
		memset(type,0,sizeof(type));
		switch (I){
			case 0 :{
				N=100;M=100;Q=15;K=15;
				break;
			}
			case 1 :{
				N=300;M=300; Q=50;K=50;	
				break;
			}			
			case 2 :{
			    N=1000;M=1000; Q=150;K=150;
				break;
			}	
			case 3 :{
			    N=10000;M=10000; Q=1500;K=1500;
				break;
			}	
			case 4 :{
		 		N=50000;M=50000; Q=5000;K=5000;
				break;
			}	
			case 5 :{
			 	N=100000;M=100000; Q=15000;K=15000;
				break;
			}	
			case 6 :{
				N=2000000;M=2000000; Q=50000;K=50000;
				break;
			}	
			case 7 :{
			    N=3000000;M=3000000; Q=100000;K=100000;
				break;
			}	
			case 8 :{
			    N=3500000;M=3500000; Q=150000;K=150000;
				break;
			}	
			case 9 :{
			    N=3500000;M=4000000; Q=200000;K=200000;					
				break;
			}
		}
		for(i=1;i<=Q/2;i++){
			arr1[i]=M-i+1;
			type[M-i+1]=1;
		}
		for(i=Q/2+1;i<=Q;i++){
			while(type[t=lrand()%M+1]);
			arr1[i]=t;
			type[t]=1;
		}
		for(i=1;i<=K;i++){
			while(type[t=lrand()%M+1]);
			arr2[i]=t;
			type[t]=1;
		}
		sort(arr1+1,arr1+1+Q);
		sort(arr2+1,arr2+1+K);
		output<<A<<" "<<B<<" "<<C<<endl;
		output<<N<<" "<<M<<" "<<Q<<" "<<K<<endl;
		for(i=1;i<=Q;i++){
			output<<arr1[i]<<" ";
		}
		cout<<endl;
		for(i=1;i<=K;i++){
			output<<arr2[i]<<" "<<(lrand()%N+1)<<" ";
		}
		output<<endl;
		EndFor:
		output.close();
	}
	
	
	for(I=0;I<5;I++){
		outfile=problemname+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		memset(type,0,sizeof(type));
		
		if(I<2){
			A=1;B=1;C=0;
			N=1000;M=50000;Q=20000;K=10000;
			for(i=1;i<=Q;i++){
				arr1[i]=M-(i-1)*2;
				type[M-(i-1)*2]=1;
			}
			for(i=1;i<=K;i++){
				while(type[t=lrand()%M+1]);
				arr2[i]=t;
				type[t]=1;
			}
			
		}else if(I==2){
			A=1;B=1;C=0;
			N=1500;M=50000;Q=10000;K=200;
			for(i=1;i<=Q;i++){
				while(type[t=lrand()%M+1]);
				arr1[i]=t;
				type[t]=1;
			}			
			for(i=1;i<=K;i++){
				while(type[t=lrand()%M+1]);
				arr2[i]=t;
				type[t]=1;
			}			
		}else if(I<5){
			A=lrand()%(int)(1e9)+1;
			B=lrand()%(int)(1e9)+1;
			C=lrand()%(int)(1e9)+1;
			if(I==4){
				B=1;C=1;
			}
			N=150;M=100000;Q=50000;K=47500;
			for(i=1;i<=Q;i++){
				while(type[t=lrand()%M+1]);
				arr1[i]=t;
				type[t]=1;
			}
			for(i=1;i<=K;i++){
				while(type[t=lrand()%M+1]);
				arr2[i]=t;
				type[t]=1;
			}
		}
		output<<A<<" "<<B<<" "<<C<<endl;
		output<<N<<" "<<M<<" "<<Q<<" "<<K<<endl;
		sort(arr1+1,arr1+1+Q);
		sort(arr2+1,arr2+1+K);		
		for(i=1;i<=Q;i++){
			output<<arr1[i]<<" ";
		}
		output<<endl;
		for(i=1;i<=K;i++){
			output<<arr2[i]<<" "<<(lrand()%N+1)<<" ";
		}
		output<<endl;		
		
		output.close();
	}	
	
	
}
void run(){
	int I;

	for(I=0;I<10;I++){
		cmd="std.exe > "+problemname+to_string(I)+".out < "+problemname+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		system(cmd.c_str());
		/*
		cmd="brute.exe > brute"+to_string(I)+".out < "+problemname+to_string(I)+".in";
		system(cmd.c_str());
		cmd="fc brute"+to_string(I)+".out "+problemname+to_string(I)+".out";
		if(system(cmd.c_str())){
			system("pause");
		}
		*/
	}
	
	for(I=0;I<5;I++){
		cmd="std.exe > "+problemname+"_ex"+to_string(I)+".out < "+problemname+"_ex"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		system(cmd.c_str());
		/*
		cmd="brute.exe > brute_ex"+to_string(I)+".out < "+problemname+"_ex"+to_string(I)+".in";
		system(cmd.c_str());
		cmd="fc brute_ex"+to_string(I)+".out "+problemname+"_ex"+to_string(I)+".out";
		if(system(cmd.c_str())){
			system("pause");
		}
		*/
	}
	
}
	
_Main(){
	getprime();
	srand(time(0));
	
	make();
	run();		


}	
	
	
}Maker;
