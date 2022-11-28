#include<cstdio>
#include<cstring>
int first[100050],next[200050],to[200050],tot=0,depth[100050],father[100050];
long long point[100050];
bool visited[100050];
int swap(int &a,int &b)
{
	a^=b;
	b^=a;
	a^=b;
	return 0;
}
long long max(long long a,long long b)
{
	if(a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int add(int x,int y)
{
	next[++tot]=first[x];
	to[tot]=y;
	first[x]=tot;
	return 0;
}
int dfs(int a)
{
	register int T;
	T=first[a];
	while(T)
	{
		if(to[T]==father[a])
		{
			T=next[T];
			continue;
		}
		father[to[T]]=a;
		depth[to[T]]=depth[a]+1;
		dfs(to[T]);
		T=next[T];
	}
	return 0;
}
int querychildtree(int a,int &mode,long long &ans)
{
	register int T;
	T=first[a];
	visited[a]=1;
	while(T)
	{
		if(depth[to[T]]==depth[a]+1&&!visited[to[T]])
		{
			dfs(to[T]);
		}
		T=next[T];
	}
	if(mode==1)
	{
		ans=max(ans,point[a]);
	}
	if(mode==2)
	{
		ans+=point[a];
	}
	return 0;
}
long long search(int x,int y,int &mode)
{
	register int T;
	long long ans=0;
	if(depth[x]<depth[y])
	{
		swap(x,y);
	}
	while(depth[x]<depth[y])
	{
		if(mode==1)
		{
			ans=max(ans,point[x]);
		}
		if(mode==2)
		{
			ans+=point[x];
		}
		if(mode==3)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans=max(ans,point[to[T]]);
				T=next[T];
			}
			visited[x]=1;
		}
		if(mode==4)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans+=point[to[T]];
				T=next[T];
			}
			visited[x]=1;
		}
		x=father[x];
	}
	while(x!=y)
	{
		if(mode==1)
		{
			ans=max(ans,max(point[x],point[y]));
		}
		if(mode==2)
		{
			ans+=point[x]+point[y];
		}
		if(mode==3)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans=max(ans,point[to[T]]);
				T=next[T];
			}
			T=first[y];
			while(T)
			{
				if(to[T]==father[y]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans=max(ans,point[to[T]]);
				T=next[T];
			}
			visited[x]=1;
			visited[y]=1;
		}
		if(mode==4)
		{
			T=first[x];
			while(T)
			{
				if(T==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans+=point[to[T]];
				T=next[T];
			}
			while(T)
			{
				if(to[T]==father[y]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				ans+=point[to[T]];
				T=next[T];
			}
			visited[x]=1;
			visited[y]=1;
		}
		x=father[x];
		y=father[y];
	}
	if(mode==1)
	{
		ans=max(ans,point[x]);
	}
	if(mode==2)
	{
		ans+=point[x];
	}
	if(mode==3)
	{
		ans=max(ans,point[father[x]]);
	}
	if(mode==4)
	{
		ans+=point[father[x]];
	}
	return ans;
}
int updatechildtree(int a,int &mode,long long &tag)
{
	register int T;
	T=first[a];
	visited[a]=1;
	while(T)
	{
		if(depth[to[T]]==depth[a]+1&&!visited[to[T]])
		{
			dfs(to[T]);
		}
		T=next[T];
	}
	if(mode==1)
	{
		point[a]=tag;
	}
	if(mode==2)
	{
		point[a]+=tag;
	}
	return 0;
}
int update(int x,int y,int &mode,long long &tag)
{
	register int T;
	if(depth[x]<depth[y])
	{
		swap(x,y);
	}
	while(depth[x]<depth[y])
	{
		if(mode==1)
		{
			point[x]=tag;
		}
		if(mode==2)
		{
			point[x]+=tag;
		}
		if(mode==3)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]=tag;
				T=next[T];
			}
			visited[x]=1;
		}
		if(mode==4)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]+=tag;
				T=next[T];
			}
			visited[x]=1;
		}
		x=father[x];
	}
	while(x!=y)
	{
		if(mode==1)
		{
			point[x]=tag;
			point[y]=tag;
		}
		if(mode==2)
		{
			point[x]+=tag;
			point[y]+=tag;
		}
		if(mode==3)
		{
			T=first[x];
			while(T)
			{
				if(to[T]==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]=tag;
				T=next[T];
			}
			T=first[y];
			while(T)
			{
				if(to[T]==father[y]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]=tag;
				T=next[T];
			}
			visited[x]=1;
			visited[y]=1;
		}
		if(mode==4)
		{
			T=first[x];
			while(T)
			{
				if(T==father[x]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]+=tag;
				T=next[T];
			}
			while(T)
			{
				if(to[T]==father[y]||visited[to[T]])
				{
					T=next[T];
					continue;
				}
				point[to[T]]+=tag;
				T=next[T];
			}
			visited[x]=1;
			visited[y]=1;
		}
		x=father[x];
		y=father[y];
	}
	if(mode==1)
	{
		point[x]=tag;
	}
	if(mode==2)
	{
		point[x]+=tag;
	}
	if(mode==3)
	{
		point[father[x]]=tag;
	}
	if(mode==4)
	{
		point[father[x]]+=tag;
	}
	return 0;
}
int main()
{
	int a,b;
	register int i,j,x,y,mode,modechange;
	register long long t,tag,ans;
	scanf("%d%d",&a,&b);
	for(i=1;i<a;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(i=1;i<=a;i++)
	{
		scanf("%d",&point[i]);
	}
	for(i=1;i<=b;i++)
	{
		scanf("%d",&mode);
		ans=0;
		if(mode==1)
		{
			modechange=2;
			scanf("%d%d%lld",&x,&y,&tag);
			update(x,y,modechange,tag);
		}
		if(mode==2)
		{
			modechange=4;
			scanf("%d%d%lld",&x,&y,&tag);
			update(x,y,modechange,tag);
		}
		if(mode==3)
		{
			modechange=2;
			scanf("%d%lld",&x,&tag);
			updatechildtree(x,modechange,tag);
		}
		if(mode==4)
		{
			modechange=1;
			scanf("%d%d%lld",&x,&y,&tag);
			update(x,y,modechange,tag);
		}
		if(mode==5)
		{
			modechange=3;
			scanf("%d%d%lld",&x,&y,&tag);
			update(x,y,modechange,tag);
		}
		if(mode==6)
		{
			modechange=1;
			scanf("%d%lld",&x,&tag);
			updatechildtree(x,modechange,tag);
		}
		if(mode==7)
		{
			modechange=1;
			scanf("%d%d",&x,&y);
			ans=search(x,y,modechange);
			printf("%lld\n",ans);
		}
		if(mode==8)
		{
			modechange=3;
			scanf("%d%d",&x,&y);
			ans=search(x,y,modechange);
			printf("%lld\n",ans);
		}
		if(mode==9)
		{
			modechange=1;
			scanf("%d",&x);
			querychildtree(x,mode,ans);
			printf("%lld\n",ans);
		}
		if(mode==10)
		{
			modechange=2;
			scanf("%d%d",&x,&y);
			ans=search(x,y,modechange);
			printf("%lld\n",ans);
		}
		if(mode==11)
		{
			modechange=4;
			scanf("%d%d",&x,&y);
			ans=search(x,y,modechange);
			printf("%lld\n",ans);
		}
		if(mode==12)
		{
			modechange=12;
			scanf("%d",&x);
			querychildtree(x,mode,ans);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
