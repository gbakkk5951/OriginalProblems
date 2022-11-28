#include <stdio.h>

int n, m[1000], v[1000000], sum[1000];

int overflow(int l, int r);
int w(int x, int l, int r);
int overwrite(int l0, int r0, int l1, int r1);
void memset();
void strcpy();
void __strlen();
int main(void) {
    //printf("haha~\n");
    scanf("%d", &n);
    //printf("%d", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m[i]);
        sum[i + 1] = sum[i] + m[i];
    }
    //printf("haha~\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m[i]; j++) {
            scanf("%d", &v[sum[i] + j]);
        }
    }
    //printf("haha~\n");
    int K;
    scanf("%d", &K);
    for (int k = 1; k <= K; k++) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            memset();
        } else if (op == 1){
            strcpy();
        } else {
            __strlen();
        }
    }
    return 0;
}
int overflow(int l, int r) {
    if (l < 0 || l >= sum[n]) {
        printf("overflow\n");
        return 1;
    }
    if (r < 0 || r >= sum[n]) {
        printf("overflow\n");
        return 1;
    }
    return 0;
}
int w(int x, int l, int r) {
    if (l < sum[x] || l >= sum[x + 1]) {
        return 1;
    }
    if (r < sum[x] || r >= sum[x + 1]) {
        return 1;
    }
    return 0;
}
int find(int id) {
    while(id < sum[n] && id >= 0) {
        if (!v[id]) {
            break;
        }
        id++;
    }
    return id;
}
void memset() {
    int x, y, val, cou;
    scanf("%d%d%d%d", &x, &y, &val, &cou);
    if (!cou) {
        printf("true\n");
        return ;
    }
    if(overflow(sum[x] + y, sum[x] + y + cou - 1)) {
        return ;
    }
    if (w(x, sum[x] + y, sum[x] + y + cou - 1)) {
        printf("w");
    }
    for (int i = 0; i < cou; i++) {
        v[sum[x] + y + i] = val;
    }
    printf("true\n");
}
int overwrite(int l0, int r0, int l1, int r1) {
    if (l1 >= l0 && l1 <= r0) {
        printf("overwrite\n");
        return 1;
    }
    if (r1 >= l0 && r1 <= r0) {
        printf("overwrite\n");
        return 1;
    }
    return 0;
}
void strcpy() {
    int x[2], y[2];
    scanf("%d%d%d%d", &x[0], &y[0], &x[1], &y[1]);

    int l[2];
    for (int i = 0; i < 2; i++) {
        l[i] = sum[x[i]] + y[i];
    }
    int r[2];
    r[0] = find(l[0]);
    int len = r[0] - l[0] + 1;
    r[1] = l[1] + len - 1;
    for (int i = 0; i < 2; i++) {
        if (overflow(l[i], r[i])) {
            return;
        }
    }

    if (overwrite(l[0], r[0], l[1], r[1])) {
        return ;
    }

    int flagw = 0;
    for (int i = 0; i < 2; i++) {
        if (w(x[i], l[i], r[i])) {
            flagw = 1;
        }
    }
    if (flagw) {
        printf("w");
    }

    for (int i = 0; i < len; i++) {
        v[l[1] + i] = v[l[0] + i];
    }
    printf("true\n");
}
void __strlen() {
    int x, y;
    scanf("%d%d", &x, &y);
    int l = sum[x] + y;
    int r = find(l);
    if (overflow(l, r)) {
        return ;
    }
    if (w(x, l, r)) {
        printf("w");
    }
    printf("%d\n", r - l);
}
