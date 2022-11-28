#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
int n,m,cnt[4],ans,star[N],k,start,top;
int a[N*3];
char tmp1[N*3],tmp2;
int enq()
{
	ans = 0;
	stack <int> L;
	queue <int> t;
	for(int flag = 0,tmpa = 0,last = 0,i = start; i < top; i++)
	{
		if(L.empty())
		{
			if(i != start)
			{
				if(a[i] == 3)
				{
					tmpa++;
					continue;
				} 
			}
			if(tmpa) ans = max(ans,tmpa);
			if(a[i] == 2 && L.empty()) flag = 0;
			L.push(a[i]);
			continue;
		}
		while(!L.empty())
		{
			if(L.top()!=3) break;
			t.push(L.top());
			L.pop();
		}
		if(!L.empty()) last = L.top();
		else last = 0;
		while(!t.empty())
		{
			L.push(t.front());
			t.pop();
		}
		if(last == 1 && a[i] == 2)
		{
			if(!flag)
			{
				flag = 1;
				tmpa = 0;
			}
			while(!L.empty())
			{
				if(L.top() == 3)
				{
					L.pop();
					tmpa++;
				}
				else break;
			}
			L.pop(); //Ïû³ıhs
			while(!L.empty())
			{
				if(L.top() == 3)
				{
					L.pop();
					tmpa++;
				}
				else break;
			}
			tmpa += 2;
			if(i == top-1) ans = max(ans,tmpa);
		}
		else
		{
			if(tmpa) ans = max(ans,tmpa);
			L.push(a[i]);
			continue;
		}
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	start = top = N;
	scanf("%d %d",&n,&m);
	scanf("%s",tmp1+N);
	for(int i = start; i < N + n; i++)
	{
		if(tmp1[i] == 's') a[top++] = 1;
		else if(tmp1[i] == 'h') a[top++] = 2;
		else a[top++] = 3;
	}
	enq();
	char t3;
	for(int t1,t2,i = 0; i < m; i++)
	{
		scanf("%d %c",&t1,&t3);
		if(t3 == 'S') t2 = 3;
		else if(t3 == 's') t2 = 1;
		else if(t3 == 'h') t2 = 2;
		if(t1 == 1) a[--start] = t2;
		else if(t1 == 2) a[top++] = t2;
		enq();
	}
	return 0;
}
