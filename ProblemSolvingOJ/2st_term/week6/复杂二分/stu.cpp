#include <iostream>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L;
int n, m;
int ans;
lld get_random() {
    return A = C + (A * B) % MOD;
}
int a[maxn];
void solve(int l, int r, lld s){
    if (l == r){
        
        if (a[l] <= s){
            ans++;
            //cout << "ans1 " << ans << endl;
        }
        return;
    }
    if (l > r) return;
    int mid = (l + r) >> 1;
    swap(a[r], a[mid]);
    int tmp = a[r];
    int i = l, cnt = 0;
    lld sum = 0;
    for (int j = l; j < r; j++){
        if (a[j] <= tmp){
            sum += a[j];
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[i], a[r]);
    if (sum > s)
        solve(l, i - 1, s);
    else{
        s -= sum;
        ans += i - l;
        //cout << "ans2 " << ans << endl;
        if (s >= a[i]){
            
            ans++;
            //cout << "ans3 " << ans << endl;
            s -= a[i];
            solve(i + 1, r, s);
        }
        else return;
    }
}
int main() {
    cin >> n >> A >> B >> C >> MOD >> L;
    int cnt = 0;
    for (int i = 1; i <= n; ++i){
        a[i] = get_random();
        if (a[i] <= 0){
            cnt++;
            L -= a[i];
            i--;
            n--;
        }
    }
    
    if (L < 0)
    {
        cout << 0;
        return 0;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] == a[1]) sum++;
    if (sum == n && n)
    {
        cout << cnt + L / a[1];
        return 0;
    }
    solve(1, n, L);
    cout << ans + cnt;
    return 0;
}


