#include<cstdio>
#define N 2000005
using namespace std;
inline int max(int a,int b){return a>b?a:b;}
int n,m,opt,ans,cur[N],lst[N],nxt[N],tot[N],cnt=1;
char s[5];
int ok[N];
inline void addh(int x){
	int nnn=nxt[0];
	cnt++;
	cur[cnt]=x;
	nxt[0]=cnt;
	lst[cnt]=0;
	nxt[cnt]=nnn;
	lst[nnn]=cnt;
	tot[cnt]=1;
}
inline void addt(int x){
	int lll=lst[1];
	cnt++;
	cur[cnt]=x;
	nxt[lll]=cnt;
	lst[cnt]=lll;
	nxt[cnt]=1;
	lst[1]=cnt;
	tot[cnt]=1;
}
inline int merge(int x,int y,int tag){
	cur[x]=1;
	tot[x]+=tot[y];
	nxt[x]=nxt[y];
	lst[nxt[y]]=x;
	ok[x]|=ok[y];
	ok[x]|=tag;
	return x;
}
inline int judge(int x,int tag){
	int maybe=0;
	if(cur[x]==1){
		if(cur[lst[x]]==1){
			maybe=merge(lst[x],x,tag);
			maybe=judge(maybe,tag);
		}
		if(maybe){
			maybe=merge(maybe,nxt[maybe],tag);
			maybe=judge(maybe,tag);
		}
		else if(cur[nxt[x]]==1){
			maybe=merge(x,nxt[x],tag);
			maybe=judge(maybe,tag);
		}
	}
	else if(cur[x]==2){
		if(cur[nxt[x]]==3){
			maybe=merge(x,nxt[x],1);
			judge(x,1);
		}
		else if(cur[nxt[x]==1]){
			int nnn=nxt[nxt[x]];
			if(cur[nnn]==3){
				maybe=merge(x,nxt[x],1);
				maybe=merge(maybe,nxt[maybe],1);
				maybe=judge(maybe,1);
			}
		}
	}
	else {
		if(cur[lst[x]]==2){
			maybe=merge(lst[x],x,1);
			judge(maybe,1);
		}
		else if(cur[lst[x]]==1){
			int lll=lst[lst[x]];
			if(cur[lll]==2){
				maybe=merge(lst[x],x,1);
				maybe=merge(lst[maybe],maybe,1);
				maybe=judge(maybe,1);
			}
		}
	}
	if(ok[maybe])ans=max(ans,tot[maybe]);
	return maybe?maybe:x;
}
int main(){
	freopen("hss.in","r",stdin);freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	nxt[1]=1;
	nxt[0]=1;
	lst[1]=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		if(s[0]=='S')addt(1);
		else if(s[0]=='s')addt(2);
		else addt(3);
		judge(cnt,0);
	}
	printf("%d\n",ans);
	while(m--){
		scanf("%d%s",&opt,s);
		int y;
		if(s[0]=='S')y=1;
		else if(s[0]=='s')y=2;
		else y=3;
		if(opt==1)addh(y);
		else addt(y);
		judge(cnt,0);
		printf("%d\n",ans);
	}
	return 0;
}
/*
6 3
S s s s h h
2 h
1 h
1 s
*/
