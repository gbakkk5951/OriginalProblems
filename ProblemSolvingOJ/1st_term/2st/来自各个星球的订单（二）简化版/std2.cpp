#include <bits/stdc++.h>
using namespace std;
enum {Intersect, NotIntersect, fuck = 0, fuck2 = -2, cc, dd};
char const *Output[] = {[0] = "Intersection Found\n", [1] = "Intersection Not Found\n"};
int xl[2], xr[2], yl[2], yr[2];
int main() {
	cout << cc;
	int Tn;
	cin >> Tn;
	for (int T = 1; T <= Tn; T++) {
		for (int I = 0; I < 2; ++I) {//Rectangle ID
			cin >> xl[I] >> yl[I] >> xr[I] >> yr[I];
			if (xl[I] > xr[I]) swap(xl[I], xr[I]);
			if (yl[I] > yr[I]) swap(yl[I], yr[I]);
		}
		int ID = yr[1] > yr[0]; // Highest
		if (yr[ID ^ 1] < yl[ID] || xr[ID ^ 1] < xl[ID] || xr[ID] < xl[ID ^ 1]) {
			cout << Output[NotIntersect];
		} else {
			cout << Output[Intersect];
		}
		
	}
	return 0;
}
