#include <fstream>
#include <algorithm>
using namespace std;
ifstream cin("selfless.in");
ofstream cout("selfless.out");
const int kmaxn=100000+5;
const int kmaxm=200000+5;
const int kmaxlg=25;
int n,m;
int ssa[10];
void ss()
{
	int md=5;
	for(int i=0;i<4;++i)
	{
		ssa[md=5]=0;
		for(int j=i;j<4;++j)
		{
			if(ssa[md]<ssa[j])
				md=j;
		}
		swap(ssa[md],ssa[i]);
	}
	int f=0;
	for(f=1;ssa[f]==ssa[0];++f);
	ssa[1]=ssa[f];
}
int lg[kmaxn];
void init()
{
	for(int i=1;i<=n;++i)
	{
		lg[i]=lg[i-1]+(i==(1<<lg[i-1]));
	}
}
struct edge
{
	int d;
	int w;
	edge* nxt;
};
edge mpool[kmaxm<<1];
int mpt;
edge* H[kmaxn];
void add_edge(int s,int d,int w)
{
	mpool[mpt].nxt=H[s];
	H[s]=&mpool[mpt++];
	H[s]->d=d;
	H[s]->w=w;
}
int v1[kmaxn][kmaxlg];
int v2[kmaxn][kmaxlg];
int fa[kmaxn][kmaxlg];
int dep[kmaxn];
void dfs(int now,int f,int v)
{
//	cout<<"dfs	"<<now<<endl;
	fa[now][0]=f;
	v1[now][0]=v;
	dep[now]=dep[f]+1;
	for(int i=1;i<lg[dep[now]];++i)
	{
		fa[now][i]=fa[f=fa[now][i-1]][i-1];
		ssa[0]=v1[now][i-1];
		ssa[1]=v2[now][i-1];
		ssa[2]=v1[f][i-1];
		ssa[3]=v2[f][i-1];
		ss();
		v1[now][i]=ssa[0];
		v2[now][i]=ssa[1];
	}
	edge* t=H[now];
	f=fa[now][0];
	while(t)
	{
		if(t->d!=f)
		{
			dfs(t->d,now,t->w);
		}
		t=t->nxt;
	}
}
void merge(int x,int i)
{
	ssa[2]=v1[x][i];
	ssa[3]=v2[x][i];
	ss();
}
int query(int x,int y)
{
	ssa[0]=ssa[1]=0;
	if(dep[x]<dep[y])swap(x,y);
	for(int i=lg[dep[x]-dep[y]]-1;i>=0;--i)
	{
		if(dep[fa[x][i]]<=dep[y])
		{
			merge(x,i);
		}
	}
	if(x==y)return x;
	for(int i=lg[dep[x]]-1;i>=0;--i)
	{
		if(fa[x][i]!=fa[y][i])
		{
			merge(x,i);
			merge(y,i);
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	ssa[2]=v1[x][0];
	ssa[3]=v1[y][0];
	ss();
	return fa[x][0];
}
struct unit{
	int a,b,c;
	const bool operator<(const unit& u)const{
		return c<u.c;
	}
};
unit lis[kmaxm];
int ans;
int sum;
int dsu[kmaxn];
int anc(int p)
{
	if(dsu[p]==p)return p;
	return dsu[p]=anc(dsu[p]);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	init();
	for(int i=0;i<m;++i)
	{
		cin>>lis[i].a>>lis[i].b>>lis[i].c;
		ans+=lis[i].c;
	}
	for(int i=1;i<=n;++i)
		dsu[i]=i;
	int a,b,c; 
	sort(lis,lis+m);
	for(int i=0,cnt=1;cnt<n&&i<m;++i)
	{
		a=lis[i].a;
		b=lis[i].b;
		c=lis[i].c;
		if(anc(a)==anc(b))continue;
//		cout<<"link	"<<a<<"	"<<b<<endl;
		add_edge(a,b,c);
		add_edge(b,a,c);
		++cnt;
		dsu[anc(a)]=anc(b);
		lis[i].c=0;
		sum+=c;
	}
	dfs(1,0,0);
//	cout<<"T"<<endl;
	for(int i=0;i<m;++i)
	{
		if(!lis[i].c)continue;
//		cout<<"try	"<<lis[i].a<<"	"<<lis[i].b<<endl;
//		cout<<query(lis[i].a,lis[i].b)<<endl;
		query(lis[i].a,lis[i].b);
		if(ssa[0]&&ssa[0]!=lis[i].c)
			ans=min(ans,sum-ssa[0]+lis[i].c);
		else if(ssa[1])
			ans=min(ans,sum-ssa[1]+lis[i].c);
//		cout<<"ans	"<<ans<<endl;
	}
	cout<<ans<<endl;
	return 0;
}/*
4 7
2 4 9
3 4 6
1 2 3
1 2 100
2 3 8
2 3 9
1 3 3
*/
