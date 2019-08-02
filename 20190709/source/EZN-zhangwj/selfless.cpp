#include<cstdio>
#include<algorithm>
struct edges
{
	int from,to,lenth;
}edge[200050];
bool operator <(const edges &a,const edges &b)
{
	return a.lenth<b.lenth;
}
int first[100050],next[200050],to[200050],lenth[200050],tot=0,pre[100050][22],premax[100050][22],presecmax[100050][22],father[100050],size[100050],depth[100050],logg[200050];
bool visited[200050];
int lowbit(int a)
{
	return a&-a;
}
int swap(int &a,int &b)
{
	a^=b;
	b^=a;
	a^=b;
	return 0;
}
int min(int a,int b)
{
	if(a<b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int max(int a,int b)
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
int add(int x,int y,int z)
{
	next[++tot]=first[x];
	to[tot]=y;
	lenth[tot]=z;
	first[x]=tot;
	return 0;
}
int find(int a)
{
	if(father[a]==a)
	{
		return a;
	}	
	else
	{
		father[a]=find(father[a]);
		return father[a];
	}
}
int merge(int a,int b)
{
	int x=find(a),y=find(b);
	if(size[x]<size[y])
	{
		swap(x,y);
	}
	father[y]=x;
	size[x]+=size[y];
	return 0;
}
int dfs(int a)
{
	register int T,k=0,maxA,maxB,secmaxA,secmaxB;
	T=first[a];
	while(pre[a][k])
	{
		k++;
		pre[a][k]=pre[pre[a][k-1]][k-1];
		maxA=premax[a][k-1];
		maxB=premax[pre[a][k-1]][k-1];
		secmaxA=presecmax[a][k-1];
		secmaxB=presecmax[pre[a][k-1]][k-1];
		if(maxA==maxB)
		{
			premax[a][k]=maxA;
			presecmax[a][k]=max(secmaxA,secmaxB);
		}
		else
		{
			if(maxA>maxB)
			{
				premax[a][k]=maxA;
				presecmax[a][k]=max(maxB,secmaxA);
			}
			if(maxA<maxB)
			{
				premax[a][k]=maxB;
				presecmax[a][k]=max(maxA,secmaxB);
			}
		}
	}
	while(T)
	{
		if(pre[a][0]==to[T])
		{
			T=next[T];
			continue;
		}
		pre[to[T]][0]=a;
		premax[to[T]][0]=lenth[T];
		depth[to[T]]=depth[a]+1;
		dfs(to[T]);
		T=next[T];
	}
	return 0;
}
int finddelta(int x,int y,int edgelenth)
{
	register int k,difference,t,maxans=0,secmaxans=0;
//	printf("X=%d Y=%d\n",x,y);
	if(depth[x]<depth[y])
	{
		swap(x,y);
	}
	difference=depth[x]-depth[y];
	while(difference)
	{
		t=lowbit(difference);
		k=logg[t]-1;
		if(maxans<premax[x][k])
		{
			secmaxans=max(maxans,presecmax[x][k]);
			maxans=premax[x][k];
		}
		else
		{
			if(secmaxans<premax[x][k])
			{
				secmaxans=premax[x][k];
			}
		}
//		printf("POS 1 MAXANS=%d\n",maxans);
		x=pre[x][k];
		difference^=t;
	}
	k=20;
	while(x!=y)
	{
		while(pre[x][k]==pre[y][k]&&k)
		{
			k--;
		}
		if(maxans>premax[x][k]&&maxans>premax[y][k])
		{
			secmaxans=max(secmaxans,max(premax[x][k],premax[y][k]));
		}
		else
		{
			if(premax[x][k]==premax[y][k])
			{
//				printf("IN MAX EQUAL\n");
				secmaxans=max(maxans,max(presecmax[x][k],presecmax[y][k]));
				maxans=premax[x][k];
			}
			else
			{
				if(premax[y][k]<premax[x][k])
				{
//					printf("X>Y\n");
					secmaxans=max(maxans,max(presecmax[x][k],premax[y][k]));
					maxans=premax[x][k];
				}
				if(premax[x][k]<premax[y][k])
				{
//					printf("Y>X\n");
					secmaxans=max(maxans,max(presecmax[y][k],premax[x][k]));
					maxans=premax[y][k];
				}
			}
		}
//		printf("POS 2 MAXANS=%d\n",maxans);
		x=pre[x][k];
		y=pre[y][k];
	}
//	printf("SECMAXANS=%d MAXANS=%d\n",secmaxans,maxans);
	if(edgelenth==maxans)
	{
		return edgelenth-secmaxans;
	}
	else
	{
		return edgelenth-maxans;
	}
}
int main()
{
	int a,b;
	int ans=1000000000,totallenth=0;
	register int i,j,x,y,z,t=1,logT=1,temp;
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	scanf("%d%d",&a,&b);
	while(logT<=a)
	{
		logg[logT]=t;
		logT<<=1;
		t++;
	}
	for(i=1;i<=a;i++)
	{
		father[i]=i;
		size[i]=1;
	}
	for(i=1;i<=b;i++)
	{
		scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].lenth);
	}
	std::sort(edge+1,edge+b+1);
	for(i=1;i<=b;i++)
	{
		if(find(edge[i].from)!=find(edge[i].to))
		{
			visited[i]=1;
			merge(edge[i].from,edge[i].to);
			add(edge[i].from,edge[i].to,edge[i].lenth);
			add(edge[i].to,edge[i].from,edge[i].lenth);
			totallenth+=edge[i].lenth;
		}
	}
//	printf("TOTALLENTH=%d\n",totallenth);
	depth[1]=1;
	dfs(1);
/*	for(i=1;i<=a;i++)
	{
		for(j=0;j<=2;j++)
		{
			printf("PRE[%d][%d]=%d PREMAX[%d][%d]=%d PRESECMAX[%d][%d]=%d\n",i,j,pre[i][j],i,j,premax[i][j],i,j,presecmax[i][j]);
		}
	}*/
	for(i=1;i<=b;i++)
	{
		if(!visited[i])
		{
			temp=finddelta(edge[i].to,edge[i].from,edge[i].lenth);
			if(temp!=edge[i].lenth)
			{
				ans=min(ans,totallenth+temp);
			}
		}
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
3 5
1 2 3 
1 2 5
2 3 4
2 3 9
1 3 2 
5 10
1 2 3
2 3 4
3 4 5
4 5 6
1 5 10
1 3 6
1 4 7
1 2 8
3 4 7
2 5 9
*/
