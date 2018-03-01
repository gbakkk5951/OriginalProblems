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
	void read() {
		OI::read(n);
		v.resize(n);
		for (int i = 0; i < n; i++) {
			OI::read(v[i]);
		}
	}
}game[50005];




}
