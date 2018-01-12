using namespace std;
int main() {}
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<vector>
namespace Protector {
const int INF = 0x3f3f3f3f;    
const int MAXN = 100010;

struct Lson{
    int operator [] (int a) {
        return a << 1;
    }
}lson;

struct Rson{
    int operator [] (int a) {
        return a << 1 | 1;
    }
}rson;

class ArrayTree {
private:
    int node[MAXN];
    int n;
    int inline lb(int a) {
        return a & (-a);
    }
    
    
public: 
    void add(int nd, int val = 1) {
        for ( ; nd <= n; nd += lb(nd)) {
            node[nd]++;
        }
    }
    
    int query(int nd) {
        int ans = 0;
        for ( ; nd; nd -= lb(nd)) {
            ans += node[nd];
        }
        return ans;
    }

    void setSize(int new_size) {
        n = new_size;
    }
     
}init_tree;




int arr1[MAXN], arr2[MAXN];
int minus_idx[MAXN], zero_idx[MAXN];
int minus_pos[MAXN];
int *rank, *sorted, *val, *rev_cnt;

int rank_cnt;
long long now_ans;


struct MinusNode {
    int sig;
    int min_cnt;
    int tot_cnt;
    int r, l;
};

class ZeroTree;

class MinusTree {
private:
    int n;    
    
    
    void build(int nd, int nl, int nr) {
        if (nl == nr) {
            if (nd >= node.size()) {
                node.resize(nd + 1);
            }
            node[nd].l = node[nd].r = minus_pos[nl];
            node[nd].min_cnt = rev_cnt[minus_pos[nl]];
            node[nd].tot_cnt = rev_cnt[minus_pos[nl]]?1:0;
            minus_idx[node[nd].r] = nd;
            return;
        }
        build(rson[nd], (nl + nr >> 1) + 1, nr);
        build(lson[nd], nl, nl + nr >> 1);
        node[nd].l = node[lson[nd]].l;
        node[nd].r = node[rson[nd]].r;
        update(nd);
    }
    void change(int nd, int left, int nl, int nr);
public:
    ZeroTree *zero_tree; 
    vector<MinusNode> node;
    
    void pushSig(int nd) {
        int sig;
        if (sig = node[nd].sig) {
            if (node[lson[nd]].min_cnt) {
                node[lson[nd]].sig += sig;
                node[lson[nd]].min_cnt += sig;                
            }
            if (node[rson[nd]].min_cnt) {
                node[rson[nd]].sig += sig;
                node[rson[nd]].min_cnt += sig;      
            }
            node[nd].sig = 0;
        }
    }
    void build(int l, int r) {
        n = r - l + 1;
        build(1, l, r);
    }
    void update_down(int nd) {
        if (nd > 1) {
            update_down(nd >> 1);
        }
        if (rson[nd] < node.size()) {
            pushSig(nd);
        }
    }
    void update_up(int nd) {
        while (nd >>= 1) {
            update(nd);
        }
    }
    void update(int nd) {
        int l = node[lson[nd]].min_cnt, r = node[rson[nd]].min_cnt;
        if (l && r) {
            node[nd].min_cnt = min(node[lson[nd]].min_cnt, node[rson[nd]].min_cnt);
        } else {
            node[nd].min_cnt = node[lson[nd]].min_cnt | node[rson[nd]].min_cnt;
        }
        node[nd].tot_cnt = node[lson[nd]].tot_cnt + node[rson[nd]].tot_cnt;
    }
    void change(int left) {
        change(1, left, 1, n);
    }
    
}minus_tree[MAXN];

struct ZeroNode {
    int min_rank;
    int rev_cnt;
};   


class ZeroTree {
private:
    int n;
    void update(int nd) {
        node[nd].min_rank = min(node[lson[nd]].min_rank, node[rson[nd]].min_rank);
        node[nd].rev_cnt = node[lson[nd]].rev_cnt + node[rson[nd]].rev_cnt;
    }
    void build(int nd, int nl, int nr) {
        if (nl == nr) {
            if (rev_cnt[nl]) {
                node[nd].min_rank = rank[nl];
            } else {
                node[nd].min_rank = INF;
            }
            node[nd].rev_cnt = rev_cnt[nl];
            zero_idx[nl] = nd;
            return;
        }
        build(lson[nd], nl, nl + nr >> 1);
        build(rson[nd], (nl + nr >> 1) + 1, nr);
        update(nd);
    }
    void change(int nd, int left, int left_rank, int nl, int nr) {
        if (nr < left || node[nd].rev_cnt == 0
            || node[nd].min_rank > left_rank 
            || (nl > left && node[nd].min_rank == left_rank) ) {
            return;    
        }
        if (nl == nr ) {
            MinusTree *tree = &minus_tree[rank[nl]];
            int minus_nd = minus_idx[nl];
            typename vector<MinusNode>::iterator it;
            it = tree->node.begin() + minus_nd;
            tree->update_down(minus_nd);
            now_ans -= it->min_cnt;
            it->min_cnt  = it->tot_cnt = 0;
            tree->update_up(minus_nd);
            node[nd].rev_cnt = 0;
            node[nd].min_rank = INF;
            return;
        }
        
        change(lson[nd], left, left_rank, nl, nl + nr >> 1);
        change(rson[nd], left, left_rank, (nl + nr >> 1) + 1, nr);
        
        update(nd);
    }
public:
    ZeroNode node[270000];
    void update_up(int nd) {
        while (nd >>= 1) {
            update(nd);
        }
    }
    void change(int left) {
        change(1, left, rank[left], 1, n);
    }
    void build() {
        build(1, 1, n);
    }
    void setSize(int new_size) {
        n = new_size;
    }
    
}zero_tree;


void MinusTree::change(int nd, int left, int nl, int nr) {
    if (node[nd].r <= left || node[nd].tot_cnt == 0) {
        return;
    }
    if (node[nd].min_cnt > 1 && node[nd].l > left) {
        now_ans -= node[nd].tot_cnt;
        node[nd].min_cnt--;
        node[nd].sig--;
        return;
    } else if(nl == nr) {
        now_ans--;
        node[nd].min_cnt = node[nd].tot_cnt = 0;
        int zero_nd = zero_idx[node[nd].r];
        zero_tree->node[zero_nd].rev_cnt = 0;
        zero_tree->node[zero_nd].min_rank = INF;
        zero_tree->update_up(zero_nd);
        return;
    }
    pushSig(nd);
    change(lson[nd], left, nl, nl + nr >> 1);
    change(rson[nd], left, (nl + nr >> 1) + 1, nr);            
    update(nd);
}    


class WarBearSolver {
    
private:  

    int n;
    void li_san_hua() {
        int i;
        sorted = &arr2[0];
        rank = &arr1[0];
        memcpy(sorted, val, (n + 1) * sizeof(int));
        sort(sorted + 1, sorted + n + 1);
        rank_cnt = unique(sorted + 1, sorted + n + 1) - sorted - 1;
        for (i = 1; i <= n; i++) {
            rank[i] = lower_bound(sorted + 1, sorted + rank_cnt + 1, val[i]) - sorted;
        }
    }
    void getRevCnt() {
        int i;
        rev_cnt = &arr2[0];
        for (i = n; i >= 1; i--) {
            rev_cnt[i] = init_tree.query(rank[i] - 1);
            now_ans += rev_cnt[i];
            init_tree.add(rank[i]);
        }
    }      
    class MinusCmp {
    public:
        bool operator () (int a, int b) {
            if (rank[a] != rank[b]) {
                return rank[a] < rank[b];
            }
            return a < b;            
        }
        
    }minus_cmp;

    void buildMinusTree() {
        int i;
        for (i = 1; i <= n; i++) {
            minus_pos[i] = i; 
        }
        sort(minus_pos + 1, minus_pos + n + 1, minus_cmp);
        int l; int r;
        for (l = r = 1; r <= n; r++) {
            if (rank[minus_pos[r + 1]] != rank[minus_pos[r]] || r == n) {
                minus_tree[rank[minus_pos[r]]].zero_tree = &zero_tree;
                minus_tree[rank[minus_pos[r]]].build(l, r); 
                l = r + 1;
            }
        }
    }
    void buildZeroTree() {
        zero_tree.setSize(n);
        zero_tree.build();
    }
public:
    WarBearSolver() {
        val = &arr1[0];
    }
    void setSize(int new_size) {
        n = new_size;
        init_tree.setSize(n);
    }
    int setVal(int nd, int new_val) {
        val[nd] = new_val;
    }
    void build() {
        li_san_hua();
        getRevCnt();
        buildMinusTree();
        buildZeroTree();
    }
    void change(int left) {
        zero_tree.change(left);
        minus_tree[rank[left]].change(left);
    }
    long long query() {
        return now_ans;
    }
}solver;



struct _Main {
    
template<typename Type>
    void read(Type &a) {
        char t, f = 1;
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
_Main() {
    long long lst_ans;
    int i, j, k;
    int a, b, c;
    int Q, Qn;
    int n;
    read(n); read(Qn);
    solver.setSize(n);
    for (i = 1; i <= n; i++) {
        read(a);
        solver.setVal(i, a);
    }
    solver.build();
    
    printf("%lld\n", lst_ans = solver.query());
    
    for (Q = 1; Q <= Qn; Q++) {
        read(a);
        if (a < 0) {
            solver.change(((lst_ans + a) % n + n) %n + 1);
        } else {
            solver.change(a);
        }
        printf("%lld\n", lst_ans = solver.query());
    }
    
    
}
    
    
    
}warbear;



}
