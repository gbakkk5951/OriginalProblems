#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
string sugar;
int t[1000010],n,t1;
string eat[1000010];
int main() {
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	cin >> n;
	cin >> sugar;
	string sugars;
	sugars = sugar;
	for (int i = 0; i < n; i++) {
		cin >> eat[i];
	}
for (int y = 0; y < n; y++) {
	for (int i = 0; i < n; i++) {
		while (sugars.find(eat[i]) != string::npos) {
			t[y]++;
		sugars.replace(sugars.find(eat[i]),eat[i].size(),"2");
		}
    }
	sugars = sugar;
}
for (int i = 0; i < n; i++) {
	t1 = max(t[i],t[i+1]);
}
	printf("%d",t1);
	return 0;
}
