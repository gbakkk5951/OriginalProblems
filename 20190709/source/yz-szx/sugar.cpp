#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<cstring>
#include<queue>
#define rg register
using namespace std;
inline int read(){
	rg char ch=getchar();
	rg int x=0,f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int tr[5000050][2],fail[5000050],dp[5000050],dep[5000050],cnt,tot,sum[5000050],last[5000010],ed[500050],n;
const int ver=1,nxt=0;
int head[5000050],edge[5000050][2],vis[5000050][2];
char s[500050],to[500050];
inline void add(int x,int y){
	edge[++tot][ver]=y;
	edge[tot][nxt]=head[x];
	head[x]=tot;
}
inline void insert(char *s){
	int len=strlen(s),p=0;
	for(int c,i=0;i<len;++i){
		c=s[i]-'0';
		if(!tr[p][c]) tr[p][c]=++cnt;
		p=tr[p][c];
	}
	++ed[p],dep[p]=len;
//	cout<<p<<endl;
}
inline void get_fail(){
	queue<int> q;
	if(tr[0][0]) q.push(tr[0][0]),vis[0][0]=1;
	if(tr[0][1]) q.push(tr[0][1]),vis[0][1]=1;
	while(!q.empty()){
		int p=q.front();q.pop();
		for(int i=0;i<2;++i){
			if(tr[p][i]){
				vis[p][i]=1;
				fail[tr[p][i]]=tr[fail[p]][i];
				q.push(tr[p][i]);
			}else tr[p][i]=tr[fail[p]][i];
		}
	}
}
void ask(char *s){
	int len=strlen(s),p=0;
	for(int i=0;i<len;++i){
		p=tr[p][s[i]-'0'];
		for(int j=p;j;j=fail[j]){
			if((!last[j]||(i+1)-last[j]>=dep[j])&&ed[j]){
//				cout<<dep[j]<<" "<<j<<endl;
				last[j]=i+1;
				++sum[j];
//				break;
			}
		}
	}
}
void work(){
	for(int i=1;i<=cnt;++i) add(fail[i],i);
}
void dfs(int x){
	dp[x]=sum[x];
	for(int i=0;i<2;++i){
		if(!vis[x][i]) continue;
		dfs(tr[x][i]);
//		sum[x]+=y;
		dp[x]=max(dp[x],dp[tr[x][i]]);
	}
//	if(ed[x]) dp[x]=max(dp[x],sum[x]);
//	cout<<x<<" "<<ed[x]<<" "<<dp[x]<<endl;
}
void find(int x){
	for(int i=head[x];i;i=edge[i][nxt]){
//		cout<<x<<" "<<edge[i][ver]<<endl;
		find(edge[i][ver]);
	}
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	n=read();
	scanf("%s",to);
	for(int i=1;i<=n;++i){
		scanf("%s",s);
		insert(s);
	}
//	cout<<"-----------"<<endl;
	get_fail();
	ask(to);
//	cout<<sum[2]<<" "<<sum[3]<<endl;
//	work();
	dfs(0);
//	for(int i=head[0];i;i=edge[i][nxt]) cout<<sum[edge[i][ver]]<<endl;
	cout<<dp[tr[0][0]]+dp[tr[0][1]]<<endl;
//	cout<<sum[3]<<" "<<dp[0]<<endl;
//	find(0);
	return 0;
}
/*
5
010101010111
010
01
11
1000
1110
*/
