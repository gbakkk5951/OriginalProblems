#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <limits>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#define lowbit(x) ( x&(-x) )
#define pi 3.141592653589793
#define e 2.718281828459045
#define INF 0x3f3f3f3f
#define HalF (l + r)>>1
#define lsn rt<<1
#define rsn rt<<1|1
#define Lson lsn, l, mid
#define Rson rsn, mid+1, r
#define QL Lson, ql, qr
#define QR Rson, ql, qr
#define myself rt, l, r
using namespace std;
typedef unsigned long long ull;
typedef unsigned int uit;
typedef long long ll;
const int maxN = 1003;
int cntx, cnty, M;
struct KM
{
    int mp[maxN][maxN], link_x[maxN], link_y[maxN], N;
    bool visx[maxN], visy[maxN];
    int que[maxN << 1], top, fail, pre[maxN];
    ll hx[maxN], hy[maxN], slk[maxN];
    inline int check(int i)
    {
        visx[i] =true;
        if(link_x[i])
        {
            que[fail++] = link_x[i];
            return visy[link_x[i]] = true;
        }
        while(i)
        {
            link_x[i] = pre[i];
            swap(i, link_y[pre[i]]);
        }
        return 0;
    }
    void bfs(int S)
    {
        for(int i=1; i<=N; i++)
        {
            slk[i] = INF;
            visx[i] = visy[i] = false;
        }
        top = 0; fail = 1;
        que[0] = S;
        visy[S] = true;
        while(true)
        {
            ll d;
            while(top < fail)
            {
                for(int i = 1, j = que[top++]; i <= N; i++)
                {
                    if(!visx[i] && slk[i] >= (d = hx[i] + hy[j] - mp[i][j]))
                    {
                        pre[i] = j;
                        if(d) slk[i] = d;
                        else if(!check(i)) return;
                    }
                }
            }
            d = INF;
            for(int i=1; i<=N; i++)
            {
                if(!visx[i] && d > slk[i]) d = slk[i];
            }
            for(int i=1; i<=N; i++)
            {
                if(visx[i]) hx[i] += d;
                else slk[i] -= d;
                if(visy[i]) hy[i] -= d;
            }
            for(int i=1; i<=N; i++)
            {
                if(!visx[i] && !slk[i] && !check(i)) return;
            }
        }
    }
    void init()
    {
        for(int i=1; i<=N; i++)
        {
            link_x[i] = link_y[i] = 0;
            visy[i] = false;
        }
        for(int i=1; i<=N; i++)
        {
            hx[i] = 0;
            for(int j=1; j<=N; j++)
            {
                if(hx[i] < mp[i][j]) hx[i] = mp[i][j];
            }
        }
    }
}km;
int main()
{
    scanf("%d%d%d", &cntx, &cnty, &M);
    for(int i=1, u, v, w; i<=M; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        km.mp[u][v] = w;
    }
    km.N = max(cntx, cnty) + 1;
    ll ans = 0;
    km.init();
    for(int i=1; i<=km.N; i++) km.bfs(i);
    for(int i=1; i<=cntx; i++) ans += km.mp[i][km.link_x[i]];
    printf("%lld\n", ans);
    for(int i=1; i<=cntx; i++) printf("%d%c", km.mp[i][km.link_x[i]] ? km.link_x[i] : 0, i == cntx ? '\n' : ' ');
    return 0;
}
