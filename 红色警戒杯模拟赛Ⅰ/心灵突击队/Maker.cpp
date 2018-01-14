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

string arr[100010];

void make(){
	int i,j,k;int I;int l,m;int n;int g;
	int a,b,c,d;
	int maxpos;int xmin,xmax,ymin,ymax;

	for(I=20;I<25;I++){
		file="commando"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		m=10000;maxpos=1e8;
		if(I>=20)m=10000 + (I-19)*4000;
		if(I<4){
			if(I&1){
				xmin=xmax=lrand()*randsym();
				ymin=lrand()%(maxpos-1000)*randsym();
				ymax=ymin+1000;
			}else{
				ymin=ymax=lrand()*randsym();
				xmin=lrand()%(maxpos-1000)*randsym();
				xmax=xmin+1000;
			}
		}else if(I<6){
			if(I==5){
				xmin=xmax=ymin=ymax=lrand()%101*randsym();
			}else{
				xmin=lrand()%(maxpos-1000)*randsym();xmax=xmin+50;ymin=lrand()%(maxpos-1000)*randsym();ymax=ymin+1000-rand()%100;
			}
		}else if(I<8){
			if(I&1){
				xmin=lrand()%(maxpos-1000)*randsym();xmax=xmin+50;ymin=lrand()%(maxpos-1000)*randsym();ymax=ymin+1000-rand()%100;
			}
			else {
				xmin=lrand()%(maxpos-1000)*randsym();xmax=xmin+1000-rand()%100;ymin=lrand()%(maxpos-1000)*randsym();ymax=ymin+50;
			}

		}else{
			ymin=lrand()%(maxpos-1000)*randsym();
			xmin=lrand()%(maxpos-1000)*randsym();
			if(I!=15)xmax=xmin+1000-rand()%300;
			else xmax=xmin+1000;
			if(I!=15)ymax=ymin+1000-rand()%300;
			else ymax=ymin+1000;			
			if(I==8){
				xmax=xmin+512;
				ymax=ymin+511;
			}else if(I==9){
				xmax=xmin+510;
				ymax=ymin+509;				
			}
		}
		cout<<m<<" "<<xmin<<" "<<ymin<<" "<<xmax<<" "<<ymax<<endl;
		for(i=0;i<m;i++){
			if(I>=8 && I<12){
				if(i<m/2){
					if(rand()%3){//Õ¨µ¯ 
						if(rand()%4<2){//ÄÚ²¿ 
							a=xmin+lrand()%(xmax-xmin+1);b=ymin+lrand()%(ymax-ymin+1);
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)min(ymax-ymin+1,xmax-xmin+1)+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;
						}else if(rand()%4<2){//±ßÔµÕ¨ 
							if(rand()&1)a=xmax-rand()%500;
							else a=xmax+rand()%500;
							if(rand()&1)b=xmax-rand()%500;
							else b=xmax+rand()%500;	
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)1000+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;													
						}
						else{//ÂÒÕ¨ 
							cout<<1<<" "<<lrand()%(maxpos+1)*randsym()<<" "<<lrand()%(maxpos+1)*randsym()<<" "
							<<lrand()%(int)1e8<<" "<<lrand()%(int)1e4<<endl;
						}
					}else{//Ï´Ïû 
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
					
					if(rand()%3){//Õ¨µ¯ 
						if(rand()%4<2){//ÄÚ²¿ 
							a=xmin+lrand()%(xmax-xmin+1);b=ymin+lrand()%(ymax-ymin+1);
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)min(ymax-ymin+1,xmax-xmin+1)+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;
						}else if(rand()%4<2){//±ßÔµÕ¨ 
							if(rand()&1)a=xmax-rand()%500;
							else a=xmax+rand()%500;
							if(rand()&1)b=xmax-rand()%500;
							else b=xmax+rand()%500;	
							cout<<1<<" "<<a<<" "<<b<<" "
							<<lrand()%(int)1000+(rand()%100)*(rand()%5==1)
							<<" "<<lrand()%(int)1e4<<endl;													
						}
						else{//ÂÒÕ¨ 
							cout<<1<<" "<<lrand()%(maxpos+1)*randsym()<<" "<<lrand()%(maxpos+1)*randsym()<<" "
							<<lrand()%(int)1e8<<" "<<lrand()%(int)1e4<<endl;
						}
					}else{//Ï´Ïû 
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
	
void run(){
	int I;
	for(I=20;I<25;I++){
		cerr<<I<<endl;
		cmd="std.exe > commando"+to_string(I)+".out < commando"+to_string(I)+".in";
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
