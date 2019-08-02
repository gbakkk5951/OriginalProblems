#include<cstdio>
#include<iostream>
#include<cstring>
#define R register int
using namespace std;
#define ull unsigned long long
#define ll long long
#define pause (for(R i=1;i<=10000000000;++i))
#define IN freopen("NOIPAK++.in","r",stdin)
#define OUT freopen("out.out","w",stdout)
namespace Fread {
	inline int g() {
		R ret=0,fix=1; register char ch; while(!isdigit(ch=getchar())) fix=ch=='-'?-1:fix;
		if(ch==EOF) return EOF; do ret=ret*10+(ch^48); while(isdigit(ch=getchar())); return ret*fix;
	} inline bool isempty(const char& ch) {return (ch<=36||ch>=127);}
	inline void gs(char* s) {
		register char ch; while(isempty(ch=getchar()));
		do *s++=ch; while(!isempty(ch=getchar()));
	}
}using Fread::g; using Fread::gs;
const int N=100010;
int l=N,r;
inline char calc(char x) { return x=='S'?'0':(x=='s'?'(':(x=='h'?')':0));}
struct stk {
	int s[N],sz;
	inline void ins(int pos) {s[++sz]=pos;}
	inline int size() {return sz;}
	inline int top() {return s[sz];}
	inline void pop() {--sz;}
	inline void clr() {sz=0; memset(s,0,sizeof(s));}
}lb,rb;
int n,m,lst,ans,tmp; char s[N];
int llen[N],rlen[N];
bool flg[N],vis[N],fir=true;
signed main() {
#ifdef JACK
#endif
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	n=g(),m=g(); for(R i=l;i<=l+n-1;++i) { register char ch; 
		while(!isalpha(ch=getchar())); s[i]=calc(ch);
	} r=l+n-1; 
	for(R i=l;i<=r;++i) {
		if(s[i-1]=='0') llen[i]=rlen[lst];
		if(s[i]=='(') {rb.ins(i); vis[i]=true; lst=i;} 
		else if(s[i]==')') {
			if(rb.size()) {flg[rb.top()]=true,flg[i]=true; vis[rb.top()]=false; rb.pop();}
			else lb.ins(i),vis[i]=true; lst=i;
		} else if(s[i]=='0') ++rlen[lst];
	} for(R i=l;i<=r;++i) {
		if(flg[i]) tmp+=rlen[i]+1,fir=false;
		if(vis[i]) ans=max(tmp,ans),tmp=0,fir=true;
		if(fir&&s[i]=='0') ++tmp;
	} ans=max(ans,tmp); printf("%d\n",ans);
	for(R i=1;i<=m;++i) { ans=0,tmp=0; lb.clr(),rb.clr(); fir=true; ++n;
		memset(vis,0,sizeof(vis)),memset(flg,0,sizeof(flg));
		memset(llen,0,sizeof(llen)),memset(rlen,0,sizeof(rlen));
		R op=g(); register char ch=getchar(); 
		if(op&1) s[--l]=calc(ch);
		else s[++r]=calc(ch);
			for(R i=l;i<=r;++i) {
				if(s[i-1]=='0') llen[i]=rlen[lst];
				if(s[i]=='(') {rb.ins(i); vis[i]=true; lst=i;} 
				else if(s[i]==')') {
					if(rb.size()) {flg[rb.top()]=true,flg[i]=true; vis[rb.top()]=false; rb.pop();}
					else lb.ins(i),vis[i]=true; lst=i;
				} else if(s[i]=='0') ++rlen[lst];
			} for(R i=l;i<=r;++i) {
				if(flg[i]) tmp+=rlen[i]+1,fir=false;
				if(vis[i]) ans=max(tmp,ans),tmp=0,fir=true;
				if(fir&&s[i]=='0') ++tmp;
			} ans=max(ans,tmp); printf("%d\n",ans-1);
		}
}
//6 0 
//S s s s h h
//7 0
//S s s s h h h
//8 0
//h S s s s h h h 
//9 0
// s h S s s s h h h

