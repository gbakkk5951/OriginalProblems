#include<bits/stdc++.h>

using namespace std;

int n,m;
char c[3050000];
int p=1000005,q=1000004;
int mxs=0;
int lmx[3050000];
int rmx[3050000];

int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	cin >> n >> m;
	stack<int> stk;
	for(int i = 0; i < n; i++)
	{
		cin >> c[++q];
		if(c[q] == 's')
		{
			stk.push(q);
		}
		else if(c[q] == 'h')
		{
			if(!stk.empty())
			{
				lmx[q] = stk.top();
				stk.pop();
				if(lmx[lmx[q]-1] != 0)
				{
					lmx[q] = lmx[lmx[q]-1];
				}
				rmx[lmx[q]] = q;
				mxs = max(mxs,q-lmx[q]+1);
			}
		}
		else
		{
			if(lmx[q-1] != 0)
			{
				lmx[q] = lmx[q-1];
				rmx[lmx[q]] = q;
			}
			else
			{
				lmx[q] = q;
				rmx[q] = q;
			}
		}
	}
	cout << mxs << endl;
	for(int i = 0; i < m; i++)
	{
		int cse;
		cin >> cse;
		if(cse == 1)
		{
			cin >> c[--p];
			if(c[p] == 's')
			{
				if(rmx[p+1] != 0)
				{
					if(c[rmx[p+1]+1] == 'h')
					{
						rmx[p] = rmx[p+1]+1;
						while(rmx[rmx[p]+1] != 0) rmx[p] = rmx[rmx[p]+1];
						lmx[rmx[p]] = p;
						mxs = max(mxs,rmx[p]-p+1);
					}
				}
				else
				{
					if(c[p+1] == 'h')
					{
						rmx[p] = p+1;
						while(rmx[rmx[p]+1] != 0) rmx[p] = rmx[rmx[p]+1];
						lmx[rmx[p]] = p;
						mxs = max(mxs,rmx[p]-p+1);
					}
				}
			}
			else if(c[p] == 'h')
			{
				;
			}
			else
			{
				if(rmx[p+1] != 0)
				{
					rmx[p] = rmx[p+1];
					lmx[rmx[p]] = p;
					mxs = max(mxs,rmx[p]-p+1);
				}
				else
				{
					rmx[p] = p;
					lmx[p] = p;
					mxs = max(mxs,1);
				}
			}
		}
		else
		{
			cin >> c[++q];
			if(c[q] == 's')
			{
				;
			}
			else if(c[q] == 'h')
			{
				if(lmx[q-1] != 0)
				{
					if(c[lmx[q-1]-1] == 's')
					{
						lmx[q] = lmx[q-1]-1;
						while(lmx[lmx[q]-1] != 0) lmx[q] = lmx[lmx[q]-1];
						rmx[lmx[q]] = q;
						mxs = max(mxs,q-lmx[q]+1);
					}
				}
				else
				{
					if(c[q-1] == 's')
					{
						lmx[q] = q-1;
						while(lmx[lmx[q]-1] != 0) lmx[q] = lmx[lmx[q]-1];
						rmx[lmx[q]] = q;
						mxs = max(mxs,q-lmx[q]+1);
					}
				}
			}
			else
			{
				if(lmx[q+1] != 0)
				{
					lmx[q] = lmx[q-1];
					rmx[lmx[q]] = q;
					mxs = max(mxs,q-lmx[q]+1);
				}
				else
				{
					lmx[q] = q;
					rmx[q] = q;
					mxs = max(mxs,1);
				}
			}
		}
		cout << mxs << endl;
	}
	return 0;
}
