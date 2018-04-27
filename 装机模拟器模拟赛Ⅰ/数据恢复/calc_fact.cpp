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
const int MXN = 1 << 22;
const lld MOD = 119 << 23 | 1;
const lld PHI = MOD - 1;
const lld G = 3;
const string sp = " ";
typedef vector<lld> V;
typedef V::iterator it;
namespace OI {
char name[] = {"name0.in"};
int beg = 0, end = 10;
V arr[1000010];
struct Cmp {
	bool operator () (int a, int b) {
		return arr[a].size() > arr[b].size;
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
	void mov_ele(V &arr[], int len) {
		for (int i = 1, j = 0, k; i < len; i++) {
			
		}
	}
	void init() {
		lld wn;
		for (int J = 0; J < 2; J++) {
			for (int I = 1; I <= 22; I++) {
				w[J][I] = (lld *)callc(1 << I - 1, sizeof(lld));
				wn = fastpower(G, (J ? -1 : 1) * PHI >> I);
				w[J][I][0] = 1;
				lld *w = NTTsp::w[J][I];
				for (int i = 1; i < 1 << I - 1; i++) {
					w[i] = w[i - 1] * wn % MOD;
				}
			}
		}
	}
	void NNT(it arr, int len, int pow) {
		lld *w, x, y;
		it a, b;
		for (int I = 1; 1 << I <= len; I++) {
			int half = 1 << I - 1;
			*w = NTTsp::w[pow == -1][I];
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
			lld wn = fastpower(G, pow * PHI >> I);
			for (int i = 0; i < len; i++) {
				arr[i] = arr[i] * wn % MOD;
			}
		}
	}
}


struct _Main {
	int idx;
	void clear() {
		idx = 0;
		for (int i = 1; i <= n * 2; i++) {
			arr[i].clear();
		}
	}
	_Main() {
		int n;
		for (int I = beg; I < end; I++) {
			name[4] = I + '0';
			cerr << "input" << sp << I << " :";	
			ofstream cout (name);
			cin >> n;
			clear();
			
		}
	}
}calc_fact;
}
