#include <bits/stdc++.h>
#define MAXN 1000005
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
int n;
int k, a[MAXN], b[MAXN], c[MAXN], maxn[MAXN], minn1[MAXN], minn2[MAXN];
void read(int &x)
{
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	x = s * f;
	return ;
}
void print(int x)
{
	if (x < 0) {
		putchar('-');
		x *= -1;
	}
	ll now = 1;
	while (x >= now * 10) now *= 10;
	if (x == 0) putchar('0');
	while (x) {
		putchar('0' + x / now);
		x %= now;
		now /= 10;
	}
	putchar(' ');
	return ;
}
void Do_max(int x) {
	if (x == n - 1) {
		b[x + 1] += b[x];
		b[x] = -1;
		return ;
	}
	if (b[x + 1] == 0) Do_max(x + 1);
	else {
		b[x + 1] += b[x];
		b[x] = -1;
		return ;
	}
	return ;
}
void Do_min(int x)
{
	if (x == n - 1) {
		b[x + 1] = ((ll)b[x] + (ll)b[x + 1]) % k;
		b[x] = -1;
		return ;
	}
	if ((ll)minn1[x + 1] + (ll)minn2[x + 1] >= (ll)k || ((ll)b[x] + (ll)minn1[x + 2] < (ll)k && b[x] > b[x + 1])) {
		int now1 = n;
		while ((ll)b[x] + (ll)b[now1] >= (ll)k) now1--;
		b[now1] = ((ll)b[x] + (ll)b[now1]) % (ll)k; 
		b[x] = -1;
	}
	else Do_min(x + 1);
	return ;
}
int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= n; i++) b[i] = a[i], c[i] = a[i];
	int maxn1 = b[1], maxn2 = -1;
	for (int i = 2; i <= n; i++)
		if (b[i] >= maxn1) {
			maxn2 = maxn1;
			maxn1 = b[i];
		}
		else if (b[i] > maxn2) maxn2 = b[i];
	for (int i = n; i >= 1; i--)
		maxn[i] = max(maxn[i + 1], b[i]);
	if ((ll)maxn1 + (ll)maxn2 >= (ll)k) {
		int now1 = 1;
		while (b[now1] != 1 && now1 <= n) now1++;
		if (now1 <= n && maxn[now1 + 1] == k - 1) {
			int now2 = n;
			while(b[now2] != k - 1) now2--;
			b[now2] = 0;
		}
		now1 = n;
		while ((ll)c[now1] + (ll)maxn[now1 + 1] < (ll)k || c[now1] == 1) {
			now1--;
			if (!now1) break;
		}
		if (now1) {
			int now2 = n;
			while ((ll)c[now1] + (ll)c[now2] < (ll)k) now2--;
			c[now2] = ((ll)c[now1] + (ll)c[now2]) % (ll)k;
			c[now1] = 1;
		}
		bool flag1 = 0, flag2 = 0, flag = 0;
		for (int i = 1; i <= n; i++) 
			if (a[i] != b[i]) {
				flag1 = 1;
				break;
 			}
 		for (int i = 1; i <= n; i++) 
			if (a[i] != c[i]) {
				flag2 = 1;
				break;
 			}
 		if (!flag2) {
 			for (int i = 1; i <= n; i++)
				print(b[i]);
		 }
		else if (!flag1) {
		 	for (int i = 1; i <= n; i++)
				print(c[i]);
		}
		else {
			for (int i = 1; i <= n; i++)
				if (b[i] > c[i]) {
					for (int j = 1; j <= n; j++)
						print(b[j]);
					flag = 1;
					break;
				}
				else if (b[i] < c[i]) {
					for (int j = 1; j <= n; j++)
						print(c[j]);
					flag = 1;
					break;
				}
			if (!flag) {
				for (int j = 1; j <= n; j++)
					print(b[j]);
			}
		}
	}
	else {
		Do_max(1);
		int h = 1;
		while (h <= n && (b[h] == -1 || !b[h])) h++;
		if (h > n) printf("0");
		else 
			for (int i = h; i <= n; i++)
				if (b[i] != -1) print(b[i]);
	}
	printf("\n");
	for (int i = 1; i <= n; i++) b[i] = a[i], c[i] = a[i];
	int minn11 = min(b[1], b[2]), minn12 = max(b[1], b[2]);
	for (int i = 3; i <= n; i++)
		if (b[i] <= minn11) {
			minn12 = minn11;
			minn11 = b[i];
		}
		else if (b[i] < minn12) minn12 = b[i];
	if ((ll)minn11 + (ll)minn12 >= (ll)k) {
		if (b[1] == 1)
			b[2] = 0;
		else {
			b[2] = ((ll)b[1] + (ll)b[2]) % (ll)k;
			b[1] = 1;
		}
	}
	else {
		minn1[n] = b[n]; minn2[n] = inf;
		for (int i = n - 1; i >= 1; i--) {
			minn1[i] = minn1[i + 1];
			minn2[i] = minn2[i + 1];
			if (b[i] <= minn1[i]) {
				minn2[i] = minn1[i];
				minn1[i] = b[i];
			}
			else if (b[i] < minn2[i]) minn2[i] = b[i];
		}
		Do_min(1);
	}
	int h = 1;
	while (h <= n && (b[h] == -1 || !b[h])) h++;
	if (h > n) printf("0");
	else 
		for (int i = h; i <= n; i++)
			if (b[i] != -1) print(b[i]);
	return 0;
}
