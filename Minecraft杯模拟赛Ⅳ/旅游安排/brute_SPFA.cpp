using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <queue>
namespace Protector {

typedef long long lld;

const int 
    NXT = 1,
    DST = 0,
    DIS = 2,
    FLOW = 2,
    COST = 3,
    INF = 0x3f3f3f3f,
    MAXN = 2100,
    MAXE = 25000
;    
const lld
    LINF = (lld)INF << 31 | INF;
;

struct Dis {
    int dst;
    long long val;
    bool operator > (const Dis & b) const {
        return val > b.val;
    }
    bool operator < (const Dis & b) const {
        return val < b.val;
    }    
};

    
class Queue {
private:
    int q[1100000];
    int head, tail;
public:
    void push(int nd) {
        q[tail++] = nd;
    }
    void pop() {
        head++;
    }
    int front() {
        return q[head];
    }
    int empty() {
        return head == tail;
    }
}q;

class Heap {
private:
    Dis node[5100];
    int n;
private:
    void swim(int nd) {
        while (nd >> 1 && node[nd >> 1] > node[nd]) {
            swap(node[nd >> 1], node[nd]);
            nd >>= 1;
        }
    }
    void sink(int nd) {
        int chose = 0;
        while (1) {
            if (nd << 1 <= n) {
                chose = nd << 1;
                if ((chose | 1) <= n && node[chose | 1] < node[chose]) {
                    chose |= 1;
                }
            }
            if (chose && node[nd] > node[chose]) {
                swap(node[nd], node[chose]);
                nd = chose;
            } else{
                break;
            }            
        }
    }
public:
    void push(const Dis &a) {
        node[++n] = a;
        swim(n);
    }
    void pop() {
        swap(node[n], node[1]);
        n--;
        sink(1);
    }
     
    Dis top() {
        return node[1];
    }
    
    int empty() {
        return n == 0;
    }
    
}heap;

int src, dst, size;

class EKCostFlow {
public:
int eidx;
lld tot_cost;
lld tot_flow;
int head[MAXN];
lld edge[MAXE][4];
queue<int> q;
int in_q[MAXN];
int from_edge[MAXN], from_node[MAXN];
lld dis[MAXN];


EKCostFlow() {
    eidx = 1;
}

void inline push(int nd) {
    if (!in_q[nd]) {
        q.push(nd);
        in_q[nd] = 1;
    }
}
int inline pop() {
    int nd = q.front();
    q.pop();
    in_q[nd] = 0;
    return nd;
}
long long SPFA() {
    memset(dis, 63, size * sizeof(lld));
    dis[src] = 0;
    push(src);
    int nd, i, t;
    while (!q.empty()) {
        nd = pop();
        for (i = head[nd]; i; i = edge[i][NXT]) {
            if (edge[i][FLOW] && dis[t = edge[i][DST]] > dis[nd] + edge[i][COST]) {
                dis[t] = dis[nd] + edge[i][COST];
                from_edge[t] = i;
                from_node[t] = nd;
                push(t);
            }
        }
    }
    return dis[dst];
}

void getFlow() {
    lld mn_flow = LINF;
    int nd, e;
    for (nd = dst; nd != src; nd = from_node[nd]) {
        mn_flow = min(mn_flow, edge[from_edge[nd]][FLOW]);
    }
    tot_flow += mn_flow;
    for (nd = dst; nd != src; nd = from_node[nd]) {
        e = from_edge[nd];
        tot_cost += mn_flow * edge[e][COST];
        edge[e][FLOW] -= mn_flow;
        edge[e ^ 1][FLOW] += mn_flow;
    }
}


void inline dir_add(lld src, lld dst, lld flow, lld cost) {
    eidx++;
    edge[eidx][DST] = dst;
    edge[eidx][FLOW] = flow;
    edge[eidx][COST] = cost;
    edge[eidx][NXT] = head[src];
    head[src] = eidx;
}
void inline add(lld src, lld dst, lld flow, lld cost) {
    dir_add(src, dst, flow, cost);
    dir_add(dst, src, 0, -cost);
}


void run() {
    while (SPFA() < LINF) {
        getFlow();
    }
}
    
}cost_flow;



int cmp_src;
bool cmp (const Dis &a, const Dis &b) {
    if (a.val != b.val) {
        return a.val < b.val;
    }
    if (abs(a.dst - cmp_src) != abs(b.dst - cmp_src)) {
        return abs(a.dst - cmp_src) < abs(b.dst - cmp_src);
    }
    return false;
}
struct _Main {
template <typename Type>
    void read(Type &a) {
        char t,f = 1;
        while (!isdigit(t = getchar())) {
            if (t == '-') {
                f = -1;
            }
        }
        a = t - '0';
        while ( isdigit(t = getchar())) {
            a *= 10;
            a += t - '0';
        }
        a *= f;
    }
    int node_idx;
    int node() {
        return node_idx++;
    }
    int n, m;
    int cnt[1005], head[1005], in_q[1005];
    lld edge[5005][3];
    lld label[1005];
    lld dis[1005][1005];
    int SPFA(int src) {
        int i, j, nd, t;
        lld *dis = this->dis[src];
        dis[src] = 0;
        in_q[src] = 1;
        q.push(src);
        cnt[src] = 1;
        while (!q.empty()) {
            nd = q.front();
            q.pop();
            in_q[nd] = 0;
            for (i = head[nd]; i; i = edge[i][NXT]) {
                if(dis[t = edge[i][DST]] > dis[nd] + edge[i][DIS]) {
                    dis[t] = dis[nd] + edge[i][DIS];
                    cnt[t]++;
                    if (cnt[t] > n) {
                        return 0;
                    }
                    if (!in_q[t]) {
                        in_q[t] = 1;
                        q.push(t);
                    }
                }
            }
        }
        return 1;
    }

    Dis linker[1005];

    int eidx;
    void add(int src, int dst, int dis) {
        eidx++;
        edge[eidx][DST] = dst;
        edge[eidx][DIS] = dis;
        edge[eidx][NXT] = head[src];
        head[src] = eidx;
    }
    
    int hold[1005], cun_min[1005], times[1005], cost[1005], mu_biao[1005];

    

    
    Dis dai_xuan[1005];
    int vidx;
    int out_id[1005], in_id[1005];
    
    void connect(int src, int dst) {
        cost_flow.add(out_id[src], in_id[dst], LINF, times[src] * cost[dst]);
    }
    
    _Main() {
        int i, j;
        int a, b, c;
        read(n); read(m);
        for (i = 1; i <= m; i++) {
            read(a); read(b); read(c);
            add(a, b, c);
        }
        if (SPFA(1)) {
            for (i = 2; i <= n; i++) {
                SPFA(i);
            }
        } else {
            printf("Negative loop found.");
            return;
        }
        src = node(); dst = node();
        for (i = 1; i <= n; i++) {
            read(mu_biao[i]);
            read(cun_min[i]);
            read(times[i]);
            read(hold[i]);
            read(cost[i]);
            out_id[i] = node();
            in_id[i] = node();
            cost_flow.add(src, out_id[i], cun_min[i], 0);
            cost_flow.add(in_id[i], dst, hold[i], 0);
        }
        for (i = 1; i <= n; i++) {
            vidx = 0;
            for (j = 1; j <= n; j++) {
                if (j != i && dis[i][j] < LINF) {
                    dai_xuan[vidx++] = (Dis) {j, dis[i][j]};
                }
            }
            cmp_src = i;
            nth_element(dai_xuan, dai_xuan + min(vidx, mu_biao[i] + 1), dai_xuan + vidx, cmp);
            sort(dai_xuan, dai_xuan + min(vidx, mu_biao[i] + 1), cmp);
            for (j = 0; j < mu_biao[i] && j < vidx; j++) {
                connect(i, dai_xuan[j].dst);
            }
            if (vidx > mu_biao[i] 
                && !cmp(dai_xuan[mu_biao[i]], dai_xuan[mu_biao[i] - 1])
                && !cmp(dai_xuan[mu_biao[i] - 1], dai_xuan[mu_biao[i]])) {
                connect(i, dai_xuan[mu_biao[i]].dst);        
            }
        }
        size = node_idx;
        cost_flow.run();
        printf("%lld", cost_flow.tot_cost);
    }
    
    
    
}tour;

}
