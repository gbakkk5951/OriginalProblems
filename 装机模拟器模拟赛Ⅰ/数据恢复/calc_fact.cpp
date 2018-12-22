using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
namespace OI {
typedef long long lld;
typedef double lf;
const int MXN = 1 << 22;
const lld MOD = 119LL << 23 | 1;
const lld PHI = MOD - 1;
const lld G = 3;
const string sp = " ";
typedef vector<lld> V;
typedef V::iterator it;

char name[] = {"name_ex0.in"};
int beg = 0, end = 1;
V arr[500010];
struct Cmp {
	bool operator () (int a, int b) {
		return arr[a].size() > arr[b].size();
	}
};

lld fastpower(lld base, lld pow) {
	lld ret = 1;
	pow += pow < 0 ? PHI : 0;
	while (pow) {
		ret = (pow & 1) ? ret * base % MOD : ret;
		base = (pow >>= 1) ? base * base % MOD : base;
	}
	return ret;
}

namespace NTTsp {
	
	lld *w[2][23];
	void mov_ele(it arr, int len) {
		for (int i = 1, j = 0, k; i < len; i++) {
			for (k = len >> 1; k & j; k >>= 1) {
				j ^= k;
			}
			j |= k;
			if (i < j) {
				swap(arr[i], arr[j]);
			}
		}
	}
	void init() {
		lld wn;
		for (int J = 0; J < 2; J++) {
			for (int I = 1; I <= 22; I++) {
				w[J][I] = (lld *)calloc(1 << I - 1, sizeof(lld));
				lld *w = NTTsp::w[J][I];
				wn = fastpower(G, (J ? -1 : 1) * PHI >> I);
				w[0] = 1;
				for (int i = 1; i < 1 << I - 1; i++) {
					w[i] = w[i - 1] * wn % MOD;
				}
			}
		}
	}
	void NTT(it arr, int len, int pow) {
		lld *w, x, y;
		it a, b;
		mov_ele(arr, len);
		for (int I = 1; 1 << I <= len; I++) {
			int half = 1 << I - 1;
			w = NTTsp::w[pow == -1][I];
			for (int i = 0; i < len; i += half << 1) {
				a = arr + i; b = arr + i + half;
				for (int j = 0; j < half; j++) {
					x = a[j];
					y = b[j] * w[j];
					a[j] = (x + y) % MOD;
					b[j] = (x - y) % MOD;
				}
			}
		}
		if (pow == -1) {
			lld wn = fastpower(len, -1);
			for (int i = 0; i < len; i++) {
				arr[i] = arr[i] * wn % MOD;
			}
		}
	}
}


struct _Main {
	int n;
	void clearvec(vector<lld> &_old) {
		vector<lld> new_;
		_old.swap(new_);
	}
	void clear() {
		for (int i = 1; i <= n; i++) {
			clearvec(arr[i]);
		}
	}
	priority_queue<int, vector<int>, Cmp> heap;
	_Main() {
		NTTsp::init();
		int input[10];
		for (int I = beg; I < end; I++) {
			cerr << "input" << sp << I << " : ";	
			cin >> input[I];
		}
		for (int I = beg; I < end; I++) {
//			name[7] = I + '0';
			cerr << "making " << I << endl;
//			ofstream cout (name);
//			cin >> n;
			n = input[I];
			clear();
			if (n == 0) {
				cout << 0 << sp << 1 << endl << 1;
				continue;
			}
			for (int i = 1; i <= n; i++) {
				int tmp = i;
				while (tmp) {
					arr[i].push_back(tmp % 10);
					tmp /= 10;
				}
				heap.push(i);
			}
			while (heap.size() > 1) {
				int a = heap.top();
				heap.pop();
				int b = heap.top();
				heap.pop();
				int mxpow;
				for (mxpow = 1; mxpow < arr[a].size() + arr[b].size() + 50; mxpow <<= 1);
				arr[a].resize(mxpow); 
				arr[b].resize(mxpow);
				using NTTsp::NTT;
				it sa, sb;
				
				NTT(sa = arr[a].begin(), mxpow, 1);
				NTT(sb = arr[b].begin(), mxpow, 1);
				for (int i = 0; i < mxpow; i++) {
					sa[i] = sa[i] * sb[i] % MOD;
				}
				NTT(sa, mxpow, -1);
				for (int i = 0; i < mxpow; i++) {
					sa[i] += sa[i] < 0 ? MOD : 0;
					if (sa[i] >= 10) {
						sa[i + 1] += sa[i] / 10;
						sa[i] %= 10;
					}
				}
				while (sa[arr[a].size() - 1] == 0) {
					arr[a].pop_back();
				}
				heap.push(a);
			}
			int ans = heap.top();
			heap.pop();
			int i;
			for (i = arr[ans].size() - 1; i > 0; i--) {
				if (arr[ans][i]) {
					break;
				}
			}
			//i -= rand() % 15 + 1;
			//i = max(i, 0);
			cout << n << sp << i + 1 << endl;
			for ( ; i >= 0; i--) {
				cout << arr[ans][i] + (arr[ans][i] < 0 ? MOD : 0);
			}
			cout << endl;
		}
	}
}calc_fact;
}
