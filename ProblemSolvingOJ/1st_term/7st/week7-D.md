
### 1. 考察知识：双向循环链表

思路如下：


### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
^表示异或，
0 ^ 0 == 0;
0 ^ 1 == 1;
1 ^ 0 == 1;
1 ^ 1 == 0;
有兴趣的同学可以提前了解下二进制的位运算

```c++
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
			cnt = (cnt % size + size) % size; //+size是为了消除负数
			if (size - cnt < cnt) {//是否换方向移动更优
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


```




**二**
作者：朱宇博
使用了left, right来表示左右的东西

```C++

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
namespace MyList
{
  const int MaxSize = 2e5 + 1;
  struct Item
  {
    int left, right;
  };
  struct list
  {
    Item item[MaxSize];
    int size;
    int cur;
    int idx;

    void init(int n)
    {
      size = 0;
      idx = 0;
      for (int i = 1; i <= n; i++)
        insert(), cur = idx;
      cur = 1;
    }

    void erase()
    {
      if (size == 0)
        return;
      else if (size == 1)
      {
        size--;
        cur = -1;
      }
      else
      {
        size--;
        int left = item[cur].left;
        int right = item[cur].right;
        item[left].right = right;
        item[right].left = left;
        cur = right;
      }
    }

    void insert()
    {
      idx = idx + 1;
      if (size == 0)
      {
        size++;
        cur = idx;
        item[cur].right = item[cur].left = cur;
      }
      else
      {
        size++;
        item[idx].left = cur;
        item[idx].right = item[cur].right;
        item[item[idx].right].left = idx;
        item[cur].right = idx;
      }
    }

    void move(int cnt, int dir)
    {
      if (size == 0)
        return;
      bool left = (dir == 1 && cnt >= 0) || (dir == 0 && cnt < 0);
      cnt = cnt % size;
      if (cnt < 0) cnt = size - ((cnt + size) % size);
      if (cnt > 500) left = !left, cnt = size - cnt;
      if (left)
        while (cnt--)
          cur = item[cur].left;
      else
        while (cnt--)
          cur = item[cur].right;
        
    }

    int getCur()
    {
      return size ? cur : -1;
    }
  };
}

int main()
{
  int n, m;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  using namespace MyList;
  list l;
  l.init(n);
  for (int i = 1; i <= m; ++i)
  {
    int opt, x;
    cin >> opt;
    if (opt == 0)
    {
      l.erase();
    }

    else if (opt == 1)
    {
      l.insert();
    }

    else if (opt == 2)
    {
      cin >> x;
      l.move(x, 0);
    }
    else if (opt == 3)
    {
      cin >> x;
      l.move(x, 1);
    }
    else if (opt == 4)
    {
      printf("%d\n", l.getCur());
    }
    else
      assert(0);
  }
  return 0;
}
```
**三**
作者：邓振霄

```c++
#include <bits/stdc++.h>
using namespace std;
namespace MyList { //用于区分我们的list和STL的list
const int MaxSize = 2e5 + 1; //从1开始用，最多需要n+m个
struct Item {
    int link[2]; //link[0]和link[1]表示0方向和1方向的下一个表项的下标, 如果你害怕数字，可以改成 int left, right;
    //int val; 本题不需要
};
struct list {
    Item item[MaxSize]; //用于存储表项
    int size; //有多少个有效的表项
    int cur; //当前表项的下标
    int idx; //每次先+1再作为新表项的下标来使用
    void init(int n)
    { //初始化1到n, 由于insert应当能够正确处理从0开始插入，所以可以直接复用insert
        /*to do*/ // 你需要先把几个变量初始化
        size = idx = 0;
        for (int i = 0; i < n; ++i)
            insert(), cur = idx;
        cur = 1;
    }
    void erase()
    { //删除cur指向的表项，具体细节见题面
        //注意size == 1时
        /*to do*/
        if (size == 0)
            return;
        item[item[cur].link[0]].link[1] = item[cur].link[1];
        item[item[cur].link[1]].link[0] = item[cur].link[0];
        cur = item[cur].link[0];

        --size;
    }
    void insert()
    { //在当前表项的0方向新增一个表项，其下标为++idx ，{如果(size == 0) {请直接忽略其相对位置，并将当前下标设置为新表项的下标}}。
        //注意size == 0时和size == 1时，可以手动模拟一下应该怎么操作
        //请了解++x和x++的区别。
        ++idx;
        if (size == 0) {
            cur = idx;
            item[cur].link[0] = cur;
            item[cur].link[1] = cur;
        } else {
            item[item[cur].link[0]].link[1] = idx;
            item[idx].link[0] = item[cur].link[0];
            item[cur].link[0] = idx;
            item[idx].link[1] = cur;
        };

        ++size;
    }
    void move(int cnt, int dir)
    { //将cur向dir方向移动cnt步，具体细节见题面
        /*先进行优化，得到最优的dir和cnt，size == 0时需要忽略操作*/
        /*to do*/
        if (size == 0)
            return;
        cnt = (cnt % size + size) % size;
        if (cnt > size - cnt)
            cnt = size - cnt, dir = 1 - dir;
        while (cnt--)
            cur = item[cur].link[dir];
    }
    int getCur()
    { //取出当前表项的下标
        return size ? cur : -1;
    }
};
}
int main() {
	//你可以在此处写个using MyList::list; 或者using namespace MyList; 这样就不用每次声明list都写MyList::前缀
	//你在这里using的namespace如果有内容和外面using的namespace冲突，则会就近原则，以最近的那一层大括号里的为准
	MyList::list l;
	int op, x, n;
	cin >> n;
	l.init(n);
	/*to do*/
	int m;
	cin >> m;
	while(m--)
	{
		int op;cin >> op;
		if(op==0) l.erase();
		else if(op==1) l.insert();
		else if(op==4) cout << l.getCur() << endl;
		else 
		{
			cin >> x;
			l.move(x,op-2);
		};
	};
	return 0;
}
```
