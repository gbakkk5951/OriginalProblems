#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int n,m;
char q[N];
struct node{
	int l,r,s,sk;
	bool v;
	char c;
}a[N];
inline void dd(int p){
	int st=p;
	while(p>0){
		if(a[p].sk)p=a[p].sk;
		else p=a[p].l;
		if(a[p].c=='s' && !a[p].v){
			a[st].sk=p;
			a[st].v=a[p].v=1;
			break;
		}
	}
}
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	int t=0;
	char ch;
	for(int i=1;i<=n;i++){
        char aa[2];
		scanf("%s",aa);
		a[++t].c=aa[0];
		a[t].l=t-1;
		a[t].r=t+1;
		if(a[t].c=='h')dd(t);
	}
	int ans=0;
	int pos;
	for(int i=t;i>0;i--){
		pos=i;
		while(a[pos].v||a[pos].c=='S'){
			if(a[pos].sk)pos=a[pos].sk;
			else pos=a[pos].l;
		}
		ans=max(ans,i-pos);
		i=pos;
	}
	printf("%d\n",ans);
	return 0;
}