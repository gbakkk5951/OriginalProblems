#include<bits/stdc++.h>
using namespace std;

const int N=5000010;
int n,cnt,len,tim,tim1,f[N];
long long ans;
char s[N],t[N];
struct AC{
	int c[2],fail,sum,len;
}a[N];

inline void insert(char* s)
{
	int p=0;
	for(int i=0;s[i];i++)
	{
		if(!a[p].c[s[i]-'0'])
			a[p].c[s[i]-'0']=++cnt,a[cnt].len=a[p].len+1;
		p=a[p].c[s[i]-'0'];
	}
	a[p].sum=1;
}

inline void build()
{
	queue<int>q;
	for(int i=0;i<2;i++)
		if(a[0].c[i])a[a[0].c[i]].fail=0,q.push(a[0].c[i]);
	while(q.size())
	{
		int x=q.front();
		q.pop();
		for(int i=0;i<2;i++)
			if(a[x].c[i])a[a[x].c[i]].fail=a[a[x].fail].c[i],q.push(a[x].c[i]);
			else a[x].c[i]=a[a[x].fail].c[i];
	}
}

inline void find(char* s)
{
	int p=0;
	len=strlen(s);
	memset(f,0xcf,sizeof(f));
	f[0]=0;
	for(int i=0;i<len;i++)
	{
		if(i)f[i]=max(f[i],f[i-1]);
		p=a[p].c[s[i]-'0'];
		f[i]=max(f[i-a[p].len]+a[p].sum,f[i]);
		for(int j=p;j;j=a[j].fail)
			f[i]=max(f[i],f[i-a[j].len]+a[j].sum);
//		f[i]=max(f[i],f[i-1]);
//		if(a[p].c[s[i]-'0'])
//			p=a[p].c[s[i]-'0'],f[i]=max(f[i-a[p].len]+a[p].sum,f[i]);
//		else f[i]=max(f[i],f[a[a[p].fail].len]+a[p].sum),p=a[p].fail;

//		if(a[p].c[s[i]-'0'])
//			p=a[p].c[s[i]-'0'];
//		else p=a[p].fail;
//		if(a[p].sum)ans+=a[p].sum,i=a[p].len,p=0;
	}
}

int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d%s",&n,t);
	for(int i=1;i<=n;i++)
		scanf("%s",s),insert(s);
	build();
	find(t);
	printf("%d\n",f[len-1]);
	fclose(stdout);
	return 0;
}

/*
5
010101010111
010
01
11
1000
1110
*/
