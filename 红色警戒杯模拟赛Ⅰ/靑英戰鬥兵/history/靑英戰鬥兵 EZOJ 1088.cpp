#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<string>
#include<cmath>
#include<cstdlib>
#include<iostream>
#define int long long
using namespace std;
int kind,num,hp,attack,hpadd;
int ecnt[5010],dp[1100010][2],harm=0,totatt=0;
struct enemy
{
	string s;int ehp,eatt;
	bool operator <(const enemy &b)const
	{
		return s<b.s;
	}
}ek[5010],tmp;
struct harmful
{
	int time,hurt,attsum;
}h[25];
int bene[50010],btot=0,btime=0,bhptot=0;
signed main()
{
	int i,j,k,len,s,ans=-1;string str;
	scanf("%lld%lld%lld%lld%lld",&kind,&num,&hp,&attack,&hpadd);
	for(i=0;i<kind;i++)
	{
		cin>>ek[i].s;
		scanf("%lld%lld",&ek[i].ehp,&ek[i].eatt);
	}
	sort(ek,ek+kind);
	for(i=0;i<num;i++)
	{
		cin>>tmp.s;
		ecnt[lower_bound(ek,ek+kind,tmp)-ek]++;
	}
//	printf("ecnt=");
//	for(i=0;i<kind;i++)
//	{
//		printf("%lld ",ecnt[i]);
//	}
//	printf("\n");
	for(i=0;i<kind;i++)
	{
		if(ek[i].eatt>0)
		{
			h[harm].time=ceil(ek[i].ehp*1.0/attack);
			h[harm].hurt=((1+ecnt[i])*ecnt[i]*h[harm].time/2-ecnt[i])*ek[i].eatt;
			h[harm].time*=ecnt[i];
			h[harm++].attsum=ecnt[i]*ek[i].eatt;
		}
		totatt+=ek[i].eatt*ecnt[i];
	}
//	for(i=0;i<harm;i++)
//	{
//		printf("h[%lld]: time=%lld hurt=%lld attsum=%lld\n",i,h[i].time,h[i].hurt,h[i].attsum);
//	}
//	printf("totatt=%lld\n",totatt);
	for(k=0;k<harm;k++)
	{
		memset(dp,0,sizeof(dp));
		dp[1<<k][0]=hp;dp[1<<k][1]=totatt-h[k].attsum;
		for(s=(1<<k)+1;s<(1<<harm);s++)
		{
			if(!(s&(1<<k)))continue;
			dp[s][0]=0;
			for(i=0;i<harm;i++)
			{
				int lefthp;
				if(!(s&(1<<i))||i==k)continue;
				dp[s][1]=dp[s^(1<<i)][1]-h[i].attsum;
				if((lefthp=dp[s^(1<<i)][0]-h[i].hurt-(dp[s^(1<<i)][1]-h[i].attsum)*h[i].time)<0)continue;
				if(lefthp>=dp[s][0])
				{
					dp[s][0]=lefthp;
				}
			}
		}
		ans=max(ans,dp[(1<<harm)-1][0]);
//		printf("k=%lld dp=%lld\n",k,dp[(1<<harm)-1][0]);
	}
	memset(dp,0,sizeof(dp));
	dp[0][0]=hp+hpadd;dp[0][1]=totatt;
	for(s=1;s<(1<<harm);s++)
	{
		dp[s][0]=0;
		for(i=0;i<harm;i++)
		{
			int lefthp;
			if(!(s&(1<<i)))continue;
			dp[s][1]=dp[s^(1<<i)][1]-h[i].attsum;
			if((lefthp=dp[s^(1<<i)][0]-h[i].hurt-(dp[s^(1<<i)][1]-h[i].attsum)*h[i].time)<0)continue;
			if(lefthp>=dp[s][0])
			{
				dp[s][0]=lefthp;
			}
		}
	}
	ans=max(ans,dp[(1<<harm)-1][0]);
//	for(s=0;s<(1<<harm);s++)
//	{
//		printf("%lld(%lld)\n",dp[s][0],dp[s][1]);
//	}
//	printf("dp=%lld\n",dp[(1<<harm)-1][0]);
	if(ans<=0)
	{
		printf("leave!\n");
		return 0;
	}
	for(i=0;i<kind;i++)
	{
		if(ek[i].eatt<=0)
		{
			bene[btot++]=-ek[i].eatt;
			btime+=ek[i].ehp/attack;
			if(!(ek[i].ehp%attack)) btime--;
			bhptot+=-ek[i].eatt;
		}
	}
	sort(bene,bene+btot);
	ans+=bhptot*btime;
	for(i=0;i<btot;i++)
	{
		ans+=bene[i]*i;
	}
	printf("%lld\n",ans);
}
/*
2 3 100 50 100
�����±� 20 30
���b��� 80 10
�����±�
�����±�
���b���
*/
/*
1 5 100 30 500
��װ�ɿ� 100 10
��װ�ɿ�
��װ�ɿ�
��װ�ɿ�
��װ�ɿ�
��װ�ɿ�
*/
/*
3 5 100 100 500
����w�б� 500 20
����̹�� 200 100
������� 50 100
����w�б�
����w�б�
����̹��
�������
�������
*/
