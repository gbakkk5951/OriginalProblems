#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N=300010;
#define ll long long
inline int read(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();	}
	while(ch<='9'&&ch>='0'){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
int n,m;
int ch[N][2],sta[N],rev[N],fa[N],mx[N],mx2[N],val[N];
ll sum;
int ans=1<<30;
struct pp{
	int x,y,w;
}e[N];
bool cmp(pp a,pp b){
	return a.w<b.w;
}
//inline int find(int x){
//	return x==fa[x]?x:fa[x]==find(fa[x]);
//}
inline int chk(int x){
	return x==ch[fa[x]][1];
}
inline int get(int x){
	return x==ch[fa[x]][1]||x==ch[fa[x]][0];
}
inline void filp(int x){
	rev[x]^=1;
	swap(ch[x][0],ch[x][1]);
}
inline void pushup(int x){
	int l=ch[x][0],r=ch[x][1];
	if(mx[l]>mx[r]){
		mx[x]=mx[l],mx2[x]=max(val[x],mx[r]);
	}
	else if(mx[r]>mx[l]){
		mx[x]=mx[r],mx2[x]=max(val[x],mx[l]);
	}
	else{
		mx[x]=mx[l];mx2[x]=max(mx2[l],mx2[r]);
	}
	if(val[x]>mx[x]){
		mx2[x]=mx[x],mx[x]=val[x];
	}
	else if(val[x]>mx2[x]){
		mx2[x]=val[x];
	} 
}
inline void pushdown(int x){
	if(!rev[x])return;
	rev[x]=0;
	if(ch[x][0])filp(ch[x][0]);
	if(ch[x][1])filp(ch[x][1]);
}
inline void zhuan(int x){
	int y=fa[x],z=fa[y],k=chk(x),w=ch[x][k^1];
	if(get(y))ch[z][chk(y)]=y;ch[x][k^1]=y,ch[y][k]=w;
	if(w)fa[w]=y;fa[y]=x,fa[x]=z;
	pushup(y);pushup(x);
}
inline void splay(int x){
	int y=x,top=0;sta[++top]=y;
	while(get(y))sta[++top]=y=fa[y];
	while(top)pushdown(sta[top--]);
	while(get(x)){
		y=fa[x];
		if(get(y))
		zhuan(chk(x)==chk(y)?y:x);
		zhuan(x);
	}
	pushup(x);
}
inline void Access(int x){
	for(int y=0;x;x=fa[y=x]){
		splay(x);ch[x][1]=y,pushup(x);
	}
}
inline void makeroot(int x){
	Access(x);splay(x);filp(x);
}
inline int findroot(int x){
	Access(x);splay(x);
	while(ch[x][0])pushdown(x),x=ch[x][0];
	return x;
}
inline void link(int x,int y){
	makeroot(x);if(findroot(y)!=x)fa[x]=y;
}
inline void split(int x,int y){
	makeroot(x);Access(y);splay(y);
}
int main(){
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].x=read();e[i].y=read();e[i].w=read();
	}
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=m;i++){
		int x=e[i].x,y=e[i].y;
		//cout<<x<<' '<<y<<' ';
		//cout<<e[i].w<<' ';
		if(findroot(x)!=findroot(y)){
			sum+=e[i].w;//cout<<"debag"<<endl;
			val[i+m]=mx[i+m]=e[i].w;
			//fa[x]=i+m;fa[i+m]=y;
			link(x,i+m),link(i+m,y);
		}
		else{
			//split(x,y);
			makeroot(x);Access(y);splay(y);
			ans=min(ans,e[i].w-(e[i].w>mx[y]?mx[y]:mx2[y]));
		}
	//	cout<<sum<<endl;
	}
	//cout<<ans<<endl;
	printf("%lld",sum+ans);
	return 0;
}


/*


3 5
1 2 3
1 2 5
2 3 4
2 3 9
1 3 3

*/
