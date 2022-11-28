#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=110;
const int inf=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

bitset<maxn> used,vis;
char in[maxn][maxn];
int val[maxn][maxn];
int su[maxn],tar[maxn][4];
int n,m,cnt,pcn,ans=inf;

inline bool judge() {
    for(int i=1;i<=pcn;i++) {
        if( used[i] ) continue;
        bool l = 0;
        for(int j=0;j<su[i];j++)
            l |= !vis[tar[i][j]];
        if( l ) return 0;
    }
    return 1;
}
inline void dfs(int pos,int cur) {
    if( cur > ans ) return;
    if( pos > pcn ) {
        if( judge() ) ans = min( ans , cur );
        return;
    }
    dfs(pos+1,cur);
    used[pos] = 1;
    for(int i=0;i<su[pos];i++)
        if( !vis[tar[pos][i]] ) {
            vis[tar[pos][i]] = 1;
            dfs(pos+1,cur+1);
            vis[tar[pos][i]] = 0;
        }
    used[pos] = 0;
}
int main() {
    srand(20010128);
    scanf("%d%d%*d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",in[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] == 'o' )
                val[i][j] = ++cnt;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] == 'l' ) {
                ++pcn;
                for(int k=0;k<4;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( val[tx][ty] ) {
                        tar[pcn][su[pcn]++] = val[tx][ty];
                    }
                }
                if( !su[pcn] )
                    --pcn;
            }
    dfs(0,0);
    
    printf("%d\n",ans);
    
    return 0;
}
