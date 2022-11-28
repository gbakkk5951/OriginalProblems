#pragma warning(disable: 4996)
#include <iostream>
const long long BIG = 998244353;
using namespace std;

int main()
{
	int list1[100] = {};
	for (int k = -7; k <= 7; ++k)
		list1[k * (3 * k - 1) / 2] += (k & 1) ? -1 : 1;
	for (int i = 0; i < 100; ++i) {
		printf("list1 %d = %d\n", i, list1[i]);
	}
	long long list2[100] = {1};
	for (int i = 1; i <= 80; ++i)
		for (int j = 0; j < i; ++j) {
			list2[i] -= list2[j] * list1[i - j];
		}
	int x;
	scanf("%d", &x);
	long long res = 0;
	for (int i = 0; i < x; ++i) {
		res += list2[i] * (x - i);
	}
	printf("%lld", res % BIG);
}
