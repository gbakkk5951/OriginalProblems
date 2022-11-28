#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<string>
#include<cmath>
#include<cstdlib>
#include<iostream>
#define int long long
#define eps (1e-8)
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
	int time,hurt,attsum,etime,eatt,num;
	string name;
}h[25];
int bene[50010],btot=0,btime=0,bhptot=0;
signed main()
{
	freopen("ypa3.in","r",stdin);
//	freopen("lyd.out","w",stdout);
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
	for(i=0;i<kind;i++)
	{
		if(ek[i].eatt>0)
		{
			h[harm].name=ek[i].s;
			h[harm].etime=ceil(ek[i].ehp*1.0/attack);
			h[harm].hurt=((1+ecnt[i])*ecnt[i]*h[harm].etime/2-ecnt[i])*ek[i].eatt;
			h[harm].time=h[harm].etime*ecnt[i];
			h[harm].eatt=ek[i].eatt;
			h[harm].num=ecnt[i];
			h[harm++].attsum=ecnt[i]*ek[i].eatt;
		}
		totatt+=ek[i].eatt*ecnt[i];
	}
/*	for(i=0;i<harm;i++)
	{
		printf("h[%lld]: time=%lld hurt=%lld attsum=%lld etime=%lld eatt=%lld num=%lld\n",i,h[i].time,h[i].hurt,h[i].attsum,h[i].etime,h[i].eatt,h[i].num);
	}*/
//	printf("totatt=%lld\n",totatt);
	memset(dp,0,sizeof(dp));
	for(k=0;k<harm;k++){dp[1<<k][0]=hp;dp[1<<k][1]=totatt-h[k].attsum;}
	dp[0][0]=hp+hpadd;dp[0][1]=totatt;
	s=0;
	cout<<"dp"<<endl;
	for(j=0;j<harm;j++)if(!((1<<j)&s)){
		cout<<h[j].name<<" ";
	}cout<<"="<<dp[s][0]<<endl;	
	
	for(s=1;s<(1<<harm);s++)
	{
		for(i=0;i<harm;i++)
		{
			int lefthp;
			if(!(s&(1<<i)))continue;
			dp[s][1]=dp[s^(1<<i)][1]-h[i].attsum;
	//		printf("dp[%lld][1]=dp[%lld][1]-h[%lld].attsum=%lld-%lld=%lld\n",s,s^(1<<i),i,dp[s^(1<<i)][1],h[i].attsum,dp[s^(1<<i)][1]-h[i].attsum);
			if(dp[s^(1<<i)][0]<=0)continue;
	//		printf("dp[%lld][1]=dp[%lld][1]-h[%lld].attsum=%lld-%lld=%lld\n",s,s^(1<<i),i,dp[s^(1<<i)][1],h[i].attsum,dp[s^(1<<i)][1]-h[i].attsum);
			
			
			
			double mid=((h[i].attsum+dp[s][1])*h[i].etime+h[i].eatt)*(double)1.0/(h[i].eatt*h[i].etime);
			if(fabs(round(mid)-mid)<eps)
			{
				if(mid<0) mid=0;if(mid>h[i].num) mid=h[i].num-1;
				if(-(mid*mid+mid)/2*h[i].eatt*h[i].etime+(h[i].attsum+dp[s][1])*(h[i].etime*(mid+1)-1)+h[i].eatt*mid-dp[s^(1<<i)][0]>-eps) continue;
			}
			else
			{
				double a=floor(mid),b=ceil(mid);
				if(a<0) a=0;if(a>h[i].num) a=h[i].num-1;if(b<0) b=0;if(b>h[i].num) b=h[i].num-1;
				if(-(a*a+a)/2*h[i].eatt*h[i].etime+(h[i].attsum+dp[s][1])*(h[i].etime*(a+1)-1)+h[i].eatt*a-dp[s^(1<<i)][0]>-eps) continue;
				if(-(b*b+b)/2*h[i].eatt*h[i].etime+(h[i].attsum+dp[s][1])*(h[i].etime*(b+1)-1)+h[i].eatt*b-dp[s^(1<<i)][0]>-eps) continue;
			}
			
			lefthp=dp[s^(1<<i)][0]-h[i].hurt-dp[s][1]*h[i].time;
			if(lefthp>=dp[s][0])
			{
				dp[s][0]=lefthp;
			}
			
			
		}
		if(dp[s][0]<=0)continue;
		cout<<"dp"<<endl;
		for(j=0;j<harm;j++)if(!((1<<j)&s)){
			cout<<h[j].name<<" ";
		}cout<<"="<<dp[s][0]<<endl;
	}
	ans=dp[(1<<harm)-1][0];
	if(ans<=0)
	{
		printf("leave!\n");
		return 0;
	}
	for(i=0;i<kind;i++)
	{
		if(ek[i].eatt<=0)
		{
			for(j=0;j<ecnt[i];j++)
			{
				bene[btot++]=-ek[i].eatt;
				btime+=ek[i].ehp/attack;
				if(!(ek[i].ehp%attack)) btime--;
				bhptot+=-ek[i].eatt;
			}
		}
	}
	sort(bene,bene+btot);
	ans+=bhptot*btime;
	printf("before dead = %lld ",ans);
	for(i=0;i<btot;i++)
	{
		
		ans+=bene[i]*i;
		printf("ans + = %lld * %lld\n",bene[i],i);
	}
	printf("%lld\n",ans);
}
/*
5 10 500 1000 700
3星动员兵 19 46
美国大兵 135 79
動員兵 39 74
动员兵 149 41
美國大兵 288 91
3星动员兵
美国大兵
动员兵
動員兵
3星动员兵
美国大兵
美国大兵
3星动员兵
动员兵
3星动员兵
*/
/*
2 3 100 50 100
尤里新兵 20 30
重裝大兵 80 10
尤里新兵
尤里新兵
重裝大兵
*/
/*
1 5 100 30 500
武装采矿车 100 10
武装采矿车
武装采矿车
武装采矿车
武装采矿车
武装采矿车
*/
/*
3 5 100 100 500
火箭飛行兵 500 20
光棱坦克 200 100
海豹部隊 50 100
火箭飛行兵
火箭飛行兵
光棱坦克
海豹部隊
海豹部隊
*/
/*
3 7 30 40 0
帝國武士 50 30
維和步兵 50 30
將軍劊子手 1 -60
帝國武士
帝國武士
帝國武士
維和步兵
維和步兵
維和步兵
將軍劊子手
*/
