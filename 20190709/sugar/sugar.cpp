#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
#define R register
struct ccf
{
	int tr[5000005][2],cnt,end[5000005],fail[5000005];
	void insert(char *kkk)
	{
		int now=0;
		for(R int i=0;kkk[i];++i)
		{
			if(!tr[now][kkk[i]-'0'])tr[now][kkk[i]-'0']=++cnt;
			now=tr[now][kkk[i]-'0'];
		}
		end[now]=1;
	}
	void build()
	{
		queue<int>q;
		for(R int i=0;i<2;i++)if(tr[0][i])q.push(tr[0][i]);
		while(!q.empty())
		{
			int now=q.front();q.pop();
			for(R int i=0;i<2;i++)
			{
				if(tr[now][i])
				{
					fail[tr[now][i]]=tr[fail[now]][i];
					q.push((tr[now][i]));
				}
				else tr[now][i]=tr[fail[now]][i];
			}
		}
	}
	int ask(char *kkk)
	{
		int now=0,res=0;
		for(R int i=0;kkk[i];i++)
		{
			now=tr[now][kkk[i]-'0'];
			for(R int j=now;j;j=fail[j])
			{
				res+=end[j];
				if(end[j]){now=0;break;}
			}
		}
		return res;
	}
}ac;
int n;
char s[5000005],ss[5000005];
int main()
{
	scanf("%d",&n);scanf("%s",ss);
	for(R int i=1;i<=n;i++)
	{
		scanf("%s",s);
		ac.insert(s);
	}
	ac.build();
	printf("%d\n",ac.ask(ss));
}
