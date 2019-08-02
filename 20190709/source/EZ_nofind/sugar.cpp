#include<bits/stdc++.h>
using namespace std;
const int maxl=5000010;
const int maxn=100010;
int n,tot,ans;
int fail[maxl];
int ac[maxl][2];
bool end[maxl];
char s[maxl],s1[maxl];
inline void insert(char *s)
{
	int len=strlen(s+1),now=0;
	for(int i=1;i<=len;i++)
	{
		int c=s[i]-'0';
		if(!ac[now][c]) ac[now][c]=++tot;
		now=ac[now][c];
	}
	end[now]=1;
}
void getfail()
{
	queue<int> q;q.push(0);
	while(!q.empty())
	{
		int x=q.front(),k=fail[x];q.pop();
		for(int i=0;i<2;i++)
		{
			int y=ac[x][i];
			if(!y) ac[x][i]=ac[k][i];
			else fail[y]=x?ac[k][i]:0,q.push(y);
		}
	}
}
void find(char *s)
{
	int len=strlen(s+1),now=0;
	for(int i=1;i<=len;i++)
	{
		int c=s[i]-'0';now=ac[now][c]?ac[now][c]:fail[now];
		int tmp=now;bool flag=0;
		while(tmp)
		{
			if(end[tmp]){ans++;flag=1;break;}
			tmp=fail[tmp];
		}
		if(flag) now=0;
	}
}
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) scanf("%s",s1+1),insert(s1);
	getfail();find(s);
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
