#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
string s[100001],p;
queue<int> q; 
int ans[100001];
struct node{
	int fail[100001],c[100001][26],val[100001],cnt;
	inline void insert(string s)
	{
		int len=s.length(),now=0;
		for(int i=0;i<len;++i)
		{
			int q=s[i]-'a';
			if(!c[now][q]) c[now][q]=++cnt;
			now=c[now][q];
		}
		val[now]++;
		return ;
	}
	inline void build()
	{
		for(int i=0;i<26;++i)
		{
			if(c[0][i]) 
			{
				fail[c[0][i]]=0;
				q.push(c[0][i]);
			}
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;++i)
			{
				if(c[u][i])
				{
					fail[c[u][i]]=c[fail[u]][i];
					q.push(c[u][i]);
				}
				else c[u][i]=c[fail[u]][i];
			}
		}
		return ;
	}
	inline int query(string k)
	{
		int now=0,len=k.length(),ans=0;
		return ans;
	}	
}ac;
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	int n;
	scanf("%d",&n);cin>>p;
	for(int i=1;i<=n;++i)
	{
		cin>>s[i];
		ac.insert(s[i]);
	}
	ac.build();
	cout<<ac.query(p)<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
