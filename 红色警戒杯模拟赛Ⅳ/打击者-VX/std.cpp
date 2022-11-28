using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>

namespace OI {
typedef long long lld;
const int 
    INF = 0x3f3f3f3f,
    MOD = 1e9 + 7,
    PHI = MOD - 1 
;
double inline mid(double a, double b) {
    return (a + b) / 2.0;
}
int lrand() {
    return rand() << 15 | rand();
}

struct Node {
    int val, rand;
    Node *fa, *son[2];
    double m[2], v;
    
    void mark(double l, double r) {
        m[0] = l; m[1] = r; v = mid(l, r);
    }
    void * operator new (size_t, int val, Node *fa);
}pool[100010];
int pidx;
Node* node[100010];
void * Node:: operator new (size_t, int val, Node *fa = 0) {
    Node* nd = &pool[pidx++];
    nd->val = val;
    nd->fa = fa;
    nd->rand = lrand();
    node[val] = nd;
    return nd;
}
int sa[100100];
int rank[100010];
int height[100010];
class SuffixHeap {
public:
    int *str, len;
    double tot;
    Node *root;
    int cmp(int idx, Node *nd) {
        if (str[idx] != str[nd->val]) {
            return str[idx] > str[nd->val];
        }
        return tot > node[nd->val + 1]->v;
    }
    void rotate(Node *nd) {
        Node *fa = nd->fa, *gfa = fa->fa, *s;
        nd->fa = gfa;
        if (gfa) {
            gfa->son[gfa->son[1] == fa] = nd;
        }
        int pos = nd == fa->son[1];
        s = fa->son[pos] = nd->son[pos ^ 1];
        if (s) {
            s->fa = fa;
        }
        nd->son[pos ^ 1] = fa;
        fa->fa = nd;
    }
    
    void insert(int idx) {
        Node *nd = root;
        while (1) {
            int pos = cmp(idx, nd);
            if (nd->son[pos]) {
                nd = nd->son[pos];
            } else {
                nd->son[pos] = new(idx, nd) Node;
                nd = nd->son[pos];
                break;
            }
        }
        while (nd->fa && nd->rand < nd->fa->rand) {
            rotate(nd);
        }
        mark_new(nd);
    }
    void mark_new(Node *nd) {
        double m[2] = {0, 1};
        Node *fa = nd->fa;
        if (fa) {
            int pos = nd == fa->son[1];
            m[pos] = fa->m[pos];
            m[pos ^ 1] = fa->v;
        } else {
            root = nd;
        }
        remark(nd, m[0], m[1]);
        tot = nd->v;
    }
    void remark(Node *nd, double l, double r) {
        if (nd) {
            nd->mark(l, r);
            remark(nd->son[0], l, nd->v);
            remark(nd->son[1], nd->v, r);
        }
    }
    void getSa(Node *nd, int &idx) {
        if (nd) {
            getSa(nd->son[0], idx);   
            sa[idx++] = nd->val;
            getSa(nd->son[1], idx);   
        }
    }
    void getRank() {
        int i;
        for (i = 0; i < len; i++) {
            rank[sa[i]] = i;
        }
    }
    void getHeight() {
        int i, j, k;
        for (i = 0, k = 0; i < len - 1; i++) {
            j = sa[rank[i] - 1];
            for (k ? k-- : 0; str[i + k] == str[j + k]; k++);
            height[rank[i]] = k;
        }
    }
    
    void build(int *_str, int _len) {
        len = _len; str = _str;
        int i, idx = 0;
        root = new(len - 1)Node;
        root->mark(0, 1);
        tot = root->v;
        for (i = len - 2; i >= 0; i--) {
            insert(i);
        }
        getSa(root, idx);
        getRank();
        getHeight();
    }
    
    
    
}tree;

lld fastpower(lld base, lld pow) {
    lld ret = 1;
    if (pow < 0) {
        pow += PHI;
    }
    while (pow) {
        if (pow & 1) {
            ret = ret * base % MOD;
        }
        pow >>= 1;
        base = base * base % MOD;
    }
    return ret;
}




struct _Main {
template <typename Type>
    void read(Type &a) {
        char t;
        while (!isdigit(t = getchar()));
        a = t - '0';
        while ( isdigit(t = getchar())) {
            a *= 10;
            a += t - '0';
        }
    }
    
    
    int n;
    int arr[100010];
    
    int getStr(int *arr) {
        int idx = 0, t;
        while (isspace(t = getchar()));
        do {
            arr[idx++] = t;
        } while (!isspace(t = getchar()));
        return idx;
    }
    lld sum, single;
    void getSum() {
        int i;
        for (i = 1; i < n; i++) {
            sum += n - sa[i] - 1 - height[i];
        }
    }
    void getSingle() {
        int i, com;
        for (i = 1; i < n; i++) {
            com = height[i];
            if (i < n - 1) {
                com = max(com, height[i + 1]);
            }
            single += n - sa[i] - 1 - com;
        }
    }
    _Main() {
        int i, j, k;
        int Q, Qn;
        lld rev_rate = 1;
        read(i); read(Qn);
        n = getStr(arr);
        arr[n++] = -INF;
        tree.build(arr, n);
        getSum();
        getSingle();
        rev_rate = single % MOD * fastpower(sum, -1) % MOD;
        rev_rate = fastpower(rev_rate, -1);
        for (Q = 1; Q <= Qn; Q++) {
            int N;
            read(N);
            N %= MOD;
            printf("%lld\n", ((N * rev_rate % MOD - 1) % MOD + MOD) % MOD); //¿¨ÕâÀï¡£                 
        }
    }
    
}VX;


}
