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
	return  abs((long long)((long long)rand()<<47) ^ (lrand()<<30) | lrand());
}
string file,cmd;
string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}

int arr[200];
int str[200];
char map[40][40];
void make(){
	int i,j,k;int I;int l,m;int n;
	long long a,b,c,d,e,f,g;
	long long ra[100],rb[100];
	int qcnt,ccnt;
	long long A,B;
	for(I=0;I<10;I++){
		file="virus"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		if(I%3==0)n=m=7;
		else if(I==8)n=1,m=50;
		else if(I&1)n=5,m=10;
		else if(!(I&1))n=10,m=5;
		if(I<6){
			A=n;B=m;
		}else{
			A=1000;B=1000;
		}
		qcnt=5;
		if(I<3){
			ccnt=1000;
		}else{
			ccnt=1000000;
		}
		cout<<A<<" "<<B<<" "<<n<<" "<<m<<" "<<ccnt<<" "<<qcnt<<endl;
		for(i=0;i<ccnt;i++){
			a=rand()%A+1;
			b=rand()%B+1;
			c=a+rand()%(A-a+1);
			d=b+rand()%(B-b+1);
			e=lrand()%(int)1e9+1;
			cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
		}
		for(i=0;i<n*m;i++){
			for(j=0;j<5;j++){
				rb[j]=lrand()%(int)1e9+1;
				ra[j]=lrand()%rb[j];
				cout<<ra[j]<<" "<<rb[j]<<" ";
			}
			cout<<endl;
		}
		for(i=0;i<qcnt;i++){
			if(I==9){
				cout<<(char)'1'+rand()%9;
				for(j=1;j<100000;j++){
					cout<<(char)'0'+rand()%10;
				}
				cout<<endl;
				
			}else if(I==3){
				cout<<0<<endl;
			}else{
				if(I<3){
					cout<<lrand()%1001<<endl;
				}else{
					cout<<llrand()%(long long)1000000000000000000LL<<endl;
				}
			}
			
			
		}
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<10;I++){
		cmd="std.exe > virus"+to_string(I)+".out < virus"+to_string(I)+".in";
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
