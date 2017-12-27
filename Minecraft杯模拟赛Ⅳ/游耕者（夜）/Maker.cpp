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

const string problemname="nomadism_night";

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
int mod=1e5+1;
void make(){
	int n;
	int I;
	int i,j,k;
	int mx;
	int range;
	int x,y;
	for(I=0;I<10;I++){
		mx=1e4+1;
		outfile=problemname+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		if(I==0){
			n=7;
		}else if(I==1){
			n=14;
		}else if(I==2){
			n=50;
		}else if(I==3){
			n=1000;
		}else if(I==4){
			n=2000;
		}else if(I==5){
			n=3000;
			output<<n<<endl;
			for(i=1;i<=20;i++){
				range=20+rand()%50;
				x=lrand()%mx*randsym();
				y=lrand()%mx*randsym();
				for(j=1;j<=80;j++){
					output<<(x+(lrand()%range*randsym()))
					<<" "<<(y+(lrand()%range*randsym()))<<endl;
				}
			}
			for(i=1;i<=1400;i++){
				output<<(lrand()%mx*randsym())<<" "<<(lrand()%mx*randsym())<<endl;
			}
			goto EndFor;
		}else if(I==6){
			n=1e5;
		}else if(I==7){
			n=2e5;
			output<<n<<endl;
			for(i=1;i<=30;i++){
				range=25+rand()%55;
				x=lrand()%mx*randsym();
				y=lrand()%mx*randsym();
				for(j=1;j<=800;j++){
					output<<(x+(lrand()%range*randsym()))
					<<" "<<(y+(lrand()%range*randsym()))<<endl;
				}
			}
			for(i=1;i<=2e5-24000;i++){
				output<<(lrand()%mx*randsym())<<" "<<(lrand()%mx*randsym())<<endl;
			}
			goto EndFor;
		}else if(I==8){
			n=3e5;
		}else if(I==9){
			n=4e5;
			output<<n<<endl;
			for(i=1;i<=300;i++){
				range=30+rand()%70;
				x=lrand()%mx*randsym();
				y=lrand()%mx*randsym();
				for(j=1;j<=800;j++){
					output<<(x+(lrand()%range*randsym()))
					<<" "<<(y+(lrand()%range*randsym()))<<endl;
				}
			}
			for(i=1;i<=4e5-240000;i++){
				output<<(lrand()%mx*randsym())<<" "<<(lrand()%mx*randsym())<<endl;
			}		
			goto EndFor;	
		}
		output<<n<<endl;
		for(i=1;i<=n;i++){
			output<<(lrand()%mx*randsym())<<" "<<(lrand()%mx*randsym())<<endl;
		}
		EndFor:
		output.close();
	}
	
	
	for(I=0;I<5;I++){
		outfile=problemname+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		
		if(I<3){
			mx=1+I*20;
			n=3000+I*198500;
			output<<n<<endl;
			for(i=1;i<=n;i++){
				output<<(lrand()%mx*randsym())<<" "<<(lrand()%mx*randsym())<<endl;
			}
		}else if(I==3){
			mx=10001;
			n=80000;
			output<<n<<endl;
			for(i=1;i<=1000;i++){
				range=20+rand()%50;
				x=lrand()%mx*randsym();
				y=lrand()%mx*randsym();
				for(j=1;j<=80;j++){
					output<<(x+(lrand()%range*randsym()))
					<<" "<<(y+(lrand()%range*randsym()))<<endl;
				}
			}
			
		}else if(I==4){
			mx=10001;
			n=8000;	
			output<<n<<endl;		
			for(i=1;i<=200;i++){
				range=20+rand()%50;
				x=lrand()%(mx-range)*randsym();
				y=lrand()%(mx-range)*randsym();
				for(j=1;j<=40;j++){
					output<<(x+(lrand()%range*randsym()))
					<<" "<<(y+(lrand()%range*randsym()))<<endl;
				}
			}
		}
		
		
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
	}
	
}
	
_Main(){
	getprime();
	srand(time(0));
	
//	make();
	run();		


}	
	
	
}Maker;
