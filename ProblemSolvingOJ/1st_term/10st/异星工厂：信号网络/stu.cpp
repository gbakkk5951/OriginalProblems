#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>
typedef unsigned long long ull;
using namespace std;

ull exp[200];

// void print(ull x)
// {
//     for(int i=0;i<64;++i)
//         printf("%d",x&1),x>>=1;

// }

template <typename Type>
void read(Type &a) {
	char t, f = 1;
	while (!isdigit(t = getchar())) {
		if (t == '-') f = -1;
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a *= f;
}
int main()
{
    int N;
    scanf("%d", &N);
    ull high = 0, low = 0;
    exp[0] = 1;
    for (int i = 1; i <= 63; ++i)
        exp[i] = exp[i - 1] << 1;
    while (N--) {
        int op;
		read(op);
        if (op == 1) {
            ull nhigh, nlow;
            int x;
			read(x);
            x = (x % 128 + 128);
            x = x >= 128 ? x - 128 : x;
            if (x == 64)
                nhigh = low, nlow = high;
            else if (x < 64)
                nhigh = (((low & ((exp[x]) - 1)) << (64 - x)) | (high >> x)), nlow = ((low >> x) | ((high & ((exp[x]) - 1)) << (64 - x)));
            else
                x -= 64, nlow = (high >> x) | ((low & ((exp[x]) - 1)) << (64 - x)), nhigh = (low >> x) | ((high & ((exp[x]) - 1)) << (64 - x));
            // printf("-%llu %llu %llu-",low,x,(low >> x) );
            // print(nlow);printf("\n");
            high = nhigh, low = nlow;
        } else if (op == 2) {
            ull ans = low & (exp[16] - 1);
            printf("%X\n", (int)ans);    
        } else {
            int l, r;
			read(l); read(r);
            ++r;
            if (l + 1 <= 64) {
                if (r <= 64) {
                    low ^= exp[r] - exp[l];
                } else {
                    low ^= (exp[64]) - exp[l];
                    r -= 64;
                    high ^= exp[r] - exp[0];
                };
            } else {
                l -= 64, r -= 64;
                high ^= exp[r] - exp[l];
            };
        };
        // print(low);printf("|");print(high);
        // printf("\n");
    };
    return 0;
}
