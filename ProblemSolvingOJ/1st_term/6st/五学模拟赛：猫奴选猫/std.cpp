#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 30;
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
int v[maxn], n, k;
lld ans = -LINF;
void dfs1(int cho = 0, int now = 1, lld sum = 0) {
	if (now == n + 1) {//now == n + 1纯粹为了压力测试
		if (cho == k) ans = max(ans, sum);
		return;
	}
//	if (k - cho <= n - now) //剪枝，不剪也能过
		dfs1(cho, now + 1, sum);
	lld base = 1;
	for (int i = 1; i < k - cho; ++i) {//应该不影响复杂度
		base *= 3;
	}
//	if (cho < k)//剪枝，不剪也能过
		dfs1(cho + 1, now + 1, sum + v[now] * base);
}
lld dfs2(int cho = 0, int now = 1) {
	if (now == n + 1) {
		return cho == k ? 0 : -LINF;
	}
	lld ret = -LINF;
//	if (k - cho < n - now) //剪枝，不剪也能过
		ret = max(ret, dfs2(cho, now + 1));
	lld base = 1;
	for (int i = 1; i < k - cho; ++i) {//应该不影响复杂度
		base *= 3;
	}
/*	if (cho < k)*/ { //剪枝，不剪也能过
		lld tmp = dfs2(cho + 1, now + 1);
		if (tmp != -LINF) {
			ret = max(ret, tmp + base * v[now]);
		}
	}
	return ret;
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> v[i];
	dfs1();
	assert(dfs2() == ans);
	cout << ans;
	return 0;
}
