#include <bits/stdc++.h>
using namespace std;
string platformName[3], woodName[10];
int woodId[3][10];
int top[3];
int n;
void move(int src, int dst) {
	cout << "Move " << woodName[woodId[src][top[src]]] << " from " << platformName[src] << " to " << platformName[dst] << '.' << endl;
	woodId[dst][++top[dst]] = woodId[src][top[src]--];
}
void hanoi(int src, int dst, int helper, int amount) {
	if (amount > 1) {
		hanoi(src, helper, dst, amount - 1);
	}
	move(src, dst);
	if (amount > 1) {
		hanoi(helper, dst, src, amount - 1);
	}
}
int main() {
	memset(top, -1, sizeof(top));
	cin >> n;
	cin.ignore();
	for (int i = 0; i < 3; ++i) getline(cin, platformName[i]);
	for (int i = 0; i < n; ++i) getline(cin, woodName[i]), woodId[0][++top[0]] = i;
	hanoi(0, 1, 2, n);
	return 0;
}
