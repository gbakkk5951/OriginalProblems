#include<cstdio>
#define reg register
#define Max(a,b) ((a)>(b)?(a):(b));
char s[1000010];
int  a200[2000010],lp,lt,lh,*l;
int  a300[2000010],rp,rt,rh,*r;
int n,L=1,R,ans;
inline void Read()
{
	reg char h=getchar();
	reg int t=0;
	while(h=='\n')h=getchar();
	while(h!='\n')
	{
		if(h=='S')s[++t]=3;
		if(h=='s')s[++t]=1;
		if(h=='h')s[++t]=2;
		h=getchar();
	}
}
int main()
{
	freopen("hss.in","r",stdin);freopen("hss.out","w",stdout);
	char h;
	int a;
	l=&a200[1000005];
	r=&a300[1000005];
	scanf("%d %d",&R,&n);
	Read();
	for(reg int i=1;i<=R;i++)
	{
		if(s[i]==1)
		{
			l[++lp]=i;
		}
		if(s[i]==2)
		{
			if(lp<=lh)lt=i;
			else --lp;
		}
		
		if(lp<=lh)
		{
			ans=Max(ans,i-lt);
		}
		else ans=Max(ans,i-l[lp]);
	}
	rt=R+1;
	for(reg int i=R;i>0;i--)
	{
		if(s[i]==2)
		{
			r[++rp]=i;
		}
		if(s[i]==1)
		{
			if(rp<=rh)rt=i;
			else --rp;
		}
		
		if(rp<=rh)
		{
			ans=Max(ans,rt-i);
		}
		else ans=Max(ans,r[lp]-i);
	}
	printf("%d\n",ans);
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d %c",&a,&h);
		//printf("%c",h);
		if(a==2)
		{
			R++;
			if(h=='s')
			{
				l[++lp]=R;
			}
			if(h=='h')
			{
				if(lp<=lh)
				{
					lt=R;
					r[--rh]=R;
				}
				else --lp;
				if(lp<=lh)
				{
					
					rt=R+1;
				}
				
			}
			
			if(lp<=lh)
			{
				ans=Max(ans,R-lt);
			}
			else ans=Max(ans,R-l[lp]);
			if(rp<=rh)
			{
				ans=Max(ans,rt-L);
			}
			else ans=Max(ans,r[lp]-L);
			
		}
		if(a==1)
		{
			L--;
			if(h=='h')
			{
				r[++rp]=L;
			}
			if(h=='s')	
			{
				if(rp<=rh)
				{
					rt=L;	l[--lh]=L;
				}
				else --rp;
				if(rp<=rh)
				{
				
					lt=L-1;
				}
			}
			
			if(lp<=lh)
			{
				ans=Max(ans,R-lt);
			}
			else ans=Max(ans,R-l[lp]);
			if(rp>rh) ans=Max(ans,r[lp]-L);
			
		}
		printf("%d\n",ans);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
6 3
S s s s h h
2 h
1 h
1 s
*/
