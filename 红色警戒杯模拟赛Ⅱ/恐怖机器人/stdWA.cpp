using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
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
bool get(int x,int y,int bn){
	if(x>=0 && x<n && y>=0 && y<m && (map[x][y]!='B' || idx[x][y]==bn)){
		if(vis2[x][y][bn]){
			return got[x][y][bn];
		}else{
			vis2[x][y][bn]=1;
			if(map[x][y]=='T'){
				return got[x][y][bn]=true;
			}
			bool ans=false;
			ans|=get(x+1,y,bn)   | get(x-1,y,bn)  ;
			ans|=get(x,y+1,bn)   | get(x,y-1,bn)  ;
			ans|=get(x+1,y+1,bn) | get(x-1,y-1,bn);
			ans|=get(x+1,y-1,bn) | get(x-1,y+1,bn);
			return got[x][y][bn]=ans;
		}
	}else{
		return false;
	}
	
	
}
int dfs(int x,int y,int dir,int bn){
	if(x>=0 && x<n &&y>=0 && y<m &&(map[x][y]!='B' || idx[x][y]==bn)){
		if(vis1[x][y][dir][bn]){
			return dp[x][y][dir][bn];
		}else{
			vis1[x][y][dir][bn]=1;
			if(map[x][y]=='T'){
				return dp[x][y][dir][bn]=1;
			}
			int ans=1e7;
			if(dir!=0) ans=min(ans,1+dfs(x+1,y,0,bn)),ans=min(ans,1+dfs(x-1,y,0,bn));
			if(dir!=1) ans=min(ans,1+dfs(x,y+1,1,bn)),ans=min(ans,1+dfs(x,y-1,1,bn));
			if(dir!=2) ans=min(ans,1+dfs(x+1,y+1,2,bn)),ans=min(ans,1+dfs(x-1,y-1,2,bn));
			if(dir!=3) ans=min(ans,1+dfs(x+1,y-1,3,bn)),ans=min(ans,1+dfs(x-1,y+1,3,bn));
			return dp[x][y][dir][bn]=ans;
		}
	}else {
		return 1e7;
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
		for(j=0;j<m;j++)if(map[i][j]=='S'){
			for(k=min(1,bidx),ans=1e7;k<=bidx;k++){
				ans=min(ans,dfs(i+1,j,0,k)),ans=min(ans,dfs(i-1,j,0,k));
				ans=min(ans,dfs(i,j+1,1,k)),ans=min(ans,dfs(i,j-1,1,k));
				ans=min(ans,dfs(i+1,j+1,2,k)),ans=min(ans,dfs(i-1,j-1,2,k));
				ans=min(ans,dfs(i+1,j-1,3,k)),ans=min(ans,dfs(i-1,j+1,3,k));
			}
			if(ans>1e6){
				for(k=min(1,bidx),ans=false;k<=bidx;k++){
					ans=false;
					ans|=get(i+1,j,k)   | get(i-1,j,k)  ;
					ans|=get(i,j+1,k)   | get(i,j-1,k)  ;
					ans|=get(i+1,j+1,k) | get(i-1,j-1,k);
					ans|=get(i+1,j-1,k) | get(i-1,j+1,k);
					if(ans)break;
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
}


	
	
}terrordrone;
