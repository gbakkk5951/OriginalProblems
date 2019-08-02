// SeptEtavioxy
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#define re register
#define ll long long
#define il inline
#define rep(i,s,t) for(re int i=(s);i<=(t);i++)
#define each(i,u) for(int i=head[u];i;i=bow[i].nxt)
#define pt(ch) putchar(ch)
#define pti(x) printf("%d",x)
#define ptll(x) printf("%lld",x)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
il int ci(){
	re char ch;
	while(isspace(ch=getchar()));
	re int x=ch^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return x;
}
il char cc(){
	re char ch;
	while(isspace(ch=getchar()));
	return ch;
}
enum{N=1000023};
int l[N],depth[N],num[N];
char end[N],s[N];
int main(){
	file("hss");
	int n= ci(), m= ci();
	#define ins() {\
		pos++;\
		if( opt=='S' ){\
			ex++;\
			num[e]++;\
		}\
		if( opt=='s' ){\
			ex-= num[e];\
			num[e]= 0;\
			l[pos]= e;\
			high= depth[pos]= depth[e]+1;\
			e= pos;\
		}\
		else if( opt=='h' ){\
			e= l[e];\
		}\
		ans= max(ans,2*(high-depth[e])+ex);\
	}
	char opt;
	int e = 0, pos = 0;
	re int ans = 0;
	int ex= 0;
	int high= 0;
	rep(i,1,n){
		opt= cc();
		ins();
	}
	pti(ans);
	while( m-- ){
		
	}
	return 0;
}
