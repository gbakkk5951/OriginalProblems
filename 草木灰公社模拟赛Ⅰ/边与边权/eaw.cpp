using namespace std;
int main() {}
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

namespace OI {
template <typename Type>
	void read(Type &a) {
		char t;
		while (!isdigit(t = getchar()));
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10;
			a += t - '0';
		}
	}


struct Game {
	int n;
	vector<int> v;
	int ans;
	void init() {
		read();
		getAns();
	}
	void read() {
		OI::read(n);
		v.resize(n);
		for (int i = 0; i < n; i++) {
			OI::read(v[i]);
		}
	}
	int zero, rz, lz;
	void getAns() {
		for (int i = 0; i < n; i++) {
			if (v[i] == 0) {
				rz = i;
				zero = 1;
				break;
			}
		}
		if (zero) {
			for (i = n - 1; i >= 0; i--) {
				if (v[i] == 0) {
					lz = i;
					break;
				}
			}
		}
		if (zero) {
			win = ((n - 1 - lz) & 1) || (rz & 1);
			return;
		}
		
		
	}
}game[50005];




}
