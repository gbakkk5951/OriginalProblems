using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
namespace OI {
typedef long long lld;
const lld MOD = 921260340LL;
const int MXN = 5100;
struct _Main {
	int id[MXN], st[75], ed[75];//以b序列(阶乘)分块
	lld b[MXN];
	lld ans[75][MXN];
	lld mul[MXN];//i号点（含）向后sq个点的连乘积
	int sq;
	int bidx;
	void init() {
		sq = (int)ceil(sqrt(n + 1));
		bidx = 1;
		for (int i = 0; i <= n; i++) {
			if (i && i % sq == 0) {
				ed[bidx] = i - 1;
				st[++bidx] = i;
			}
			id[i] = bidx;
		}
		st[1] = 0;
		ed[bidx] = n;
		st[0] = ed[0] = n + 1;
		
		b[0] = 1;
		for (int i = 1; i <= n; i++) {
			b[i] = b[i - 1] * i % MOD;
		}
		
		for (int i = 1; i <= n; i++) {
			mul[i] = i;
			for (int j = i + 1; j < i + sq; j++) {
				mul[i] = mul[i] * j % MOD;
			}
		}
		
		for (int i = 1; i <= bidx; i++) {//块
			for (int j = 1; j <= n; j++) {//起点
				lld tmp = 1;
				for (int k = 0; k < sq && j + k <= n; k++) {
					tmp = tmp * (j + k) % MOD;
					ans[i][j] = (ans[i][j] + tmp * b[st[i] + k]) % MOD; //st[i] + k > n 的部分 = 0无影响
				}
//				printf("ans[%d, %d] X [%d, %d] = %lld\n", st[i], ed[i], j, j + sq - 1, ans[i][j]);
			}
		}
		
	}
	lld query(int _a, int _b) {
		lld ret = 0, tmp = 1;
		int i = _a, j = _b, t;
		if (j != st[id[j]] && i - j + ed[id[j]] <= n) {
			t = ed[id[j]];
			for (; j <= t; j++, i++) {
				tmp = tmp * i % MOD;
				ret = (ret + tmp * b[j]) % MOD;
			}
		}
		for (; j <= n && i - j + ed[id[j]] <= n; i += sq, j += sq) {
			ret = (ret + tmp * ans[id[j]][i]) % MOD;
			tmp = tmp * mul[i] % MOD;
		}
		for (; j <= n && i <= n; i++, j++) {
			tmp = tmp * i % MOD;
			ret = (ret + tmp * b[j]) % MOD;
		}
		return ret;
	}

	int n;
	_Main() {
		int Qn, a, b;
		read(n); read(Qn);
		init();
		for (int Q = 1; Q <= Qn; Q++) {
			read(a); read(b);
			printf("%lld\n", query(a, b));
		}
	}
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
	}
}groxtrd;
}
