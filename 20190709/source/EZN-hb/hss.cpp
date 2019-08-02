#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;
const int N=1000010;
int l[N],r[N],tot=1;
char c[N],st[N],e[N];
void add(int a,char c){
	if(a==2){
		l[++tot]=0;
		r[tot]=r[0];
		l[r[0]]=tot;
		r[0]=tot;
		e[tot]=c;
	}
	else if(a==1){
		r[++tot]=1;
		l[tot]=l[1];
		r[l[1]]=tot;
		l[1]=tot;
		e[tot]=c;
	}
}

int work(){
	int ans1=0,lnt=0,rnt=0,ans2=0,ans;
	bool flag=0;
	for(int i=r[0];i!=1;i=r[i]){
		if(e[i]!='S'&&flag==0) {
			st[++lnt]=e[i];
			if(st[lnt-1]=='s'&&st[lnt]=='h') ans1+=2,lnt-=2;
		}
		else if(e[i]=='S'){
			flag=1;
		}
		else if(flag==1){
			st[++rnt]=e[i];
			if(st[rnt-1]=='s'&&st[rnt]=='h') ans2+=2,rnt-=2;
		}
	}
	if(lnt==0&&rnt==0) ans=ans1+ans2+1;
	else if(lnt==0&&rnt!=0) ans=max(ans1+1,ans2);
	else if(rnt==0&&lnt!=0) ans=max(ans1,ans2+1);
	return ans;
}

int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	int n,m;
	l[0]=1,r[1]=0,r[0]=1,l[1]=0;
	scanf("%d%d",&n,&m);
	scanf("%s",c);
	int len=strlen(c);
	for(int i=0;i<n;i++) add(1,c[i]);
	printf("%d\n",work());
	while(m--){
		int a;
		char op[2];
		scanf("%d%s",&a,op);
		if(a==2){
		add(1,op[0]);
	}
		else if(a==1)
		add(2,op[0]);
		printf("%d\n",work());
	} 
	return 0;
}
