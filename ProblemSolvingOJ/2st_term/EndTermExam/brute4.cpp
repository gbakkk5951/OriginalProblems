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
lld remain[maxn];
lld time[maxn];
int test(lld power) {//是否有解不能只判断需要充电的人数 > 总时间
	count = 0;// 忘了
	memset(need, 0, (m + 2) * sizeof(int));
//	printf("\n\ntest %lld\n", power);
	for (int i = 1; i <= n; ++i) {
		remain[i] = initial[i];
		time[i] = 0; //第几秒的开始, 能撑到第m秒开始即可
		lld delta = remain[i] / consume[i];
		time[i] += delta; 
		remain[i] -= delta * consume[i];
	}
	for (int i = 0; i <= m; ++i) {
		int cho = 1;
		for (int j = 1; j <= n; ++j) {
			if (time[j] < time[cho]) {
				cho = j;
			}
		}
		if (time[cho] >= m) return 1;
		if (i == m || time[cho] < i) return 0;
		remain[cho] += power;
		lld delta = remain[cho] / consume[cho];
		time[cho] += delta;
		remain[cho] -= delta * consume[cho];
	}
	return 1;
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

