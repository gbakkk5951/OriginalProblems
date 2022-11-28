#include <bits/stdc++.h>
using namespace std;
namespace MyList {//用于区分我们的list和STL的list
	const int MaxSize = 2e5 + 1;//从1开始用，最多需要n+m个 
	struct Item {
		int link[2];//link[0]和link[1]表示0方向和1方向的下一个表项的下标, 如果你害怕数字，可以改成 int left, right;
		//int val; 本题不需要
	};
	struct list {
		Item item[MaxSize];//用于存储表项
		int size;//有多少个有效的表项
		int cur;//当前表项的下标
		int idx;//每次先+1再作为新表项的下标来使用
		int next;
		int last;
		void init(int n) {//初始化1到n, 由于insert应当能够正确处理从0开始插入，所以可以直接复用insert
			/*to do*/ // 你需要先把几个变量初始化
			size = 0;
			idx = 1;
			cur = 1;
			for (int i = 0; i < n; ++i) insert(), cur = idx;
			cur = 1;
		}
		void erase() {//删除cur指向的表项，具体细节见题面
			//注意size == 1时
			/*to do*/
			if(size == 0) return;
			if(size == 1)
			{
			    cur = ++idx;
			    size--;
			    return;
			}
			next = item[cur].link[0];
			last = item[cur].link[1];
			item[next].link[1] = last;
			item[last].link[0] = next;
			cur = next;
			size--;		
		}
		void insert() {//在当前表项的0方向新增一个表项，其下标为++idx ，{如果(size == 0) {请直接忽略其相对位置，并将当前下标设置为新表项的下标}}。
			//注意size == 0时和size == 1时，可以手动模拟一下应该怎么操作
			//请了解++x和x++的区别。
			/*to do*/
			if(size == 0)
			{
				item[cur].link[0] = cur;
				item[cur].link[1] = cur;
			}
			else 
			{
			    next = item[cur].link[0];
			    item[cur].link[0] = ++idx;
				item[idx].link[0] = next;
				item[idx].link[1] = cur;
				item[next].link[1] = idx;
			}
			size++;
		}
		void move(int cnt, int dir) {//将cur向dir方向移动cnt步，具体细节见题面
			/*先进行优化，得到最优的dir和cnt，size == 0时需要忽略操作*/
			/*to do*/
			if(size == 0) return;
			if(cnt < 0) 
			{
			    cnt *= -1;
			    if(dir = 0) 
			    {
			        dir = 1;
			    }
			    else
			    {
			        dir = 0;
			    }
	         }
	         cnt %= size;
		/*	if(2 * cnt > size)
			{
			    cnt = size - cnt;
			    if(dir = 0)
			    {
			        dir = 1;
			    }
			    else 
			    {
			        dir = 0;
			    }    
			}
		*/
			while(cnt--)
			{
				cur = item[cur].link[dir];
			}
		}
		int getCur() {//取出当前表项的下标
			return size ? cur : -1;
		}

	};
}
int main() {
	using MyList::list;
	//你可以在此处写个using MyList::list; 或者using namespace MyList; 这样就不用每次声明list都写MyList::前缀
	//你在这里using的namespace如果有内容和外面using的namespace冲突，则会就近原则，以最近的那一层大括号里的为准
	list l;
	int op, x, n, m;
	cin >> n >> m;
	l.init(n);
	while(m--)
	{
		cin >> op;
		if(op == 0)
		{
			l.erase();
		} 
		else if(op == 1)
		{
			l.insert();
		}
		else if(op == 2)
		{
			cin >> x;
			l.move(x, 0);
		}
		else if(op == 3)
		{
			cin >> x;
			l.move(x, 1);
		}
		else if(op == 4)
		{
			x = l.getCur();
			cout << x << endl;
		}
	}
	
	return 0;
}
