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
	/*
	for(I=0;I<20;I++){
		cerr<<"Make "<<I<<endl;
		outfile="metro"+to_string(I)+".in";
		ofstream output(outfile.c_str());
		if(I<6){
			n=10+I*10;
			if(I==3)k=lrand()%((int)(5e8+1));
			else k=lrand()%((int)n*10+1);
			output<<n<<" "<<k<<endl;
			for(i=1;i<=n-1;i++){
				output<<lrand()%((int)1e2+1)<<" "<<lrand()%((int)1e3+1)<<" "<<lrand()%((int)1e2+1)<<endl;
			}				
			
		}else if(I<12){
			n=I*500+4500;
			if(I==10)k=lrand()%((int)(5e8+1));
			else k=lrand()%((int)n*100+1);
			output<<n<<" "<<k<<endl;
			for(i=1;i<=n-1;i++){
				output<<lrand()%((int)1e5+1)<<" "<<lrand()%((int)1e6+1)<<" "<<lrand()%((int)1e5+1)<<endl;
			}			
			
			
		}else if(I<16){
			n=25000+I*5000;
			k=lrand()%((int)5e8+1);
			output<<n<<" "<<k<<endl;
			for(i=1;i<=n-1;i++){
				output<<lrand()%((int)1e4+1)<<" "<<lrand()%((int)1e7+1)<<" "<<lrand()%((int)1e4+1)<<endl;
			}
		

		}else if(I<20){
			n=100000;
			k=lrand()%((int)5e8+1);
			output<<n<<" "<<k<<endl;
			for(i=1;i<=n-1;i++){
				output<<lrand()%((int)1e5+1)<<" "<<lrand()%((int)1e9+1)<<" "<<lrand()%((int)1e5+1)<<endl;
			}			
			
		}

		output.close();
	}
	*/
	/*
	for(I=9;I<10;I++){
		cerr<<"Make "<<I<<endl;
		outfile="metro_ex"+to_string(I)+".in";
		ofstream output(outfile.c_str());
		n=100000;k=99998;
		output<<n<<" "<<k<<endl;
		for(i=1;i<=n;i++){
			output<<1<<" "<<1<<" "<<1<<endl;
		}
		output.close();
	}	*/
	
	
}
	
void run(){
	int I;
	/*
	for(I=0;I<20;I++){
		cerr<<"Run: "<<I<<endl;
		cmd="std.exe > metro"+to_string(I)+".out < metro"+to_string(I)+".in";
		system(cmd.c_str());

			
		
//			cmd="brute.exe > brute"+to_string(I)+".out < metro"+to_string(I)+".in";
//			system(cmd.c_str());
//			cmd="fc brute"+to_string(I)+".out metro"+to_string(I)+".out";
//			if(system(cmd.c_str())){
//				system("pause");
//			}
		
	}
	*/
	
	for(I=9;I<10;I++){
		cerr<<"Run: "<<I<<endl;
		cmd="brute.exe > brute"+to_string(I)+".out < metro_ex"+to_string(I)+".in";
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
