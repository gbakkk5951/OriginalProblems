#include <bits/stdc++.h>
using namespace std;
int main() 
{
	int T, a, b, c;
	cin >> T;
	while (T--)
	{
		cin >> a >> b >> c;
		cout << (char)(((a & 1) == (b & 1) && (b & 1) == (c & 1)) ? 'y' : 'n') << endl;
	}
	return 0;
}
