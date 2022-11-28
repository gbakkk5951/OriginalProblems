#include <bits/stdc++.h>
using namespace std;
namespace Exam {
typedef long long lld;
int n, m;
template <typename type>
void read(type &a) {
	int f = 0, t;
	while (!isdigit(t = getchar())) {
		f |= a == '-';
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10; a += t - '0';
	}
	a = f ? -a : a;
}
const int maxn = 1e6 + 10;
int need[maxn];
lld initial[maxn], consume[maxn];
lld ceil(lld a, lld b) {
	return (a + b - 1) / b;
}
int count;
typedef pair<int, int> p;
priority_queue<p> heap;
lld remain[maxn];
int test(lld power) {//是否有解不能只判断需要充电的人数 > 总时间
	count = 0;// 忘了
	memset(need, 0, (m + 2) * sizeof(int));
	while (heap.size()) heap.pop();
//	printf("\n\ntest %lld\n", power);
	for (int i = 1; i <= n; ++i) {
		remain[i] = initial[i];
		lld time = 0; //第几秒的开始, 能撑到第m秒开始即可
		lld delta = remain[i] / consume[i];
		time += delta; 
		remain[i] -= delta * consume[i];
		heap.push((p) {-time, i});
	}
	for (int i = 0; i < m && heap.size(); ++i) {
		p nd = heap.top();
//		printf("I = %d, time = %d, id = %d, remain = %lld\n", i, -nd.first, nd.second, remain[nd.second]);
		heap.pop();
		if (-nd.first < i) return 0;
		remain[nd.second] += power;
		lld time = -nd.first;
		lld delta = remain[nd.second] / consume[nd.second];
		time += delta;
		remain[nd.second] -= delta * consume[nd.second];
		if (time < m) heap.push((p) {-time, nd.second});
	}
	return heap.empty();
}
}
int main() {
	using namespace Exam;
	read(n); read(m);
	lld max_consume = 0, need_power = 0;
	for (int i = 1; i <= n; i++) {
		read(initial[i]);
	}
	for (int i = 1, real = 1; i <= n; i++, real++) {
		read(consume[i]);
		if (consume[i] * m > initial[real]) {
			initial[i] = initial[real];
//			printf("c %lld i %lld\n", consume[i], initial[i]);
			if (consume[i] * m > initial[i]) {//need it 
				need_power += consume[i] * m - initial[i];
				max_consume = max(max_consume, consume[i] * m - initial[i]);
			}
		} else {//卡掉没删去就判断非法的
			--i; --n; continue;
		}
	}
//	printf("n = %d\n", n);
	int first = 1;
	lld l = ceil(need_power, m);
	lld r = max_consume;
//	printf("l = %lld, r = %lld\n", l, r);
	while (l < r) {
		lld mid = l;
		if (first) {
			mid = r;
			first = 0;
		}
		if (test(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	printf("%lld", l == r ? l : -1);
	return 0;
}

