#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int a[3000010];
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	int l=1000000,r=l+n-1;
	for(int i=l;i<=r;i++){
		char s[3];
		scanf("%s",s);
		if(s[0]=='S')a[i]=2;
		else if(s[0]=='s')a[i]=0;
		else a[i]=1;
	}
	int ans=0;
	int top=0,cnt=0;
	for(int i=l;i<=r;i++){
		if(a[i]==2)cnt++;
		if(a[i]==0)top++;
		else if(a[i]==1){
			top--;
			if(top<0){
				ans=max(ans,cnt);
				cnt=0;
				top=0;
			}
			else{
				cnt+=2;
			}
		}
	}
	ans=max(ans,cnt);
	printf("%d\n",ans);
	while(m--){
		int p,x;
		char s[2];
		scanf("%d",&p);
		scanf("%s",s);
		if(s[0]=='S')x=2;
		else if(s[0]=='s')x=0;
		else x=1;
		if(p==1)a[--l]=x;
		else a[++r]=x;
		ans=0;
		top=0,cnt=0;
		for(int i=l;i<=r;i++){
			if(a[i]==2)cnt++;
			if(a[i]==0)top++;
			else if(a[i]==1){
				top--;
				if(top<0){
					ans=max(ans,cnt);
					cnt=0;
					top=0;
				}
				else{
					cnt+=2;
				}
			}
		}
		ans=max(ans,cnt);
		printf("%d\n",ans);
	}
	return 0;
}
/*6 3
S s s s h h
2 h
1 h
1 s
*/
//# ( ( ( ) )
//2 0 0 0 1 1
