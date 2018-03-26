using namespace std;
int main(){}
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#define DoNothing()
namespace Protector{
const int base=20005;
const int mx  =40010;	
int inline lowbit(const int &a){
	return a&(-a);
}
struct Node{
	int idx,x,y;
	struct XYLessIdxGreater{
		bool  operator () (const Node & a,const Node & b) {
			return a.x==b.x?(a.y==b.y?a.idx>b.idx:a.y<b.y):a.x<b.x;
		}			
	};
	struct SumLess{
		bool  operator () (const Node & a,const Node & b) {
			return a.x+a.y<b.x+b.y;
		}		
	};
	struct XYLess{
		bool  operator () (const Node & a,const Node & b) {
			return a.x==b.x?a.y<b.y:a.x<b.x;
		}				
	};
	struct XYEqual{
		bool operator () (const Node &a,const Node &b){
			return a.x==b.x && a.y==b.y;
		}
	};
	Node(){
		idx=x=y=0;
	}
}arr[400050];	
struct Edge{
	int a,b,val;
	bool operator < (const Edge & obj) const {
		return val<obj.val;
	}
}edge[1600050];
int eidx;
struct ArrayTree{
	Node node[40100];
	Node::SumLess cmp;
	void insert(int nd,Node val){
		for( ;nd<=mx;nd+=lowbit(nd)){
			if(cmp(val,node[nd])){
				node[nd]=val;
			}else{
				return;
			}
		}
	}
	
	Node query(int nd){
		Node ans=node[0];
		for( ;nd;nd-=lowbit(nd)){
			ans=min(ans,node[nd],cmp);
		}
		return ans;
	}
	void clear(){
		memset(this,63,sizeof(ArrayTree));
	}
	
}tree;
int fa[400010];
int getfa(int a){
	return fa[a]?(fa[a]=getfa(fa[a])):a;
}
struct List{
	int head[400010];
	int list[800010][2];
	int idx;	
	void add(int a,int b){
		idx++;
		list[idx][1]=head[a];
		head[a]=idx;
		list[idx][0]=b;
	}
}s,e;

struct _Main{


template<typename Type>
	void read(Type &a){
		char t,f=1;
		while(!isdigit(t=getchar())){
			if(t=='-') f=-1;
		}
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
		a*=f;
	}
int getdis(const Node &a,const Node &b)	{
	return abs(a.x-b.x)+abs(a.y-b.y);
}
	
long long ans;
_Main(){
	Node::XYEqual equal;
	Node tmp;
	int n;
	int a,b,c;
	int i,j,k;
	int I;
	read(n);
	for(i=1;i<=n;i++){
		read(arr[i].x);
		read(arr[i].y);
		arr[i].idx=i;
	}
	sort(arr+1,arr+n+1,Node::XYLessIdxGreater());
	a=n;
	for(i=n-1;i>=1;i--){
		if(equal(arr[i],arr[a])){
			s.add(arr[a].idx,arr[i].idx);
			swap(arr[n],arr[i]);
			n--;
			if(n+1==a)a=i;
		}else{
			a=i;
		}
	}
	
	for(I=1;I<=4;I++){
		switch (I){
			case 1:{
				DoNothing();
				break;
			}
			case 2:{
				for(i=1;i<=n;i++){
					swap(arr[i].x,arr[i].y);
				}
				break;
			}
			case 3:{
				for(i=1;i<=n;i++){
					arr[i].x=-arr[i].x;
				}
				break;
			}
			case 4:{
				for(i=1;i<=n;i++){
					swap(arr[i].x,arr[i].y);
				}				
				break;
			}
		}
		tree.clear();
		sort(arr+1,arr+n+1,Node::XYLess());
		for(i=n;i>=1;i--){
			tmp=tree.query(mx-(arr[i].y-arr[i].x+base));
			if(tmp.idx<1e6){
				edge[eidx++]=(Edge){arr[i].idx,tmp.idx,getdis(arr[i],tmp)};
			}
			tree.insert(mx-(arr[i].y-arr[i].x+base),arr[i]);
		}
	}
	sort(edge,edge+eidx);
	for(i=0;i<eidx;i++){
		if((a=getfa(edge[i].a))!=(b=getfa(edge[i].b))){
			e.add(edge[i].a,edge[i].b);
			e.add(edge[i].b,edge[i].a);
			ans+=edge[i].val;
			fa[a]=b;
		}
	}
//	printf("%lld", ans);
	dfs();
	printf("1");
}
void dfs(int nd=1,int from=0){
	printf("%d ",nd);
	int i;
	for(i=s.head[nd];i;i=s.list[i][1]){
		printf("%d ",s.list[i][0]);
	}
	for(i=e.head[nd];i;i=e.list[i][1]){
		if(e.list[i][0]!=from){
			dfs(e.list[i][0],nd);
		}
	}
}	
}nomadism_night;

}
