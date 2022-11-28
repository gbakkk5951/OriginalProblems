#include <fstream>
#include <string>
#include <queue>
using namespace std;
ifstream cin("sugar.in");
ofstream cout("sugar.out");
const int kmaxn=5000000*2+5;
const int kmaxl=2;
struct node
{
	int mind;
	int ebit;
	int s[2+1];
	int fa,f;
};
node T[kmaxn];
int rt=1;
int mpt=1;
int alloc_node()
{
	return ++mpt;
}
void insert(const string &str)
{
	int len=str.size();
	int i=0;
	int p=rt;
	int v=0;
//	int t=0;
	while(i<len)
	{
		v=str[i]-'0';
		if(!T[p].s[v])
		{
			T[p].s[v]=alloc_node();
			T[T[p].s[v]].fa=p;
		}
		p=T[p].s[v];
		T[p].mind=++i;
	}
	T[p].ebit=1;
}
void init()
{
	queue<int> q;
	queue<int> q2;
	q.push(rt);
	q2.push(kmaxl);
	int p,v,t; 
	while(!q.empty())
	{
		p=q.front();
		v=q2.front();
		q.pop();q2.pop();
		t=T[p].fa;
		t=T[t].f;
		while((!T[t].s[v])&&t!=T[t].f)
		{
			t=T[t].f;
		}
		if(T[t].s[v]&&T[p].fa!=rt)T[p].f=T[t].s[v];
		else T[p].f=rt;
		if(T[T[p].f].ebit)
		{
			T[p].ebit=1;
			T[p].mind=T[T[p].f].mind;
		}
		for(int i=0;i<kmaxl;++i)
		{
			if(T[p].s[i])
			{
				q.push(T[p].s[i]);
				q2.push(i);
			}
		}
	}
}
void output(int p)
{
	if(!p)return;
	output(T[p].s[0]);
	cout<<p<<"	"<<T[p].fa<<"	"<<T[p].f<<"	"<<T[p].ebit<<"	"<<T[p].mind<<"	"<<T[p].s[0]<<"	"<<T[p].s[1]<<endl;
	output(T[p].s[1]);
}
int dp[kmaxn];
int main()
{
	ios::sync_with_stdio(false);
	T[1].f=1;
	T[1].fa=1;
	T[1].mind=0;
	int n,v;
	int p=rt;
	string str,str2;
	cin>>n;
	cin>>str;
	for(int i=1;i<=n;++i)
	{
		cin>>str2;
		insert(str2);
	}
	init();
//	output(rt);
	for(int i=1,j=str.size();i<=j;++i)
	{
		v=str[i-1]-'0';
		dp[i]=dp[i-1];
		while((!T[p].s[v])&&T[p].f!=p)
		{
			p=T[p].f;
		}
		p=T[p].s[v];
//		cout<<"p	"<<p<<endl;
		if(T[p].ebit)
		{
//			cout<<"ebit"<<endl;
			dp[i]=max(dp[i],dp[i-T[p].mind]+1);
		}
	}
	cout<<dp[str.size()]<<endl;
	return 0;
} 

/*
5
010101010111
010
01
11
1000
1110


3
010101010101010110
11
01
10

*/
