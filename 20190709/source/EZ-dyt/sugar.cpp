#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
struct Tree//字典树 
{
     int fail;
     int vis[2];
	      int end;
}AC[5000000];
int cnt=0,anss=0; 
inline void Build(char *s) //(char s[]) 
{
        int l=strlen(s); //l=strlen(s) 
        int now=0;
        for(int i=0;i<l;++i)
        {
                if(AC[now].vis[s[i]-'0']==0)
                   AC[now].vis[s[i]-'0']=++cnt;
                now=AC[now].vis[s[i]-'0']; 
        }
        AC[now].end+=1;
}
void Get_fail()
{
        queue<int> Q;
        for(int i=0;i<2;i++)
        {
               if(AC[0].vis[i]!=0)
               {
                   AC[AC[0].vis[i]].fail=0;
                   Q.push(AC[0].vis[i]);
               }
        }
        while(!Q.empty())
        {
              int u=Q.front();
              Q.pop();
              for(int i=0;i<2;++i)
              {
                        if(AC[u].vis[i]!=0)
                      {
                                AC[AC[u].vis[i]].fail=AC[AC[u].fail].vis[i];
                                    
                                Q.push(AC[u].vis[i]);//压入队列 
                      }
                      else
                      AC[u].vis[i]=AC[AC[u].fail].vis[i];
                      
              }
        }
}
int AC_Query(char *s)
{
        int l=strlen(s);
        int now=0,ans=0;
        for(int i=0;i<l;++i)
        {
                now=AC[now].vis[s[i]-'0']; 
                for(int t=now;t&&AC[t].end!=-1;t=AC[t].fail)
                {                            
                         ans+=AC[t].end; 
                         anss++;
                         now=0;
						 AC[t].end=-1;//标记 
                } 
        }
        return ans;
}
char str[5000001];char ss[5000001];
int main()
{
    freopen("sugar.in","r",stdin);
    freopen("sugar.out","w",stdout);
	 int n;
     scanf("%d",&n);
     scanf("%s",str);
     for(int i=1;i<=n;++i)
     {
        scanf("%s",ss);
        Build(ss); 
     }
     AC[0].fail=0;
     Get_fail(); 
     int xxx=AC_Query(str);
     cout<<anss;
     fclose(stdin);
     fclose(stdout);
     return 0;
}
