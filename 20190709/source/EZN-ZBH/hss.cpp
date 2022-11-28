#include <fstream>
#include <set>
#include <queue>
#include <string>
using namespace std;
ifstream cin("hss.in");
ofstream cout("hss.out");
struct seg
{
	int l,r;
	const bool operator<(const seg& s)const{
		return r<s.l;
	}
};
set<seg> st;
set<seg>::iterator itr;
deque<int> lq;
deque<int> rq;
int n,m;
int al,ar;
string str;
int ans;
enum VALUE{
	E,L,R
};
VALUE trans(const char& c)
{
	switch(c)
	{
		case 'S':
			return E;
		case 's':
			return L;
		case 'h':
			return R;
	}
	return E;
}
void mins(int l,int r)
{
	seg t;
	t.l=l-1;
	t.r=r+1;
	while(!st.empty()&&(itr=st.find(t))!=st.end())
	{
		t.l=min(t.l,itr->l-1);
		t.r=max(t.r,itr->r+1);
		st.erase(itr);
	}
	++t.l;
	--t.r;
	ans=max(ans,t.r-t.l+1);
	st.insert(t);
}
void insr(VALUE v)
{
	++ar;
	if(v==E)
	{
		mins(ar,ar);
	}
	if(v==R)
	{
		if(lq.empty())
		{
			rq.push_back(ar);
		}
		else
		{
			int l=lq.back();
			lq.pop_back();
			mins(l,ar);
		}
	}
	if(v==L)
	{
		lq.push_back(ar);
	}
}
void insl(VALUE v)
{
	--al;
	if(v==E)
	{
		mins(al,al);
	}
	if(v==L)
	{
		if(rq.empty())
		{
			lq.push_front(al);
		}
		else
		{
			int r=rq.front();
			rq.pop_front();
			mins(al,r);
		}
	}
	if(v==R)
	{
		rq.push_front(al);
	}
}
int main()
{
	ios::sync_with_stdio(false); 
	cin>>n>>m;
	cin>>str;
	VALUE v;
	ar=-1;
	for(int i=0;i<n;++i)
	{
		v=trans(str[i]);
		insr(v);
	}
	cout<<ans<<endl;
	int x;
	char c;
	while(m--)
	{
		cin>>x>>c;
		if(x==1)
		{
			insl(trans(c));
		}
		else
		{
			insr(trans(c));
		}
		cout<<ans<<endl;
	}
	return 0;
}
/*
6 3
Sssshh
2 h
1 h
1 s


*/
