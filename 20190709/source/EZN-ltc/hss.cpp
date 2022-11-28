#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

inline int read(){
	int x=0,f=1;
	char p=getchar();
	while(!isdigit(p)){
		if(p=='-') f=-1;
		p=getchar();
	}
	while(isdigit(p)) x=(x<<3)+(x<<1)+p-48,p=getchar();
	return x*f;
}

const int maxn=5005;

int n,m,top,cnt,s[maxn],ans;
char a[maxn]; 

inline void solve(int x){
	top=0;int cnt1=0;
	for(int i=x;i<=n;i++){
		if(a[i]=='S') cnt1++;
		if(a[i]=='s') top++,cnt1++;
		if(a[i]=='h'){
			top--;
			cnt1++;
			if(top==0) cnt=max(cnt,cnt1);
			if(top<0) return;
		}
	}
}

int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		cnt=0;
		solve(i);
		ans=max(ans,cnt);
	}
	cout<<ans<<endl;
	return 0;
}
