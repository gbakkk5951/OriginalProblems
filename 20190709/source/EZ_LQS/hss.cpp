#include<bits/stdc++.h>
using namespace std;
int n, m;
char ch;
int a[2000010];
int h[2000010], s[2000010];
struct node{
    int num, len, bef, nxt;
}q[2000010];
int head, tail, tot, x;
int main(){
    freopen("hss.in", "r", stdin);
    freopen("hss.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        scanf(" %c", &ch);
        if(ch=='h'){
            if(s[0]==0){
                a[i] = 1;
                h[0]++;
                h[h[0]] = i;
            }
            else{
                a[i] = 0;
                a[s[s[0]]] = 0;
                s[0]--;
            }
        }
        else if(ch=='s'){
            s[0]++;
            a[i] = -1;
            s[s[0]] = i;
        }
    }
    int maxi = 0;
    q[++tot].num = a[1];
    q[tot].len = 1;
    for (int i = 2; i <= n;i++){
        if(a[i]==q[tot].num){
            q[tot].len++;
        }
        else{
            q[tot].nxt = tot + 1;
            q[++tot].num = a[i];
            q[tot].bef = tot - 1;
            q[tot].len = 1;
        }
        if (q[tot].num == 0 && q[tot].len > maxi)
            maxi = q[tot].len;
    }
    printf("%d\n", maxi);
    while(m--){
        scanf("%d %c", &x, &ch);
        // if(x==1){
        //     if(ch=='s'){
        //         if(h[0]==0&&hh[0]==0){
        //             aa[++tot] = -1;
        //             if(q[head].num==-1){
        //                 q[head].len++;
        //                 aap[tot] = head;
        //             }
        //             else{
        //                 q[head].bef = ++toti;
        //                 q[toti].nxt = head;
        //                 aap[tot] = toti;
        //                 head = toti;
        //                 q[toti].num = -1;
        //                 q[toti].len = 1;
        //             }
        //         }
        //         else if(hh[0]!=0){
        //             aa[hh[hh[0]]] = 0;
        //             hh[0]--;
        //             aa[++tot] = 0;
        //             if(q[head].num==0){
        //                 q[head].len++;
        //                 aap[tot] = head;
        //             }
        //             else{
        //                 q[head].bef = ++toti;
        //                 q[toti].nxt = head;
        //                 aap[tot] = toti;
        //                 head = toti;
        //                 q[toti].num = 0;
        //                 q[toti].len = 1;
        //             }
        //         }
        //         else{
        //             a[h[hhead]] = 0;
        //             if (a[h[hhead] + 1] == 0 && a[h[hhead] - 1] == 0){

        //             }
        //                 hhead++;
        //         }
        //     }
        // }
        printf("%d\n", maxi);
    }
}
