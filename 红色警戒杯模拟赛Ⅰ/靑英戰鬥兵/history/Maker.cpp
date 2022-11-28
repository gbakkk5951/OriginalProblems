using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
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
string name[5000]={
	"1","2","3","4","5","3星动员兵","美国大兵","動員兵","动员兵","美國大兵","火箭飛行兵","USpresident","HammerTank","Ivan","Kriov","gbakkk5951","光棱塔"
	,"發電廠","MCV","狂獸人" ,"尤里X","戰爭工廠"
};
void make(){
	int i,j,k;int I;int l,m;int n;int lim;int g;
	int hp,hpmx,atk,atkmx,hpadd;
//	name[0]=;name[1]="美國大兵"
	for(i=17;i<5000;i++){
		l=1+rand()%100;
		for(j=0;j<l;j++){
			k=rand()%3;
			if(k==0){
				name[i]+='0'+rand()%10;
			}else if(k==1){
				name[i]+='a'+rand()%26;
			}else{
				name[i]+='A'+rand()%26;
			}
		}
	}
	for(I=50;I<51;I++){
		file="ypa"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		if(I<10){
			m=rand()%50+5;
			n=10+rand()%5;k=rand()%10;hp=500-lrand()%400;hpadd=lrand()%700;
			atk=lrand()%2000+1;atkmx=lrand()%300+1;hpmx=lrand()%300+1;
		}else if(I<15){
			n=lrand()%4900+100;m=lrand()%50000+1;k=11+rand()%10;hp=lrand()%(int)(1e9-500)+500;
			hpadd=lrand()%(int)(1e9);hpmx=1e5;atkmx=1e5;atk=lrand()%(int)(1e5)+1;
		}else if(I<20){
			n=5000-rand()%100;m=50000-rand()%1005;k=20-rand()%3;hp=lrand()%(int)(1e9-500)+500;
			hpadd=lrand()%(int)(1e9);hpmx=1e5;atkmx=1e5;atk=lrand()%(int)(1e5)+1;			
		}else{
			m=10;
			n=5;k=rand()%6;hp=500;hpadd=700;
			atk=1000;atkmx=300;hpmx=300;			
		}
		if(I==18){
			n=k;
		}
		if(I==8){
			k=0;
		}
		if(I==7){
			atk=1;
		}
		printf("%d %d %d %d %d\n",n,m,hp,atk,hpadd);
		for(i=0;i<k;i++){
			cout<<name[i]<<" ";
			printf("%d %d\n",lrand()%hpmx+1,lrand()%atkmx+1);
		}
		for(i=k;i<n;i++){
			cout<<name[i]<<" ";
			printf("%d %d\n",lrand()%hpmx+1,-(lrand()%atkmx));
		}
		for(i=0;i<m;i++){
			if(k){
				if(lrand()%n<k){
					cout<<name[lrand()%k]<<endl;
				}else{
					cout<<name[lrand()%n]<<endl;
				}
			}else{
				cout<<name[lrand()%n]<<endl;
			}
		}

		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=21;I<22;I++){
		cmd="std.exe > ypa"+to_string(I)+".out < ypa"+to_string(I)+".in";
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
