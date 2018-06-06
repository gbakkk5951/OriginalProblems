#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace OI {
typedef long long lld;
const lld MOD = 1e9 + 7;
const lld PHI = MOD - 1;
const int MXN = 2e3 + 10;
const int DST = 0, NXT = 1, VAL = 2;
lld com[MXN][MXN], comr[MXN][MXN];
lld fc[MXN], fcr[MXN];
lld rev[MXN];
lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow += (pow < 0) * PHI;
	while (pow) {
		ret = (pow & 1) ? ret * base % MOD : ret;
		base = (pow >>= 1) ? base * base % MOD : base;
	}
	return ret;
}
struct _Main {
	lld ans;
	int n;
	lld rate(int tot, int cho, int some, int in) {
		return com[in][some] * com[tot - in][cho - some] % MOD * comr[tot][cho] % MOD;
	}
	void init() {
		fc[0] = fcr[0] = 1;
		for (int i = 1; i <= n; i++) {
			rev[i] = fastpower(i, -1);
		}
		for (int i = 1; i <= n; i++) {
			fc[i] = fc[i - 1] * i % MOD;
			fcr[i] = fcr[i - 1] * rev[i] % MOD;
		}
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				com[i][j] = fc[i] * fcr[j] % MOD * fcr[i - j] % MOD;
				comr[i][j] = fcr[i] * fc[j] % MOD * fc[i - j] % MOD;
			}
		}
	}
	int size[MXN];
	int it[MXN];
	lld dp[MXN][2][MXN];
	void getdp(int nd, int fa) {
		size[nd] = 1;
		int t, psum, sum, tsum;
		lld *old, *now, *dst, val;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				val = edge[e][VAL];
				
				getdp(t, nd);
				
				dst = dp[t][it[t]];
				psum = size[nd];
				size[nd] += tsum = size[t];
				sum = size[nd];
				
				old = dp[nd][it[nd]];
				it[nd] ^= 1;
				now = dp[nd][it[nd]];
				
				for (int i = 1; i <= sum; i++) {//共选i个
					now[i] = 0;
					for (int j = max(1, i - psum); j <= i && j <= tsum; j++) {//其中j个来自dst
						now[i] = (now[i] + (old[i - j] + dst[j] + val) * rate(sum, i, j, tsum)) % MOD;
						//之前now[i] += 没模爆mod了
					}
				}
				for (int i = 1; i <= psum; i++) {//0个来自dst
					now[i] = (now[i] + old[i] * rate(sum, i, 0, tsum)) % MOD;
				}
			}
		}
		//现在dp[nd][i]算的是到nd（含非法）点数为i时长度期望（没有×2）
	}
	lld xsum[MXN];//对于点数为i的贡献系数
	void getans(int nd, int fa) {
		lld *now = dp[nd][it[nd]], *dst, val;
		int t, tsum, sum = size[nd];
		//将自己的贡献加入贡献系数中去
		for (int i = 1; i <= sum; i++) {//要循环到sum因为自己也要用 
			xsum[i] = (xsum[i] + rev[sum] * comr[sum][i]) % MOD;
		}
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				val = edge[e][VAL];
				tsum = size[t];
				dst = dp[t][it[t]];
				for (int i = 1; i <= tsum; i++) {
					now[i] = (now[i] - (dst[i] + val) * rate(sum, i, i, tsum) % MOD) % MOD;
				}
			}
		}
		for (int i = 1; i <= sum; i++) {
			ans = (ans + xsum[i] * com[sum][i] % MOD * now[i]) % MOD;
			//式子列错了，多乘了一个i
		}
		
		for (int e = head[nd]; e; e = edge[e][NXT]) {//忘了递归23333
			t = edge[e][DST];
			if (t != fa) {
				getans(t, nd);
			}
		}
		//删掉自己对的贡献系数的贡献
		for (int i = 1; i <= sum; i++) {
			xsum[i] = (xsum[i] - rev[sum] * comr[sum][i]) % MOD;
		}
	}
	_Main() {
		read(n);
		init();
		int a, b, c;
		for (int i = 1; i <= n - 1; i++) {
			read(a); read(b); read(c);
			add(a, b, c); add(b, a, c);
		}
		getdp(1, 0);
		getans(1, 0);
		ans = ans * 2 * rev[n] % MOD;
		ans += (ans < 0) * MOD;
		printf("%lld", ans);
	}
	int eidx;
	int head[MXN], edge[MXN << 1][3];
	void add(int a, int b, int c) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][VAL] = c;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
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
}std;
}
