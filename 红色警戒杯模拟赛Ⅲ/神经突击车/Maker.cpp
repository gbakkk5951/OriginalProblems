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
	"光棱坦克","美国大兵","重装大兵","工程师","MCV","WestWood之星","超时空兵团","警犬",
	"灰熊坦克","超时空采矿车","发电站","矿石精炼厂","矿石精炼器","多功能步兵车","机枪碉堡",
	"火箭飞行兵","谭雅","盟军围墙","戰車工廠","裂縫產生器","愛國者飛彈","光棱塔","兵營",
	"間諜衛星","超時空傳送儀","天氣控制儀","空指部","作戰實驗室","維修廠","遙控坦克",
	"戰鬥要塞","幻影坦克","海豹部隊"
};

bool Glink[305][305];
int n,m,e,i,j,k,I,block;
int gap[2005];
char buf[30];
struct Edge{
	int first,second;	
}edge[90010];

void printmap(){
	m=0;
	for(i=2;i<=33;i++){
		swap(org[i],org[rand()%i+1]);
	}
	for(i=1;i<=13;i++){
		name[i]=org[i];
	}
	for(i=14;i<=n;i++){
		name[i]="";
		if(I&1){
			for(j=0;j<30;j++){
				name[i]+="A1";
			}
			sprintf(buf,"%03d",i);
			name[i]+=buf;
			for(j=63;j<80;j++){
				name[i]+='z';
			}						
		}else{
			for(j=64;j<80;j++){
				name[i]+='a';
			}
			sprintf(buf,"%04d",i);
			name[i]+=buf;
			for(j=0;j<30;j++){
				name[i]+="_2";
			}			
		}
	}
	
	for(i=2;i<=n;i++){
		swap(name[i],name[rand()%i+1]);
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(Glink[i][j]){
				edge[m].first=i;
				edge[m].second=j;
				m++;
			}
		}
	}
	
	
	
	for(i=1;i<=m-1;i++){
		swap(edge[rand()%i],edge[i]);
	}
	
	cout<<n<<" "<<m<<endl;
	for(i=0;i<m;i++){
		if(rand()&1){
			swap(edge[i].first,edge[i].second);
		}
		cout<<name[edge[i].first]<<" "<<name[edge[i].second]<<endl;
	}
	
	
	
}
void make(){
	
	for(I=0;I<20;I++){
		
		
		file="chaosdrone"+to_string(I)+".in";
		freopen(file.c_str(),"w",stdout);
		
		memset(Glink,0,sizeof(Glink));
		memset(gap,0,sizeof(gap));
		if(I<4){
			n=10;m=0;
			for(i=1;i<=10;i++){
				for(j=i+1;j<=10;j++){
					Glink[i][j]=(rand()%3==0);
					if(Glink[i][j])m++;
					if(m==20) break;
				}
				if(m==20)break;
			}
		}else if((I==4) || (I==5)){//随机森林 
			n=300-rand()%30;
			block=rand()%n+1;
			e=n-block;
			for(i=1;i<block;i++){
				gap[i]=1;
			}
			for(i=2;i<n;i++){
				swap(gap[i],gap[lrand()%i+1]);
			}
			int lst=1;int test=0;
			for(i=1;i<=n;i++){
				if(i>lst){
					test++;
					Glink[lst+rand()%(i-lst)][i]=1;
				}
				if(gap[i]){
					lst=i+1;
				}
			}
			if(test!=e){
				cerr<<"wrong"<<endl;
			}
		}else if((I==6) || (I==7)){//随机树 
			n=300-rand()%30;
			e=n-1;
			
			for(i=2;i<=n;i++){
				Glink[lrand()%(i-1)+1][i]=1;
			}
		}else if((I==8) || (I==9)){
			n=300;
			if(I&1){
				for(i=1;i<=5;i++){
					Glink[i][i%5+1]=1;
				}
				for(i=6;i<=n-1;i++){
					Glink[i][rand()%1+1]=1;
				}
			}else {
				for(i=1;i<=271;i++){
					Glink[i][i%271+1]=1;
				}
				for(i=272;i<=n-1;i++){
					Glink[i][rand()%1+1]=1;
				}
			}
		}else if((I==10) || (I==11) ){
			n=300;
			if(I&1){
				for(i=1;i<=5;i++){
					Glink[i][i%5+1]=1;
				}
				for(i=6;i<=150-1;i++){
					Glink[i][rand()%1+1]=1;
				}
				for(i=1;i<=7;i++){
					Glink[150+i][150+i%7+1]=1;
				}
				for(i=8;i<=150-1;i++){
					Glink[150+i][150+rand()%1+1]=1;
				}		
			}else{
				for(i=1;i<=11;i++){
					Glink[i][i%11+1]=1;
				}
				for(i=12;i<=100-1;i++){
					Glink[i][rand()%1+1]=1;
				}		
				for(i=1;i<=4;i++){
					Glink[100+i][100+i%4+1]=1;
				}
				for(i=5;i<=100-1;i++){
					Glink[100+i][100+rand()%1+1]=1;
				}				
				for(i=1;i<=3;i++){
					Glink[200+i][200+i%3+1]=1;
				}
				for(i=4;i<=100-1;i++){
					Glink[200+i][200+rand()%1+1]=1;
				}							
			}
		}else if((I==12) || (I==13)){
			if(I==12)n=300;
			else n=299;
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++){
					Glink[i][j]=1;
				}
			}
		}else{
			if(I<16){
				n=300-rand()%30;
			}else{
				n=300;
			}
			for(i=1;i<=n;i++){
				for(j=i+1;j<=n;j++){
					Glink[i][j]=( I==16?rand()%10==1:rand()%100==1);
				}
			}
		}
		printmap();
		fclose(stdout);
	}
	
	
	
}
	
void run(){
	int I;
	for(I=0;I<21;I++){
		cmd="std.exe > chaosdrone"+to_string(I)+".out < chaosdrone"+to_string(I)+".in";
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
