#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
const int T = 5e5+7;
int n,t;
char B[N],tmp[N];
struct Aho
{
    queue <int> q;
    struct state 
    {
        int nxt[2];
        int fail,cnt;
        bool used;
        
    }tre[N];
    int size;
    void init()  
    {
        for(int i = 0; i < T; i++)
        {
            memset(tre[i].nxt,0,sizeof(tre[i].nxt));
            tre[i].fail = tre[i].cnt = 0;
        }
        size = 1; 
    }
    void Insert(char * s)
    {
        int n = strlen(s);
        int now = 0;
        for(int i = 0; i < n; i++)
        {
            int c = s[i] - '0';
            if(!tre[now].nxt[c]) tre[now].nxt[c] = size++;
            now = tre[now].nxt[c];
        }
        tre[now].cnt++;
    }
    void Build()
    {
        tre[0].fail = -1;
        q.push(0);
        while(!q.empty())
        {
            int u = q.front();
            int v = tre[u].fail; 
            q.pop();
            for(int i = 0; i < 2; i++)
            {
                if(tre[u].nxt[i]) 
                {
                    if(u == 0) tre[tre[u].nxt[i]].fail = 0; 
                    else
                    {
                        
                        while(v != -1)
                        {
                            if(tre[v].nxt[i])
                            {
                                tre[tre[u].nxt[i]].fail = tre[v].nxt[i]; 
                                break; 
                            }
                            v = tre[v].fail;
                        }
                        if(v == -1) tre[tre[u].nxt[i]].fail = 0;
                    }
                    q.push(tre[u].nxt[i]);
                }
            }
        }
    }
    int Get(int u)
    {
        int res = 0;
        while(u)
        {
            res = res + tre[u].cnt;
            u = tre[u].fail;
        }
        return res;
    }
    int Match(char * s)
    {
        int n = strlen(s);
        int res = 0, now = 0;
        for(int i = 0; i < n; i++)
        {
            int c = s[i] - '0';
            if(tre[now].nxt[c]) now = tre[now].nxt[c]; 
            else
            {
                int p = tre[now].fail; 
                while(p != - 1 && tre[p].nxt[c] == 0) p = tre[p].fail; 
                if(p == -1) now = 0; 
                else now = tre[p].nxt[c]; 
            }
            if(tre[now].cnt) res = res + Get(now);
        }
        return res;
    }
}ACtre;
//写炸了 不想改了 
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
    scanf("%d",&n);
	scanf("%s",B);
    for(int i = 0; i < n; i++)
    {
        scanf("%s",tmp);
        ACtre.Insert(tmp);
    }
    ACtre.Build();
    printf("%d\n",ACtre.Match(B));
    return 0;
}
