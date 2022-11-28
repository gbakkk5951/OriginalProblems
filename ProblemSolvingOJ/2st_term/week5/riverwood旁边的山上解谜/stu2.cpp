#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5;
int num1[N] = {0}, num2[N] = {0};
int maxx[N] = {0}, max2 = 0;                                  //最小进位
int minn[N] = {0}, min2 = 0, min3 = 0;                        //最小不进位,最大倒序且不进位
int n = 0, k = 0, flag1 = 0, flag2 = 0, sign1 = 0, sign2 = 0; // sign表示跳过输出
void findlarge(){
    if (flag1 != 0 && flag2 != 0 && flag2 > max2){
        num1[flag2] = 0;
    }
    else{
        if (max2 == 0){
            num1[2] += num1[1];
            sign1 = 1;
            num1[sign1] = 0;
        }
        else{
            for (int j = n; j > max2; j--){
                if (num1[j] + num1[max2] >= k){
                    num1[j] = (num1[j] + num1[max2]) % k;
                    num1[max2] = 1;
                    break;
                }
            }
        }
    }
}
void findsmall(){
    // todo
    if (min2 == 0){
        num2[2] = (num2[1] + num2[2]) % k;
        num2[1] = 1;
    }
    else{
        if (min3 != 0){
            for (int i = n; i > min3 + 1; i--){
                if (num2[min3] + num2[i] < k){
                    sign2 = min3;
                    num2[i] += num2[min3];
                    num2[min3] = 0;
                    break;
                }
            }
        }
        if (sign2 == 0){
            for (int i = n; i > min2; i--){
                if (num2[min2] + num2[i] < k){
                    sign2 = min2;
                    num2[i] += num2[min2];
                    num2[min2] = 0;
                    break;
                }
            }
        }
    }
}
int main(){
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++){
        scanf("%d", &num1[i]);
        num2[i] = num1[i];
    }
    minn[n + 1] = k;
    for (int i = n; i >= 1; i--){
        maxx[i] = max(num1[i], maxx[i + 1]);
        minn[i] = min(num1[i], minn[i + 1]);
        if ((num1[i] + maxx[i + 1] >= k) && max2 == 0){
            max2 = i;
        }
        if ((num2[i] + minn[i + 1] < k) && i != n && min2 == 0){
            min2 = i; //最低不进位
        }
        if (num1[i] == 1){
            flag1 = i;
        }
        if ((flag2 == 0) && (num1[i] == k - 1)){
            flag2 = i;
        }
        if (i != n && num1[i] > num1[i + 1] && (minn[i + 1] + num1[i]) < k){
            min3 = i; //最高倒序不进位
        }
    }
    findlarge();
    int begin1 = 1, begin2 = 1;
    for (int i = 1; num1[i] == 0; i++){//去零
        begin1++;
    }
    for (int i = begin1; i <= n; i++){
        if (i == sign1)
            continue;
        printf("%d ", num1[i]);
    }
    printf("\n");
    findsmall();
    for (int i = 1; num2[i] == 0; i++){//去零
        begin2++;
    }
    for (int i = begin2; i <= n; i++){
        if (i == sign2)
            continue;
        printf("%d ", num2[i]);
    }
    return 0;
}
