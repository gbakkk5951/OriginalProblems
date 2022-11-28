#include <iostream>

using namespace std;

const int N = 4e6;
int status[N + 5]; // 1 栈顶/ 2 被压/ 3 倒序/
char a[N + 5];

int main() {
	int n, m;
	cin >> n >> m;
	getchar();
	int x = 0, y = 0;
	for (int i = 0; i < m; i++) {
		scanf("%c", &a[i]);
		if (a[i] == '0') {
			x++;
		}
		else if (a[i] == '1') {
			if (x > 0) {
				y++;
				x--;
			}
		}
	}
	int head = 0, tail = 0;
	int empty = n, punum = 0, ponum = 0;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		if (a[i] == '0') {
			if (ponum + punum == y) {
				continue;
			}
			punum++;
			if (empty > 0) {
				empty--;
				status[tail] = 1;
				tail++;
			}
			else {
				status[tail] = 1;
				status[tail - 1] = 2;
				tail++;
			}
		}
		else if (a[i] == '1') {
			if (punum == 0)
				continue;
			ponum++; punum--;
			ans += 2;
			if (status[head] == 1) {
				if (status[head + 1] == 3) {
					status[head + 1] = 1;
				}
				else {
					empty++;
				}
			}
			else if(status[head] == 2) {
				int tmp = head + 1;
				while (status[tmp] == 2) {
					status[tmp] = 3;
					tmp++;
				}
				status[tmp] = 3;
				status[head + 1] = 1;
				ans += 2 * (tmp - head);
				if (status[tmp + 1] == 1){
					status[tmp + 1] = 3;
					empty++;
				}
			}
			head++;
		}
	}
	cout << ans << endl;
}
