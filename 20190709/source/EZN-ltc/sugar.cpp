#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

struct node{
	int vis[2];
	int end;
	int last;
	int fail;
	int can;
}ac[5000005];
string s,s1;
int n,tot,ans;

inline void build(string s){
	int len=s.length(),now=0;
	for(int i=0;i<len;i++){
		int x=s[i]-'0';
		if(ac[ac[now].vis[x]].end) return;
		if(!ac[now].vis[x]) ac[now].vis[x]=++tot;
		now=ac[now].vis[x];
 	}
	ac[now].end=1;
 	ac[now].vis[1]=0;
 	ac[now].vis[0]=0;
}

inline void get_fail(){
	queue<int> q;
	for(int i=0;i<2;i++)
		if(ac[0].vis[i]){
			ac[ac[0].vis[i]].fail=0;
			q.push(ac[0].vis[i]);
		}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<2;i++){
			if(ac[x].vis[i]){
				ac[ac[x].vis[i]].fail=ac[ac[x].fail].vis[i];
				q.push(ac[x].vis[i]);
			}
			else ac[x].vis[i]=ac[ac[x].fail].vis[i];
		}
	}
}

inline void ac_query(string s){
	int len=s.length(),now=0,cnt=0,ben=0,pos=0;
	for(int i=0;i<len;i++){
		now=ac[now].vis[s[i]-'0'];
		ben=0;
		for(int t=now;t;t=ac[t].fail){
			if(ac[t].last+1>=ben){
				ac[t].last+=ac[t].end;
				ben=ac[t].last;
				pos=t;
				cnt=max(cnt,ac[t].last);
			}
		}
		if(ben<cnt) ans+=ben,ac[pos].last=1;
	}
}

int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	cin>>n;
	cin>>s;
	for(int i=1;i<=n;i++){
		cin>>s1;
		build(s1);
	}
	ac[0].fail=0;
	get_fail();
	ac_query(s);
	cout<<ans<<endl;
	return 0;
}
