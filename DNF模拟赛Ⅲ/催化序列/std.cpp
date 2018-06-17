#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <cstring>
namespace OI {
typedef unsigned int u;
typedef unsigned char uc;
const int SQ = 500;
struct _8Tree {
	uc nxt[256][8], pre[256][8];//upper_bound
	uc lnxt[256][8], lpre[256][8];//lower_bound;
	int base;
	uc node[37500];
	uc vis[250010];
	void clear() {
		memset(node, 0, sizeof(node));
		memset(vis, 0, sizeof(vis));
	}
	_8Tree() {
		//maintain 0 ~ 2^18 - 1, first leaf = base
		base = ((1 << 18) - 1) / 7;
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 8; j++) {
				for (int k = j + 1; k < 8; k++) {
					if (i >> k & 1) {
						nxt[i][j] = k + 1;
						break;
					}
				}
				for (int k = j - 1; k >= 0; k--) {
					if (i >> k & 1) {
						pre[i][j] = k + 1;
						break;
					}
				}
				for (int k = j; k < 8; k++) {
					if (i >> k & 1) {
						lnxt[i][j] = k + 1;
						break;
					}
				}
				for (int k = j; k >= 0; k--) {
					if (i >> k & 1) {
						lpre[i][j] = k + 1;
						break;
					}
				}
			}
		}
	}
	void insert(int nd) {
		vis[nd] = 1;
		u s;
		nd += base;
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			if ((node[nd] |= 1u << s) != 1u << s) break;//不用上传
		}
	}
	void erase(int nd) {
		vis[nd] = 0;
		u s;
		nd += base;
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			if (node[nd] ^= 1u << s) break;//不用上传
		}
	}
	int getnxt(int nd) {
		if (vis[nd]) return nd;
		u s;
		nd += base;
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			if (s = nxt[node[nd]][s]) {
				nd = (nd << 3) + s;
				break;
			}
		}
		if (nd == -1) return 0;
		while (nd < base) {
			nd = (nd << 3) + lnxt[node[nd]][0];
		}
		return nd - base;
	}
	int getpre(int nd) {
		if (vis[nd]) return nd;
		u s;
		nd += base;//没加base╮(╯_╰)╭
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			if (s = pre[node[nd]][s]) {
				nd = (nd << 3) + s;
				break;
			}
		}
		if (nd == -1) return 0;
		while (nd < base) {
			nd = (nd << 3) + lpre[node[nd]][7];
		}
		return nd - base;
	}
}tree;
const int MXN = 1e5 + 10;
const int MXV = 2.5e5 + 15;
struct _Main {
	int arr[MXN];
	int ans[MXV];//开小了
	int l[MXN];//右端点为i的符合条件下最靠左的位置
	_Main() {
		int n, a, b, now, h, mx = 0;
		read(n);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
			mx = max(mx, arr[i]);
			l[i] = i;
		}
		for (int i = 1; i <= n - 1; i++) {
			now = 2.5e5 + 3;//开大了
			for (int j = i; j <= n; j++) {
				a = tree.getpre(arr[j]);
				b = tree.getnxt(arr[j]);
				if (a) now = min(now, arr[j] - a);
				if (b) now = min(now, b - arr[j]);
				ans[now] = max(ans[now], j - i + 1);
				if (now > SQ) {
					l[j] = min(l[j], i);
				}
				if (now <= SQ || j == n) {
					for (int k = i; k < j; k++) {
						tree.erase(arr[k]);
					}
					break;
				}
				tree.insert(arr[j]);
			}
		}
		for (int i = SQ; i >= 0; i--) {
			h = 1;
			for (int j = 1; j <= n; j++) {
				while (1) {
					a = tree.getpre(arr[j]);
					b = tree.getnxt(arr[j]);
					if ((a == 0 || arr[j] - a >= i) && (b == 0 || b - arr[j] >= i)) {
						break;
					}
					tree.erase(arr[h++]);
				}
				if (h < l[j]) {//为了恰好
					l[j] = h;
					ans[i] = max(ans[i], j - h + 1);//j - i + 1 ???
				}
				tree.insert(arr[j]);//忘了insert
			}
			if (n - h + 1 <= 1000) {//memset 比普通赋值快7倍(别人的博客上说的)
				for (int k = h; k <= n; k++) {
					tree.erase(arr[k]);
				}
			} else {
				tree.clear();
			}
		}
		for (int i = 0; i < mx; i++) {
			printf("%d\n", ans[i]);
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
}std;
}
