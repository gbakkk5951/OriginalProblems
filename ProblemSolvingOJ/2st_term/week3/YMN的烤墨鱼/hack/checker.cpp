#include <bits/stdc++.h>
using namespace std;
int arr[(int)1e6 + 10];
int main() {
	int Tn, n;
	cin >> Tn;
	for (; Tn--;) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> arr[i];
		}
		sort(arr + 1, arr + n + 1);
		for (int i = 1; i <= n; ++i) {
			if (arr[i] != i) {
				cerr << "???";
			}
		}
	}
}
