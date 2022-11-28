#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;
long long Max = -1e19;
long long rankplus(int start, int now, int k, int n, int* temp, int* v) {
	for (int i = start; i <= n; i++) {
		temp[now] = i;
		if (now == 1) {
			long long good = 0;
			for (int j = k; j >= 1; j--) {
				long long power = 1;
				for (int k = 1; k <= j - 1; k++) {
					power *= 3;
				}
				good += v[temp[j]] * power;
			}
			if (good > Max) { Max = good; }
		}
		else
			rankplus(i + 1, now - 1, k, n, temp, v);
	}
	return Max;
}
int main() {
	int n, k;
	cin >> n >> k;
	int v[26];
	int temp[26];
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	cout << rankplus(1, k, k, n, temp, v);
	return 0;


}
