#include<cstdio>
#define reg register
const int root=0;
int p;
int ans;
char s[5000010];
struct AC
{
	bool t;
	int l,r;
	int net;
}ac[5000010];
char a[5000010];
int  h[5000010],ht,hp;
inline void build(char a[])
{
	reg int t=root;
	for(reg int i=1;a[i];i++)
	{
		if(a[i]=='1')
		{
			if(ac[t].l)t=ac[t].l;
			else
			{
				ac[t].l=++p;
				t=p;
			}
		}
		if(a[i]=='0')
		{
			if(ac[t].r)t=ac[t].r;
			else
			{
				ac[t].r=++p;
				t=p;
			}
		}
	}
	ac[t].t=true;
}
inline void Build()
{
	if(ac[root].l)h[++hp]=ac[root].l;
	if(ac[root].r)h[++hp]=ac[root].r;
	while(++ht<=hp)
	{
		reg int x=h[ht],t=ac[x].net;
		if(ac[x].l)
		{
			while(t&&!ac[t].l)t=ac[t].net;
			ac[ac[x].l].net=ac[t].l;
			h[++hp]=ac[x].l;
		}
		t=ac[x].net;
		if(ac[x].r)
		{
			while(t&&!ac[t].r)t=ac[t].net;
			ac[ac[x].r].net=ac[t].r;
			h[++hp]=ac[x].r;
		}
	}
}
void kmp()
{
	int t=root;
	for(reg int i=1;s[i];i++)
	{
		if(s[i]=='1')
		{
			while(t&&!ac[t].l)t=ac[t].net;
			t=ac[t].l;
			if(ac[t].t)ans++,t=root;
		}
		if(s[i]=='0')
		{
			while(t&&!ac[t].r)t=ac[t].net;
			t=ac[t].r;
			if(ac[t].t)ans++,t=root;
		}
	}
}
int main()
{
	freopen("sugar.in","r",stdin);freopen("sugar.out","w",stdout);
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	while(n--)
	{
		scanf("%s",a+1);
		build(a);
	}
	Build();
	kmp();
	printf("%d",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}
/*5
010101010111
010
01
11
1000
1110
*/
