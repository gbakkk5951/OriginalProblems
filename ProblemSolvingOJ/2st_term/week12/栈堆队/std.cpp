#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e6 + 10;
int n;
int m;
int empty;
int ans;
char s[maxn], bottom[maxn];
int main() {
	scanf("%d%d%s", &n, &m, s);
	empty = n;
	int valid_number = 0;
	int in_stack = 0;
	for (int i = 0; i < m; ++i) {
		if (s[i] == '0') {
			++in_stack;
		} else {
			if (in_stack) {
				--in_stack;
				++valid_number;
			}
		}
	}
	int pushed = 0, poped = 0;
	for (int i = 0; i < m; ++i) {
		if (s[i] == '0') {
			if (pushed < valid_number) {
				if (empty) {
					--empty;
					bottom[++pushed] = 1;
					ans += 2;
				} else {
					bottom[++pushed] = 0;
					ans += 4;
				}
			}
		} else {
			if (poped < pushed) {
				empty += bottom[++poped];
			}
		}
		if (poped < pushed) {
			if (empty == n) {
				empty = n - 1;
				bottom[pushed] = 1;//两项都要有
			}
		}
	}
	cout << ans;
	return 0;
}
