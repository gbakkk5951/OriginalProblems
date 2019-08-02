#include<bits/stdc++.h>
#define N 500010
using namespace std;
queue<int>q;
struct Aho_Corasick_Automaton{
    int c[N][26],val[N],fail[N],cnt;
    void ins(char *s){
        int len=strlen(s);int now=0;
        for(int i=0;i<len;i++){
            int v=s[i]-'0';
            if(!c[now][v])c[now][v]=++cnt;
            now=c[now][v];
        }
        val[now]++;
    }
    void build(){
        for(int i=0;i<26;i++)if(c[0][i])fail[c[0][i]]=0,q.push(c[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=0;i<26;i++)
            if(c[u][i])fail[c[u][i]]=c[fail[u]][i],q.push(c[u][i]);
            else c[u][i]=c[fail[u]][i];
        }
    }
    int query(char *s){
        int len=strlen(s);int now=0,ans=0;
        for(int i=0;i<len;i++){
            now=c[now][s[i]-'0'];
            for(int t=now;t&&~val[t];t=fail[t])ans+=val[t],val[t]=-1;
        }
        return ans;
    }
}AC;
int n;char p[1000005],l[1000005];
int main(){
    freopen("sugar.in","r",stdin);
    freopen("sugar.out","w",stdout);
    scanf("%d",&n);scanf("%s",l);
    for(int i=1;i<=n;i++)scanf("%s",p),AC.ins(p);
    AC.build();
    int ans=AC.query(l);
    printf("%d\n",ans);
    return 0;
}
