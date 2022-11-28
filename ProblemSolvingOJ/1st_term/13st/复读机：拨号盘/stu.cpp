/*#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int a[22][22];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            if (i < j && !((a[i][j] - i) * (a[i][j] - j))) {
                printf("%d %d\n", i, j);
            }
        }
    }
}*/
#include <stdio.h>
/*
 1
8
1 1 1 1 1 1 1 1
0 1 0 0 1 1 0 1
0 0 1 0 1 0 1 1
0 0 0 1 0 1 0 1
0 0 0 0 1 0 0 1
0 0 0 0 0 1 0 1
0 0 0 0 0 0 1 1
0 0 0 0 0 0 0 1
 */
int main(void) {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int n;
        scanf("%d", &n);
        int a[50][50] = {0};
        int vhash[50] = {0};
        for (int i = 0; i < n; i++) {
            int j;
            scanf ("%d", &j);
            a[i][j - 1] = 1;
        }

        int flag = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    if ((i - j) * (i - k) * (j - k) && a[i][j] && a[j][k] && a[k][i]) {
                        flag = 1;
                        break;
                    }
        if (flag) {
            printf("N\n");
            continue;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) {
                if (a[i][j] * a[j][i]) {
                    for (int k = 0; k < n; k++) {
                        a[j][k] += a[i][k];
                        a[k][j] += a[k][i];
                        a[i][k] = 0;
                        a[k][i] = 0;
                        vhash[i] = 1;
                    }
                }
            }

        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("vhash:%d", vhash[i]);
            printf("\n");
        }*/
        int sumflag = 0;
        for (int i = 0; i < n; i++) {
            if (vhash[i]){
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (vhash[j] || i == j) {
                    continue;
                }
                int x[50], count = 0;
                for (int k = 0; k < n; k++) {
                    if (a[i][k] * a[j][k]) {
                        x[count++] = k;
                    }
                }
                int countsup = 0;
                for (int k = 0; k < count; k++) {
                    int flag = 0;
                    for (int l = 0; l < count; l++) {
                        if (l != k && a[x[l]][x[k]]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        countsup++;
                    }
                }
                //printf("countsup: %d\n", countsup);
                if (countsup > 1) {
                    sumflag = 1;
                }

                count = 0;
                for (int k = 0; k < n; k++) {
                    if (a[k][i] * a[k][j]) {
                        x[count++] = k;
                    }
                }
                int countinf = 0;
                for (int k = 0; k < count; k++) {
                    int flag = 0;
                    for (int l = 0; l < count; l++) {
                        if (l != k && a[x[k]][x[l]]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        countinf++;
                    }
                }
                //printf("countinf: %d\n", countinf);
                if (countinf > 1) {
                    sumflag = 1;
                }
            }
        }
        if (!sumflag) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    return 0;
}
