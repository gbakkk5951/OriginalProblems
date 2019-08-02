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
char s[2000010];
int l,r,n,m,ans;
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	n=read(),m=read();
	scanf("%s",s+1000001);
	l=1000001;r=l+n-1;
//	for(int i=l;i<=r;++i) cout<<s[i]<<endl;
	for(int S,H,i=l;i<=r;++i){
		S=H=0;
		for(int j=i;j<=r;++j){
			if(s[j]=='s') ++S;
			if(s[j]=='h') ++H;
			if(S==H) ans=max(ans,j-i+1);
		}
	}
	cout<<ans<<endl;
	char ch;
	for(int S,H,op,t=1;t<=m;++t){
		op=read();scanf("%s",&ch);
		S=H=0;
		if(op==1){
			s[--l]=ch;
			for(int j=l;j<=r;++j){
				if(s[j]=='s') ++S;
				if(s[j]=='h') ++H;
				if(S==H) ans=max(ans,j-l+1);
			}
			printf("%d\n",ans);
		}else{
			s[++r]=ch;
			for(int j=r;j>=l;--j){
				if(s[j]=='s') ++S;
				if(s[j]=='h') ++H;
				if(S==H) ans=max(ans,r-j+1);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
/*
6 3
Shhhss
2 s
1 s
1 h
*/
