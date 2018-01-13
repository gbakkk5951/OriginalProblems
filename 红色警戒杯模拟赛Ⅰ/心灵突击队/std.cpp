using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <vector>
namespace Protector {
const int INF = 0x3f3f3f3f;
struct Point {
    int x[2];
    int& operator [] (int a) {
        return x[a];
    }
};

struct KDNode{
    int son[2];
    int dim;
    int val, sig;
    KDNode(){
        
    }
    KDNode(int lson, int rson, int new_dim) {
        dim = new_dim;
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
    vector<Node> node;
    int build(int nd, Point xi, Point xj) {
        int mxdim;
        node.push_back(Node());
        nd = node_idx++;
        if (xj == xi && yj == yi) {
            return nd;
        }
        node.push
        node.push_back(Node(build())); 
    }
    
public:      
    void setSize(int new_n, int new_m) {
        n = new_n;
        m = new_m;
    }
    void build() {
        root = build(1, 1, 1, n, m);
        
    }
    void change(int xi, int yi, int xj, int yj, int val) {
        
        
    }
    int query(int xi, int yi, int xj, int yj) {
        
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
                        xj = xi + ri; yj = xi + ri;
                        xi = xi - ri; yi = xi - ri;
                        solver.change(xi, yi, xj, yj, pi);
                        solver.change(xi, yi - 1, xj, yi - 1, pi >> 2);//ио
                        solver.change(xi, yj + 1, xj, yj + 1, pi >> 2);//об 
                        solver.change(xi - 1, yi, xi - 1, yj, pi >> 2);//вС 
                        solver.change(xj + 1, yi, xj + 1, yj, pi >> 2);//ср 
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
