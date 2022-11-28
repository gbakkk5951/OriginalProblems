#include <bits/stdc++.h>
using namespace std;
namespace L {//用于区分我们的list和STL的list
	const int maxn = 2e5 + 1;//从1开始用，最多需要n+m个 
	struct item {
		int link[2];//link[0]和link[1]表示0方向和1方向的下一个表项的下标, 如果你害怕数字，可以改成 int left, right;
		//int val; 本题不需要
	};
	struct List {
		item list[maxn];
		int size;//有多少个有效的表项
		int cur;//当前表项的下标
		int idx;//每次先+1再作为新表项的下标来使用
		void init(int n) {//初始化1到n, 由于insert应当能够正确处理从0开始插入，所以可以直接复用insert
			for (int i = 0; i < n; ++i) insert(), cur = idx;
			cur = 1;
		}
		void erase() {
			//注意size == 1时
			/*to do*/
			if (!(size = max(0, size - 1))) return;
			for (int i = 0; i < 2; ++i) {
				list[list[cur].link[i]].link[i ^ 1] = list[cur].link[i ^ 1];
			}
			cur = list[cur].link[0];
		}
		void insert() {//在当前表项的0方向新增一个表项，其下标为++idx ，如果size == 0请直接忽略其相对位置，并将当前下标设置为新表项的下标。
			//注意size == 0时和size == 1时，可以手动模拟一下应该怎么操作
			//请了解++x和x++的区别。
			/*to do*/
			++idx;
			if (++size == 1) {
				cur = idx;
				list[cur].link[0] = list[cur].link[1] = cur;
			} else {
				list[idx].link[1] = cur;
				list[idx].link[0] = list[cur].link[0];
				list[list[cur].link[0]].link[1] = idx;
				list[cur].link[0] = idx;
			}
		
		}
		void move(int cnt, int dir) {
			/*先进行优化，得到最优的dir和cnt，size == 0时需要忽略操作*/
			/*to do*/
			if (size == 0) return;
			cnt = (cnt % size + size) % size;
			if (size - cnt < cnt) {
				dir ^= 1;
				cnt = size - cnt;
			}
			while (cnt--) {
				cur = list[cur].link[dir];
			}
		}
		int getcur() {//取出当前表项的下标
			return size ? cur : -1;
		}

	}list;//全局变量，默认的初始值全部为0 
}
int main() {
	//你可以在此处写个using L::list; 或者using namespace L; 这样就不用每次调用list都写L::前缀
	int op, x, n, m;
	ios::sync_with_stdio(false);
	cin >> n >> m;
	L::list.init(n);
	/*to do*/
	using L::list;
	for (int i = 1; i <= m; ++i) {
		cin >> op;
		switch (op) {
			case 0: {
				list.erase();
				break;
			}
			case 1: {
				list.insert();
				break;
			}
			case 2: {
				cin >> x;
				list.move(x, 0);
				break;
			}
			case 3: {
				cin >> x;
				list.move(x, 1);
				break;
			}
			case 4: {
				cout << list.getcur() << endl;
				break;
			}
		}
	}
	return 0;
}
