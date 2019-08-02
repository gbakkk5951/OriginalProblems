#include<bits/stdc++.h>
using namespace std;
int n,cnt;
int f[5000100];
struct acc{
    int fail,ch[2];
    int sum,len;
    #define fail(x) ac[x].fail
    #define sum(x) ac[x].sum
    #define len(x) ac[x].len
}ac[5000100];
inline void insert(string s,int x){
    int len=s.length();
    int p=0;
    for(int i=0;i<len;i++){
        if(!ac[p].ch[s[i]-'0']) ac[p].ch[s[i]-'0']=++cnt,len(cnt)=len(p)+1;
        p=ac[p].ch[s[i]-'0'];
    }
    sum(p)=1;
}
inline void getfail(){
    queue<int> q;
    for(int i=0;i<2;i++)
        if(ac[0].ch[i]) 
            q.push(ac[0].ch[i]),fail(ac[0].ch[i])=0;
    while(q.size()){
        int p=q.front();
        q.pop();
        for(int i=0;i<2;i++){
            if(ac[p].ch[i]) 
                fail(ac[p].ch[i])=ac[fail(p)].ch[i],q.push(ac[p].ch[i]);
            else ac[p].ch[i]=ac[fail(p)].ch[i];
        }
    }
}
inline void work(string s){
    memset(f,128,sizeof(f));
    int len=s.length();
    int now=0;    
    f[now]=0;
    for(int i=0;i<len;i++){
        f[i]=max(f[i],f[i-1]);
        now=ac[now].ch[s[i]-'0'];
        f[i]=max(f[i],f[i-len(now)]+sum(now));
        for(int j=now;j;j=fail(j)){
            f[i]=max(f[i],f[i-len(j)]+sum(j));
        }
    }
}
int main()
{
    freopen("sugar.in","r",stdin);
    freopen("sugar.out","w",stdout);
    scanf("%d",&n);
    string s;
    cin>>s;
    for(int i=1;i<=n;i++){
        string c;
        cin>>c;
        insert(c,i);
    }
    getfail();
    work(s);
    printf("%d\n",f[s.length()-1]);
    // system("pause");
    return 0;
}