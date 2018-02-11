using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>


namespace OI {
const int 
    ADDX = 0,
    ADDY = 1,
    ROTX = 2,
    ROTY = 3,
    ROTXY = 4,
    ROTX_Y = 5,
    ROT = 6,
    ASK = 7
;
const double PI = acos(-1);

struct Lson {
    inline int operator [] (int a) {
        return a << 1;
    }
}lson;

struct Rson {
    inline int operator [] (int a) {
        return a << 1 | 1;
    }
}rson;
struct Sig {
    int neg;
    double add;    
};

struct Tag {
    char swp, roted;
    double rot[2];
    Sig sig[2];
    
    void zero() {
        memset(this, 0, sizeof(Tag));
        rot[0] = 1;
    }
};



class SegmentTree {
public:
    Tag node[132003];
    int leaf[50010];
    int n;
    int inline mid(int a, int b) {
        return a + b >> 1;
    }
    
    void build(int _n) {
        n = _n;
        getLeaf(1, 1, n);
    }
    void getLeaf(int nd, int l, int r) {
        node[nd].zero();
        if (l == r) {
            leaf[l] = nd;
            return;
        }
        getLeaf(lson[nd], l, mid(l, r));
        getLeaf(rson[nd], mid(l, r) + 1, r);
    }
    
    void addTag(const Tag &src, Tag &dst) {
        double x1, y1, x2, y2;
        int i;
        //swp
        if (src.swp) {
            swap(dst.sig[0], dst.sig[1]);
            dst.swp ^= 1;
            dst.rot[1] *= -1;
        }
        //neg
        for (i = 0; i < 2; i++) {
            if (src.sig[i].neg) {
                dst.sig[i].add *= -1;
                dst.sig[i].neg ^= 1;
                dst.rot[1] *= -1;
            }
        }
       //rot
        if (src.roted) {
            x1 = src.rot[0];
            y1 = src.rot[1];
            x2 = dst.sig[0].add;
            y2 = dst.sig[1].add;
            dst.sig[0].add = x1 * x2 - y1 * y2; 
            dst.sig[1].add = x1 * y2 + x2 * y1;
            x2 = dst.rot[0];
            y2 = dst.rot[1];   
            dst.rot[0] = x1 * x2 - y1 * y2; 
            dst.rot[1] = x1 * y2 + x2 * y1;   
            dst.roted = 1;         
        }
        //add
        dst.sig[0].add += src.sig[0].add;
        dst.sig[1].add += src.sig[1].add;
    }
    
    void pushSig(int nd) {
        addTag(node[nd], node[lson[nd]]);
        addTag(node[nd], node[rson[nd]]);
        node[nd].zero();
    }
    void change(int l, int r, const Tag &val) {
        change(l, r, val, 1, 1, n);
    } 
    void change(int l, int r, const Tag &val, int nd, int nl, int nr) {
        if (l > nr || r < nl) {
            return;
        }
        if (l <= nl && r >= nr) {
            addTag(val, node[nd]);
            return;
        }
        pushSig(nd);
        change(l, r, val, lson[nd], nl, mid(nl, nr));
        change(l, r, val, rson[nd], mid(nl, nr) + 1, nr);
    }
    void query(int nd, int l, int r, int nl, int nr) {
        if (l > nr || r < nl) {
            return;
        }
        if (nl == nr) {
            int i;
            for (i = 0; i < 2; i++) {
                printf("%.2f ", node[nd].sig[i].add);
            }
            printf("\n");
            return;
        }
        pushSig(nd);
        query(lson[nd], l, r, nl, mid(nl, nr));
        query(rson[nd], l, r, mid(nl, nr) + 1, nr);
    }
    void print(int dst = 0) {
        if (dst == 0) {
            query(1, 1, n, 1, n);
        } else {
            query(1, dst, dst, 1, n);
        }
    }
    
}tree;



struct _Main {

    
    _Main() {
        int i, j, k;
        int Q, Qn;
        int n;
        int oper;
        int l, r, a;
        Tag tag;
        read(n); read(Qn);
        tree.build(n);
        for (i = 1; i <= n; i++) {
            for (j = 0; j < 2; j++) {
                read(tree.node[tree.leaf[i]].sig[j].add);
            }
        }
        for (Q = 1; Q <= Qn; Q++) {
            tag.zero();
            read(oper);
            switch (oper) {
                case ADDX:{
                    read(l); read(r); read(a);
                    tag.sig[0].add = a;
                    tree.change(l, r, tag);
                	break;
                }            
                case ADDY:{
                    read(l); read(r); read(a);
                    tag.sig[1].add = a;
                    tree.change(l, r, tag);                    
                	break;
                }                
                case ROTX:{
                    read(l); read(r);
                    tag.sig[1].neg = 1;
                    tree.change(l, r, tag);                    
                	break;
                }    
                case ROTY:{
                    read(l); read(r);
                    tag.sig[0].neg = 1;
                    tree.change(l, r, tag);                         
                	break;
                }    
                case ROTXY:{
                    read(l); read(r);
                    tag.swp = 1;
                    tree.change(l, r, tag);                          
                	break;
                }            
                case ROTX_Y:{
                    read(l); read(r);
                    tag.swp = 1;
                    tag.sig[0].neg = tag.sig[1].neg = 1;
                    tree.change(l, r, tag);                        
                	break;
                }
                case ROT:{
                    read(l); read(r); read(a);
                    if (a % 360 ) {
                        tag.roted = 1;
                        tag.rot[0] = cos(a / 180.0 * PI );
                        tag.rot[1] = sin(a / 180.0 * PI );
                        tree.change(l, r, tag);
                    }
                    break;
                }    
                case ASK:{
                    read(a);
                    tree.print(a);
                	break;
                }                               
            }
        }
        tree.print();
    }
     

template <typename Type>
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
}vaccum_imploder;










}


