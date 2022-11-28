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

const string problemname="agriculture";

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
void make(){
	int n,m,k,a,b;
	int I;
	int i,j;
	int la,lb;
	/*
	for(I=0;I<10;I++){
		
		outfile=problemname+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		if(I<4){
			n=1;
			m=30+rand()%21;
			output<<n<<endl;
			output<<"0.0";
			if(I<2){
				for(i=1;i<=m;i++){
					output<<(char)(rand()%10+'0');
				}
				output<<" 0"<<endl;
			}else{
				la=rand()%(m-10)+1;
				lb=m-la;
				for(i=1;i<=la;i++){
					output<<(char)(rand()%10+'0');
				}
				output<<" ";	
				for(i=1;i<=lb;i++){
					output<<(char)(rand()%10+'0');
				}
				output<<endl;							
			}
		}else if(I<6){
			n=I;
			output<<n<<endl;
			la=lrand()%190+1;
			lb=195-la;
			for(j=1;j<=n;j++){
				la=lrand()%190+1;
				lb=195-la;		
				output<<"0.0";
				for(i=1;i<=la;i++){
					output<<(char)(rand()%10+'0');
				}			
				output<<" ";	
				for(i=1;i<=lb;i++){
					output<<(char)(rand()%10+'0');
				}
				output<<endl;					
			}
			
		}else{
			n=10;
			output<<n<<endl;
			for(j=1;j<=n;j++){
				la=lrand()%190+1;
				lb=195-la;		
				output<<"0.0";		
				for(i=1;i<=la;i++){
					output<<(char)(rand()%10+'0');
				}			
				output<<" ";	
				for(i=1;i<=lb;i++){
					output<<(char)(rand()%10+'0');
				}
				output<<endl;					
			}
		}


		output.close();
	}
	*/
	
	for(I=5;I<9;I++){
		outfile=problemname+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		n=10;
		output<<n<<endl;
		if(I!=8)
		for(i=1;i<=n;i++){
			output<<"0.0";			
			if(((i&1)&&I==5 )|| I==7){
				output<<" ";
				for(j=1;j<=195;j++){
					output<<(char)(rand()%10+'0');
				}
				output<<endl;
			}else{
				for(j=1;j<=195;j++){
					output<<(char)(rand()%10+'0');
				}
				output<<" 0"<<endl;				
			}
			
		}
		if(I==8){
			
			for(i=1;i<=n;i++){
				la=i*18;
				lb=195-la;
				output<<"0.0";
				for(j=1;j<=la;j++){
					output<<(char)(rand()%10+'0');
				}
				output<<" ";	
				for(j=1;j<=lb;j++){
					output<<(char)(rand()%10+'0');
				}
				output<<endl;					
			}
			
			
		}
		
		output.close();
	}	
	
	
}
void run(){
	int I;
	/*
	for(I=0;I<10;I++){
		
		cmd="std.exe > "+problemname+to_string(I)+".out < "+problemname+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		system(cmd.c_str());

//			cmd="brute.exe > brute"+to_string(I)+".out < metro"+to_string(I)+".in";
//			system(cmd.c_str());
//			cmd="fc brute"+to_string(I)+".out metro"+to_string(I)+".out";
//			if(system(cmd.c_str())){
//				system("pause");
//			}
		
	}*/
	for(I=0;I<9;I++){
		
		cmd="std.exe > "+problemname+"_ex"+to_string(I)+".out < "+problemname+"_ex"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
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
