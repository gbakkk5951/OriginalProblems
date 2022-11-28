#include <bits/stdc++.h>
using namespace std;
const int MXN = 5e5 + 10;
typedef pair<int, int> p;
p arr[MXN], tmp[MXN];
long long rev;
long long mncnt;
int n;
template <typename Type>
void read(Type &a) {
	int t, f = 1;
	while (!isdigit(t = getchar())) {
		f = t == '-' ? -1 : f;
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a *= f;
}
void merge_sort(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	int tn = 0;
	int al = l, bl = mid + 1;
	while (al <= mid && bl <= r) {
		if (arr[al] < arr[bl]) {
			tmp[tn++] = arr[al];
			++al;
			rev += bl - (mid + 1);
		} else {
			tmp[tn++] = arr[bl];
			++bl;
		}
	}
	while (al <= mid) {
		tmp[tn++] = arr[al];
		++al;
		rev += bl - (mid + 1);
	}
	while (bl <= r) {
		tmp[tn++] = arr[bl];
		++bl;
	}
	memcpy(arr + l, tmp, (r - l + 1) * sizeof(p));
}
int main() { //用正、负结合数卡一下直接相加法
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(arr[i].first); read(arr[i].second);
	}
	p mn = arr[1];
	mncnt = 1;
	for (int i = 2; i <= n; ++i) {
		if (arr[i] < mn) {
			mn = arr[i];
			++mncnt;
		}
	}
	merge_sort(1, n);
	cout << rev * 2 + n - mncnt;
	
}
