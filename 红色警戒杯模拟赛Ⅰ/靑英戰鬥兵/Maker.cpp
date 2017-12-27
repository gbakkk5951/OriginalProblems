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
	long long hp,hpmx,atk,atkmx,hpadd;
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

	for(I=24;I<25;I++){
		for(i=1;i<17;i++){
			swap(name[i],name[rand()%(i+1)]);
		}

		file="boris"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		if(I==22 ){
			hp=101795046;
			atk=1;
			hpadd=0;
			n=40001;
			m=3;
			cout<<m<<" "<<n<<" "<<hp<<" "<<atk<<" "<<hpadd<<endl;
			cout<<name[0]<<" "<< 1 <<" "<<1<<endl;
			cout<<name[1]<<" "<< 1 <<" "<<1<<endl;
			cout<<name[2]<<" "<< 1 <<" "<<-5730<<endl;
			for(i=1;i<=20000;i++)cout<<name[0]<<endl;
			for(i=1;i<=20000;i++)cout<<name[1]<<endl;
			cout<<name[2]<<endl;
		}else if(I==23){
			hp=101795046;
			atk=1;
			hpadd=0;
			n=40001;
			m=3;
			cout<<m<<" "<<n<<" "<<hp<<" "<<atk<<" "<<hpadd<<endl;
			cout<<name[0]<<" "<< 1 <<" "<<1<<endl;
			cout<<name[1]<<" "<< 1 <<" "<<1<<endl;
			cout<<name[2]<<" "<< 1 <<" "<<-5731<<endl;
			for(i=1;i<=20000;i++)cout<<name[0]<<endl;
			for(i=1;i<=20000;i++)cout<<name[1]<<endl;
			cout<<name[2]<<endl;	
		}else if(I==24){
			hp=1;
			n=40001;
			m=3;
			hpadd=0;
			atk=1;
			cout<<m<<" "<<n<<" "<<hp<<" "<<atk<<" "<<hpadd<<endl;
			cout<<name[0]<<" "<< 2 <<" "<<2<<endl;
			cout<<name[1]<<" "<< 2 <<" "<<2<<endl;
			cout<<name[2]<<" "<< 1 <<" "<<-39999<<endl;			
			for(i=1;i<=20000;i++)cout<<name[0]<<endl;
			for(i=1;i<=20000;i++)cout<<name[1]<<endl;
			cout<<name[2]<<endl;							
		}

		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=23;I<24;I++){
		cmd="std.exe > boris"+to_string(I)+".out < boris"+to_string(I)+".in";
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
