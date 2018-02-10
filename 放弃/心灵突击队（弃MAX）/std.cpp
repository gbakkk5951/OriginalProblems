using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <vector>
#include <iostream>

namespace Protector {
const int INF = 0x3f3f3f3f;
int cnt;
struct Point {
    int x[2];
    bool operator == (const Point &b) {
        return x[0] == b.x[0] && x[1] == b.x[1];
    }
    int& operator [] (int a) {
        return x[a];
    }
    Point (){
        
    }
    Point (int x0, int x1) {
        x[0] = x0; x[1] = x1;
    }
};

struct KDNode{
    int son[2];
    int val, sig;
    Point ri, rj;
    KDNode(){
        
    }
    KDNode(int lson, int rson) {
        son[0] = lson;
        son[1] = rson;
    }    
    
};
    
class Solver{
    
    typedef KDNode Node;
private:
    int n, m; 
    int node_idx;
    int root;
    Node node[10500010];
    int build(Point xi, Point xj) {
        int nd;
        nd = node_idx++;
        node[nd].ri = xi; node[nd].rj = xj;
        if (xj == xi) {
            return nd;
        }
        int dim; Point mid;
        dim = xj[0] - xi[0] < xj[1] - xi[1];
        mid = xj;
        mid[dim] = xi[dim] + xj[dim] >> 1;
        node[nd].son[0] = build(xi, mid);
        mid = xi;
        mid[dim] = (xi[dim] + xj[dim] >> 1) + 1;
        node[nd].son[1] = build(mid, xj);
        return nd;
    }
    char inRange(Point xi, Point xj, Point ri, Point rj) { //-1 完全不在; 0 部分在; 1 完全在 
        int i;
        for (i = 0; i < 2; i++) {
            if (xi[i] > rj[i] || xj[i] < ri[i]) {
                return -1;
            }
        }
        for (i = 0; i < 2; i++) {
            if (!(ri[i] <= xi[i] && xj[i] <= rj[i])) {
                return 0;
            }
        }
        return 1;
    }
    void inline update(int nd) {
        node[nd].val = max(node[node[nd].son[0]].val, node[node[nd].son[1]].val);
    }
    void pushSig(int nd) {
        int sig, son, i;
        if (sig = node[nd].sig) {
            node[nd].sig = 0;
            for (i = 0; i < 2; i++) {
                son = node[nd].son[i];
                node[son].sig += sig;
                node[son].val += sig;
            }
        }
    }    
    void change(int nd, Point xi, Point xj, int val) {
//        cnt++;
        int t;
        t = inRange(node[nd].ri, node[nd].rj, xi, xj);
        if (t == -1) {
            return;
        }
        if (t == 1) {
            node[nd].sig += val;
            node[nd].val += val;
            return;
        }
        pushSig(nd);
        change(node[nd].son[0], xi, xj, val);
        change(node[nd].son[1], xi, xj, val);
        update(nd);
    }
    int query(int nd, Point xi, Point xj) {
//        cnt++;
        int t;
        t = inRange(node[nd].ri, node[nd].rj, xi, xj);
        if (t == -1) {
            return -INF;
        }
        if (t == 1) {
            return node[nd].val;
        }
        pushSig(nd);
//        if (max(query(node[nd].son[0], xi, xj), query(node[nd].son[1], xi, xj)) > node[nd].val) {
//            cerr<<"Wa";
//        }
        return max(query(node[nd].son[0], xi, xj), query(node[nd].son[1], xi, xj));
    }
public:      
    void setSize(int new_n, int new_m) {
        n = new_n;
        m = new_m;
    }
    void build() {
        root = build(Point(1, 1), Point(n, m));
    }

    void change(int xi, int yi, int xj, int yj, int val) {
        xi = max(xi, 1); xj = min(xj, n);
        yi = max(yi, 1); yj = min(yj, m);        
        if (xi > n || xj < 1 || yi > m || yj < 1) {
            return;
        }
        cnt = 0;
        change(root, Point(xi, yi), Point(xj, yj), val);
//        cerr<<"change "<<cnt<<endl;
    }
    
    int query(int xi, int yi, int xj, int yj) {
//        cnt = 0;
        int ret = query(root, Point(xi, yi), Point(xj, yj));
//        cerr<<"query "<<cnt<<endl;
        return ret;
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
    int x_base, y_base;
    
    void read(int &x, int &y) {
        read(x); read(y);
        x -= x_base; y -= y_base;
    }
    _Main (){
        
        int i, j, k;
        int x, y;
        
        int Q, Qn;
        int a, b;
        int Qtype;
        int xi, yi, xj, yj, ri, pi;
        
        read(Qn);
        read(x_base); read(y_base);
        x_base--; y_base--;
        read(x); read(y);
        x = x - x_base;
        y = y - y_base;
        solver.setSize(x, y);
        solver.build();
        for (Q = 1; Q <= Qn; Q++) {
            read(Qtype);
            switch (Qtype) {
                case 0: {
                    read(xi, yi); read(xj, yj);
                    printf("%d\n", max(solver.query(xi, yi, xj, yj), 0));
                	break;
                }
                
                case 1: {
                    read(xi, yi);
                    read(ri); read(pi);
                    ri--;
                    if (ri == 0) {
                        solver.change(xi, yi, xi, yi, pi);
                    } else {
                        xj = xi + ri; yj = yi + ri;
                        xi = xi - ri; yi = yi - ri;
                        solver.change(xi, yi, xj, yj, pi);
                        solver.change(xi, yi - 1, xj, yi - 1, pi >> 2);//上
                        solver.change(xi, yj + 1, xj, yj + 1, pi >> 2);//下 
                        solver.change(xi - 1, yi, xi - 1, yj, pi >> 2);//左 
                        solver.change(xj + 1, yi, xj + 1, yj, pi >> 2);//右 
                    }
                	break;
                }
                
                case 2:{
                    read(xi, yi); read(xj, yj);
                    read(pi);
                    solver.change(xi, yi, xj, yj, -pi);
                	break;
                }
                
            }
            
        }
        
        
    }
    
    
    
        
}std;












}
