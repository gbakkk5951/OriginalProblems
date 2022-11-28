#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6+50;
int n,m,b[200],tot,head,stck[N*2],tp,tail;char c[N];
struct node{
	int x,nxt;
}a[N*2];
int ask(){
	tp=0;int ret=0,j=head,now1=0;
	while(a[j].x==0&&j)j=a[j].nxt,now1++;
	ret=now1;
	for(int i=head,now=0,la=0;i;i=a[i].nxt,now++){
		while((now==now1||a[j].x==0)&&j)j=a[j].nxt,now1++;
		ret=max(ret,now1-now-1);
		if(a[i].x==0){la++;continue;}
		if(a[i].x==1)stck[++tp]=now-la,la=0;
		else if(tp){
			la=now-stck[tp--]+1;
			ret=max(ret,la+now1-now-1);
		}
		else la=0;
	}
	return ret;
}
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	b['S']=0;b['s']=1;b['h']=-1;
	scanf("%d%d%s",&n,&m,c+1);
	for(int i=1;i<=n;i++)a[i]=(node){b[c[i]],i+1};
	a[n].nxt=0;head=1;tail=tot=n;
	printf("%d\n",ask());
	for(int i=1,k;i<=m;i++){
		scanf("%d%s",&k,c);
		if(k==1)a[++tot]=(node){b[c[0]],head},head=tot;
		else a[++tot]=(node){b[c[0]],0},a[tail].nxt=tot,tail=tot;
		printf("%d\n",ask());
	}
	return 0;
}
