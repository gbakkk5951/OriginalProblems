#include<iostream>
using namespace std;
int maxN(0); 
const int space(1000 + 15);
char AString[space] = {0};
int Index[space];

int FlagDetermine(int s, int plus){
    int index = Index[s] + plus;
    if (index < 0 || index >= maxN )
        return 2;
    else if (index < Index[s] || index >= Index[s + 1])
        return 1;
    else 
        return 0;
}

void MyMemset(int a, int b, char c, int d) {
    int flag(0);
    for (int i = b; i < b + d; i++) {
        if (flag < FlagDetermine(a, i))
            flag = FlagDetermine(a, i);
        }
        if (flag == 2) {
            printf("overflow\n");
            return;
        }
        else {
            for (int i = Index[a] + b; i < Index[a] + b + d; i++) {
                AString[i] = c;
        }
        if (flag == 1) printf("w");
        printf("true\n");
    }
}

void MyStrcpy(int a, int b, int c, int d) {
    int flag(0);
    int end_1(0);
    for(int i = 0; 1; i++){
        if (flag < FlagDetermine(a, b + i)){
            flag = FlagDetermine(a, b + i);
        }
        if (flag == 2) {
            printf("overflow\n");
            return;
        }
        if (AString[Index[a] + b + i] == '0') {
            end_1 = Index[a] + b + i;
            break;
        }
    }
    for (int i = 0; Index[a] + b + i <= end_1; i++){
        if (flag < FlagDetermine(c, d + i)){
            flag = FlagDetermine(c, d + i);
        }
        if (flag == 2) {
            printf("overflow\n");
            return;
        }
    }
    if (Index[c] + d >= Index[a] + b && Index[c] + d <= end_1){
        printf("overwrite\n");
        return;        
    }
    for (int i = 0; Index[a] + b + i <= end_1; i++){
        AString[Index[c] + d + i] = AString[Index[a] + b + i];
    }
    if (flag == 1) printf("w");
    printf("true\n");
}

void MyStrlen(int a, int b) {
    int flag(0);
    for(int i = 0; 1; i++){
        if (flag < FlagDetermine(a, b + i)){
            flag = FlagDetermine(a, b + i);
        }
        if (flag == 2) {
            printf("overflow\n");
            break;
        }
        if (AString[Index[a] + b + i] == '0') {
            if (flag == 1) printf("w");
            printf("%d\n", i);
            break;
        }
    }
}

int main() {
    int n(0), m(0);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        maxN += m;
        Index[i] = maxN - m;
    }
    Index[n] = maxN;
    getchar();
    for (int i = 0; i < n; i++) {
        for (int j = Index[i]; j < Index[i + 1]; j++){
            scanf("%c", &AString[j]);
            getchar();
        }
    }
    int k(0), opt(0);
    int a(0), b(0), c(0), d(0);
    bool warning(0), overflow(0);
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &opt);
        switch (opt) {
            case 0:
                scanf("%d%d %c%d", &a, &b, &c, &d);
                MyMemset(a, b, c, d);
                break;
            case 1:
                scanf("%d%d%d%d", &a, &b, &c, &d);
                MyStrcpy(a, b, c, d);
                break;
            case 2:
                scanf("%d%d", &a, &b);
                MyStrlen(a, b);
                break;
            default:
                break;
        }
    }
    return 0;
}
