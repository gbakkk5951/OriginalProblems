#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define re register
using namespace std;
const int N=1e5+7;
const int M=2e5+7;
const int INF=1<<30;
int n,m,cnt,col,delta=INF;
int anc[N];
int fa[N],son[N],top[N],dep[N],siz[N],dfn[N],val[N],a[N],head[N];
long long sum;
struct Edge
{
	int u,v,w;
	bool operator<(const Edge &o)const 
	{
		return w<o.w;
	}
}E[M];
queue<Edge>q;
struct edge
{
	int next,to,dis;
}e[M];
inline void add(int u,int v,int w)
{
	e[++cnt].next=head[u];
	head[u]=cnt;
	e[cnt].to=v;
	e[cnt].dis=w;
}
inline int find(int x)
{
	return x==anc[x]?x:anc[x]=find(anc[x]);	
}
inline void kruskal()
{
	sort(E+1,E+m+1);
	for(re int i=1;i<=m;i++)
	{
		if(find(E[i].u)!=find(E[i].v))
		{
			sum+=E[i].w;
			add(E[i].u,E[i].v,E[i].w);
			add(E[i].v,E[i].u,E[i].w);
			anc[find(E[i].u)]=find(E[i].v);
		}
		else q.push(E[i]);
	}
}
inline void dfs1(int x,int father,int deep)
{
	fa[x]=father;dep[x]=deep;siz[x]=1;
	re int maxson=-1;
	for(re int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y==father)continue;
		val[y]=e[i].dis;
		dfs1(y,x,deep+1);
		siz[x]+=siz[y];
		if(siz[y]>maxson)
		{
			maxson=siz[y];
			son[x]=y;
		}
	}
}
inline void dfs2(int x,int topp)
{
	top[x]=topp;
	dfn[x]=++col;
	a[col]=val[x];
	if(!son[x])return;
	dfs2(son[x],topp);
	for(re int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
pair<int,int >Tree[N<<2];
inline void push_up(int x)
{
	if(Tree[ls(x)].first>Tree[rs(x)].first)
	{
		Tree[x].first=Tree[ls(x)].first;
		Tree[x].second=max(Tree[ls(x)].second,Tree[rs(x)].first);
	}
	else if(Tree[ls(x)].first<Tree[rs(x)].first)
	{
		Tree[x].first=Tree[rs(x)].first;
		Tree[x].second=max(Tree[rs(x)].second,Tree[ls(x)].first);
	}
	else 
	{
		Tree[x].first=Tree[ls(x)].first;
		Tree[x].second=max(Tree[ls(x)].second,Tree[rs(x)].second);
	}
}
inline void build(int x,int l,int r)
{
	Tree[x].first=Tree[x].second=-INF;
	if(l==r)
	{
		Tree[x].first=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	push_up(x);
}
inline pair<int,int> basic_query(int x,int ql,int qr,int l,int r)
{
	if(l==ql&&qr==r)return Tree[x];
	int mid=(l+r)>>1;
	if(qr<=mid)return basic_query(ls(x),ql,qr,l,mid);
	else if(ql>mid)return basic_query(rs(x),ql,qr,mid+1,r);
	else
	{
		pair<int,int>tmp;
		pair<int,int> lv=basic_query(ls(x),ql,mid,l,mid);
		pair<int,int> rv=basic_query(rs(x),mid+1,qr,mid+1,r);
		if(lv.first>rv.first)
		{
			tmp.first=lv.first;
			tmp.second=max(lv.second,rv.first);
		}
		else if(lv.first<rv.first)
		{
			tmp.first=rv.first;
			tmp.second=max(rv.second,lv.first);
		}
		else 
		{
			tmp.first=lv.first;
			tmp.second=max(lv.second,rv.second);
		}
		return tmp;
	}
}
inline pair<int,int> query(int x,int y)
{
	pair<int,int >res(-INF,-INF);
	pair<int,int >tmp;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tmp=basic_query(1,dfn[top[x]],dfn[x],1,col);
		if(tmp.first>res.first)
		{
			res.second=max(tmp.second,res.first);
			res.first=tmp.first;
		}
		else if(tmp.first<res.first)
		{
			res.second=max(res.second,tmp.first);
		}
		else 
		{
			res.second=max(tmp.second,res.second);
		}
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	//cout<<dfn[x]<<" "<<dfn[y]<<endl;
	if(dfn[x]<dfn[y])tmp=basic_query(1,dfn[x]+1,dfn[y],1,col);
	//cout<<tmp.first<<endl;
	if(tmp.first>res.first)
	{
		res.second=max(tmp.second,res.first);
		res.first=tmp.first;
	}
	else if(tmp.first<res.first)
	{
		res.second=max(res.second,tmp.first);
	}

	else 
	{
		res.second=max(tmp.second,res.second);
	}
	return res;
}
inline void rebuild()
{
	while(!q.empty())
	{
		if(q.front().u>q.front().v)swap(q.front().u,q.front().v);
		pair<int,int>tmp=query(q.front().u,q.front().v);
		delta=min(delta,tmp.first==q.front().w?q.front().w-tmp.second:q.front().w-tmp.first);
		q.pop();
	}
}
inline int read()
{
	re char ch=getchar();re int f=1,x=0;
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	n=read();m=read();
	for(re int i=1;i<=n;i++)anc[i]=i;
	for(re int i=1;i<=m;i++)
	{
		E[i].u=read();
		E[i].v=read();
		E[i].w=read();
	}
	kruskal();
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,col);
	//for(re int i=1;i<=(col*4);i++)cout<<"debug "<<i<<" "<<Tree[i].first<<endl;
	/*	for(register int i=1;i<=col;i++)
		for(register int j=1;j<=col;j++)
			if(i<=j)
				cout<<basic_query(1,i,j,1,col).second<<endl; */
	//cout<<query(1,2).first<<endl;
	//for(register int i=1;i<=n;i++)
	//	for(register int j=1;j<=n;j++)
	//		if(i<j)
	//			cout<<query(i,j).first<<endl; 	
	rebuild();
	cout<<sum+delta<<endl;
	return 0;
}
/*
3 5
1 2 3 
1 2 5
2 3 4
2 3 9
1 3 3
*/
