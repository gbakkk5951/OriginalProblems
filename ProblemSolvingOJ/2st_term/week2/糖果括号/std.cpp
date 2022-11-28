#include <bits/stdc++.h>
using namespace std;
struct ele {
	int type;
	long long v;
};
deque<ele> q;
void eraser() {
	q.pop_back();
}
void erase() {
	q.pop_front();
}
auto beg() {
	return q.begin();
}
auto rbeg() {
	return q.rbegin();
}
long long ans = 0;
template <typename iterator>
void chk(iterator (*getbeg) (), void (*erase) (), int l, int r) {
	long long sum;
	while (q.size() > 1) {
		iterator beg = getbeg();
		if (beg->type == 2 && (beg + 1)->type == 2 || beg->type == l && (beg + 1)->type == r) {	
			*(beg + 1) = (ele) {2, beg->v + (beg + 1)->v};
			erase();
	 	} else
		if (q.size() > 2 && beg->type == l && (beg + 1)->type == 2 && (beg + 2)->type == r) {
			*(beg + 2) = (ele) {2, beg->v + (beg + 1)->v + (beg + 2)->v};
			erase();
			erase();
		} else {
			break;
		}
	}
	if (getbeg()->type == 2) ans = max(ans, getbeg()->v);
}
const int MXN = 1e6 + 10;
int t[MXN];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		cin >> t[i];
	}
	long long v;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &v);
		q.push_back((ele) {t[i], v});
		chk(rbeg, eraser, 1, 0);
	}
	printf("%lld\n", ans);
	for (int i = 1, t, p; i <= m; ++i) {
		scanf("%d%d%lld", &p, &t, &v);
		if (p) {
			q.push_back((ele) {t, v});
			chk(rbeg, eraser, 1, 0);
		} else {
			q.push_front((ele) {t, v});
			chk(beg, erase, 0, 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
