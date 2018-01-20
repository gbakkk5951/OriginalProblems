using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>


namespace Protector {
const int 
    NXT = 1,
    DST = 0,
    DIS = 2,
    FLOW = 2,
    COST = 3
;    
struct Dis {
    long long val;
    int dst;
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
                if (node[nd << 1 | 1] < node[chose]) {
                    chose |= 1;
                }
                if (node[nd] > node[chose]) {
                    swap(node[nd], node[chose]);
                    nd = chose;
                } else{
                    break;
                }
            } else {
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
    
    _Main() {
        
        
        
    }
    
    
    
};

}
