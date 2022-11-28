#include<bits/stdc++.h>

using namespace std;

int n,m;
int fa[100005];
struct bian
{
	int x,y;
	int w;
	bool f;
}bi[200005];
int lts,msm=1000000;

bool cmp1(bian a, bian b)
{
	return a.w < b.w;
}

bool cmp2(bian a, bian b)
{
	if(a.f != b.f)
		return a.f;
	return 0;
}

int getf(int p)
{
	int pp=fa[p],tp;
	while(fa[pp] != pp) pp = fa[pp];
	while(fa[p] != p) tp=p, p=fa[p], fa[tp]=pp;
	return pp;
}

struct tnd
{
	int to;
	int w;
}tp;
vector<tnd> vt[100005];

struct Nd
{
	int dep;
	int to[20];
	int mx[20];
	int _2x[20];
}nd[100005];

void dfs(int p)
{
	for(int i = 0; i < (int)vt[p].size(); i++)
	{
		int son = vt[p][i].to;
		if(fa[son])
		{
			fa[son] = 0;
			nd[son].dep = nd[p].dep+1;
			nd[son].to[0] = p;
			nd[son].mx[0] = vt[p][i].w;
			for(int j = 1; j < 20; j++)
			{
				nd[son].to[j] = nd[nd[son].to[j-1]].to[j-1];
				nd[son].mx[j] = max(nd[son].mx[j-1],nd[nd[son].to[j-1]].mx[j-1]);
				if(nd[son].mx[j-1] < nd[son].mx[j])
					nd[son]._2x[j] = max(nd[son]._2x[j],nd[son].mx[j-1]);
				if(nd[nd[son].to[j-1]].mx[j-1] < nd[son].mx[j])
					nd[son]._2x[j] = max(nd[son]._2x[j],nd[nd[son].to[j-1]].mx[j-1]);
				nd[son]._2x[j] = max(nd[son]._2x[j],max(nd[son]._2x[j-1],nd[nd[son].to[j-1]]._2x[j-1]));
			}
			dfs(son);
		}
	}
}

int main()
{
	freopen("selfless.in","r",stdin);
	freopen("selfless.out","w",stdout);
	register int i;
	cin >> n >> m;
	for(i = 0; i < m; i++)
	{
		cin >> bi[i].x >> bi[i].y >> bi[i].w;
	}
	sort(bi,bi+m,cmp1);
	for(i = 1; i <= n; i++) fa[i] = i;
	for(i = 0; i < m; i++)
	{
		if(getf(bi[i].x) != getf(bi[i].y))
		{
			lts += bi[i].w;
			fa[getf(bi[i].x)] = getf(bi[i].y);
			bi[i].f= 1;
		}
	}
	sort(bi,bi+m,cmp2);
	for(i = 0; bi[i].f; i++)
	{
		tp.to = bi[i].x;
		tp.w = bi[i].w;
		vt[bi[i].y].push_back(tp);
		tp.to = bi[i].y;
		vt[bi[i].x].push_back(tp);
	}
	nd[1].dep=0;
	for(i = 0; i < 20; i++)
	{
		nd[1].to[i] = -1;
		nd[1].mx[i] = 0;
		nd[1]._2x[i] = 0;
	}
	dfs(1);
	for(i = m-1; !bi[i].f; i--)
	{
		int tas=0;
		if(nd[bi[i].x].dep < nd[bi[i].y].dep)
		{
			swap(bi[i].x,bi[i].y);
		}
		for(int j=19; j >= 0; j--)
		{
			if(nd[bi[i].x].dep+(1<<j) < nd[bi[i].y].dep)
			{
				if(nd[bi[i].x].mx[j] != bi[i].w)
				{
					tas = max(tas,nd[bi[i].x].mx[j]);
				}
				else
				{
					tas = max(tas,nd[bi[i].x]._2x[j]);
				}
				bi[i].x = nd[bi[i].x].to[j];
			}
		}
		for(int j=19; j>=0; j--)
		{
			if(nd[bi[i].x].to[j] != nd[bi[i].y].to[j])
			{
				if(nd[bi[i].x].mx[j] != bi[i].w)
				{
					tas = max(tas,nd[bi[i].x].mx[j]);
				}
				else
				{
					tas = max(tas,nd[bi[i].x]._2x[j]);
				}
				bi[i].x = nd[bi[i].x].to[j];
				if(nd[bi[i].y].mx[j] != bi[i].w)
				{
					tas = max(tas,nd[bi[i].y].mx[j]);
				}
				else
				{
					tas = max(tas,nd[bi[i].y]._2x[j]);
				}
				bi[i].y = nd[bi[i].y].to[j];
			}
		}
		msm = min(msm,bi[i].w-tas);
	}
	cout << lts+msm << endl;
	return 0;
}
