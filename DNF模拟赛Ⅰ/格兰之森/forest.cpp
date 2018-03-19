using namespace std;
int main() {}
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <cmath>

namespace OI {
typedef long long lld;
const int MXN = 500050;
const int INF = 0x3f3f3f3f;
const int DST = 1, NXT = 0;

struct Block {
	lld sum[MXN];
	int org[MXN], srt[MXN];
	int id[MXN], st[MXN], ed[MXN], add[MXN], val[MXN];
	int idx;
	Block() {
		st[0] = ed[0] = MXN - 5;
	}
	void init(int l, int r) {
		if (l > r) swap(l, r);
		int sq = (int)ceil(sqrt(r - l + 1.0));
		idx++;
		for (int i = l; i <= r; i++) {
			id[i] = idx;
			if (i % sq == 0) {
				ed[idx] = i;
				st[++idx] = i + 1;
			}
		}
		st[id[l]] = l;
		ed[id[r]] = r;
		idx = id[r];
		for (int i = id[l]; i <= id[r]; i++) {
			val[i] = INF;
			build(i);	
		}
	}
	void build(int id) {
		
		memcpy(srt + st[id], org + st[id], (ed[id] - st[id] + 1) * sizeof(int));
		sort(srt + st[id], srt + ed[id] + 1); 
		sum[st[id]] = srt[st[id]];
		for (int i = st[id] + 1; i <= ed[id]; i++) {
			sum[i] = sum[i - 1] + srt[i];
		}
	}
	void push(int id) {
		if (val[id] < INF) {
			for (int i = st[id]; i <= ed[id]; i++) {
				org[i] = val[id];
			}
			val[id] = INF;
		}
	}
	inline void brchange(int op, int l, int r, int c) {
		if (op == 1) {//ADD
			push(id[l]);
			for (int i = l; i <= r; i++) {
				org[i] += c;
			}
		} else {//赋值
			push(id[l]);
			for (int i = l; i <= r; i++) {
				org[i] = c - add[id[l]];
			}
		}
		build(id[l]);
	}
	inline void blchange(int op, int id, int c) {
		if (op == 1) {//ADD
			if (val[id] < INF) {
				val[id] += c;
			} else {
				add[id] += c;
			}
		} else {//赋值
			add[id] = 0;
			val[id] = c;
		}
	}
	void change(int op, int l, int r, int c) {
		if (l > r) swap(l, r);
		if (l != st[id[l]] && r >= ed[id[l]]) {
			brchange(op, l, ed[id[l]], c);
			l = ed[id[l]] + 1;
		}
		while (ed[id[l]] <= r) {
			blchange(op, id[l], c);
			l = ed[id[l]] + 1;
		}
		if (l <= r) {
			brchange(op, l, r, c);
		}
	}
	lld brquery(int op, int l, int r, int c) {
//		printf("br %d %d %d %d\n", op, l, r, c);
		c -= add[id[l]];//忘了 
		lld ret = 0;
		if (op == 3) {//数量
			if (val[id[l]] < INF) {
				ret += (r - l + 1) * (val[id[l]] >= c);
			} else for (int i = l; i <= r; i++) {
				ret += org[i] >= c;
			}
		} else {
			if (val[id[l]] < INF) {
				ret += (r - l + 1LL) * (val[id[l]] >= c) * val[id[l]];
			} else for (int i = l; i <= r; i++) {
				ret += (org[i] >= c) ? org[i] + add[id[l]] : 0;
			}
		}
		return ret;
	}
	lld blquery(int op, int id, int c) {
		if (val[id] < INF) {
			if (op == 3) {
				return (ed[id] - st[id] + 1) * (val[id] >= c);
			} else {
				return (ed[id] - st[id] + 1LL) * (val[id] >= c) * val[id];
			}
		}
		c -= add[id]; //忘了 
		/*
		printf("blq [%d %d] %d\n", st[id], ed[id], c); 
		printf("str : ");
		for (int i = st[id]; i <= ed[id]; i++) {
			printf("%d ", srt[i]);
		}
		printf("\n");
		*/
		int pos = lower_bound(srt + st[id], srt + ed[id] + 1, c) - (srt + st[id]);
		if (op == 3) {//数量
			return ed[id] - st[id] + 1 - pos;
		} else {
			return sum[ed[id]] - (pos ? sum[st[id] + pos - 1] : 0) 
				+ add[id] * (ed[id] - st[id] + 1LL - pos);
		}
	}
	lld query(int op, int l, int r, int c) {
//		printf("q %d %d %d %d\n", op, l, r, c);
		lld ret = 0;
		if (l > r) swap(l, r);
		if (l != st[id[l]] && r >= ed[id[l]]) {
			ret += brquery(op, l, ed[id[l]], c); //又把ed[id[l]]写成 r
			l = ed[id[l]] + 1;
		}
		while (ed[id[l]] <= r) {
			ret += blquery(op, id[l], c);
			l = ed[id[l]] + 1;
		}
		if (l <= r) {
			ret += brquery(op, l, r, c);
		}
//		printf("ret = %lld\n", ret);
		return ret;
	}
}data;


struct _Main {
int edge[MXN << 1][2], head[MXN];
int eidx;
inline void add(int a, int b) {
	eidx++;
	edge[eidx][DST] = b;
	edge[eidx][NXT] = head[a];
	head[a] = eidx;
}
int h[MXN], f[MXN], val[MXN], size[MXN], chose[MXN], id[MXN], tp[MXN];
void dfs0(int nd, int fa) {
	
	h[nd] = h[fa] + 1;
	f[nd] = fa;
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		if (!h[t = edge[e][DST]]) {
			dfs0(t, nd);
			size[nd] += size[t];
			if (!chose[nd] || size[chose[nd]] < size[t]) {
				chose[nd] = t;
			}
		}
	}
	size[nd]++;
}
void dfs1(int nd, int top, int &idx) {
	id[nd] = ++idx;
	tp[nd] = top;
	data.org[id[nd]] = val[nd];
	if (chose[nd]) {
		dfs1(chose[nd], top, idx);
	} else {
		data.init(id[top], id[nd]);
		return;
	}
	int t;
	for (int e = head[nd]; e; e = edge[e][NXT]) {
		if (!id[t = edge[e][DST]]) {
			dfs1(t, t, idx);
		}
	}
}


lld ask(int op, int a, int b, int c) {
	lld ret = 0;
	while (tp[a] != tp[b]) {
		if (h[tp[a]] < h[tp[b]]) {//一定要比较tp的h
			swap(a, b);
		}
		ret += data.query(op, id[a], id[tp[a]], c);
		a = f[tp[a]];
	}
	ret += data.query(op, id[a], id[b], c);//底下忘了id 
	return ret;
}

void change(int op, int a, int b, int c) {
	while (tp[a] != tp[b]) {
		if (h[tp[a]] < h[tp[b]]) {//一定要比较tp的h 
			swap(a, b);
		}
		data.change(op, id[a], id[tp[a]], c);
		a = f[tp[a]];
	}
	data.change(op, id[a], id[b], c);
}



	_Main() {
		int n, en, Qn;
		int a, b, c;
		int idx = 0;
		int op;
		read(n); read(en); read(Qn);
		for (int i = 1; i <= n; i++) {
			read(val[i]);
		}
		for (int i = 1; i <= en; i++) {
			read(a); read(b);
			add(a, b); add(b, a);
		}
		for (int i = 1; i <= n; i++) {
			if (!h[i]) {
				dfs0(i, 0);
				dfs1(i, i, idx);
			}
		}
		for (int Q = 1; Q <= Qn; Q++) {
			read(op); read(a); read(b); read(c);
			if (op <= 2) {
				change(op, a, b, c);
			} else {
				printf("%lld\n", ask(op, a, b, c));
			}
		}

	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			if (t == '-') f = -1;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
		a *= f;
	}



}forest;
}
