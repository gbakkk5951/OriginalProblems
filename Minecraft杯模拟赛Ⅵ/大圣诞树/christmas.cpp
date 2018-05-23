#pragma GCC optimize(2)
using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#include <iostream>
#include <string>

#include <vector>
#include <queue>
#include <map>
#include <set>
namespace OI {


typedef pair<int, int> p;
typedef priority_queue<p> hp;
typedef set<p, greater<p> > st;
const int DST = 0, NXT = 1;
const int MXN = 2e5 + 10;
const int MXP = 19;
const int INF = 0x3f3f3f3f;

const string sp = " ";

int a[MXN], b[MXN], c[MXN];
int n;
struct _Pre {
	_Pre() {
		read(n);
		for (int i = 1; i <= n - 1; i++) {
			read(a[i]); read(b[i]); read(c[i]);
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
}reader;

int ins_cnt;
struct _Main {
	st sub_set[MXP][MXN];
	hp sub_hp[MXN];
	hp tot_hp;
	int sub_f[MXP][MXN];
	int sub_dis[MXP][MXN];
	int sub_del[MXP][MXN];
	int sub_tp[MXP][MXN];
	int mark[MXN];
	int lst[MXN];
	int mxa[MXN], mxb[MXN];
	int mxlen[MXN];
	
	void update_sub_hp(int rt) {
		int mk = mark[rt];
		mxa[rt] = gettop(sub_hp[rt], mk);
		mxb[rt] = getsec(sub_hp[rt], mk);
		mxlen[rt] = sub_set[mk][mxa[rt]].begin()->first + sub_set[mk][mxb[rt]].begin()->first;
		if (mxlen[rt] > 0) tot_hp.push((p) {mxlen[rt], rt});
	}
	void deledge(int nd, int fa) {
		int rt = fa, mk = mark[fa];
		while (rt) {
			if (sub_f[mk][nd] == fa && !sub_del[mk][nd]) {
				deldfs(nd, fa, mk);
				update_sub_hp(rt);
			}
			rt = lst[rt];
			--mk;
		}
	}
	void popheap(hp &heap, int mk) {
		int id, val;
		while (1) { // 有空元素
			id = heap.top().second;
			if (sub_del[mk][id]) {
				heap.pop();
			} else {
				val = sub_set[mk][id].begin()->first;
				if (val != heap.top().first) {
					heap.pop();
					heap.push((p) {val, id});
				} else {
					break;
				}
			}
		}
	}
	int gettop(hp &heap, int mk) {//有两个空元素 -1,0
		popheap(heap, mk);
		return heap.top().second;
	}
	int getsec(hp &heap, int mk) {//top已经合法 有两个空元素 -1,0
		int top = heap.top().second;
		int ret = 0;
		heap.pop();
		popheap(heap, mk);
		ret = heap.top().second;
		heap.push((p) {sub_set[mk][top].begin()->first, top});
		return ret;
	}
	
	void deldfs(int nd, int fa, int mk) {
		int t;
		sub_del[mk][nd] = 1;
		sub_set[mk][sub_tp[mk][nd]].erase((p) {sub_dis[mk][nd], nd});
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!sub_del[mk][t] && mark[t] > mk && t != fa) {
				deldfs(t, nd, mk);
			}
		}
	}
	void delpath(int a, int b) {
		if (h[a] < h[b]) swap(a, b);
		while (h[a] > h[b]) {
			deledge(a, f[a]);
			deledge(f[a], a);
			a = f[a];
		}
		while (a != b) {
			deledge(a, f[a]);
			deledge(f[a], a);
			deledge(b, f[b]);
			deledge(f[b], b);
			a = f[a]; b = f[b];
		}
	}
	int h[MXN], f[MXN], size[MXN];
	void predfs(int nd, int fa) {
		int t;
		f[nd] = fa;
		h[nd] = h[fa] + 1;
		size[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa) {
				predfs(t, nd);
				size[nd] += size[t];
			}
		}
	}
	int val, cho;
	void getsize(int nd, int fa, int tot) {
		int t;
		int mx = 0;
		size[nd] = 1;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (t != fa && !mark[t]) {
				getsize(t, nd, tot);
				size[nd] += size[t];
				mx = max(mx, size[t]);
			}
		}
		mx = max(mx, tot - size[nd]);
		if (mx < val) {
			val = mx;
			cho = nd;
		}
	}
	void getdis(int nd, int fa, int dis, int tp, int mk) {
		sub_f[mk][nd] = fa;
		sub_dis[mk][nd] = dis;
		sub_tp[mk][nd] = tp;
		sub_set[mk][tp].insert((p) {dis, nd});
		
		int t;
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!mark[t] && t != fa) {
				getdis(t, nd, dis + 1, tp, mk);
			}
		}
		
	}
	void init_hp(int nd) {
		sub_hp[nd].push((p) {0, nd});
		sub_hp[nd].push((p) {-1, 0});
		sub_hp[nd].push((p) {-1, 0});
		sub_set[mark[nd]][nd].insert((p) {0, nd});
	}
	void build_tree(int nd, int tot, int fa, int mk) {
		val = INF;
		getsize(nd, 0, tot);
		nd = cho;
		lst[nd] = fa;
		mark[nd] = mk;
		int t;
		init_hp(nd);
		if (tot == 1) return; //不应该是size[nd] 因为根已经变了
		for (int e = head[nd]; e; e = edge[e][NXT]) {
			t = edge[e][DST];
			if (!mark[t]) {
				getdis(t, nd, 1, t, mk);
				sub_hp[nd].push((p) {sub_set[mk][t].begin()->first, t});
			}
		}
		update_sub_hp(nd);
		for (int e = head[nd]; e; e = edge[e][NXT]) { //可以尝试并到上面去
			t = edge[e][DST];
			if (!mark[t]) {
				getsize(t, nd, 0);
				build_tree(t, size[t], nd, mk + 1);
			}
		}
		
	}
	_Main() {
		p nd;
		int mk, id, ans = 0;
		for (int i = 1; 1 << i <= n; i++) {
			sub_set[i][0].insert((p) {-1, 0});
		}
		if (ins_cnt++ == 1) {
			memset(c, 0, n * sizeof(int));
		}
		
		for (int i = 1; i <= n - 1; i++) {
			if (!c[i]) {
				add(a[i], b[i]);
				add(b[i], a[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!mark[i]) {
				predfs(i, 0);
				build_tree(i, size[i], 0, 1);
			}
		}
		while (!tot_hp.empty()) {
			while (!tot_hp.empty()) {
				nd = tot_hp.top();
				id = nd.second;
				mk = mark[id];
				if (nd.first != mxlen[id]) {
					tot_hp.pop();
					if (mxlen[id] > 0) tot_hp.push((p) {mxlen[id], id});
				} else {
					break;
				}
			}
			
			if (!tot_hp.empty()) {
				tot_hp.pop();
				delpath(sub_set[mk][mxa[id]].begin()->second, sub_set[mk][mxb[id]].begin()->second);
				++ans;
			}
		}
		printf("%d\n", ans);
	}
	int eidx;
	int head[MXN], edge[MXN << 1][2];
	void add(int a, int b) {
		eidx++;
		edge[eidx][DST] = b;
		edge[eidx][NXT] = head[a];
		head[a] = eidx;
	}
}solver[2];
}
