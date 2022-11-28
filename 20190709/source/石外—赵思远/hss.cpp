#include<bits/stdc++.h>
using namespace std;
string dfs,k;
int ps[5002],ph[5002];
int cs,ch,n,m,len,op;
inline bool check(string s)
{
	for(int i=1;i<len-1;++i)
	{
		if(s[i]!='S') return 0;
	}
	return 1;
}
inline int ask()
{
	cs=0;ch=0;
	memset(ps,0,sizeof(ps));
	memset(ph,0,sizeof(ph));
	string s="h"+k+"s";
	len=s.length();
	for(int i=0;i<len;++i)
	{
		if(s[i]=='s')ps[++cs]=i;
		else if(s[i]=='h') ph[++ch]=i;
	}
	
	int now=cs-1,maxx=0,last=len-2,i;
	for(i=ch;i>=1&&now>=1;i--)
	{
		if(ph[i]>ps[now]) 
		{
			now--;
		}
		else
		{
			maxx=max(maxx,last-ps[now]);
			last=ph[ch]-1;now--;
			while(now>=1&&ph[i]<ps[now]) now--;
		}
	}
	if(now==0) 
	{
		maxx=max(maxx,last-ph[i]);
	}
	if(check(k)) printf("%d\n",len-2);
	else printf("%d\n",maxx);
}
inline void cl(int op,string qs)
{
	if(op==1) k=qs+k;
	else k+=qs;
	return ;
}
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		cin>>dfs;
		k+=dfs;
	} 
	ask();
	while(m--)
	{
		scanf("%d",&op);cin>>dfs;
		cl(op,dfs);
		ask(); 
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
