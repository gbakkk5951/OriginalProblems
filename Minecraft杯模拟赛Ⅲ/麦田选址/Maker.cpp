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

const string problemname="wheet";

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
	for(I=0;I<20;I++){
		
		outfile=problemname+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		if(I<4){
			n=10-rand()%10;
			m=10-rand()%10;
			k=rand()%50;
			output<<n<<" "<<m<<" "<<k<<endl;
			for(i=0;i<k;i++){
				output<<rand()%n+1<<" "<<rand()%m+1<<endl;
			}
		}else if(I<14){
			n=5000-rand()%3000;
			m=5000-rand()%3000;
			k=(rand()%3==0)?(rand()%201):200;
			output<<n<<" "<<m<<" "<<k<<endl;
			for(i=0;i<k;i++){
				output<<rand()%n+1<<" "<<rand()%m+1<<endl;
			}			
		}else{
			n=10500+500*I;
			m=10500+500*I-rand()%3000;
			k=(rand()%3==0)?(rand()%201):200;
			output<<n<<" "<<m<<" "<<k<<endl;
			for(i=0;i<k;i++){
				output<<rand()%n+1<<" "<<rand()%m+1<<endl;
			}
		}


		output.close();
	}
	
	
	for(I=0;I<5;I++){
		outfile=problemname+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		if(I<3){
			n=25-rand()%10;
			m=25-rand()%10;
			k=rand()%101;
			output<<n<<" "<<m<<" "<<k<<endl;
			for(i=0;i<k;i++){
				output<<rand()%n+1<<" "<<rand()%m+1<<endl;
			}			
		}else if(I==3){
			n=m=47;k=0;
			output<<n<<" "<<m<<" "<<k<<endl;
		}else if(I==4){
			n=lrand()%100000+1;m=lrand()%100000+1;k=0;
			output<<n<<" "<<m<<" "<<k<<endl;			
		}

		
		output.close();
	}	
	
	
}
void run(){
	int I;
	
	for(I=0;I<20;I++){
		
		cmd="std.exe > "+problemname+to_string(I)+".out < "+problemname+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		system(cmd.c_str());
		
		cmd="brute.exe > lyd"+to_string(I)+".out < "+problemname+to_string(I)+".in";
		system(cmd.c_str());
		cmd="fc "+problemname+to_string(I)+".out brute"+to_string(I)+".out";
		if(system(cmd.c_str())){
			system("pause");
		}
	
	}
	for(I=0;I<5;I++){
		
		cmd="std.exe > "+problemname+"_ex"+to_string(I)+".out < "+problemname+"_ex"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
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
