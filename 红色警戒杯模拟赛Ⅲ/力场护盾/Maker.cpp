using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<windows.h>
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
string name[305];
string org[34]={"",
	"����̹��","�������","��װ���","����ʦ","MCV","WestWood֮��","��ʱ�ձ���","��Ȯ",
	"����̹��","��ʱ�ղɿ�","����վ","��ʯ������","��ʯ������","�๦�ܲ�����","��ǹ�ﱤ",
	"������б�","̷��","�˾�Χǽ","��܇���S","�ѿp�a����","�ۇ����w��","������","���I",
	"�gՙ�l��","���r�Ղ��̓x","�����ƃx","��ָ��","���������","�S�ޏS","�b��̹��",
	"���YҪ��","��Ӱ̹��","�������"
};


int n,m,e,i,j,k,I,block;
char buf[30];



void make(){
int pbase,plim,tlim;
int n,a,b,m,s,r;
int x1,x2,y1,y2;
	for(I=0;I<20;I++){
		
		file="forceshield"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
	
		if(I<6){
			plim=30;
			tlim=30;
			a=b=1000;
			n=2000;
			pbase=-14+rand()%(30-plim+1);
			m=lrand()%plim;
			s=lrand()%tlim;
			r=lrand()%tlim;
		}else{
			pbase=-1499+rand()%(3000-plim+1);
			if(I<15){
				tlim=3000-lrand()%1500;
				plim=3000-lrand()%1500;
				a=200000-lrand()%100000;
				b=200000-lrand()%100000;
			}else{
				a=b=200000;
				n=500000;
				tlim=3000;
				plim=3000;
			}
			if((I&1) && (I!=19)){
				b=200000;
				m=lrand()%plim;
				s=lrand()%tlim;
				r=lrand()%tlim;
			}else if(I!=19){
				b=1000;
				m=lrand()%200;
				r=lrand()%50;
				s=lrand()%50;
			}else{
				b=1000;
				m=plim;
				r=lrand()%50;
				s=lrand()%50;				
			}
		}
		
		cout<<n<<" "<<m<<" "<<r<<" "<<s<<" "<<a<<" "<<b<<endl;
		for(i=1;i<=n;i++){
			cout<<pbase+lrand()%plim<<" "<<1+lrand()%tlim<<endl;
		}
		for(i=1;i<=a;i++){
			x1=lrand()%plim;
			x2=x1+lrand()%min(plim-x1,(I&1)?200:3000);
			y1=lrand()%(tlim+1);
			y2=lrand()%min(tlim-y1+1,(I&1)?200:3000);
			cout<<pbase+x1<<" "<<x2+pbase<<" "<<y1<<" "<<y2+1<<" "<<lrand()%1000+1<<endl;
		}
		for(j=1;j<=b;j++){
			x1=lrand()%plim;
			x2=x1+lrand()%min(plim-x1,(I&1)?200:3000);
			y1=lrand()%tlim+1;
			y2=lrand()%min(tlim-y1+1,(I&1)?200:3000);
			cout<<pbase+x1<<" "<<x2+pbase<<" "<<y1<<" "<<y2+1<<" "<<lrand()%1000+1<<endl;			
		}
		
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<20;I++){
		cmd="std.exe > forceshield"+to_string(I)+".out < forceshield"+to_string(I)+".in";
		system(cmd.c_str());
	}
}
	
_Main(){

	srand(time(0));
	getprime();	
//	make();
	run();
}	
	
	
}Maker;
