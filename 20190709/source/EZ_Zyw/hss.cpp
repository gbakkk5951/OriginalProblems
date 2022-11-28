#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
int n,m;
char q[N];
struct Node{
	int l,r,s,ski;
	bool v;
	char c;
}a[N];

inline void match(int p)
{
	int st=p;
//	cout<<"*"<<st<<endl;
	while(p>0)
	{
//		cout<<p<<" "<<a[p].c<<endl;;
		if(a[p].ski)p=a[p].ski;
		else p=a[p].l;
		if(a[p].c=='s' && !a[p].v)
		{
			a[st].ski=p;
			a[st].v=a[p].v=1;
			break;
		}
	}
//	cout<<endl;
}


int main()
{
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	scanf("%d%d",&n,&m);
	int t=0;
	char ch;
	for(int i=1;i<=n;i++)
	{
		do ch=getchar();
		while(ch=='\n' || ch==' ');
		a[++t].c=ch;
		a[t].l=t-1;
		a[t].r=t+1;
		if(a[t].c=='h')match(t);
	}
	int ans=0;
	int pos;
	
	for(int i=t;i>0;i--)
	{
//		cout<<i<<endl;
		pos=i;
		while(a[pos].v||a[pos].c=='S')
		{
			if(a[pos].ski)pos=a[pos].ski;
			else pos=a[pos].l;
		}
		ans=max(ans,i-pos);
		i=pos;
	}
	printf("%d\n",ans);
	fclose(stdout);
	return 0;
//	cout<<ans<<endl;
//	for(int i=1;i<=n;i++)
//		cout<<a[i].v<<" ";
//	cout<<endl;
//	for(int i=1;i<=n;i++)
//		cout<<a[i].l<<" ";
//	cout<<endl;
//	
//	for(int i=1;i<=n;i++)
//		cout<<a[i].c<<" ";
//	cout<<endl;
//	
//	for(int i=1;i<=n;i++)
//		cout<<a[i].ski<<" ";
//	cout<<endl;
//	
}


/*
8 3
s S S s s S h h
2 h
1 h
1 s

4
7
7
9
*/
