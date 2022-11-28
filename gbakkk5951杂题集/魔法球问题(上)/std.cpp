using namespace std;
int main() {}
#include <cstdio>
#include <algorithm>

struct _Main {
    int ans[1005][1005];
    int inline pf(int a) {
        return a * a;
    }
    void odd_way(int x, int y, int n) {
        int i, j, k;
        int now = (pf(n + 1) >> 1) - 1;
        while (1) {
            if (n == 1) {
                ans[x][y] = 1;
                return; 
            } 
            for (i = y + n - 1; i >= y; i--) {
                ans[x][i] = now--;
            }
            for (i = y; i <= y + n - 1; i++) {
                ans[x + 1][i] = now--;
            }
            x = x + 2;
            y = y + 1;
            n = n - 2;
        }
    }
    //x 为横坐标 y 为纵坐标 
    void even_way(int x, int y, int n) {
        int now = (pf(n + 1) >> 1) - 1;
        int i;
        for (i = 1; i <= y + n - 1; i++) {
            ans[x][i] = now--;
        }
        odd_way(x + 1, y, n - 1);
    }
    _Main() {
        int n;
        scanf("%d", &n);
        int i, j, k;
        if (n & 1) {
            odd_way(1, 1, n);
            for (i = n; i >= 1; i--) {
                for (j = 1; ans[j][i]; j++) {
                    printf("%d ", ans[j][i]);
                }
                printf("\n");
            }                
        } else {
            even_way(1, 1, n);
            for (i = 1; i <= n; i++) {
                for (j = 1; ans[j][i]; j++) {
                    printf("%d ", ans[j][i]);
                }
                printf("\n");
            }
        }
        
        
    }    
    
}mogic_1s;


