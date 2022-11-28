#include <bits/stdc++.h>
using namespace std;
namespace MyList
{                                //用于区分我们的list和STL的list
    const int MaxSize = 2e5 + 1; //从1开始用，最多需要n+m个
    struct Item
    {
        int right, left; // link[0]和link[1]表示0方向和1方向的下一个表项的下标, 如果你害怕数字，可以改成 int left, right;
        // int val; 本题不需要
    };
    struct list
    {
        Item item[MaxSize]; //用于存储表项
        int size;           //有多少个有效的表项
        int cur;            //当前表项的下标
        int idx;            //每次先+1再作为新表项的下标来使用
        void init(int n)
        { //初始化1到n, 由于insert应当能够正确处理从0开始插入，所以可以直接复用insert
            size = 0;
            idx = 0;
            cur = 1; // 你需要先把几个变量初始化

            for (int i = 0; i < n; ++i)
                insert(), cur = idx;
            cur = 1;
        }
        void erase()
        { //删除cur指向的表项，具体细节见题面
            item[item[cur].left].right = item[cur].right;
            item[item[cur].right].left = item[cur].left;
            cur = item[cur].left;
            size--;
        }
        void insert()
        { //在当前表项的0方向新增一个表项，其下标为++idx ，{如果(size == 0) {请直接忽略其相对位置，并将当前下标设置为新表项的下标}}。
          //注意size == 0时和size == 1时，可以手动模拟一下应该怎么操作
          //请了解++x和x++的区别。
            if (size == 0)
            {
                cur = ++idx;
                item[cur].left = cur;
                item[cur].right = cur;
                size++;
            }
            else if (size == 1)
            {
                size++;
                item[cur].left = ++idx;
                item[cur].right = idx;
                item[idx].left = cur;
                item[idx].right = cur;
            }
            else
            {
                item[++idx].right = cur;
                item[idx].left = item[cur].left;
                item[item[cur].left].right = idx;
                item[cur].left = idx;
                size++;
            }
        }
        void move(int cnt, int dir)
        { //将cur向dir方向移动cnt步，具体细节见题面
            /*先进行优化，得到最优的dir和cnt，size == 0时需要忽略操作*/
            if (size == 0)
                return;
            cnt %= size;
            if (cnt < 0)
                cnt += size;
            if (cnt > (size / 2))
            {
                dir = !dir;
                cnt = size - cnt;
            }
            while (cnt--)
            {
                if (dir)
                    cur = item[cur].right;
                else
                    cur = item[cur].left;
            }
        }
        int getCur()
        { //取出当前表项的下标
            return size ? cur : -1;
        }
    };
}
int main()
{
    using MyList::list;
    //你可以在此处写个using MyList::list; 或者using namespace MyList; 这样就不用每次声明list都写MyList::前缀
    //你在这里using的namespace如果有内容和外面using的namespace冲突，则会就近原则，以最近的那一层大括号里的为准
    list l;
    int op, x, n;
    cin >> n;
    l.init(n);
    int m;
    cin >> m;
    while (m--)
    {
        cin >> op;
        switch (op)
        {
        case 0:
            if (l.size)
                l.erase();
            break;
        case 1:
            l.insert();
            break;
        case 2:
            if (l.size)
            {
                cin >> x;
                l.move(x, 0);
            }
            break;
        case 3:
            cin >> x;
            l.move(x, 1);
            break;
        default:
            cout << l.getCur() << endl;
            break;
        }
    }

    return 0;
}
