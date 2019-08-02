#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;
const int N=5005;
int n,m,a[N],sum[N],cnt,ans[N],res;
char p[N];
inline bool getsum(int l,int r){
	return (sum[r]-sum[l-1]==0)?1:0;
}
bool flag;
inline void judge(int l,int r){
	int mid=(l+r)>>1;
	if(r==l)return ;
	if(sum[mid]-sum[l-1]<0){
		flag&=0;return ;
	}
	judge(l,mid);
}
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(register int i=1;i<=n;i++){
		cin>>p[i];
		switch(p[i]){
			case 'S':{
				a[i]=0;
				break;
			}
			case 's':{
				a[i]=1;
				break;
			}
			case 'h':{
				a[i]=-1;
				break;
			}
		}
		sum[i]=sum[i-1]+a[i];
	}
	cnt=0,res=0;
	for(register int i=1;i<=n;i++){
		for(register int j=i;j<=n;j++){
			if(getsum(i,j)){
				flag=1;judge(i,j);
				if(flag) ans[++cnt]=j-i+1,res=max(res,ans[cnt]);
			}
		}
	}
	printf("%d\n",res);
}
