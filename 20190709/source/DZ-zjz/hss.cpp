#include<iostream>
#include<cstdio>
#define regin register int
#include<algorithm>
#include<cmath>
#include<cstring>
#include<deque>

using namespace std;
deque<char> q;
int n,m;
int ans;
int mx;
int main ()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	getchar();
	for(regin i=1;i<=n;i++)
	{
		char c;
		scanf("%c",&c);
		if(c=='S'&&ans) 
		{
			ans++;
			mx=max(mx,ans);
			continue;
		}
		if(q.size()==0)
		{
			 q.push_back(c);continue;
		}
		if(c=='h'&&q.back()=='s')
		{
			ans+=2;
			q.pop_back();
			while(q.back()=='S'&&q.size())
			{
				ans++;
				if(q.size()==1) q.pop_front();
				else q.pop_back();
			}
		}
		else if(q.back()=='h')
		{
			ans=0;
			q.push_back(c);
		}
		else 
		{
			q.push_back(c);
		}		
		mx=max(mx,ans);
	}
	printf("%d\n",mx);
	
	for(regin i=1;i<=m;i++)
	{
		int x;
		char c;
		cin>>x;
		cin>>c;
		if(x==1)
		{
			if(c=='s'&&q.front()=='h')
			{
				ans+=2;
				q.pop_front();
				while(q.front()=='S'&&q.size())
				{
					ans++;
					q.pop_front();
				}
			}
			else q.push_front(c);
		}
		else 
		{
			if(c=='h'&&q.back()=='s')
			{
				ans+=2;
				q.pop_back();
				while(q.back()=='S'&&q.size())
				{
					ans++;
					if(q.size()==1) q.pop_front();
					else q.pop_back();
				}
			}
			else q.push_back(c);
		}
		printf("%d\n",ans);
	}
	return 0;
}
