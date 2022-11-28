using namespace std;
int main() {}
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>

namespace Protector {
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
class ArrayTree {

private:
    int n;    
    int node[MAXN];
    int inline lb(int a) {
        return a & (-a);   
    }
public:
    void setSize(int new_size) {
        n = new_size;
    }
    
    void add(int nd, int val = 1) {
        for ( ; nd <= n; nd += lb(nd)) {
            node[nd] += val;
        }
    }
    
    int query(int nd) {
        int ret = 0;
        for ( ; nd; nd -= lb(nd)) {
            ret += node[nd];
        }
        return ret;
    }
    
};
struct Node {
    int rev_cnt; // 有逆序对的点的个数 
    int min_rank; // 最小的有逆序对的 
    
};
class SegMentTree {
private:
    struct Lson{
        int operator [] (int nd) {
            return nd << 1;
        }
    }lson;
    struct Rson{
        int operator [] (int nd) {
            return nd << 1 | 1;
        }
    }rson;

    long long now_ans;
    int arr1[MAXN], arr2[MAXN];
    int *val, *sorted, *rank, *num;
    int n;
    int base;
    ArrayTree tree;
    Node node[270000];
    void update(int nd) {
        node[nd].rev_cnt = node[lson[nd]].rev_cnt + node[rson[nd]].rev_cnt;
        node[nd].min_rank = min(node[lson[nd]].min_rank, node[rson[nd]].min_rank);
    }
    void preProcess () {
        sorted = &arr2[0];
        memcpy(sorted, val, (n + 1) * sizeof(int));
        sort(sorted + 1, sorted + n + 1);
        rank = &arr1[0];
        int i;
        int tmp;
        for (i = 1; i <= n; i++) {
            rank[i] = lower_bound(sorted + 1, sorted + n + 1, val[i]) - sorted;
        }
        num = &arr2[0];
        tree.setSize(n);
        for (i = n; i >= 1; i--) {
            num[i] =  tree.query(rank[i] - 1);
            now_ans += num[i];
            tree.add(rank[i]);
        }        
    }    
    
    void change(int nd, int max_rank, int l, int nl, int nr) {
        if (   nr < l 
            || node[nd].rev_cnt == 0 
            || node[nd].min_rank > max_rank
            || nl > l && node[nd].min_rank == max_rank){
            return;
        } 
        if (nl == nr) {
            now_ans -= node[nd].rev_cnt;
            node[nd].rev_cnt = 0;
            node[nd].min_rank = INF;
            return;
        }
        change(lson[nd], max_rank, l, nl, nl + nr >> 1);
        change(rson[nd], max_rank, l, (nl + nr >> 1) + 1, nr);
        update(nd);
    }
    void minus_one(int nd, int max_rank, int l, int nl, int nr) {
        if (   nr <= l 
            || node[nd].rev_cnt == 0 
            || node[nd].min_rank > max_rank){
            return;
        }
        if (nl == nr) {
           now_ans--;
           node[nd].rev_cnt--;
           if (node[nd].rev_cnt == 0) {
               node[nd].min_rank = INF;
           }
           return; 
        }
        minus_one(lson[nd], max_rank, l, nl, nl + nr >> 1);
        minus_one(rson[nd], max_rank, l, (nl + nr >> 1) + 1, nr);
        update(nd);
    }
    void build (int nd, int l, int r) {
        if (l == r) {
            node[nd].rev_cnt = num[l];
            if (num[l]) {
                node[nd].min_rank = rank[l];
            } else {
                node[nd].min_rank = INF;
            }
            return;
        }
        build(lson[nd], l, l + r >> 1);
        build(rson[nd], (l + r >> 1) + 1, r);
        update(nd);
    }
public:
    SegMentTree() {
        val = &arr1[0];
    }
    void setSize(int new_size) {
        n = new_size;
    }
    void setVal(int idx, int new_val) {
        val[idx] = new_val;
    }    
    void build() { 
        preProcess();
        build(1, 1, n);
    }
    void change(int pos) {
        change(1, rank[pos], pos, 1, n);
        minus_one(1, rank[pos], pos, 1, n);
    }
    long long query() {
        return now_ans;
    }
    
}tree;

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
        long long lstans;
        int i, j;
        int Q, Qn;
        int n;
        int a, b, c;
        read(n); read(Qn);
        tree.setSize(n);
        for (i = 1; i <= n; i++) {
            read(a); 
            tree.setVal(i, a);
        }
        tree.build();
        printf("%lld\n", lstans = tree.query());
        for (Q = 1; Q <= Qn; Q++) {
            read(a);
            if (a < 0) {
                a = ((lstans + a) % n + n) % n + 1;
            }
            tree.change(a);
            printf("%lld\n", lstans = tree.query());
        }
    }
    
    
    
}T1;

}
