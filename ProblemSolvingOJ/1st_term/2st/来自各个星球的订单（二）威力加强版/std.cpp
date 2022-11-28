using namespace std;
#include <bits/stdc++.h>
enum Type{Area, Edge, Point, None};
char const *Output[] = {[Area] = "Area\n", [Edge] = "Edge\n", [Point] = "Point\n", [None] = "None\n"};
int x[2][2][2][2];
int tp[2];
char NodeInArea() {
	char Ret = 0;
	
	return Ret;
}
int main() {
	int Tn;
	cin >> Tn;
	for (int T = 1; T <= Tn; T++) {
		for (int I = 0; I < 2; ++I) {
			int xin[2][2];
			for (int i = 0; i < 4; i++) {
				cin >> xin[i];
			}
			for (int i = 0; i < 2; i++) {
				if (xin[i][0] > xin[i][1]) swap(xin[i][0], xin[i][1]);
			}
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					x[I][i][j]
				}
			}
			x[I][0][0][0] = x1;
			x[I][0][0][1] = y1;
			x[I][1][0] = x2;
			x[I][1][1] = y1;
			x[I][2][0] = x2;
			x[I][1][0] = y1;
		}
	}
	return 0;
}
