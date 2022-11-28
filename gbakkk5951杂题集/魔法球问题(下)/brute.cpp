using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
namespace OI {
typedef long long lld;
const lld MOD = 1e9;
class Long {
private:
    int high;
    lld num[60010];
public:    
    void read() {
        char *buf = new char[200020];
        memset(buf, 0, 200020 * sizeof(char));
        int i, j, len, base;
        scanf("%s", buf);
        len = strlen(buf);
        
        for (i = 0; i * 9 < len; i++) {
            base = len - i * 9 - 1;
            for (j = min(8, base); j >= 0; j--) {
                num[i] *= 10;
                num[i] += buf[base - j] - '0';
            }
        }
        high = i - 1;
        delete buf;
    }
    void zero() {
        memset(num, 0, (high + 2) * sizeof(lld));
        high = 0;
    }
    void power() {
        lld * ans = new lld[60010];
        memset(ans, 0, 60010 * sizeof(lld));
        int i, j;
        for (i = 0; i <= high; i++) {
            for (j = 0; j <= high; j++) {
                ans[i + j + 1] += ans[i + j] / MOD;
                ans[i + j] %= MOD; 
                ans[i + j] += num[i] * num[j];
                ans[i + j + 1] += ans[i + j] / MOD;
                ans[i + j] %= MOD;                 
            }
        }
        memcpy(num, ans, sizeof(num));
        delete ans;
        for (i = high * 2 + 2; num[i] == 0 && i > 0; i--) {
            if (num[i]) {
                break;
            }
        }
        high = i;

    }
    void add1() {
        int i;
        for (i = 0; num[i] == MOD - 1; i++) {
            num[i] = 0;
        }
        num[i]++;
        high = max(high, i);
    }
    void minus1() {
        int i;
        for (i = 0; num[i] == 0; i++) {
            num[i] = MOD - 1;
        }
        num[i]--;     
    }
    void div2() {
        int i, r = 0;
        for (i = high; i >= 0; i--) {
            num[i] += r * MOD;
            r = num[i] & 1;
            num[i] /= 2;
        }
    }
    void print() {
        int i;
        for (i = high + 1; i > 0 && num[i] == 0; i--);
        printf("%lld", num[i]);
        for (i--; i >= 0; i--) {
            printf("%09lld", num[i]);
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
