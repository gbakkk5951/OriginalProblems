#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld OA;
lld L;
int n, m;
lld get_random() {
	return A = C + (A * B) % MOD;
}
int a[maxn];
int end1, end2;
int mxlen;
bool confirm() {
	int need_loop = 100000, min_into = 5000;
	map<int, int> mp;
	for (int i = 1; i <= need_loop; ++i) {
		int a = get_random();
		if (mp[a] != 0) {
			if (mp[a] >= min_into) {
				return true;
			} else {
				mxlen = max(mxlen, mp[a]);
				++end1;
				return false;
			}
		} else {
			mp[a] = i;
		}
	}
	
	++end2;
	return false;
}
int bit_rand() {
	if (rand() % 10) return rand();
	return rand() & ((1 << (rand() % 29)) - 1);
}
int main() {
//	cin >> n >> A >> B >> C >> MOD >> L;
	srand(time(0));
	/* to do */
	/* complete this function and the whole program */
	n = 1.8e7;
	
	int cnt = 0;
	do {
		++cnt;
		if(cnt % 100 == 0)printf("test %d end1 %d end2 %d mxlen %d\n", cnt, end1, end2, mxlen);
		OA = A = bit_rand() % (int)(1e9 + 1);
		B = bit_rand() % (int)(1e9 + 1) - 1e9;
//		C = bit_rand() % (int)(2e9 + 1) - 1e9;
		C = rand() % 10 - 5;
		MOD = rand() % 500000 + 2;
//		MOD = bit_rand() % (int)(2e5 + 1) - 1e5;
		MOD += !MOD;
	} while (!confirm());
	printf("[cnt = %d]\n", cnt);
	cout << n << " " << OA << " " << B << " " << C << " " << MOD << endl;
	
	return 0;
}
