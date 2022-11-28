#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L, sum, num;
int n, m, an, x;
lld get_random() {
	return A = C + (A * B) % MOD;
}
int a[maxn];

int Paratition(int p,int r)
{
    int key = a[r];
    //cout << key << " ";
    int i = p - 1;
    sum = 0, num = 1;
    for(int j = p; j < r; j++){
        if(a[j] < key)
        {
            i++;
            sum += a[j];
            swap(a[i],a[j]);
        }
        if (a[j] == key)
            num++;
    }
    //cout << sum << endl;
    swap(a[i+1],a[r]);
    return i+1;
}

int RandomParatition(int p,int r)
{
    int x = (p + r) / 2;
    swap(a[x],a[r]);  
    return Paratition(p,r);
}

int RandomziedSelect(int p,int r, lld lim)
{
    if (p == r){
        if (a[p] <= lim) return p;
        else return p - 1;
    }
    int q = RandomParatition(p,r);  
    if (sum <= lim && sum + num *(lld) a[q] > lim) 
    {
       for (int i = 1; i <= num; ++i)
           if (sum + (lld)i *a[q] > lim)
               return q + i - 2;
    }
    if (sum + a[q] == lim) 
        return q;
    else if (sum + a[q] > lim){
        if (p < q) return RandomziedSelect(p, q - 1,lim);
        else return q - 1;
    }
    else{
        if (q < r) return RandomziedSelect(q + 1,r,lim - sum - a[q]);
        else return q;
    }
}

int main() 
{
	cin >> n >> A >> B >> C >> MOD >> L;
    m = 0, an = 0;
	for (int i = 1; i <= n; ++i) {
        x = get_random();
        if (x <= 0) {L -= x; m++;}
        else a[++an] = x;
    }
    //cout << an;
    //for (int i = 1; i <= 10; ++i) cout << a[i] << " ";
    //cout << endl;
    if (L < 0) {cout << 0; return 0;}
    else if (L == 0) {cout << m; return 0;}
    else{
        if (!an) {cout << m; return 0;}
        else {cout << m + RandomziedSelect(1, an, L); return 0;}
    }
}
//18000000 10000 -1 0 18000000
//90000000000
