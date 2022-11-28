#include<bits/stdc++.h>
using namespace std;
char s1[500003],s2[500003];
int next[500003][2],fail[500003],tot;
bool end[500003];
void insert(char* s)
{
	int len=strlen(s),now=0;
	for(int i=0;i<len;i++)
	{
		if(end[now])return;
		if(!next[now][s[i]-'0'])next[now][s[i]-'0']=++tot;
		now=next[now][s[i]-'0'];
	}
	end[now]=1;
}
int q[500003],he,tl;
void bfs()
{
	if(next[0][0])q[++tl]=next[0][0];
	if(next[0][1])q[++tl]=next[0][1];
	while(++he<=tl)
	{
		int now=q[he];
		//if(end[now])fail[now]=0;
		for(int i=0;i<=1;i++)
		{
			if(next[now][i])
			{
				int t=fail[now];
				while(t&&(!next[t][i]))t=fail[t];
				if(next[t][i])fail[next[now][i]]=next[t][i];
			}
			else
			{
				int t=fail[now];
				while(t&&(!next[t][i]))t=fail[t];
				next[now][i]=next[t][i];
			}
		}
	}
}
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	int n;
	scanf("%d",&n);
	scanf("%s",s1);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s2);
		insert(s2);
	}
	bfs();
	int len=strlen(s1),now=0,ans=0;
	for(int i=0;i<len;i++)
	{
		now=next[now][s1[i]-'0'];
		if(end[now])ans++,now=0;
	}
	printf("%d\n",ans);
}
