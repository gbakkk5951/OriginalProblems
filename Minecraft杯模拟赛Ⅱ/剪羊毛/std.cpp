using namespace std;
int main(){}
#include<cstdio>
#include<iostream>
#include<cctype>
#include<cstring>
#include<queue>
#include<bitset>
const int mx=1061109567;
int pspeed[10][2];//0全1部分 
int kspeed[50];
int speed[1050000];
int orgspeed;
int* dp[1050000];
int arr[60000][10];
int arrcnt;
int dis[22][22];//0~9牛群，10~19箱子,20起点 
int vis[10][10];
int chestcnt;
char map[12][12];
bitset<10500000>inq;
struct _Main{
queue<int>q[2],sq;

	void push(int x,int y){
		if(x>=0 && y>=0 &&x<n && y<m &&map[x][y]!='B' && !vis[x][y]){
			vis[x][y]=1;
			q[1].push(x*10+y);
		}
	}
	void getdis(){
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				if(map[i][j]=='C'){
					map[i][j]=10+(chestcnt++);
				}else if(map[i][j]=='S'){
					map[i][j]=20;
				}else if(map[i][j]>10){
					continue;
				}
				q[0].push(i*10+j);
			}
		}
		int x,y,beg,g,d;
		while(!q[0].empty()){
			memset(vis,0,sizeof(vis));
			x=q[0].front()/10;y=q[0].front()%10;
			beg=map[x][y];
			vis[x][y]=1;
			q[1].push(q[0].front());
			q[0].pop();
			d=0;
			while(!q[1].empty()){
				g=q[1].size();
				for(i=0;i<g;i++){
					x=q[1].front()/10;y=q[1].front()%10;
					q[1].pop();
					if(map[x][y]<21){
						dis[beg][map[x][y]]=d;
					}
					push(x-1,y);
					push(x+1,y);
					push(x,y-1);
					push(x,y+1);
				}
				d++;
			}
		}
	}
	void getspeed(int s=0,int idx=0,int sum=orgspeed){
		if(idx==p){
			dp[s]=arr[arrcnt++];
			speed[s]=max(sum,1);
		}else{
			getspeed(s|(2<<(idx<<1)),idx+1,sum+pspeed[idx][1]);
			getspeed(s|(3<<(idx<<1)),idx+1,sum+pspeed[idx][0]);
			getspeed(s,idx+1,sum);
		}
	}
	int inline alldown(int s){
		int i;
		for(i=0;i<p;i++){
			s&=(~(1<<(i<<1)));
		}
		return s;
	}
	int n,m;
	int p,kinds;
	
	_Main(){
		memset(arr,63,sizeof(arr));
		int i,j,k;
		int a,b,c,d;
		int s,nd,t,ss;
		bool finish=false;
		int ans=mx;
		scanf("%d%d%d%d%d",&n,&m,&p,&kinds,&orgspeed);
		for(i=0;i<kinds;i++){
			scanf("%d",&kspeed[i]);
		}
		for(i=0;i<p;i++){
			for(j=0;j<kinds;j++){
				scanf("%d",&a);
				pspeed[i][0]+=kspeed[j]*a;
				if(kspeed[j]<0){
					pspeed[i][1]+=kspeed[j]*a;
				}
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				cin>>map[i][j];
				if(isdigit(map[i][j])){
					map[i][j]-='0';
				}
			}
		}
		getspeed();
		getdis();
		for(i=0;i<p;i++){
			dp[3<<(i<<1)][i]=speed[0]*dis[20][i];
			inq[(3<<(i<<1))*10+i]=1;
			sq.push((3<<(i<<1))*10+i);
		}
		while(!sq.empty()){
			s=sq.front()/10;nd=sq.front()%10;
			sq.pop();
			ss=alldown(s);
			finish=true;
			for(j=0;j<p;j++)if(!(3&((s)>>(j<<1)))){
				t=s|(3<<(j<<1));
				dp[t][j]=min(dp[t][j],dp[s][nd]+dis[nd][j]*speed[s]);
				if(!inq[t*10+j]){
					inq[t*10+j]=1;
					sq.push(t*10+j);
				}
				for(i=0;i<chestcnt;i++){
					t=ss|(3<<(j<<1));
					dp[t][j]=min(dp[t][j],dp[s][nd]+dis[nd][10+i]*speed[s]+dis[10+i][j]*speed[ss]);					
				}
				if(!inq[t*10+j]){
					inq[t*10+j]=1;
					sq.push(t*10+j);
				}
				finish=false;
			}
			if(finish){
				for(i=0;i<chestcnt;i++){
					ans=min(ans,dp[s][nd]+dis[nd][10+i]*speed[s]);
				}
			}
		}
		printf("%d",ans);
	}
	
	
	
	
	
}wool;
