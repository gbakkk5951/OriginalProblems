#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=5e6+50,inf=0x3f3f3f3f;
int n,t[N][2],cnt,q[N],l,r,mi[N],fail[N],a[N],dp[N],len;char c[N],b[N];LL ans;
void insert(char *c){
	int len=strlen(c),x=0;
	for(int i=0;i<len;i++){
		int y=c[i]-'0';
		if(!t[x][y])t[x][y]=++cnt;
		x=t[x][y];
	}
	mi[x]=len;
}
void build(){
	for(int i=0;i<2;i++)if(t[0][i])q[++r]=t[0][i];
	l=1;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<2;i++){
			int &y=t[x][i],z=t[fail[x]][i];
			if(!y)y=z;
			else fail[y]=z,q[++r]=y,mi[y]=min(mi[y],mi[z]);
		}
	}
}
void ask(char*c){
	int x=0;len=strlen(c+1);
	for(int i=1;i<=len;i++){
		int y=c[i]-'0';
		x=t[x][y];a[i]=mi[x];
	}
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d%s",&n,b+1);
	memset(mi,0x3f,sizeof(mi));
	for(int i=1;i<=n;i++)scanf("%s",c),insert(c);
	build();ask(b);
	for(int i=1;i<=len;i++){
		dp[i]=dp[i-1];
		if(a[i]!=inf)dp[i]=max(dp[i],dp[i-a[i]]+1);
	}
	printf("%d",dp[len]);
	return 0;
}
