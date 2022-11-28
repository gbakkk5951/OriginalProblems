#include <iostream>
using namespace std;
int number[100010];
int zero[100010];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &number[i]);
	zero[n + 1] = 0;
	for (int i = n; i >= 1; i--)
	{
		if (number[i] == 0)
			zero[i] = 0;
		else
			zero[i] = zero[i + 1] + 1;
	}
	for (int i = 1; i <= n; i++)
	{
		if (zero[i] == n - i + 1)
			printf("overflow\n");
		else
			printf("%d\n", zero[i]);
	}
	return 0;
}
