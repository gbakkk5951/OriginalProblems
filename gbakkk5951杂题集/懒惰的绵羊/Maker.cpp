int main(){}
using namespace std;
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<ctime>
long long lrand(){
	return (long long) ((long long)rand()<<45LL) | ((long long)rand()<<30LL) | ((long long)rand()<<15LL) | (long long)rand();
}

template<typename Type>
void shuffle(Type *begin,Type *end){
	int n=1;Type *idx,*dst,temp;
	for(idx=begin;idx!=end;idx++){
		dst=begin+lrand()%n;
		temp=*idx;*idx=*dst;
		*dst=temp;
		n++;
	}
}

int n,q,t;
int tl[300010];
struct Ques{
	int op,a,b;
}ques[6050000];
const long long mod=(long long)1e9;

void print(bool mess=false){
	if(mess){
		shuffle(ques,ques+q);
	}
	int i,j,k;
	printf("%d %d %d\n",n,q,t);
	for(i=0;i<=n;i++){
		printf("%d ",tl[i]);
	}putchar('\n');
	for(i=0;i<q;i++){
		if(ques[i].op==1){
			printf("%d %d %d\n",ques[i].op,ques[i].a,ques[i].b);
		}else{
			printf("%d %d\n",ques[i].op,ques[i].a);
		}
	}
}
void ini(){
	int i;
	for(i=0;i<=(n/2);i++){
		tl[i]=1+rand()%5;
	}
	for(i=(n/2+1);i<=n;i++){
		tl[i]=1+lrand()%(n/2);
	}	
}
void make1(){
	long long rem=50000000;
	int i,j,k;int a,b,c;int temp;
	n=297836;t=1;q=5990807;
	ini();
	for(i=0;i<q;i++){
		if(rand()<=300)
		temp=lrand()%(n+1);
		else if(rand()<=10000)
		temp=lrand()%(n/4);
		else temp=lrand()%(n/500);
		if(rem<temp){
			ques[i].op=2;
			if(rand()<=15){
				ques[i].a=lrand()%mod;
			}else{
				ques[i].a=lrand()%(n+1);
			}
		}else{
			rem-=temp;
			ques[i].op=1;ques[i].a=temp;
			ques[i].b=1+lrand()%(n/2);
		}
	}
	print(true);
}
void make2(){
	int i,j,k;int a,b,c;int temp;
	n=299750;q=5989709;t=1;int goal=0;int cnt=0;
	ini();
	for(i=0;i<q;i++){
		if(i<=goal){
			ques[i].op=1;
			ques[i].a=lrand()%(n+1);
			if(rand()<=15){
				ques[i].b=lrand()%mod+1;
			}else{
				if(rand()<3000)
				ques[i].b=lrand()%(n/10)+1;
				else ques[i].b=lrand()%n+1;
			}
			continue;
		}
		if(i>=50000&&i%50000==0 &&cnt<100){
			cnt++;
			if(i==50000){
				goal=i+2000;
			}else{
				goal=i+900+rand()%90;
			}
		}
		ques[i].op=2;
		if(rand()<=15){
			ques[i].a=lrand()%mod;
		}else{
			ques[i].a=lrand()%(n+1);
		}
	}
	print(false);
}
void make3(){
	int i,j,k;int a,b,c;int temp;
	n=298759;q=5993560;t=2;int goal=0;int cnt=0;
	ini();	
	for(i=0;i<q;i++){
		if(i<=goal){
			ques[i].op=2;
			if(rand()<=15){
				ques[i].a=lrand()%mod;	
			}else{
				ques[i].a=lrand()%(n+1);
			}
			continue;
		}
		if(i>=50000&&i%50000==0&&cnt<100){
			cnt++;
			if(i==50000){
				goal=i+2000;
			}else{
				goal=i+900+rand()%90;
			}
		}
		ques[i].op=1;
		ques[i].a=lrand()%(n+1);
		if(rand()<=15){
			ques[i].b=lrand()%mod+1;
		}else{
			if(rand()<3000)
			ques[i].b=lrand()%(n/10)+1;
			else ques[i].b=lrand()%n+1;
		}
	}
	print(false);	
	
}
void make4(){
	int i,j,k;int a,b,c;int temp;
	n=288759;q=999993;t=2;int mid=0;int cnt=0;
	ini();	
	
	for(i=0;i<q;i++){
		if(i%10000==0&&cnt<100){
			cnt++;
			mid=250+(lrand()%(n-505));
		}
		if(rand()&1){
			ques[i].op=1;
			if(rand()&1){
				ques[i].a=mid+lrand()%251;
			}else{
				ques[i].a=mid-lrand()%251;
			}
			if(rand()<=15){
				ques[i].b=lrand()%mod+1;
			}else{
				if(rand()<3000)
				ques[i].b=lrand()%(n/10)+1;
				else ques[i].b=lrand()%n+1;
			}
		}else{
			ques[i].op=2;
			if(rand()&1){
				ques[i].a=mid+lrand()%251;
			}else{
				ques[i].a=mid-lrand()%251;
			}			
		}
	}
	
	
	print(false);
}

struct _Main{

_Main(){
	freopen("sheep4.in","w",stdout);
	srand(time(0));
	make4();
	fclose(stdout);
}

	
	
}Maker;
