using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<queue>

namespace Protector{
const int poolsize=5510031;
const int mxlayer=14;
struct SkipList{
	int key;
	int idx;
	bool operator < (const SkipList &b) const {
		return key==b.key?idx<b.idx:key<b.key;
	}
	bool operator > (const SkipList &b) const {
		return key==b.key?idx>b.idx:key>b.key;
	}
	SkipList *up,*down,*l,*r;
}pool[poolsize],arr[3500031];
int poolidx;
queue<SkipList *>q;


SkipList * Lhead[16], * Rhead[16], * L[16];
void inline link(SkipList *a,SkipList *b){
	b->r=a->r;
	a->r->l=b;
	a->r=b;
	b->l=a;
}
SkipList * newlist(){
	SkipList *nd;
	if(!q.empty()){
		nd=q.front();
		q.pop();
	}else if(poolidx<poolsize){
		nd=&pool[poolidx++];
	}else{
		nd=new SkipList;
	}
	return nd;
}
void inline free(SkipList *a){
	q.push(a);
}
void inline dislink(SkipList *a){
	a->l->r=a->r;
	a->r->l=a->l;
	a->r=a->l=0;

}
void erase(SkipList *nd){
	if(nd->l){
		dislink(nd);
		while(nd=nd->up){
			nd->down->up=0;
			nd->down=0;
			dislink(nd);
			free(nd);
		}
	}
}
void insert(SkipList *nd){
	int i;
	link(L[0],nd);L[0]=nd;
	for(i=1;i<mxlayer &&(rand()&3)==0;i++){
		nd->up=newlist();
		nd->up->down=nd;
		nd->up->idx=nd->idx;
		nd->up->key=nd->key;
		nd=nd->up;
		link(L[i],nd);
		L[i]=nd;			
	}
}
void find(const SkipList &tmp){
	int i;
	memcpy(L,Lhead,sizeof(L));
	for(i=mxlayer-1;i>=0;i--){	
		while((* L[i]->r)< tmp){
			L[i]=L[i]->r;
		}
		if(i)L[i-1]=L[i]->down;
	}
}

struct _Main{
char type[4000010];//0É¾ 1ÎÊ 2¸Ä 
int dst[400010];
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
		srand(998244353);
		SkipList *nd,tmp;
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
		for(i=0;i<mxlayer;i++){
			Lhead[i]=newlist();
			Rhead[i]=newlist();
			Lhead[i]->r=Rhead[i];
			Rhead[i]->l=Lhead[i];
			Lhead[i]->idx=-1e9;
			Lhead[i]->key=-1e9;
			Rhead[i]->idx=1e9;
			Rhead[i]->key=1e9;			
			if(i){
				Lhead[i]->down=Lhead[i-1];
				Lhead[i-1]->up=Lhead[i];
				Rhead[i]->down=Rhead[i-1];
				Rhead[i-1]->up=Rhead[i];				
			}
		}
		memcpy(L,Lhead,sizeof(L));
		for(i=1;i<=n;i++){
			arr[i].idx=arr[i].key=i;
			insert(&arr[i]);
		}
		for(Q=1;Q<=q;Q++){
			switch (type[Q]){
				case 0:{			
//					printf("del %d \n",random2());
					erase(&arr[random()]);
					break;
				}
				case 1:{
//					printf("query %d \n",random2());
					tmp.key=random();tmp.idx=1e9;
					find(tmp);
					if(L[0]->r->idx>n && L[0]->idx<0){
						printf("0\n");
					}else if(L[0]->r->key-tmp.key<tmp.key-L[0]->key){
						printf("%d\n",L[0]->r->idx);
					}else{
						printf("%d\n",L[0]->idx);
					}
					break;
				}
				case 2:{
					++dstidx;
					nd=&arr[dst[dstidx]];
//					printf("change %d to %d\n",dst[dstidx],random2());
					erase(nd);
					nd->key=random();
					find(*nd);
					insert(nd);
					break;
				}
			}
			
			
		}
	}
	
	
}std;

}

