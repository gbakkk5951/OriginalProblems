#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 998244353;
const int mxn = 4e3 + 10;
int com[mxn][mxn / 2];
// answer = com[(m - 1) + (n + 1) - 1][n];
int main() {
    int n, m;
    cin >> n >> m;
    int from = m - 1 + n + 1 - 1;
    int choose = n;
    for (int i = 0; i <= from; ++i) {
        com[i][0] = 1;
        for (int j = 1; j <= i && j <= choose; ++j) {
            com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
            com[i][j] -= com[i][j] >= p ? p : 0;
        }
    }
    cout << com[from][choose];
}
