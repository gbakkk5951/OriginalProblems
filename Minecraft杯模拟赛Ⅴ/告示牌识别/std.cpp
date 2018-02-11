using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace OI {
typedef long long lld;
typedef double lf;
const int 
    INF = 0x3f3f3f3f,
    MAXN = 250050
;
lf mid(lf a, lf b) {
    return (a + b) / 2.0;
}
struct Node {
    int val, rand;
    Node *fa, *son[2];
    lf m[2], v;
    void mark(lf l, lf r) {
        m[0] = l; m[1] = r; v = mid(l, r);
    }
    
    void * operator new(size_t, int val, Node *fa);
}pool[MAXN];
int pidx;
Node *node[MAXN];
int lrand() {
    return rand() << 15 | rand();
}

void * Node:: operator new(size_t, int val, Node *fa = 0) {
    Node *nd = &pool[pidx++];
    nd->fa = fa;
    nd->val = val;
    nd->rand = lrand();
    node[nd->val] = nd;
    return nd;
}
int sa[MAXN], rank[MAXN], height[MAXN];

class SuffixHeap {
public:
    int *str, len;
    Node *root;
    lf tot;
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
            gfa->son[fa == gfa->son[1]] = nd;
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
                nd = nd->son[pos] = new(idx, nd) Node;
                break;
            }
        }
        while (nd->fa && nd->fa->rand < nd->rand) {
            rotate(nd);
        }
        mark_new(nd);
    }
    void mark_new(Node *nd) {
        lf m[2] = {0, 1};
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
    
    void remark(Node *nd, lf l, lf r) {
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
        int i, idx = 0;
        str = _str; len = _len;
        root = new(len - 1) Node;
        root->mark(0, 1);
        for (i = len - 2; i >= 0; i--) {
            insert(i);
        }
        getSa(root, idx);
        getRank();
        getHeight();
        
    }
    
}tree;

struct _Main {
    int readStr(int *str) {
        int idx = 0, t;
        while (!isalpha(t = getchar()));
        do {
            str[idx++] = t;
        } while ( isalpha(t = getchar()));
        return idx;
    }
    int str[MAXN];
    int common[MAXN];
    int l1, l2, n;
    inline bool in(int a, int l, int r) {
        return a >= l && a <= r;
    }
    
    void count(int l, int r) {
        int com = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (i && !in(sa[i - 1], l, r)) { //卡一下分割符相同且没特判的；好像自然卡不需要构造 
                com = height[i];
            }
            com = min(com, height[i]);  
            if (com >= need && in(sa[i], l, r)) {
                common[sa[i]] = max(common[sa[i]], min(com - need + 1, limit - need + 1));   
            }
        }
    }
    int limit;
    int need;
    lld ans;
    int len[10];
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
    
    void rev() {
        int i;
        for (i = 0; i < n; i++) {
            height[i] = height[i + 1];
        }
        for (i = 0; i < n >> 1; i++) {
            swap(height[i], height[n - i - 1]);
            swap(sa[i], sa[n - i - 1]);
        }
    }
    _Main() {
        static int l[10], r[10];
        int cnt;
        int Q, Qn;
        int i, j, k;
        int I;
        
        read(cnt); read(Qn);
        for (i = 1; i <= cnt; i++) {
            l[i] = n;
            len[i] = readStr(str+ n);
            n += len[i];
            r[i] = n - 1;
            str[n++] = -INF + i;
        }
        tree.build(str, n);     
        for (Q = 1; Q <= Qn; Q++) {
            memset(common, 0, n * sizeof(int));
            ans = 0;
            lld a, b;
            scanf("%lld%lld", &a, &b);
            need = min((lld)5e4 + 10, a);
            limit = min((lld)5e4 + 10, b);
            for (I = 1; I <= 2; I++) {
                for (i = 1; i <= cnt; i++) {
                    if (need <= len[i]) {
                        count(l[i], r[i]);
                    }
                }
                rev();
            }
            for (i = 1; i <= cnt; i++) {
                if (len[i] >= need) {
                    lld mx = min(len[i], limit);
                    ans += (len[i] - mx + 1) * (mx - need + 1);
                    ans += (1 + mx - need + 1 - 1) * (len[i] - need + 1 - (len[i] - mx + 1 + 1) + 1) >> 1;
                }
            }
            for (i = 0; i < n; i++) {
                ans -= common[i];
            }
            printf("%lld\n", ans);
        }
    }
    
}jskl;



}

