using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
int base=0;//位置偏移量 
struct SumType{
	long long val;
	int r;
}sum,q[3005];
struct Defender{
	int pos,tme;
}arr[500005];

int pmn,pmx,tmx;

struct _Main{
template<typename Type>
	void read(Type &a){
		char t,f=1;
		while(!isdigit(t=getchar())){
			if(t=='-')f=-1;
		}
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
		a*=f;
	}	

long long dp[3005];//i时间，（护盾就绪）最少受到的伤害。 
long long atk[3005][3005];//第i位置前j时间受到的总伤害。 
long long lost[3005];//前i时间的总损失， 
int num[3005][3005]; //i位置 j时间 有多少设施 
long long dec[3005];//滚动使用，当前时刻若力场护盾加在i处，能减少的损失。 
long long mxdec;
void inline change(int x1,int x2,int y1,int y2,int val){
	x1=max(x1,1);
	x2=min(x2,pmx);
	if(x1>x2)return;
	tmx=max(tmx,y2);
	atk[x1-1][y1-1]+=val;
	atk[x2][y2]+=val;
	atk[x1-1][y2]-=val;
	atk[x2][y1-1]-=val;
}

int head,tail;

int n,m,r,s;
_Main(){
	
	memset(dp,63,sizeof(dp));
	int i,j;
	int a,b,c,d,e,f,g;
	pmx=-50000;
	pmn=50000;
	read(n);read(m);read(r);read(s);read(a);read(b);
	for(i=1;i<=n;i++){
		read(arr[i].pos);read(arr[i].tme);
		pmn=min(arr[i].pos,pmn);
		pmx=max(arr[i].pos,pmx);
	}
	base=-pmn+1;
	pmx=pmx-pmn+1;
	for(i=1;i<=n;i++){
		c=arr[i].pos;d=arr[i].tme;
		num[c+base][d]++;
	}
	
	for(i=1;i<=a;i++){
		read(c);read(d);read(e);read(f);read(g);
		change(c+base,d+base,e,e+f-1,g);		
	}
	for(i=1;i<=b;i++){
		read(c);read(d);read(e);read(f);read(g);
		change(c+base,d+base,e,e+f-1,-g);
	}
	for(i=pmx;i>=1;i--){
		for(j=tmx;j>=1;j--){
			atk[i][j]+=atk[i+1][j]+atk[i][j+1]-atk[i+1][j+1];
		}
	}
	for(i=1;i<=pmx;i++){
		for(j=1;j<=tmx;j++){
			num[i][j]+=num[i][j-1];
			lost[j]+=num[i][j]*atk[i][j];
			atk[i][j]+=atk[i][j-1];
		}
	}
	for(i=1;i<=tmx;i++){
		lost[i]+=lost[i-1];
	}
	dp[0]=0;
	dp[1]=0;
	for(i=1;i<=tmx;i++){
		dp[i+1]=min(dp[i+1],dp[i]+lost[i]);
		for(j=1;j<=pmx;j++){
			dec[j]=num[j][i]*(atk[j][min(tmx,i+r-1)]-atk[j][i-1]);
		}
		mxdec=0;
		head=tail=sum.val=0;
		sum.r=0;
		q[tail++]=sum;
		for(j=1;j<=pmx;j++){
			sum.val+=dec[j];
			sum.r=j;
			while(tail>head &&q[tail-1].val>=sum.val){
				tail--;
			}
			q[tail++]=sum;
			if(q[head].r<j-m){
				head++;
			}
			mxdec=max(mxdec,sum.val-q[head].val);
		}
		dp[min(r+i+s,tmx+1)]=min(dp[min(r+i+s,tmx+1)], dp[i]+lost[min(r+i+s-1,tmx)]-lost[i-1]-mxdec);
	}
	printf("%lld",dp[tmx+1]);
}	
	
	
}forceshield;
