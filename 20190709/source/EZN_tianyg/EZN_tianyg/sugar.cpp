#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<set>
#include<cmath>
#define re register
using namespace std;
const int base1=31;
const int base2=137;
const int p1=1e9+7;
const int p2=19260817;
const int N=5e6+7;
set<pair<unsigned int,unsigned int> >bax;
int ans;
string s,ss;
inline void hash(string sss)
{
	unsigned int res1=0,res2=0;
	for(re int i=0;i<sss.length();i++)
	{
		res1=(res1*base1%p1+sss[i]-'0')%p1;
		res2=(res2*base2%p2+sss[i]-'0')%p2;
	}
	bax.insert(pair<unsigned int,unsigned int>(res1,res2));
}
pair<unsigned int,unsigned int>sum[N];
pair<unsigned int,unsigned int>flo[N];
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	int n;
	cin>>n;
	cin>>s;
	for(re int i=0;i<s.length();i++)
	{
		sum[i+1].first=(sum[i].first*base1%p1+s[i]-'0')%p1;
		sum[i+1].second=(sum[i].second*base2%p2+s[i]-'0')%p2;
	}
	flo[0].first=flo[0].second=1;
	for(re int i=0;i<s.length();i++)
	{
		flo[i+1].first=flo[i].first*base1%p1;
		flo[i+1].second=flo[i].second*base2%p2;
	}
	for(re int i=1;i<=n;i++)cin>>ss,hash(ss);
	
	for(re int l=0;l<s.length();l++)
	{
		for(re int r=0;r<s.length();r++)
		{
			if(r<l)continue;
			unsigned int val1=abs(sum[r].first-sum[l-1].first)/flo[l-1].first;
			unsigned int val2=abs(sum[r].second-sum[l-1].second)/flo[l-1].second;
		//	cout<<val1<<endl;
			pair<unsigned int,unsigned int> val=*bax.lower_bound(pair<unsigned int,unsigned int>(val1,val2));
			if(val==pair<unsigned int,unsigned int>(val1,val2))ans++;
		}
	}
	cout<<ans<<endl;
}
/*
5
010101010111
010
01
11
1000
1110
*/
