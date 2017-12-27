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



	for(I=18;I<19;I++){
		file="terrordrone"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		
		n=m=40;
		cout<<40<<" "<<40<<endl;
			memset(map,'S',sizeof(map));
			for(i=2;i+1<40;i+=3){
				if((i/3)&1){
					for(j=0;j<38;j++){
						map[j][i]='B';
					}
				}else{
					for(j=2;j<40;j++){
						map[j][i]='B';
					}			
				}
			}
			for(i=0;i<n;i++){
				for(j=0;j<m;j++){
					cout<<map[i][j];
				}
				cout<<endl;
			}
/*		if(I==15){
			for(i=1;i<=n;i++){
				for(j=1;j<=m;j++){
					if( ((i+j)&1) == ((I/2)&1)){
						cout<<'T';
					}else{
						cout<<'S';
					}
				}
				cout<<endl;
			}		
		}else if(I%6==0){

		}else if(I%3==0){
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				if( ((i+j)&1) == ((I/2)&1)){
					cout<<'B';
				}else{
					cout<<'E';
				}
			}
			cout<<endl;
		}
		}else{
			for(i=1;i<=n;i++){
				for(j=1;j<=m;j++){
					if(I!=19)
					cout<<((char)(rand()&1)?'B':'S');
					else cout<<((char)(rand()&1)?'B':'T');
				}
				cout<<endl;
			}
		}
*/
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<20;I++){
		cmd="std.exe > terrordrone"+to_string(I)+".out < terrordrone"+to_string(I)+".in";
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
