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
enum{N=100023,M=200023,D=18};
il void chkmin(int&a,int b){
	if( b<a ) a=b;
}
int find_fa[N];
int *p_fa[N];
il int fd(int x){
	int tot = 0;
	while( x!=find_fa[x] ){
		p_fa[++tot]=find_fa+x;
		x= find_fa[x];
	}
	while( tot ) *p_fa[tot--]= x;
	return find_fa[x];
}
class Edge{
public:
	int nxt,to,len;
	il void operator()(int a,int b,int c){
		nxt= a, to= b, len= c;
	}
}bow[N<<1];
int head[N];
int f1[N][D+1],f2[N][D+1],anc[N][D+1];
int depth[N];
void dfs(int u,int fa,int ue){
	anc[u][0] = fa;
	f1[u][0] = bow[ue].len;
	int F,t=1;
//	printf("%d : ",u);
//	printf("%d (%d %d) , ",0,f1[u][0],f2[u][0]);
	while(( anc[u][t] = anc[F=anc[u][t-1]][t-1] )){
		f1[u][t]= max(f1[u][t-1],f1[F][t-1]);
		f2[u][t]= max(min(f1[u][t-1],f1[F][t-1]),max(f2[u][t-1],f2[F][t-1]));
		t++;
//		printf("%d (%d %d) , ",t,f1[u][t],f2[u][t]);
	}
//	pt('\n');
	int v;
	each(i,u) if( i^ue^1 ){
		v= bow[i].to;
		depth[v]= depth[u]+1;
		dfs(v,u,i);
	}
}
class Rd{
public:
	int x,y,c;
	il void in(){
		x= ci(), y= ci(), c= ci();
	}
	il bool operator <(const Rd&e)const{
		return c < e.c;
	}
}rd[M];
bool cho[M];
int main(){
	file("selfless");
	int n= ci(), m= ci();
	rep(i,1,m) rd[i].in();
	int sum= 0;
	{//kruscal
		sort(rd+1,rd+m+1);
		rep(i,1,n) find_fa[i]=i;
		re int j = 1;
		int x,y;
		rep(i,2,n){
			while( fd(rd[j].x)==fd(rd[j].y) ) j++;
			x=rd[j].x , y=rd[j].y;
			bow[i<<1](head[x],y,rd[j].c);
			bow[i<<1|1](head[y],x,rd[j].c);
			head[y]= (head[x]=i<<1) | 1 ;
			find_fa[find_fa[y]]=find_fa[x];
			sum+= rd[j].c;
//			printf("%d+",rd[j].c);
			cho[j++]= 1;
		}
//		pt('\n');
	}
	int Min = 0x3f3f3f3f;
	{
		dfs(1,0,0);
		int p,q,mx1,mx2,delta,len;
		re int t;
		rep(j,1,m) if( !cho[j] ){
			p=rd[j].x , q=rd[j].y;
			if( depth[p]<depth[q] ) swap(p,q);
			mx1=0 , mx2=0 ;
			delta= depth[p]-depth[q];
			#define chk(p,t) {\
				if( f1[p][t]>mx1 ){\
					if( mx2<mx1 ) mx2=mx1;\
					mx1= f1[p][t];\
				}\
				else if( f1[p][t]==mx1 && f1[p][t]>mx2 ){\
					mx2= f1[p][t];\
				}\
				if( f2[p][t]>mx2 ){\
					mx2= f1[p][t];\
				}\
			}
			for(t=D;t>=0;t--) if( delta&(1<<t) ){
				chk(p,t);
				p= anc[p][t];
			}
//			printf("end delta\n");
//			printf("%d %d\n",p,q);
			if( p!=q ){
				for(t=D;t>=0;t--) if( anc[p][t]!=anc[q][t] ){
//					printf("t : %d ,",t);
					chk(p,t);
					chk(q,t);
					p= anc[p][t];
					q= anc[q][t];
				}
				chk(p,0);
				chk(q,0);
			}
//				printf("pq : %d %d\n",p,q);
//				printf("%d %d\n",mx1,mx2);
			len = rd[j].c;
			if( len>mx1 ) chkmin(Min,len-mx1);
			if( len>mx2 ) chkmin(Min,len-mx2);
//			printf("min : %d\n",Min);
		}
	}
	pti(sum+Min);
	return 0;
}
/*
5 6
1 2 1
2 3 1
3 5 1
5 2 2
3 4 2
1 5 4
*/
