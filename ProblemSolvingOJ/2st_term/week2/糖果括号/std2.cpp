#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
struct ele {
	int type;
	lld v;
};
typedef deque<ele> d;
d q;
lld ans = 0;
template <typename iterator>
void chk(iterator (d::*begin) (), void (d::*pop) (), int l, int r) {
	lld sum;
	while (q.size() > 1) {
		iterator beg = (q.*begin)();
		if (beg->type == 2 && (beg + 1)->type == 2 || beg->type == l && (beg + 1)->type == r) {	
			*(beg + 1) = (ele) {2, beg->v + (beg + 1)->v};
			(q.*pop)();
	 	} else
		if (q.size() > 2 && beg->type == l && (beg + 1)->type == 2 && (beg + 2)->type == r) {
			*(beg + 2) = (ele) {2, beg->v + (beg + 1)->v + (beg + 2)->v};
			(q.*pop)();
			(q.*pop)();
		} else {
			break;
		}
	}
	if ((q.*begin)()->type == 2) ans = max(ans, (q.*begin)()->v);
}
const int MXN = 1e6 + 10;
int t[MXN];
void inline rpush(int t, lld v) {
	q.push_back((ele) {t, v});
	chk(&d::rbegin, &d::pop_back, 1, 0);
}
void inline lpush(int t, lld v) {
	q.push_front((ele) {t, v});
	chk(&d::begin, &d::pop_front, 0, 1);
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t[i]);
	}
	lld v;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &v);
		rpush(t[i], v);
	}
	printf("%lld\n", ans);
	for (int i = 1, t, p; i <= m; ++i) {
		scanf("%d%d%lld", &p, &t, &v);
		if (p) {
			rpush(t, v);
		} else {
			lpush(t, v);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

