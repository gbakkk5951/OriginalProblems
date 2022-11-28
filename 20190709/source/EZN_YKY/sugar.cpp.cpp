#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int N=5000010;
#define ll long long
inline int read(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();	}
	while(ch<='9'&&ch>='0'){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
char s[N],ss[N];
int bo[N],fail[N],f[N];
int ch[N][2];
int n;
int tot;
inline void insert(const char*s){
	int len=strlen(s);int u=0;
	for(int i=0;i<len;i++){
		int v=s[i]-'0';
		if(!ch[u][v])ch[u][v]=++tot;
		u=ch[u][v];
	}
	if(bo[u])bo[u]=min(bo[u],len);
	else bo[u]=len;
}
inline void bfs(){
	queue<int>q;
	if(ch[0][0])q.push(ch[0][0]);
	if(ch[0][1])q.push(ch[0][1]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<2;i++){
			if(!ch[u][i]){
				ch[u][i]=ch[fail[u]][i];
			}
			else{
				fail[ch[u][i]]=ch[fail[u]][i];
				q.push(ch[u][i]);
			}
		}
	}
}
inline int ask(const char*s){
	int ans=0;
	int len=strlen(s);int u=0;
	for(int i=0;i<len;i++){
		int v=s[i]-'0';
		u=ch[u][v];
		for(int j=u;j;j=fail[j]){
			if(bo[j])
			f[i]=max(f[i],f[i-bo[j]]+1);
		}
	}
	return f[len-1];
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	n=read();
	scanf("%s",s);
	for(int i=1;i<=n;i++){
		scanf("%s",ss);
		insert(ss);
	}
	bfs();
	cout<<ask(s);
}
