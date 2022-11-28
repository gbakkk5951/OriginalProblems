#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define N 5000010
char str[N],wen[N];
int n,cnt,val[N],ver[N],nxt[N],tot,head[N],size[N];
int fail[N],trie[N][3];
queue<int>q;
long long ans;
void add(int x,int y)
{
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int u)
{
	for(int i=head[u];i;i=nxt[i])
	{
		dfs(ver[i]);
		size[u]+=size[ver[i]];
	}
}
void insert(char *s,int v)
{
	int len=strlen(s),now=0;
	for(int i=0;i<len;i++)
	{
		int ch=s[i]-'0';
		if(trie[now][ch]==0)trie[now][ch]=++cnt;
		now=trie[now][ch];
	}
	val[v]=now;
}
void bfs()
{
	for(int i=0;i<2;i++)
	{
		if(trie[0][i]==0)
		{
		 fail[trie[0][i]]=0;
		 q.push(trie[0][i]);
	    }
	}
	while(q.size())
	{
		int x=q.front();
		q.pop();
		for(int i=0;i<2;i++)
		{
			if(!trie[x][i])
			{
				fail[trie[x][i]]=trie[fail[x]][i];
				q.push(trie[x][i]);
			}
			else
			fail[x]=fail[trie[x][i]];
		}
	}
}
void query(char *s)
{
	int len=strlen(s);
	int now=0;
	for(int i=0;i<len;i++)
	{
		now=trie[now][s[i]-'0'];
		size[now]++;
	}
}
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",wen);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		insert(str,i);
	}
	bfs();
	query(wen);
	for(int i=1;i<=cnt;i++)add(fail[i],i);
	dfs(0);
//	long long sum=0;
	for(int i=1;i<=n;i++)
	{
		ans+=size[val[i]];
//		printf("%d ",val[i]);
//		printf("%d ",size[i]);
	}
	printf("%lld",ans);
//	printf("0");
	return 0;
}
