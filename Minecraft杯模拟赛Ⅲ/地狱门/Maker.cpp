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
#include<fstream>
#include<bitset>
struct Node{
	int world[2];
	int x[2],y[2];
	int tme;int delta;
}node[3010],s,t;
struct World{
	int name;
	int t;
}world[205];
void swap1(World &a,World &b){
	swap(a.name,b.name);
}

struct _Main{

	int lim,alph;
template<typename Type>
	void shuffle(Type *beg,int size){
		int i;
		for(i=1;i<size;i++){
			swap(beg[rand()%(i+1)],beg[i]);
		}
	}
	
template<typename Type>	
	void shuffle(Type *beg,int size,void (*swap)(Type &,Type &)){
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
int idx;
void newnode(int world1,int x1,int y1,int world2,int x2,int y2,int tme,int delta){
	idx++;
	node[idx].x[0]=x1;node[idx].x[1]=x2;
	node[idx].y[0]=y1;node[idx].y[1]=y2;
	node[idx].world[0]=world1;node[idx].world[1]=world2;
	node[idx].tme=tme;node[idx].delta=delta;
}
typedef bitset<155>Num;
Num arr[505],ans;
int layercnt[205];
int n,m;
int randlayer(){
	int ans=rand()%m+1;
	while(layercnt[ans]>=50){
		ans=rand()%m+1;
	}
	layercnt[ans]++;
	return ans;
}

void make(){
	int i,j,k;int I;
	int a,b,c,d;
	int oper;
	
	int x,y;
	for(I=0;I<20;I++){
		cerr<<I<<endl;
		outfile="netherportal"+to_string(I)+".in";
		ofstream output(outfile.c_str());
		idx=0;
		memset(layercnt,0,sizeof(layercnt));
		if(I==0){//大量自环 
			n=1349;
			m=100;
			
			for(i=1;i<=m;i++){
				world[i].t=10;
			}
			for(i=1;i<m;i+=2){
				for(j=1;j<=13;j++){
					newnode(i,j*10,0,i+1,j*10,0,-1,-idx*3);
					newnode(i+1,j*10,0,i,j*10,0,-1,-idx*3);
				}
				if(i+2<=m){
					newnode(i,j*10,0,i+2,0,0,0,-1e4);
				}
			}
			s.x[0]=s.y[0]=0;
			s.world[0]=1;
			t.x[0]=j*10;
			t.y[0]=0;
			t.world[0]=100;			
		}else if(I==1){//超级环 
			m=100;
			n=99*20+19+ 1 +1;
			for(i=1;i<=m;i++){
				world[i].t=10;
			}
			for(i=1;i<=20;i++){
				if(i&1){
					for(j=1;j<=99;j++){
						if(i==1 && j==1)
						newnode(j,i*10,10,j+1,i*10,10,-10000,-1);
						else 
						newnode(j,i*10,10,j+1,i*10,10,-10000,0);
					}
					newnode(j,i*10,10,j,i*10+10,10,-10000,0);
				}else{
					for(j=100;j>=2;j--){
						newnode(j,i*10,10,j-1,i*10,10,-10000,0);
					}
					if(i!=20)
					newnode(j,i*10,10,j,i*10+10,10,-10000,0);	
				}
			}
			newnode(1,20*10,10,1,1*10,10,-10000,0);
			newnode(1,11,10,1,-5000,-5000,-10000,15);
			s.x[0]=s.y[0]=s.world[0]=1;
			t.x[0]=t.y[0]=-4999;
			t.world[0]=1;
		}else if(I<6){//稀疏图
			m=rand()%100+1;
			n=rand()%(3*m)+1;
			for(i=1;i<=m;i++){
				world[i].t=rand()%11;
			}
			for(i=1;i<=n;i++){
				newnode(randlayer(),lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%m+1,lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%10001*randsym(),lrand()%((rand()&1)?10001:(rand()%10001+1))*randsym()
				);
			}
			s.x[0]=lrand()%10001*randsym();s.y[0]=lrand()%10001*randsym();
			s.world[0]=rand()%m+1;
			t.x[0]=lrand()%10001*randsym();t.y[0]=lrand()%10001*randsym();
			t.world[0]=rand()%m+1;			
			
		}else if(I<9){//负无穷 
			m=100;
			n=3000;
			for(i=1;i<=m;i++){
				world[i].t=-rand()%10-1;
			}
			for(i=1;i<=n;i++){
				newnode(randlayer(),lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%m+1,lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%10001*randsym(),lrand()%((rand()&1)?10001:(rand()%10001+1))*randsym()
				);
			}				
			s.x[0]=lrand()%10001*randsym();s.y[0]=lrand()%10001*randsym();
			s.world[0]=rand()%m+1;
			t.x[0]=lrand()%10001*randsym();t.y[0]=lrand()%10001*randsym();
			t.world[0]=rand()%m+1;		
		}else if(I==9){//一路到底 
			m=100;
			n=99*20+19+ 1 +1 -1;
			for(i=1;i<=m;i++){
				world[i].t=1;
			}
			for(i=1;i<=20;i++){
				if(i&1){
					for(j=1;j<=99;j++){
						if(i==1 && j==1)
						newnode(j,i*10,10,j+1,i*10,10,-10000,-1);
						else 
						newnode(j,i*10,10,j+1,i*10,10,-10000,0);
					}
					newnode(j,i*10,10,j,i*10+10,10,-10000,0);
				}else{
					for(j=100;j>=2;j--){
						newnode(j,i*10,10,j-1,i*10,10,-10000,0);
					}
					if(i!=20)
					newnode(j,i*10,10,j,i*10+10,10,-10000,0);	
				}
			}
			newnode(1,20*10+2,17,1,-5000,-5001,-10000,15);
			s.x[0]=s.y[0]=s.world[0]=1;
			t.x[0]=t.y[0]=-4999;
			t.world[0]=1;
		}else if(I<18){//纯随机 
			m=rand()%100+1;
			n=rand()%(50*m)+1;
			n=min(n,3000);
			for(i=1;i<=m;i++){
				world[i].t=rand()%11*(rand()%4==0?-1:1);
			}
			for(i=1;i<=n;i++){
				newnode(randlayer(),lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%m+1,lrand()%10001*randsym(),lrand()%10001*randsym(),
						lrand()%10001*randsym(),lrand()%((rand()&1)?10001:(rand()%10001+1))*randsym()
				);
			}				

			s.x[0]=lrand()%10001*randsym();s.y[0]=lrand()%10001*randsym();
			s.world[0]=rand()%m+1;
			t.x[0]=lrand()%10001*randsym();t.y[0]=lrand()%10001*randsym();
			t.world[0]=rand()%m+1;				
		}else if(I<19){//不走门 
			m=rand()%100+1;
			n=rand()%(50*m)+1;
			n=min(n,3000);
			for(i=1;i<=m;i++){
				world[i].t=rand()%11*randsym();
			}
			for(i=1;i<=n;i++){
				newnode(randlayer(),lrand()%4001*randsym(),lrand()%4001*randsym(),
						lrand()%m+1,lrand()%4001*randsym(),lrand()%4001*randsym(),
						lrand()%4001*randsym(),8005+lrand()%((rand()&1)?1001:(rand()%1001+1))
				);
			}				
			s.x[0]=lrand()%4001*randsym();s.y[0]=lrand()%4001*randsym();
			s.world[0]=rand()%m+1;
			t.x[0]=lrand()%4001*randsym();t.y[0]=lrand()%4001*randsym();
			t.world[0]=rand()%m+1;						
		}else if(I<20){//无门 
			m=rand()%100+1;
			n=0;
			for(i=1;i<=m;i++){
				world[i].t=rand()%11;
			}
			s.x[0]=lrand()%10001*randsym();s.y[0]=lrand()%10001*randsym();
			s.world[0]=5;
			t.x[0]=lrand()%10001*randsym();t.y[0]=lrand()%10001*randsym();
			t.world[0]=5;							
		}


		for(i=1;i<=m;i++){
			world[i].name=i;
		}
		shuffle(world+1,m,&swap1);
		shuffle(node+1,n);
		output<<n<<" "<<m<<endl;
		output<<world[s.world[0]].name<<" "<<s.x[0]<<" "<<s.y[0]<<" "<<world[t.world[0]].name<<" "<<t.x[0]<<" "<<t.y[0]<<endl;
		for(i=1;i<=m;i++){
			for(j=1;j<=m;j++){
				if(world[j].name==i){
					output<<world[j].t<<" ";
					break;
				}
			}
		}
		output<<endl;
		for(i=1;i<=n;i++){
			output<<world[node[i].world[0]].name<<" "<<node[i].x[0]<<" "<<node[i].y[0]<<" "
				  <<world[node[i].world[1]].name<<" "<<node[i].x[1]<<" "<<node[i].y[1]<<" "
			      <<node[i].tme<<" "<<node[i].delta<<endl;
		}
		output.close();
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<20;I++){
		cerr<<I<<endl;
		cmd="std.exe > netherportal"+to_string(I)+".out < netherportal"+to_string(I)+".in";
		system(cmd.c_str());
	}
	for(I=0;I<2;I++){
		cerr<<I<<endl;
		cmd="std.exe > netherportal_ex"+to_string(I)+".out < netherportal_ex"+to_string(I)+".in";
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
