#include<cstdio>
#include<queue>
#define N 5000005
using namespace std;
char txt[N],s[N];
int n,tr[N][2],tot,fail[N],end[N],ans;
inline void build(){
	int u=0;
	for(int i=1;s[i];i++){
		if(!tr[u][s[i]-'0'])tr[u][s[i]-'0']=++tot;
		u=tr[u][s[i]-'0'];
	}
	end[u]++;
}
queue<int>q;
inline void getfail(){
	for(int i=0;i<2;i++){
		if(tr[0][i])q.push(tr[0][i]);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<2;i++){
			if(tr[u][i]){
				int v=tr[u][i];
				fail[v]=tr[fail[u]][i];
				q.push(v);
			}
			else {
				tr[u][i]=tr[fail[u]][i];
			}
		}
	}
}
int main(){
	freopen("sugar.in","r",stdin);freopen("sugar.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",txt+1);
//	printf("%c",txt[1]);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		build();
	}
	getfail();
	int u=0;
	for(int i=1;txt[i];i++){
		u=tr[u][txt[i]-'0'];
		for(int j=u;j;j=fail[j]){
			if(end[j]){
				ans++;
				u=0;
				break;
			}
		}
	}
	printf("%d",ans);
	return 0;
}/*
5
010101010111
010
01
11
1000
1110
*/
/*
3
10010001111111
1000
100
01111111
*/
