#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxN = 2e6 + 5;
struct node {
    int typ;
    ll val;
    node() {}
    node(ll x) { typ = x; val = 0; }
    node(ll x, ll y) { typ = x; val = y; }
};
ll N, M, pos, type, Typ[maxN];
ll t2, maxn, Val[maxN];
int main()
{
    deque<node> q;
    cin >> N >> M;
    if (N == 0) printf("0\n");
    for (int i = 1; i <= N; ++i) scanf("%d", &Typ[i]);
    for (int i = 1; i <= N; ++i) scanf("%lld", &Val[i]);
    for (int i = 1; i <= M + N; ++i) {
        if (i <= N) { type = Typ[i]; pos = 1; t2 = Val[i]; }
        else { scanf("%d%d%lld", &pos, &type, &t2); }
        node* n = new node(type, t2);
        if (pos == 0) q.push_front(*n);
        else q.push_back(*n);
        if (type == 2 && pos == 0) {
            if (q.size() == 1) maxn = t2;
            else {
                if (q[1].typ == 2) { q[1].val += t2; q.pop_front(); }
                maxn = max(maxn, q[0].val);
            }
        }
        else if (type == 2 && pos == 1) {
            if (q.size() == 1) maxn = t2;
            else {
                if (q[q.size() - 2].typ == 2) { q[q.size() - 2].val += t2; q.pop_back(); }
                maxn = max(maxn, q[q.size() - 1].val);
            }
        }
        else if (type == 0 && pos == 0) {
            ll j, flag = 0, aim = 0;
            for (j = 1; j < q.size() && j <= 2; ++j)
                if (q[j].typ == 1) { flag = 1; aim = j; break; }
            if (flag) {
                if (j + 1 < q.size() && q[j + 1].typ == 2) aim = j + 1;
                for (int k = 0; k < aim; ++k) q[aim].val += q[k].val;
                q[aim].typ = 2;
                for (int k = 0; k < aim; ++k)
                    q.pop_front();
                maxn = max(maxn, q[0].val);
            }
        }
        else if (type == 1 && pos == 1) {
            ll j, flag = 0, aim = 0;
            for (j = q.size() - 2; j >= 0 && j >= q.size() - 3; --j)
                if (q[j].typ == 0) { flag = 1; aim = j; break; }
            if (flag) {
                if (j - 1 >= 0 && q[j - 1].typ == 2) aim = j - 1;
                for (int k = q.size() - 1; k > aim; --k) q[aim].val += q[k].val;
                q[aim].typ = 2;
                for (int k = q.size() - 1; k > aim; --k)
                    q.pop_back();
                maxn = max(maxn, q[q.size() - 1].val);
            }
        }
        if (i >= N) printf("%lld\n", maxn);
    }

    //for (int i = 0; i < q.size(); ++i) cout << q[i].typ << " ";
    //cout << endl;
    //for (int i = 0; i < q.size(); ++i) cout << q[i].val << " ";

}

