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
const SQ = 500;
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
		uc s;
		nd += base;
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			node[nd] |= 1u << s;
			if (node[nd] != 1u << s) break;//不用上传
		}
	}
	void erase(int nd) {
		vis[nd] = 0;
		uc s;
		nd += base;
		while (nd--) {
			s = nd & 7;
			nd >>= 3;
			if (node[nd] ^= 1u << s) break;//不用上传
		}
	}
	int getnxt(int nd) {
		if (vis[nd]) return nd;
		uc s;
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
		uc s;
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
struct _Main {
	int ans[MXN];
	int l[MXN];//右端点为i的符合条件下最靠左的位置
	_Main() {
		int n;
		read(n);
		for (int i = 1; i <= n; i++) {
			read(arr[i]);
			l[i] = i;
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
