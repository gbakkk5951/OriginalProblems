#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5000005;
int trie[N][2], tot;
int end[N];
char s[N];
void add(void) {
	int p = 0, len = strlen(s + 1);
	for (int i = 1;i <= len; i++) {
		int digit = s[i] - '0';
		if (!trie[p][digit]) trie[p][digit] = ++tot;
		p = trie[p][digit];
	}
	end[p]++;
}

int fail[N];
queue<int> q;

void build() {
	if (trie[0][0]) q.push(trie[0][0]);
	if (trie[0][1]) q.push(trie[0][1]);
	while (q.size()) {
		int p = q.front(); q.pop();
		for (int i = 0;i <= 1; i++) {
			int j = trie[p][i];
			if (!j) trie[p][i] = trie[fail[p]][i];
			else {
				fail[j] = trie[fail[p]][i];
				q.push(j);
			}
		}
	}
}

char s1[N];

int query() {
	int ans = 0, len = strlen(s1 + 1);
	int p = 0;
	for (int i = 1;i <= len; i++) {
		p = trie[p][s1[i] - '0'];
		for (int t = p; t && end[t]; t = fail[t])
			if (end[t]) p = 0, ans++;
	}
	return ans;
}

int main() {
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	int n;
	scanf ("%d", &n);
	scanf ("%s", s1 + 1);
	for (int i = 1;i <= n; i++) {
		scanf ("%s", s + 1);
		add();
	}
	build();
	int ans = query();
	cout << ans << endl;
	return 0;
}
/*
5
010101010111
010
0100
11
1000
1110

*/
