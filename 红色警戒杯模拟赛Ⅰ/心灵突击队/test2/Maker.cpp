using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>

struct _Main{
bool small;	
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
int randsym(){
	return (rand()&1)?-1:1;
}
int gap[2005];
void make(){
	int i,j,k;int I;int l,m;int n;int lim;int g;
	int hp,hpmx,atk,atkmx,hpadd;int block;int e;int a,b,c,d;
	int x1,x2,y1,y2;int xmin,xmax,ymin,ymax;int maxpos;
	maxpos=20;
	for(I=0;I<20;I++){
		file="commando"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		
		if(I<4){
			if(I&1){
				xmin=xmax=lrand()*randsym();
				ymin=lrand()%(maxpos-10)*randsym();
				ymax=ymin+10;
			}else{
				ymin=ymax=lrand()*randsym();
				xmin=lrand()%(maxpos-10)*randsym();
				xmax=xmin+10;
			}
		}else if(I<6){
			maxpos=100;
			if(I==5){
				xmin=xmax=ymin=ymax=lrand()%11*randsym();
			}else{
				xmin=-100;xmax=100;ymin=-100;ymax=100;
			}
			m=1000;
		}else if(I<8){
			maxpos=500;
			xmin=-1*(lrand()%300+200);
			ymin=-1*(lrand()%300+200);
			if(I==6){
				xmax=xmin+512;
				ymax=ymin+511;
			}else if(I==7){
				xmax=xmin+510;
				ymax=ymin+509;				
			}
		}else{
			xmin=lrand()%(xmax-10)*randsym();
			if(I!=15)xmax=xmin+20-rand()%20;
			else xmax=xmin+20;
			if(I!=15)ymax=ymin+20-rand()%20;
			else ymax=ymin+20;			
		}
		m=8;
		cout<<m<<" "<<xmin<<" "<<ymin<<" "<<xmax<<" "<<ymax<<endl;
		for(i=0;i<m;i++){
			if(I>=8 && I<12){
				if(i<m/2){
					if(rand()%3){//炸弹 
						if(rand()%4==0){//内部 
							a=xmin+lrand()%(xmax-xmin+1);b=ymin+lrand()%(ymax-ymin+1);
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)min(ymax-ymin+1,xmax-xmin+1)+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;
						}else{
							cout<<1<<" "<<lrand()%(maxpos+1)*randsym()<<" "<<lrand()%(maxpos+1)*randsym()<<" "
							<<lrand()%(int)1e8<<" "<<lrand()%(int)1e4<<endl;
						}
					}else{//洗消 
						a=lrand()%(xmax-xmin+1);
						b=lrand()%(xmax-xmin+1-a);
						c=lrand()%(ymax-ymin+1);
						d=lrand()%(ymax-ymin+1-c);
						cout<<2<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<lrand()%(int)1e4<<endl;						
					}
				}else{
					a=lrand()%(xmax-xmin+1);
					b=lrand()%(xmax-xmin+1-a);
					c=lrand()%(ymax-ymin+1);
					d=lrand()%(ymax-ymin+1-c);
					cout<<0<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<endl;	
				}
			}else{
				if(rand()&1){
					
					if(rand()%3){//炸弹 
						if(rand()%4==0){//内部 
							a=xmin+lrand()%(xmax-xmin+1);b=ymin+lrand()%(ymax-ymin+1);
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)min(ymax-ymin+1,xmax-xmin+1)+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;
						}else{
							cout<<1<<" "<<lrand()%(maxpos+1)*randsym()<<" "<<lrand()%(maxpos+1)*randsym()<<" "
							<<lrand()%(int)1e8<<" "<<lrand()%(int)1e4<<endl;
						}
					}else{//洗消 
						a=lrand()%(xmax-xmin+1);
						b=lrand()%(xmax-xmin+1-a);
						c=lrand()%(ymax-ymin+1);
						d=lrand()%(ymax-ymin+1-c);
						cout<<2<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<lrand()%(int)1e4<<endl;						
					}
					
				}else{
					
					a=lrand()%(xmax-xmin+1);
					b=lrand()%(xmax-xmin+1-a);
					c=lrand()%(ymax-ymin+1);
					d=lrand()%(ymax-ymin+1-c);
					cout<<0<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<endl;				
					
				}			
				
			}
		}
		
		fclose(stdout);
	}
	
	
	
}
int totcnt;
void run(){
	int I;
	cmd="output"+to_string(totcnt/20)+".res";
	freopen(cmd.c_str(),"w",stdout);
	for(I=0;I<20;I++){
		
		cerr<<"["<<I+totcnt<<"]"<<endl;
		
		cmd="std.exe > std"+to_string(I)+".out < commando"+to_string(I)+".in";
		system(cmd.c_str());		
		cmd="brute.exe > brute"+to_string(I)+".out < commando"+to_string(I)+".in";
		system(cmd.c_str());
		cmd="fc brute"+to_string(I)+".out  std"+to_string(I)+".out";
		system(cmd.c_str());
	}
	cerr<<"请按任意键继续. . . "<<endl;
	totcnt+=25;
}
	
_Main(){
	getprime();
small=false;
srand(time(0));
while(1){
	make();
	run();	
	getchar();
}
	

}	
	
	
}Maker;
