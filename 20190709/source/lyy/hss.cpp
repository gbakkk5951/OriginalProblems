#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
struct node
{
	int l,r,end;
}q[4000005];
int n,m,px,mn,mx,ap[1000005];
int to0,tolast,ll,ans,sum;
string s;
char xl;
void up(int x)
{
	sum++;
	if(!q[to0].end)q[to0].l=1-sum,q[to0].end=1,q[to0].r=-999999999;
	else q[to0].r=max(q[to0].l,q[to0].r),q[to0].l=1-sum;
	ans=max(ans,q[to0].r-q[to0].l);
	to0-=x;tolast-=x;
	ans=max(ans,max(q[to0].l+sum,q[to0].r+sum));
}
void down(int x)
{
	tolast+=x;
	if(!q[tolast].end)q[tolast].l=ll,q[tolast].end=1,q[tolast].r=-999999999;
	else q[tolast].r=ll;
	if(tolast==to0)ans=ll;
	ans=max(ans,q[tolast].r-q[tolast].l);
}
int main()
{
	//freopen("hss.in","r",stdin);
	//freopen("hss.out","w",stdout);
	cin>>n>>m;ap[0]=2000000;
	cin>>s;ll=s.length();
	for(int i=1;i<=s.length();i++)
	{
		ap[i]=ap[i-1];
		if(s[i-1]=='s')ap[i]++;
		if(s[i-1]=='h')ap[i]--;
		if(!q[ap[i]].end)q[ap[i]].l=i,q[ap[i]].end=1,q[ap[i]].r=-99999999;
		else q[ap[i]].r=i;
		if(ap[i]==0)ans=i;
		mn=min(mn,ap[i]);
		mx=max(mx,ap[i]);
	}
	for(int i=mn;i<=mx;i++)ans=max(ans,q[i].r-q[i].l);
	to0=ap[0];
	tolast=ap[ll];
	cout<<ans<<endl;
	for(int i=1;i<=m;i++)
	{
		cin>>px>>xl;ll++;
		if(xl!='S')ans=max(ans,1);
		if(px==1)
		{
			if(xl=='s')up(1);
			if(xl=='h')up(-1);
			if(xl=='S')up(0);
		}
		if(px==2)
		{
			if(xl=='s')down(1);
			if(xl=='h')down(-1);
			if(xl=='S')down(0);
		}
		cout<<ans<<endl;
	}
	return 0;
}
