#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
char st[5100],str[10010];
int a[5010],b[5010],c[5010];
int ans1,ans2,ans3,beg,max123,qqq=0,cnt,max1;
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	if(m==0){
        for(int i=0;i<n;i++){
        	cin>>st[i];
        }
		int len=strlen(st);
			int maxn=0,ans1=0,ans2=0,ans3=0;
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
			memset(c,0,sizeof(c));
			for(int j=0;j<len;j++){
				if(st[j]=='S'){
					ans1++;a[ans1]=j;
				}
			    if(st[j]=='s'){
			    	
			        ans2++;	b[ans2]=j;
			        
			    }
			    if(st[j]=='h'){	
			    	ans3++; c[ans3]=j;
			    }
				if(ans2<ans3){
					int max1=ans1+ans2+ans2;
					maxn=max(maxn,max1);
					ans1=0,ans2=0,ans3=0;
					
				}
				if(st[j+1]!='s'&&ans2==ans3&&ans2!=0){
					int max1=ans1+ans2+ans2;
					maxn=max(maxn,max1);
					ans1=0,ans2=0,ans3=0;
				}
			}
			if(ans2>ans3){
				for(int k=c[ans3]+1;k<len;k++){
					if(st[k]='S') qqq++;
					else break;
				}
				 max1=c[ans3]+qqq-b[ans2-ans3];
			}
			maxn=max(maxn,max1);
			max123=max(max123,maxn);
		}
		cout<<max123<<endl;	
	return 0;
}
