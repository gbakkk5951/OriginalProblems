#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N=200010;
#define ll long long
inline int read(){
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();	}
	while(ch<='9'&&ch>='0'){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
int n,m,ans;
int a[N],f[N],b[N];
char c;
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='S'){
			a[i]=2;
		}
		if(c=='s'){
			a[i]=-1;
		}
		if(c=='h'){
			a[i]=1;
		}
	}
	int len=0;
	for(len=n;len>=0;len-=2){
		for(int i=1;i<=n-len;i++){
			int now=0;
			for(int j=i;j<=i+len;j++){
				if(a[j]==2)break;
				now+=a[j];
			}
			if(now==0){
				ans=len;
				if(a[i-1]==2||a[i+len+1]==2)ans++;
				break;
			}
		}
		if(ans)break;
	}
	cout<<ans<<endl;
	ans=0;int opt;
	while(m--){
		opt=read();cin>>c;
		if(opt==1){
			for(int i=1;i<=n;i++)b[i]=a[i];
			if(c=='h')a[1]=1;
			else a[1]=-1;
			for(int i=2;i<=n+1;i++)
			a[i]=b[i-1];
			n++;
			for(len=n;len>=0;len-=2){
				for(int i=1;i<=n-len;i++){
				int now=0;
				for(int j=i;j<=i+len;j++){
					if(a[j]==2)break;
					now+=a[j];
				}
				if(now==0){
					ans=len;
					if(a[i-1]==2||a[i+len+1]==2)ans++;
					break;
				}
			}
				if(ans)break;
			}
			cout<<ans<<endl;
		}
		if(opt==2){
			if(c=='h')
			a[++n]=1;
			else a[++n]=-1;
			for(len=n;len>=0;len-=2){
				for(int i=1;i<=n-len;i++){
				int now=0;
				for(int j=i;j<=i+len;j++){
					if(a[j]==2)break;
					now+=a[j];
				}
				if(now==0){
					ans=len;
					if(a[i-1]==2||a[i+len+1]==2)ans++;
					break;
				}
			}
			if(ans)break;
			}
			cout<<ans<<endl;
		}
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
