
#pragma GCC optimize("Ofast","no-stack-protector")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
typedef long long int lli;
using namespace std;
const int maxn=3e5+1e2;
const int inf = 0x3f3f3f3f;
const lli minf = -1061109568;

int n,l,r;

struct SegmentTree {
    lli dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    SegmentTree() { memset(dat,0xcf,sizeof(dat)); }
    inline void update(int pos,int l,int r,const int &tar,const lli &val) {
        dat[pos] = max( dat[pos] , val );
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar,val) : update(rson(pos),mid+1,r,tar,val);
    }
    inline lli query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1; lli ret = minf;
        if( ll <= mid ) ret = max( ret , query(lson(pos),l,mid,ll,rr) );
        if( mid < rr )  ret = max( ret , query(rson(pos),mid+1,r,ll,rr) );
        return ret;
    }
    inline void reset() {
        memset(dat,0xcf,sizeof(dat));
    }
    inline void reset(int pos,int l,int r,const int &tar) {
        dat[pos] = minf;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        tar <= mid ? reset(lson(pos),l,mid,tar) : reset(rson(pos),mid+1,r,tar);
    }
}sgt;


int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli in[maxn],ans[maxn],tag[maxn];
lli vs[maxn]; int ds[maxn],ps[maxn],cnt;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

int siz[maxn],mxs[maxn],ban[maxn];

inline void findrt(int pos,int fa,const int &fs,int &rt) {
    siz[pos] = 1 , mxs[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) {
        findrt(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = max( mxs[pos] , siz[t[at]] );
    }
    if( ( mxs[pos] = max( mxs[pos] , fs - siz[pos] ) ) < mxs[rt] ) rt = pos;
}
inline void dfs(int pos,int fa,int dep,lli val) {
    ps[++cnt] = pos , ds[cnt] = dep , vs[cnt] = val;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) dfs(t[at],pos,dep+1,val+in[t[at]]);
}
inline void push_dfs(int pos,int fa) {
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) push_dfs(t[at],pos);
    tag[fa] = max( tag[fa] , tag[pos] ) , ans[pos] = max( ans[pos] , tag[pos] ) , tag[pos] = minf;
}
inline void solve(int pos,int fs) {
    if( fs == 1 ) return;
    
    int rt = 0; *mxs = inf , findrt(pos,-1,fs,rt) , ban[rt] = 1;
    vector<int> sons;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) sons.push_back(t[at]);
    
    cnt = 0;
    
    for(auto i:sons) {
        const int lst = cnt; dfs(i,-1,1,in[i]);
        for(int j=lst+1;j<=cnt;j++) {
            if( r - ds[j] - 1 >= 1 ) {
                tag[ps[j]] = max( tag[ps[j]] , vs[j] + in[rt] + sgt.query(1,1,n,max(1,l-ds[j]-1),min(r-ds[j]-1,n)) );
            } if( ds[j] + 1 <= r && ds[j] + 1 >= l ) tag[ps[j]] = max( tag[ps[j]] , in[rt] + vs[j] );
        }
        for(int j=lst+1;j<=cnt;j++) sgt.update(1,1,n,ds[j],vs[j]);
    }
    for(int i=1;i<=cnt;i++) sgt.reset(1,1,n,ds[i]);
    
    reverse(sons.begin(),sons.end()) , cnt = 0;
    for(auto i:sons) {
        const int lst = cnt; dfs(i,-1,1,in[i]);
        for(int j=lst+1;j<=cnt;j++) {
            if( r - ds[j] - 1 >= 1 ) {
                tag[ps[j]] = max( tag[ps[j]] , vs[j] + in[rt] + sgt.query(1,1,n,max(1,l-ds[j]-1),min(r-ds[j]-1,n)) );
            } if( ds[j] + 1 <= r && ds[j] + 1 >= l ) tag[ps[j]] = max( tag[ps[j]] , in[rt] + vs[j] );
        }
        for(int j=lst+1;j<=cnt;j++) sgt.update(1,1,n,ds[j],vs[j]);
    }
    for(int i=1;i<=cnt;i++) sgt.reset(1,1,n,ds[i]);
    
    for(auto i:sons) push_dfs(i,rt);
    
    ans[rt] = max( ans[rt] , tag[rt] ) , tag[rt] = minf;
    
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
}


int main() {
    scanf("%d%d%d",&n,&l,&r) , ++l , ++r , memset(ans,0xcf,sizeof(ans)) , memset(tag,0xcf,sizeof(tag));
    for(int i=1;i<=n;i++) {
        scanf("%lld",in+i);
        if( l == 1 ) ans[i] = in[i];
    }
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    
    solve(1,n);
    
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]<-3e8?minf:ans[i]);
    
    return 0;
}


