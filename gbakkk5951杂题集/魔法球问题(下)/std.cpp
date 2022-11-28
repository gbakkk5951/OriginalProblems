using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
namespace OI {
typedef long long lld;

const lld MOD = (479 << 21) + 1;
const lld PHI = MOD - 1;
const lld G = 3;


lld fastpower(lld base, lld pow) {
    lld ret = 1;
    pow = (pow % PHI + PHI) % PHI;
    while (pow) {
        if (pow & 1) {
            ret = ret * base % MOD;
        }
        pow >>= 1;
        base = base * base % MOD;
    } 
    return ret;
}
void moveEle(lld arr[], int len) {
    int i, j, k;
    for (i = 1, j = 0; i < len; i++) {
        for (k = 1; j & len >> k; k++) {
            j ^= len >> k;
        }
        j |= len >> k;
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
}
void NTT (lld arr[], int len, int rev = 0) {
    int i, j, k, mid;
    lld x, y, w;
    lld wn[25];
    moveEle(arr, len);
    if (rev) {
        for (i = 1; 1 << i <= len; i++) {
            wn[i] = fastpower(G, - (PHI >> i));
        }
    } else {
        for (i = 1; 1 << i <= len; i++) {
            wn[i] = fastpower(G, PHI >> i);
        }
    }
    for (i = 1; 1 << i <= len; i++) {
        mid = 1 << i - 1;
        for (j = 0; j < len; j += 1 << i) {
            w = 1;
            for (k = j; k < j + mid; k++) {
                x = arr[k];
                y = arr[k + mid] * w % MOD;
                arr[k] = (x + y) % MOD;
                arr[k + mid] = (x - y) % MOD;
                w = w * wn[i] % MOD;
            }
        }
    }
    if (rev) {
        w = fastpower(len, - 1);
        for (i = 0; i < len ;i++) {
            arr[i] = arr[i] * w % MOD;
        }
    }
    for (i = 0; i < len; i++) {
        if (arr[i] < 0) {
            arr[i] += MOD;
        }
    }
}

class Long {
private:
    int high;
    lld num[540000];
public:    
    void read() {
        char *buf = new char[200010];
        scanf("%s", buf);
        int i;
        high = strlen(buf) - 1;
        for (i = 0; i <= high; i++) {
            num[i] = buf[high - i] - '0';
        }
        delete buf;
    }
    void zero() {
        memset(num, 0, (high + 2) * sizeof(lld));
        high = 0;
    }
    void power() {
        int len, t, i;
        for (len = 1; len < high + high + 2; len <<= 1);
        NTT(num, len);
        for (i = 0; i < len; i++) {
            num[i] = num[i] * num[i] % MOD;
        }
        NTT(num, len, 1);
        for (i = 0, t = 0; i < len; i ++) {
            num[i] += t;
            t = num[i] / 10;
            num[i] %= 10;
        }        
        for (i = len; num[i] == 0 && i > 0; i--) {
            if (num[i]) {
                break;
            }
        }
        high = i;

    }
    void add1() {
        int i;
        for (i = 0; num[i] == 9; i++) {
            num[i] = 0;
        }
        num[i]++;
        high = max(high, i);
    }
    void minus1() {
        int i;
        for (i = 0; num[i] == 0; i++) {
            num[i] = 9;
        }
        num[i]--;     
    }
    void div2() {
        int i, r = 0;
        for (i = high; i >= 0; i--) {
            num[i] += r * 10;
            r = num[i] & 1;
            num[i] /= 2;
        }
    }
    void print() {
        int i;
        for (i = high + 1; i > 0 && num[i] == 0; i--);
        for (; i >= 0; i--) {
            printf("%lld", num[i]);
        }
        printf("\n");
    }
}a;

struct _Main {
    
    _Main() {
        int T, Tn;
        int i, j, k;
        scanf("%d", &Tn);
        for (T = 1; T <= Tn; T++) {
            if (T > 1) {
                a.zero();
            }
            a.read();
            a.add1();
            a.power();
            a.div2();
            a.minus1();
            a.print();
        }
    }
    
    
    
}mogic_2s;

}
