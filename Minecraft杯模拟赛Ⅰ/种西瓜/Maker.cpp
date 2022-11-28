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
	int rd;


	for(I=10;I<20;I++){
		if(I==17 || I==16)continue;
		file="melon"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		int cnt=0;
		if(I<10){
			m=100;
			if(I<4){
				n=1;
			}else{
				n=I+1;
			}
			printf("%d %d 0\n",n,m);
			for(i=1;i<=n;i++){
				for(j=1;j<=m;j++){
					if(I==1){
						if(j&1){
							putchar('l');
						}else{
							putchar('o');
						}
						continue;
					}else if(I==5){
						if((i+j)&1){
							putchar('l');
						}else{
							putchar('o');
						}
						continue;
					}
					rd=rand()%7;
					if(rd<3){
						putchar('l');
					}else if(rd==6){
						putchar('x');
					}else{
						putchar('o');
					}
				}
				putchar('\n');
			}
			
			
			
		}else{
			m=10;
			if(I<14){
				n=1;
			}else{
				n=I-10+1;
			}
			printf("%d %d 1\n",n,m);
			for(i=1;i<=n;i++){
				for(j=1;j<=m;j++){
					if(I==15 || I==10 || I==14){
						if( ((i+j+I)&1) && cnt<18){
							cnt++;
							putchar('l');
						}else{
							putchar('o');
						}
						continue;
					}
					
					rd=rand()%7;
					if(rd<3 && cnt<18){
						cnt++;
						putchar('l');
					}else if(rd==6){
						putchar('x');
					}else{
						putchar('o');
					}
				}
				putchar('\n');
			}			
			
		}
		

		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	/*for(I=0;I<20;I++){
		cmd="std.exe > melon"+to_string(I)+".out < melon"+to_string(I)+".in";
		system(cmd.c_str());
	}*/
	for(I=2;I<4;I++){
		cmd="std.exe > melon_ex"+to_string(I)+".out < melon_ex"+to_string(I)+".in";
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
