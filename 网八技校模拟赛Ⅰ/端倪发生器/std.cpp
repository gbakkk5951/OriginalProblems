using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
#include <cassert>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef long double Lf;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 1e5 + 10;
const int SQ = 321;
struct _Main {
	int n;
	lld sum[MXN];
	lld srt[MXN];
	int sq;
	lld is[SQ][MXN];
	lld ns[SQ][MXN];
	lld as[SQ];
	int vn;
	int bl[MXN], st[SQ], ed[SQ];
	void init() {
		int idx = 0, sq = ceil(sqrt(n));
		for (int i = 0; i <= n; i++) {
			if (i % sq == 0) {
				ed[idx] = i - 1;
				++idx;
				st[idx] = i;
			}
			bl[i] = idx;
		}
		ed[idx] = n;
		int v;
		for (int i = 1; i <= idx; i++) {
			memcpy(is[i], is[i - 1], (vn + 1) * sizeof(lld));
			memcpy(ns[i], ns[i - 1], (vn + 1) * sizeof(lld));
			as[i] = as[i - 1];
			lld *as = &this->as[i], *ns = this->ns[i], *is = this->is[i];
			for (int j = st[i]; j <= ed[i]; j++) {
				v = sum[j];
				*as += ns[v] * j - is[v];
				ns[v] += 1;
				is[v] += j;
			}
		}
	}
	lld tns[MXN], tis[MXN];
	lld query(int l, int r) {
		int lb = bl[l], rb = bl[r];
		int v;
		lld ret = 0;
		if (lb == rb) {
			for (int i = l; i <= r; i++) {
				v = sum[i];
				ret += tns[v] * i - tis[v];
				tns[v] += 1;
				tis[v] += i;
			}
			for (int i = l; i <= r; i++) {
				v = sum[i];
				tns[v] -= 1;
				tis[v] -= i;
			}
			return ret;
		}
		
		lld *lns = ns[lb], *rns = ns[rb - 1];
		lld *lis = is[lb], *ris = is[rb - 1];
		ret = as[rb - 1] - as[lb];
		
		for (int i = ed[lb]; i >= l; i--) {
			v = sum[i];
			ret += (tis[v] + ris[v] - lis[v]) - (tns[v] + rns[v] - lns[v]) * i;
			tns[v] += 1;
			tis[v] += i;
		}
		for (int i = st[rb]; i <= r; i++) {
			v = sum[i];
			ret += (tns[v] + rns[v] - lns[v]) * i - (tis[v] + ris[v] - lis[v]);
			tns[v] += 1;
			tis[v] += i;
		}
		for (int i = ed[lb]; i >= l; i--) {
			v = sum[i];
			tns[v] -= 1;
			tis[v] -= i;
		}
		for (int i = st[rb]; i <= r; i++) {
			v = sum[i];
			tns[v] -= 1;
			tis[v] -= i;
		}
		return ret;
	}
	_Main() {
		int Qn;
		read(n); read(Qn);
		lld lstans = 0; 
		for (int i = 1; i <= n; i++) {
			read(sum[i]);
			sum[i] += sum[i - 1];
		}
		memcpy(srt, sum, (n + 1) * sizeof(lld));
		sort(srt, srt + n + 1);
		vn = unique(srt, srt + n + 1) - srt - 1;
		for (int i = 0; i <= n; i++) {
			sum[i] = lower_bound(srt, srt + vn + 1, sum[i]) - srt;
		}
		init();
		int l, r;
		for (int Q = 1; Q <= Qn; Q++) {
			read(l); read(r);
			l = (l ^ lstans) % n + 1; r = (r ^ lstans) % n + 1;
			if (l > r) swap(l, r);
			lstans = query(l - 1, r);
			printf("%lld\n", lstans);
		}
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}
