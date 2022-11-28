#include <bits/stdc++.h>
using namespace std;
inline bool imply(bool a, bool b) {
	return !a || b;
}
int main() {
    bool cereal, bread, apple, yogurt;
    cin >> cereal >> bread >> apple >> yogurt;
    cout << imply((cereal || bread) && apple, yogurt);
    return 0;
}
