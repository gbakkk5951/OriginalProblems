#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
#define R register
struct ccf
{
	char s;
	int len;
}iakioi[2000010];
ccf *fff=iakioi+1000005;
int n,m,blo,tot,fufff=1,zhizhen;
char ss[1000005];
int ans=-999999999;
int zuoans(int now)
{
	if(now<fufff)return 0;
	zhizhen=now-1;
	if(fff[now].s=='S')
	{
		return fff[now].len+zuoans(now-1);
	}
	if(fff[now].s=='s')return 0;
	if(fff[now].s=='h')
	{
		if(fff[now-1].s=='s')
		{
			if(fff[now-1].len==fff[now].len)return fff[now].len*2+zuoans(now-2);
			else if(fff[now-1].len>fff[now].len)return fff[now].len*2;
			else if(fff[now-1].len<fff[now].len)
			{
				zhizhen=now-1;
				return 0;
			}
		}
		else if(fff[now-1].s=='S')
		{
			if(fff[now-2].s=='s')
			{
				if(fff[now-2].len==fff[now].len)return fff[now-1].len+fff[now].len*2+zuoans(now-2);
				else if(fff[now-2].len>fff[now].len)return fff[now-1].len+fff[now].len*2;
				else if(fff[now-2].len<fff[now].len)
				{
					zhizhen=now-2;
					return fff[now-1].len;
				}
			}
		}
	}
	return 0;
}
int youans(int now)
{
	if(now>tot)return 0;
	if(fff[now].s=='S')
	{
		return fff[now].len+youans(now+1);
	}
	if(fff[now].s=='h')return 0;
	if(fff[now].s=='s')
	{
		if(fff[now+1].s=='h')
		{
			if(fff[now+1].len==fff[now].len)return fff[now].len*2+youans(now+2);
			else if(fff[now+1].len>fff[now].len)return fff[now].len*2;
			else if(fff[now+1].len<fff[now].len)return 0;
		}
		else if(fff[now+1].s=='S')
		{
			if(fff[now+2].s=='h')
			{
				if(fff[now+2].len==fff[now].len)return fff[now+1].len+fff[now].len*2+youans(now+2);
				else if(fff[now+2].len>fff[now].len)return fff[now+1].len+fff[now].len*2;
				else if(fff[now+2].len<fff[now].len)return fff[now+1].len;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(R int i=1;i<=n;i++)cin>>ss[i];
	ss[n+1]='&';
	for(R int i=2;i<=n+1;i++)
	{
		if(ss[i]!=ss[i-1])
		{
			tot++;
			fff[tot].s=ss[i-1];
			fff[tot].len=blo+1;
			blo=0;
		}
		else blo++;
	}
	/*for(R int i=fufff;i<=tot;i++)
	{
		cout<<fff[i].s<<" "<<fff[i].len<<endl;
	}*/
	zhizhen=tot;
	while(zhizhen>0)ans=max(ans,zuoans(zhizhen));
	printf("%d\n",ans);
	int x;char c;
	for(R int i=1;i<=m;i++)
	{
		scanf("%d",&x);cin>>c;
		if(x==2)
		{
			if(fff[tot].s==c)fff[tot].len++;
			else 
			{
				tot++;
				fff[tot].s=c;
				fff[tot].len=1;
			}
			ans=max(zuoans(tot),ans);
			printf("%d\n",ans);
		}
		else
		{
			if(fff[fufff].s==c)fff[fufff].len++;
			else
			{
				fufff--;
				fff[fufff].s=c;
				fff[fufff].len=1;
			}
			ans=max(youans(fufff),ans);
			printf("%d\n",ans);
		}
	}
}
