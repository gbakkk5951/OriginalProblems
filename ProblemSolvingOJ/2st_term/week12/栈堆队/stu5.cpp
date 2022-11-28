#include <bits/stdc++.h>
using namespace std;
int n, m, res, ans, st1, st2, tru[4000005] ,minn;
char a[4000005];
int main()
{
//	freopen("data0.in","r",stdin);
	scanf("%d%d", &n, &m);
	scanf("%s", &a);
	res = n;
	int qnum = 0, top = 0;
	for (int i = 1; i <= m; i++)
	{
		int now = a[i - 1] - '0';
		if (now == 0)
		{
			qnum++;
			tru[++top] = now;
		}
		
		else
		{
			if (qnum)
			{
				qnum--;
				tru[++top] = now;
			}
		}
	}

	if (qnum)
	{
		for (int i = top; i >= 1 && qnum; i--)
		{
			if (!tru[i])
			{
				tru[i] = -1;
				qnum--;
			}

			//			cout<<"f"<<tru[i]<<endl;
		}
	}
	for (int i = 1; i <= top; i++)
	{
		if (tru[i] == 0)
		{
			ans++;
			if (res)
			{
				res--;
			}
			else
			{
				if (st2)
				{
					st2++;
				}
				else
				{
					st2 = 2;
				}
			}
		}
		else if (tru[i] == 1)
		{
			ans++;
			if (st1)
			{
				st1--;
				if (!st1)
					res++;
			}
			else if (st2)
			{
				if(res == n-1){
					st1 += st2 - 1;
					ans += (st2 - 1) * 2;
					st2 = 0;
					minn = 0;
				}
				else if(minn){
					st1 = st2;
					ans += (st2 - 1) * 2;
					st2 = 0;
					minn = 0;
					res++;
				}
				else res++;
			}
			else res++;
			if(res == n-1 && st2){
				minn = 1;
			}
		}
//		cout<<i<<" "<<tru[i]<<" "<<ans<<" "<<st1<<" "<<st2<<" "<<res<<" "<<minn<<endl;
	}
	cout << ans;
}
