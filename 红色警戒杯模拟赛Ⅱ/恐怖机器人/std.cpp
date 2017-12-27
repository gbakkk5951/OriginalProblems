using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<queue>
queue<int>q;
struct _Main{
	
template<typename Type>
	void read(Type &a){
		char t;
		while( !isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}
int write(int x,int y,int dir,int bn){
	return bn+dir*810+y*4*810+x*4*810*40;
}
void decom(int src,int &x,int &y,int &dir,int &bn){
	bn=src%810;
	dir=src/810%4;
	y=src/(4*810)%40;
	x=src/(4*810*40);
}

char map[40][40];
int idx[40][40];
int bidx;
bool vis1[40][40][4][805];
int dp[40][40][4][805];
//  0    1      2        3   
//上下 左右 左上右下 左下右上 

void floodfill(int x,int y,int val){
	if(x>=0 && x<n && y>=0 &&y<m && !idx[x][y] && map[x][y]=='B'){
		idx[x][y]=val;
		floodfill(x-1,y,val);
		floodfill(x+1,y,val);
		floodfill(x,y-1,val);
		floodfill(x,y+1,val);				
	}
}
bool got[40][40][805];
bool vis2[40][40][805];
void get(int x,int y,int bn){
	if(x>=0 && x<n && y>=0 && y<m && !vis2[x][y][bn] &&(map[x][y]!='B' || idx[x][y]==bn)){
		vis2[x][y][bn]=1;got[x][y][bn]=1;
		get(x-1,y,bn);get(x+1,y,bn);
		get(x,y+1,bn);get(x,y-1,bn);
		get(x-1,y-1,bn);get(x-1,y+1,bn);
		get(x+1,y-1,bn);get(x+1,y+1,bn);
	}
}
int bfs(){
	int i,j,k,g;int x,y,dir,bn,val;
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)if(map[i][j]=='T'){
			x=i,y=j;
			for(k=0;k<=bidx;k++){
				insert(x+1,y,0,k,0);insert(x-1,y,0,k,0);
				insert(x,y+1,1,k,0);insert(x,y-1,1,k,0);
				insert(x+1,y+1,2,k,0);insert(x-1,y-1,2,k,0);
				insert(x+1,y-1,3,k,0);insert(x-1,y+1,3,k,0);
			}
		}
	}
	while(!q.empty()){
		g=q.size();
		for(i=0;i<g;i++){
			decom(q.front(),x,y,dir,bn);q.pop();
			val=dp[x][y][dir][bn];
			if(dir!=0)insert(x+1,y,0,bn,val+1),insert(x-1,y,0,bn,val+1);
			if(dir!=1)insert(x,y+1,1,bn,val+1),insert(x,y-1,1,bn,val+1);
			if(dir!=2)insert(x+1,y+1,2,bn,val+1),insert(x-1,y-1,2,bn,val+1);
			if(dir!=3)insert(x+1,y-1,3,bn,val+1),insert(x-1,y+1,3,bn,val+1);
		}
	}


}

void inline insert(int x,int y,int dir,int bn,int val){
	if(x>=0 && x<n && y>=0 && y<m && (map[x][y]!='B' || idx[x][y]==bn) && !vis1[x][y][dir][bn]){
		vis1[x][y][dir][bn]=1;
		dp[x][y][dir][bn]=val;
		q.push(write(x,y,dir,bn));
	}
}
int n,m;//n行m列 
_Main(){
	int i,j,k;int ans;char t;
	read(n);read(m);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			while(!isalpha(t=getchar()));
			map[i][j]=t;
		}
	}
	memset(dp,63,sizeof(dp));
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)if(map[i][j]=='B' && idx[i][j]==0){
			floodfill(i,j,++bidx);
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)if(map[i][j]=='T'){
			for(k=0;k<=bidx;k++){
				get(i,j,k);
			}
		}
	}
	bfs();	
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)if(map[i][j]=='S'){
			ans=1e7;
			for(k=min(1,bidx);k<=bidx;k++){
				ans=min(ans,dp[i][j][0][k]);ans=min(ans,dp[i][j][1][k]);
				ans=min(ans,dp[i][j][2][k]);ans=min(ans,dp[i][j][3][k]);			
			}
			ans++;
			if(ans>1e6){
				for(k=min(1,bidx);k<=bidx;k++){
					if(got[i][j][k])break;
				}
				if(k==bidx+1){
					printf("%d\n",-1);
				}else{
					printf("%d\n",-2);
				}
			}else{
				printf("%d\n",ans);
			}
		}
	}
	fclose(stdout);
}


	
	
}terrordrone;
