using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<set>
#include<queue>

namespace Protector{
struct Node{
	int key;
	int idx;
	bool operator < (const Node &b) const {
		return key==b.key?idx<b.idx:key<b.key;
	}
	bool operator > (const Node &b) const {
		return key==b.key?idx>b.idx:key>b.key;
	}
	struct IdxCmp{
		bool operator () (const Node &a,const Node &b){
			return a.idx<b.idx;
		}
	};
};



set<Node> tree;
set<Node>::iterator it,it0,itarr[4000100];
struct _Main{
char type[4000010];//0É¾ 1ÎÊ 2¸Ä 
int dst[500010];
int dstidx;
template<typename Type>	
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}
	int A,B,C,n;
	int random(){
		static long long a=A;
		return (int)(a=((a*B+C)%n+1));
	}
	int random2(){
		static long long a=A;
		return (int)(a=((a*B+C)%n+1));
	}
	_Main(){
		int Q,q,q1,q2;
		int i,j,k;
		int a,b,c;
		int t;
		Node nd;
		read(A);read(B);read(C);
		read(n);read(q);read(q1);read(q2);
		for(i=1;i<=q1;i++){
			read(a);
			type[a]=1;
		}
		for(i=1;i<=q2;i++){
			read(b);
			type[b]=2;
			read(dst[i]);
		}
		tree.insert((Node){-1e9,-1e9});
		tree.insert((Node){1e9,1e9});
		for(i=1;i<=n;i++){
			tree.insert((Node){i,i});
			itarr[i]=tree.find((Node){i,i});
		}
		for(Q=1;Q<=q;Q++){
			switch (type[Q]){
				case 0:{
					t=random();
					if(itarr[t]!=tree.begin()){
						tree.erase(itarr[t]);
						itarr[t]=tree.begin();
					}
					break;
				}
				case 1:{
					nd.key=random();nd.idx=1e9;
					it0=it=tree.lower_bound(nd);
					it0--;
					if(it->idx> n && it0->idx<0){
						printf("0\n");
					}else if(it->key-nd.key<nd.key-it0->key){
						printf("%d\n",it->idx);
					}else{
						printf("%d\n",it0->idx);
					}
					break;
				}
				case 2:{				
					++dstidx;
					it=itarr[dst[dstidx]];
					if(it!=tree.begin()){
						tree.erase(it);
					}
					nd.idx=dst[dstidx];
					nd.key=random();
					tree.insert(nd);
					itarr[dst[dstidx]]=tree.find(nd);
					break;
				}
			}
			
			
		}
	}
	
	
}std;

}

