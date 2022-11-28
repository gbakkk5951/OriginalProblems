#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1000005;
char s[N];
struct node{
	int x;
	int pre, nxt;
}a[N];
int head, tail, tot;
void add_tail(int x) {
	a[++tot] = (node){x, tail, 0};
	a[tail].nxt = tot;
	tail = tot;
}

void add_head(int x) {
	a[++tot] = (node){x, 0, head};
	a[head].pre = tot;
	head = tot;
}
int ans;
int main() {
	freopen("hss.in", "r", stdin);
	freopen("hss.out","w", stdout);
	int n, m;
	scanf ("%d %d", &n, &m);
	scanf ("%s", s + 1);
	for (int i = 1;i <= n; i++) {
		int x = 0;
		if (s[i] == 's') x = 1;
		if (s[i] == 'h') x = -1;
		add_tail(x);
	}
	int sum = 0,cnt = 0;
	for (int i = 1;i <= n; i++) {
		sum = 0, cnt = 0;
		for (int j = i;j <= n; j++) {
			sum += a[j].x;
			if (sum < 0) break;
			cnt++;
			if (sum == 0) ans = max(ans, cnt);
		}
	}
	printf("%d\n", ans);
	head = 1;
	for (int i = 1;i <= m; i++) {
		int x = 0, k;
		scanf ("%d", &k);
		char tmp[5];
		scanf ("%s", tmp);
		if (tmp[0] == 's') x = 1;
		if (tmp[0] == 'h') x = -1;
		if (k == 1) add_head(x);
		else add_tail(x);
		sum = 0, cnt = 0;
		if (k == 1)
		for (int j = head; j ; j = a[j].nxt) {
			sum += a[j].x;
			if (sum < 0) break;
			cnt++;
			if (sum == 0) ans = max(ans, cnt);
		}
		else 
		for (int j = tail; j ; j = a[j].pre) {
			sum += a[j].x;
			if (sum > 0) break;
			cnt++;
			if (sum == 0) ans = max(ans, cnt);
		}
		printf("%d\n", ans);
	}
	return 0;
}
/*
6 3
Sssshh
2 h
1 h 
1 s
*/
