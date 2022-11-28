#include <iostream>
#include <cmath>
#define ll long long

using namespace std;

const int N = 1e6;
const int M = 998244353;

int map[N + 5];
int visit[N + 5], path[N + 5];
int cir[N + 5];
int jud[N + 5];
int m;
int cnt;

const int len = 1000;
int prime[1000];
int p[1000];
int t[1000];//times
int store[N+ 5];

int prime_set() {
    for (int i = 2; i < len; i++) {
        if (prime[i] == 0) {
            for (int j = 2 * i; j < len; j += i) {
                prime[j] = 1;
            }
        }
    }
    int j = 2;
    int id = 0;
    while (j < len) {
        if (prime[j] == 0) {
            p[id] = j;
            id++;
        }
        j++;
    }
    return id;
}

void clear(int n){
    for (int i = 0; i <= n; i++){
        map[i] = path[i] = cir[i] = jud[i] = visit[i] = 0;
    }
    for (int i = 0; i < len; i++){
        t[i] = 0;
    }
}

void dfs(int k)
{
    visit[k] = 1;
    path[m++] = k;
    if (visit[map[k]] == 0)
    {
        dfs(map[k]);
    }
    if (visit[map[k]] == 1)
    {
        int tmp = 0;
        for (int j = m - 1;; j--)
        {
            tmp++;
            if (path[j] == map[k])
            {
                if (jud[tmp]) {
                    ;
                }
                else {
                    
                    jud[tmp] = 1;
                    cir[cnt] = tmp;
                    cnt++;
                }
                break;
            }
        }
    }
    visit[k] = -1;
    m--;
}

int main()
{
    int T;
    int n;
    scanf("%d", &T);
    int len_p = prime_set();
    while (T--) {
        cnt = 0;
        m = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &map[i]);
            if (map[i] == i){
                visit[i] = -1;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (visit[i] != -1)
                dfs(i);
        }
        int idx = 0;
        for (int j = 0; j < cnt; j++) {
            int tmp = cir[j];
            for (int k = 0; k < len_p && tmp > 1; k++) {
                if (tmp % p[k])
                    continue;
                else {
                    int cn = 0;
                    while (tmp % p[k] == 0) {
                        tmp /= p[k];
                        cn++;
                    }
                    t[p[k]] = max(cn, t[p[k]]);
                }
            }
            if (tmp > 1){
                store[idx] = tmp;
                idx++;
            } 
        }
        
        ll ans = 1;
        for (int j = 0; j < len_p; j++) {
            while (t[p[j]]--) {
                ans *= p[j];
                ans %= M;
            }
        }
        for (int j = 0; j < idx; j++){
            ans *= store[j];
            ans %= M;
        }
        printf("%lld\n", ans);
        clear(n);
    }
    return 0;
}

