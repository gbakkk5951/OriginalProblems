#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define R register int
using namespace std;
#define ull unsigned long long
#define ll long long
#define pause (for(R i=1;i<=10000000000;++i))
#define IN freopen("NOIPAK++.in","r",stdin)
#define OUT freopen("out.out","w",stdout)
const int N=5000010; int n,tot,ans;
int c[N][2],end[N],fail[N],l[N],f[N],nxt[N];
char s[N],a[N];
inline void ins(char* s) { R len=strlen(s),now=0;
	for(R i=0;i<len;++i) { R ch=s[i]-'0';
		if(!c[now][ch]) c[now][ch]=++tot;
		now=c[now][ch];
	} end[now]=len;
}
queue<int> q;
inline void build() { q.push(0);
	while(q.size()) { R u=q.front(); q.pop();
		for(R i=0;i<2;++i) { R v=c[u][i];
			if(!v) {c[u][i]=c[fail[u]][i]; continue;}
			fail[v]=u?c[fail[u]][i]:0; 
			nxt[v]=end[fail[v]]?fail[v]:nxt[fail[u]];
			q.push(v);
		}
	}
}
inline void query(char* s) { R len=strlen(s),now=0;
	for(R i=0;i<len;++i) { R ch=s[i]-'0';
		now=c[now][ch];
		for(R t=now;t;t=nxt[t]) end[t]&&(l[i+1]=min(l[i+1],end[t]));
	}
}
signed main() {
#ifdef JACK
#endif
	freopen("sugar.in","r",stdin); freopen("sugar.out","w",stdout);
	memset(l,0x3f,sizeof(l));
	scanf("%d",&n); scanf("%s",s); for(R i=1;i<=n;++i) scanf("%s",a),ins(a); build();
	query(s); R len=strlen(s);
	for(R i=1;i<=len;++i) f[i]=max(f[i-1],max(f[i],(i>=l[i])?(f[i-l[i]]+1):0)); //,cout<<l[i]<<endl;;//,cout<<f[i]<<endl;//
	printf("%d\n",f[len]);
}
