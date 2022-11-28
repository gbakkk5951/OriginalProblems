#include<bits/stdc++.h>

using namespace std;

int n;
string s,s1;
struct Nd
{
	int son[3];
	bool sm;
	int fl;
}nd[5000005];
int tp=2;
int ans = 0;

int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	cin >> n >> s;
	nd[0].son[0] = 1;
	nd[0].son[1] = 1;
	nd[0].fl = 0;
	nd[1].fl = 0;
	for(int j = 0; j < n; j++)
	{
		cin >> s1;
		int p=1;
		for(int i = 0; i < (int)s1.size(); i++)
		{
			if(nd[p].son[s1[i]-'0'] == 0)
			{
				nd[p].son[s1[i]-'0'] = tp++;
			}
			p = nd[p].son[s1[i]-'0'];
		}
		nd[p].sm = 1;
	}
	queue<int> que;
	que.push(1);
	while(!que.empty())
	{
		if(nd[que.front()].son[0] != 0)
		{
			int p = nd[que.front()].fl;
			while(nd[p].son[0] == 0) p = nd[p].fl;
			nd[nd[que.front()].son[0]].fl = nd[p].son[0];
			que.push(nd[que.front()].son[0]);
		}
		if(nd[que.front()].son[1] != 0)
		{
			int p = nd[que.front()].fl;
			while(nd[p].son[1] == 0) p = nd[p].fl;
			nd[nd[que.front()].son[1]].fl = nd[p].son[1];
			que.push(nd[que.front()].son[1]);
		}
		que.pop();
	}
	int p = 1;
	for(int i = 0; i < (int)s.size(); i++)
	{
		while(nd[p].son[s[i]-'0'] == 0) p = nd[p].fl;
		p = nd[p].son[s[i]-'0'];
		if(nd[p].sm)
		{
			p = 1;
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
