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
     
};
struct MinusNode {
    int sig;
    int min_cnt;
    int l, r;
};
struct ZeroNode {
    int min_rank;
    int rev_cnt;
    
};

class WarBearSolver {
    
private:    
    int arr1[MAXN], arr2[MAXN];
    int minus_idx[MAXN], zero_idx[MAXN];
    int minus_pos[MAXN];
    int *rank, *sorted, *val, *rev_cnt;
    
    int rank_cnt;
    long long now_ans;
    ArrayTree init_tree;
    
    
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
                return;
            }
            build(rson[nd], (nl + nr >> 1) + 1, nr);
            build(lson[nd], nl, nl + nr >> 1);
            node[nd].l = node[lson[nd]].l;
            node[nd].r = node[rson[nd]].r;
        }
             
    public:
        vector<MinusNode> node;
        
        void pushSig(int nd) {
            int sig;
            if (sig = node[nd].sig) {
                node[lson[nd]].sig += sig;
                node[lson[nd]].min_cnt += sig;
                node[rson[nd]].sig += sig;
                node[rson[nd]].min_cnt += sig;
                node[nd].sig = 0;
            }
        }
        void build(int l, int r) {
            build(nd, l, r);
        }
        void update_down(int nd) {
            if (nd > 1) {
                update_down(nd);
            }
            if (rson[nd] < node.size()) {
                push_down;
            }
        }
        void update(int nd) {
            node[nd].min_cnt = min(node[lson[nd]].min_cnt, node[rson[nd]].min_cnt);
        }
        
    }minus_tree[MAXN];
    
    class ZeroTree {
        
        
    };
    
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
            tree.add(rank[i]);
        }
    }
    void 
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
    }
    long long query() {
        return now_ans;
    }
}solver;



struct _Main {

    _Main() {
        
        
    }
    
    
    
}warbear;



}
