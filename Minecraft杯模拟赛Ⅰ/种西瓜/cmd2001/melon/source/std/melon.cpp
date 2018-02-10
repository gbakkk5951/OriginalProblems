using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
const int endpoint=1005;


const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
struct _Main{
int head[1010];
int nxt[20005];
int to[20005];
int flow[20005];
int finalflow;
int eidx;
int cur[1010];
int layer[1010];
void netflow(){
	while(getlayer()){
		do{
			memset(cur,255,sizeof(cur));
		}while(getflow(1,200000));
	}
}
bool vis[1010];
int getflow(int nd,int mx){
	if(nd==endpoint){
		finalflow+=mx;
		return mx;
	}
	int tot=0;
	int i,tmp;
	for(i=(cur[nd]==-1?head[nd]:cur[nd]);i;i=nxt[i]){
		if(flow[i] && layer[to[i]]==layer[nd]+1){
			tmp=getflow(to[i],min(mx-tot,flow[i]));
			tot+=tmp;
			flow[i]-=tmp;
			flow[i^1]+=tmp;
			if(tot==mx){
				cur[nd]=i;
				return tot;
			}
		}
	}
	cur[nd]=0;
	return tot;
}
int q[1015];
int qhead,qtail;
void inline push(int a){
	q[qtail++]=a;
}
int inline pop(){
	return q[qhead++];
}
bool getlayer(){
	qhead=qtail=0;
	memset(layer,255,sizeof(layer));
	memset(vis,0,sizeof(vis));
	layer[1]=1;
	push(1);
	int nd,i;
	vis[1]=1;//不这样可能会导致layer[1]>1; 
	while(qhead<qtail){
		nd=pop();
		for(i=head[nd];i;i=nxt[i]){
			if(flow[i] && !vis[to[i]]){
				push(to[i]);
				layer[to[i]]=layer[nd]+1;
				vis[to[i]]=1;
			}
		}
	}
	return vis[endpoint];
}



void inline add(int a,int b,int c){
	eidx++;
	nxt[eidx]=head[a];
	head[a]=eidx;
	to[eidx]=b;
	flow[eidx]=c;
}	
char inline getalpha(){
	char ans;
	while(!isalpha(ans=getchar()));
	return ans;
}
vector<vector<char> >map;
vector<vector<int> >mmp;
vector<vector<int> >cover;
vector<vector<bool> >occupy;
vector<vector<int> >need;
int n,m;int tp;
int mmpidx;
int ans;
int stemcnt;int stemx[40],stemy[40];
int revmmp[2000];
void bipartite(){
	int i,j,k;
	mmpidx=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(map[i][j]=='l' || map[i][j]=='o'){
				mmp[i][j]=++mmpidx;
			}
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(map[i][j]=='l'){
				add(1,mmp[i][j],1);
				add(mmp[i][j],1,0);
				for(k=0;k<4;k++){
					if(map[i+dx[k]][j+dy[k]]=='o'){
						add(mmp[i][j],mmp[i+dx[k]][j+dy[k]],1);
						add(mmp[i+dx[k]][j+dy[k]],mmp[i][j],0);
					}
				}	
			}else if(map[i][j]=='o'){
				add(mmp[i][j],endpoint,1);
				add(endpoint,mmp[i][j],0);
			}
		}
	}
	netflow();
	printf("%d",finalflow);
	
}
int got[40];
int dir[40];//0什么都不做,1上，2下，3左，4右； 
bool ind[40];
//int way[15];int bestway[15];

void dfs(int idx,int tot){

	#define ndx stemx[idx]+dx[k]
	#define ndy stemy[idx]+dy[k]
	int arr[4],arrcnt=0;
	int k;int chose=0;
	int needcnt=0;
	if(ind[idx]){
//		way[idx]=got[idx]?-1:0;
		dfs(idx+1,tot+got[idx]);
		return;
	}
	if(tot>=ans)return;
	if(idx==stemcnt){
		/*
		if(tot<ans){
			printf("tot=%d\n",tot);
			memcpy(bestway,way,sizeof(way));
			for(int i=1,ccnt=0;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(map[i][j]=='l'){
						printf("%d ",way[ccnt]);
						ccnt++;
					}else printf("%c ",map[i][j]);
				}
				printf("\n");
			}
		}*/
		ans=tot;
		return ;
	}
	
	
	for(k=0;k<4;k++){
		if(map[ndx][ndy]=='o' &&need[ndx][ndy] && (cover[ndx][ndy]<=1) && (!occupy[ndx][ndy]) ){
			needcnt++;
		}
	}
	if(needcnt>1){
		return;
	}
	//消除影响 
	for(k=0;k<4;k++){
		if(map[ndx][ndy]=='o'){
			arr[arrcnt++]=k;
			cover[ndx][ndy]--;
		}
	}
	
	
	//能否随便放 
	if(needcnt==0)
	for(k=0,chose=0;k<4;k++){
		if(map[ndx][ndy]=='o' &&cover[ndx][ndy])break;
		else if(!occupy[ndx][ndy] && map[ndx][ndy]=='o')chose=k+1;
	}
	if(needcnt==0 && k==4){
//		way[idx]=(chose>0)?-1:0;
		dfs(idx+1,tot+(chose>0));
		goto EndDfs; 
	}
	
	
	//被包围 
	if(needcnt==0){
		for(k=0;k<4;k++){
			if(map[ndx][ndy]=='o'){
				need[ndx][ndy]++;
				if(!cover[ndx][ndy] && !occupy[ndx][ndy])break;
			}
		}
//		way[idx]=0;
		if(k==4)
			dfs(idx+1,tot);
		for(k=0;k<4;k++){
			if(map[ndx][ndy]=='o'){
				need[ndx][ndy]--;
				if(!cover[ndx][ndy] && !occupy[ndx][ndy])break;				
			}
		}
	}
	//四个方向 
	for(k=0;k<4;k++){
		if(map[ndx][ndy]=='o' &&( ( needcnt==0 && cover[ndx][ndy]) || (need[ndx][ndy] && cover[ndx][ndy]==0) ) && !occupy[ndx][ndy]){
			occupy[ndx][ndy]=1;
//			way[idx]=k+1;
			dfs(idx+1,tot+1);
			occupy[ndx][ndy]=0;
		}
	}
	
	//恢复影响
	EndDfs:
	for(k=0;k<4;k++){
		if(map[ndx][ndy]=='o'){
			cover[ndx][ndy]++;
		}
	}

}

_Main(){
	eidx=1;
	int i,j,k;int ccnt=0;
	scanf("%d%d%d",&n,&m,&tp);
	map.resize(n+2);
	for(i=0;i<=n+1;i++){
		map[i].resize(m+2);
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			map[i][j]=getalpha();
		}
	}
	if(tp==0){
		mmp.resize(n+2);
		for(i=0;i<=n+1;i++){
			mmp[i].resize(m+2);
		}
		bipartite();		
		goto EndMain;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(map[i][j]=='l'){
				stemx[stemcnt]=i;
				stemy[stemcnt]=j;
				stemcnt++;
			}
		}
	}
	ans=stemcnt;
	cover.resize(n+2);
	occupy.resize(n+2);
	need.resize(n+2);
	for(i=0;i<=n+1;i++){
		cover[i].resize(m+2);
		occupy[i].resize(m+2);
		need[i].resize(m+2);
	}
	for(i=0;i<stemcnt;i++){
		for(k=0;k<4;k++){
			if(map[stemx[i]+dx[k]][stemy[i]+dy[k]]=='o')
				cover[stemx[i]+dx[k]][stemy[i]+dy[k]]++,got[i]=1;
		}
	}
	for(i=0;i<stemcnt;i++){
		for(k=0;k<4;k++){
			if(map[stemx[i]+dx[k]][stemy[i]+dy[k]]=='o' && cover[stemx[i]+dx[k]][stemy[i]+dy[k]]!=1)
				break;
		}
		if(k==4){
			ind[i]=1;
		}
	}
	/*
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(map[i][j]=='o')printf("%d ",cover[i][j]);
			else printf("%c ",map[i][j]);
		}
		printf("\n");
	}	
	*/
	dfs(0,0);


	printf("%d",ans);
	
	EndMain:
		fclose(stdout);
}
	
	
	
	
}melon;
