#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,ans=0;
string str,s2;
int main(){
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	cin>>n>>m>>str;
	for(int a=0;a<n;a++){
		for(int b=a;b<n;b++){
			s2=str;
			int f2=1;
			for(int c=a;c<=b;c++){
				int flag=1;
				if(s2[c]=='s'){
					flag=0;
					for(int d=c+1;d<=b;d++){
						if(s2[d]=='h'){
							s2[d]='S';
							flag=1;
							break;
						}
					}
				}
				if(s2[c]=='h')flag=0;
				if(flag==0){
					f2=0;
					break;
				}
			}
			if(f2==1)ans=max(ans,b-a+1);
	}
}
	cout<<ans;
	return 0;
}

