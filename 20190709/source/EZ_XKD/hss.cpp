#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ret=0,fix=1;char ch;
	while(!isdigit(ch=getchar()))fix=ch=='-'?-1:fix;
	do ret=(ret<<1)+(ret<<3)+ch-'0';
	while(isdigit(ch=getchar()));
	return ret*fix;
}
const int maxn=1000009;
int n,m,maxl;
char s[maxn*3];
int sums[maxn],sumh[maxn];
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	int st=m+1,ed=n+m;int lS=0;
	for(int i=1;i<=n;i++){
		scanf("%c",&s[m+i]);
		if(s[m+i]=='s')sums[m+i]=sums[m+i-1]+1;
		else sums[m+i]=sums[m+i-1];
		if(s[m+i]=='h')sumh[m+i]=sumh[m+i-1]+1;
		else sumh[m+i]=sumh[m+i-1];
		if((s[i]=='S' && s[i-1]=='S') || lS==0)lS++;
		else if(s[i]!='S')maxl=max(maxl,lS),lS=0;
	}
	int fl=maxl;
	for(int l=n;l>=2;l--){
		int f=0;
		for(int i=st;i<=ed-l+1;i++){
			if(sums[i+l-1]-sums[i-1]!=sumh[i+l-1]-sumh[i-1])continue;
			int cnts=0;f=0;
			for(int j=i;j<=i+l-1;j++){
				if(s[j]=='s')cnts++;
				if(s[j]=='h'){
					if(cnts==0)break;
					cnts--;
				}
				if(j==i+l-1)f=1;
			}
			if(f){fl=max(fl,l);break;}
		}
		if(f)break;
	}
	printf("%d\n",fl+1);
	char op[2],ch;int p;
	for(int t=1;t<=m;t++){
//		scanf("%d%s",&p,op);
		p=read();
		op[0]=getchar();getchar();
		if(p==1)s[--st]=op[0];
		else s[++ed]=op[0];
		
		fl=maxl;
		for(int l=n+t;l>=2;l--){
//			int f=0;
			for(int i=st;i<=ed-l+1;i++){
				if(sums[i+l-1]-sums[i-1]!=sumh[i+l-1]-sumh[i-1])continue;
				int cnts=0;int f=0;
				for(int j=i;j<=i+l-1;j++){
					if(s[j]=='s')cnts++;
					if(s[j]=='h'){
						if(cnts==0)break;
						cnts--;
					}
					if(j==i+l-1)f=1;
				}
				if(f){fl=max(fl,l);break;}
			}
//			if(f)break;
		}
		printf("%d\n",fl);
	}
}
