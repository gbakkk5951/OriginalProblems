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
	int i,j,k;int I;int l,m;int n;int g;
	int a,b,c,d;
	int eidx;int nd;int tmp;
	for(I=0;I<10;I++){
		
		outfile="spyplane"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		eidx=0;
		if(I<2){
			n=40000+I*60000;
			m=n-1;
			for(i=2;i<=n;i++){
				add(i,rand()%(i-1)+1,rand()%1001,eidx);
			}
		}else if(I<5){
			n=20000+I*20000;
			m=n*2;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%1001,eidx);
			}
			nd=1;
			for(i=1;i<n;i++){
				tmp=lrand()%n+1;
				add(nd,tmp,rand()%1001,eidx);
				nd=tmp;
			}
			add(tmp,1,rand()%1001,eidx);
		}else{
			n=10000+I*10000;
			m=n*2;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%1001,eidx);
			}
			nd=1;
			for(i=1;i<n-((I+1)/2);i++){
				tmp=lrand()%n+1;
				add(nd,tmp,rand()%1001,eidx);
				nd=tmp;
			}
			add(tmp,1,rand()%1001,eidx);			
			for(i=1;i<=((I+1)/2);i++){
				tmp=lrand()%n+1;nd=lrand()%n+1;
				while(nd==tmp)nd=lrand()%n+1;
				add(nd,tmp,rand()%1001,eidx);
			}
		}

		shuffleedge(edge,n,m);
		output<<n<<" "<<m<<endl;
		for(i=0;i<m;i++){
			output<<edge[i].a<<" "<<edge[i].b<<" "<<edge[i].c<<endl;
		}
		output.close();
	}
	
	
	for(I=3;I<10;I++){
		outfile="spyplane_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		eidx=0;
		if(I==3){
			n=20;
			m=190;
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++){
					add(i,j,rand()%1001,eidx);
				}
			}
		}else if(I==4){
			n=5000+I*5000;
			m=n*2;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%7,eidx);
			}
			nd=1;
			for(i=1;i<n-((I+1)/2);i++){
				tmp=lrand()%n+1;
				add(nd,tmp,rand()%7,eidx);
				nd=tmp;
			}
			add(tmp,1,rand()%7,eidx);			
			for(i=1;i<=((I+1)/2);i++){
				tmp=lrand()%n+1;nd=lrand()%n+1;
				while(nd==tmp)nd=lrand()%n+1;
				add(nd,tmp,rand()%7,eidx);
			}
		}else if(I==5){
			n=5000+I*5000;
			m=n*2;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%1,eidx);
			}
			nd=1;
			for(i=1;i<n-((I+1)/2);i++){
				tmp=lrand()%n+1;
				add(nd,tmp,rand()%1,eidx);
				nd=tmp;
			}
			add(tmp,1,rand()%1,eidx);			
			for(i=1;i<=((I+1)/2);i++){
				tmp=lrand()%n+1;nd=lrand()%n+1;
				while(nd==tmp)nd=lrand()%n+1;
				add(nd,tmp,rand()%1,eidx);
			}			
		}else if(I==6){
			n=20;
			m=190;
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++){
					add(i,j,rand()%7,eidx);
				}
			}			
		}else if(I==7){
			n=20;
			m=190;
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++){
					add(i,j,rand()%1,eidx);
				}
			}				
		}else if(I==8){
			n=5000+I*5000;
			m=n+10;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%1001,eidx);
			}			
			for(i=1;i<=10;i++){
				tmp=lrand()%n+1;nd=lrand()%n+1;
				while(nd==tmp)nd=lrand()%n+1;
				add(nd,tmp,rand()%1001,eidx);
			}
		}else if(I==9){
			n=5000+I*5000;
			m=n+10;
			for(i=1;i<=n;i++){
				add(i,i%n+1,rand()%7,eidx);
			}			
			for(i=1;i<=10;i++){
				tmp=lrand()%n+1;nd=lrand()%n+1;
				while(nd==tmp)nd=lrand()%n+1;
				add(nd,tmp,rand()%7,eidx);
			}
		}
		shuffleedge(edge,n,m);
		output<<n<<" "<<m<<endl;
		for(i=0;i<m;i++){
			output<<edge[i].a<<" "<<edge[i].b<<" "<<edge[i].c<<endl;
		}		
		
		output.close();
	}	
	
	
}
void run(){
	int I;
	
	for(I=0;I<10;I++){
		
		cmd="std.exe > spyplane"+to_string(I)+".out < spyplane"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		system(cmd.c_str());

//			cmd="brute.exe > brute"+to_string(I)+".out < metro"+to_string(I)+".in";
//			system(cmd.c_str());
//			cmd="fc brute"+to_string(I)+".out metro"+to_string(I)+".out";
//			if(system(cmd.c_str())){
//				system("pause");
//			}
		
	}
	for(I=0;I<10;I++){
		
		cmd="std.exe > spyplane_ex"+to_string(I)+".out < spyplane_ex"+to_string(I)+".in";
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
