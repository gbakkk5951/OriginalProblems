// SeptEtavioxy
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
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
enum{N=5000023};
const int inf = 0x3f3f3f3f;
class node{
public:
	int minlen;
	node*c[2],*fail;
	node():minlen(inf){}
}d[N];
node *rt = d, *the_new_node = d+1;
char s[N];
int f[N];
il void chkmin(int&a,int b){
	if( b<a ) a=b;
}
int main(){
	file("sugar");
	int n= ci();
	scanf("%s",s);
	int end = strlen(s)-1;
	{//ins
		re char ch;
		re node* e;
		int Len;
		while( n-- ){
			e= rt;
			Len= 0;
			while(isspace(ch=getchar())); do
			{
				ch^= '0';
				Len++;
				if( !e->c[ch] )	e->c[ch]= the_new_node++;
				e=e->c[ch];
			}
			while(isdigit(ch=getchar()));
			chkmin(e->minlen,Len);
		}
	}
//	
//		for(re node*p=d;p<the_new_node;p++){
//			printf("%d %d %d\n",p->c[0]-d,p->c[1]-d,p->minlen);
//		}pt('\n');
	{//build_AC
		queue <node*> q;
		rt->fail= rt->c[0]->fail= rt->c[1]->fail= rt;
		if( rt->c[0] ) q.push(rt->c[0]);
		else rt->c[0]= rt;
		if( rt->c[1] ) q.push(rt->c[1]);
		else rt->c[1]= rt;
		node*e;
		while( !q.empty() ){
			e=q.front();
			q.pop();
			if( e->c[0] )
				e->c[0]->fail=e->fail->c[0],
				chkmin(e->c[0]->minlen,e->fail->c[0]->minlen),
				q.push(e->c[0]);
			else
				e->c[0]=e->fail->c[0];
			if( e->c[1] )
				e->c[1]->fail=e->fail->c[1],
				chkmin(e->c[1]->minlen,e->fail->c[1]->minlen),
				q.push(e->c[1]);
			else 
				e->c[1]=e->fail->c[1];
		}
	}
	{
		re node* e = rt;
		for(re int i=0;i<=end;i++){
			e=e->c[s[i]^'0'];
			if( e->minlen < N ){
				f[i]= max(f[i-1],f[i-e->minlen]+1);
			}
			else f[i]= f[i-1];
//			printf("%d %d\n",e->minlen,f[i]);
		}
	}
	pti(f[end]);
	return 0;
}
