#include <cstdio>
#include <cmath>
#define maxn 2010
using namespace std;

int val[maxn], pos[maxn], cnt[50][maxn], ans[maxn<<1], size, tn, n, m, k, q;
int id[maxn], st[50], ed[50], deltans[maxn];
void opt(int l, int delt, int tp){
	if (l > n) {
		return;
	}
	for (int i = l; i <= ed[id[l]]; i++) {
		deltans[delt + i - l] += tp * val[i];
	}
	for (int i = id[l] + 1; i <= tn; i++) {
		cnt[i][delt + st[i] - l] += tp;
	}
}
int main(){
	int l,r;
	scanf("%d%d%d%d", &n, &m, &k, &q);
	size = sqrt(n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
	}
	for(int i = 1; i <= n; i++){
		id[i] = i / size + 1;
		if (id[i] > id[i - 1]) {
			st[id[i]] = i;
			ed[id[i] - 1] = i - 1;
		}
	}
	tn = id[n]; 
	ed[tn] = n;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &pos[i]);
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &l, &r);
		opt(l, 0, 1);
		opt(r + 1, r + 1 - l, -1);
	}
	for (int i = 1; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			deltans[j + i - st[id[i]]] += cnt[id[i]][j]*val[i];
		}
	}
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			ans[pos[j] + i] += deltans[i];
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}

