using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <vector>
namespace Protector {
const int INF = 0x3f3f3f3f;
class SegmentTree {
private:
    vector<int>node;
    int base;
    int n;
public:
    int setSize(int new_size) {
        n = new_size;
    }
    void build() {
        for (base = 1; base < n + 2; base <<= 1);
        node.resize((base << 1) + 2);
    }
    int getMax(int s, int t) {
        int lans = -INF, rans = -INF;
        for (s += base - 1, t += base + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
            lans +=node[s]; rans+=node[t];
            if (~s & 1) {
                lans = max(lans, node[s ^ 1]);
            }
            if ( t & 1) {
                rans = max(rans, node[t ^ 1]);
            }
        }
        lans = max(lans + node[s], rans + node[t]);
        for (s >>= 1; s; s >>= 1) {
            lans += node[s];
        }
        return lans;
    }
    void change(int s, int t, int val) {
        int a;
        for (s += base - 1, t += base + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
            if (~s & 1) {
                node[s ^ 1] += val;
            }
            if ( t & 1) {
                node[t ^ 1] += val;
            }
            a = max(node[s], node[s ^ 1]);
            if (a) {
                node[s] -= a; node[s ^ 1] -=a; node[s >> 1] += a; 
            }
            a = max(node[t], node[t ^ 1]);
            if (a) {
                node[t] -= a; node[t ^ 1] -=a; node[t >> 1] += a;   
            }   
        }
        for ( ; s > 1; s >>= 1) {
            a = max(node[s], node[s ^ 1]);
            if (a) {
                node[s] -= a; node[s ^ 1] -=a; node[s >> 1] += a;
            }      
        }
    }
    
};
    
class Solver{
private:
    int n, m; 
    SegmentTree tree[2005];   
public:      
    void setSize(int new_n, int new_m) {
        n = new_n;
        m = new_m;
    }
    void build() {
        int i;
        for (i = 1; i <= n; i++) {
            tree[i].setSize(m);
            tree[i].build();
        }
    }
    void change(int xi, int yi, int xj, int yj, int val) {
        xi = max(xi, 1); yi = max(yi, 1);
        xj = min(xj, n); yj = min(yj, m);
        if (xi > n || xj < 1 || yi > m || yj < 1) {
            return;
        }
        int i;
        for (i = xi; i <= xj; i++) {
            tree[i].change(yi, yj, val);
        }
    }
    int query(int xi, int yi, int xj, int yj) {
        int ans = -INF;
        int i;
        for (i = xi; i <= xj; i++) {
            ans = max(ans, tree[i].getMax(yi, yj));  
        }
        return ans;
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
    char swp_sig = 0;
    int x_base, y_base;
    
    void read(int &x, int &y) {
        read(x); read(y);
        if (swp_sig) {
            swap(x, y);
        }
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
        if (x > y) {
            swp_sig = 1;
            swap(x, y);
            swap(x_base, y_base);
        }
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
    
    
    
        
}brute;












}
