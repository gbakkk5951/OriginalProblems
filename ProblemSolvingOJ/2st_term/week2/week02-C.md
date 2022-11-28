
### 1. 考察知识：性质挖掘、双端队列、算法优化
一些性质已经在题目提示中有，这里直接讲做法
维护一个双端队列
初始有n个，我们看作n次右侧插入
每次插入时判断是否构成 
() 或 sugar sugar 或 (sugar) 
若构成则合并为一个新的 sugar
仅需要在该侧队头为sugar时更新一次answer




### 2. 优秀代码
**零**
作者：张浩宇
代码写的比较短、比较潦草，
详细见一
```c++
#include <bits/stdc++.h>
using namespace std;
struct ele {
	int type;
	long long v;
};
typedef deque<ele> d;
d q;
long long ans = 0;
template <typename iterator>
void chk(iterator (d::*begin) (), void (d::*pop) (), int l, int r) {
	long long sum;
	while (q.size() > 1) {
		iterator beg = (q.*begin)();
		if (beg->type == 2 && (beg + 1)->type == 2 || beg->type == l && (beg + 1)->type == r) {	
			*(beg + 1) = (ele) {2, beg->v + (beg + 1)->v};
			(q.*pop)();
	 	} else
		if (q.size() > 2 && beg->type == l && (beg + 1)->type == 2 && (beg + 2)->type == r) {
			*(beg + 2) = (ele) {2, beg->v + (beg + 1)->v + (beg + 2)->v};
			(q.*pop)();
			(q.*pop)();
		} else {
			break;
		}
	}
	if ((q.*begin)()->type == 2) ans = max(ans, (q.*begin)()->v);
}
const int MXN = 1e6 + 10;
int t[MXN];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t[i]);
	}
	long long v;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &v);
		q.push_back((ele) {t[i], v});
		chk(&d::rbegin, &d::pop_back, 1, 0);
	}
	printf("%lld\n", ans);
	for (int i = 1, t, p; i <= m; ++i) {
		scanf("%d%d%lld", &p, &t, &v);
		if (p) {
			q.push_back((ele) {t, v});
			chk(&d::rbegin, &d::pop_back, 1, 0);
		} else {
			q.push_front((ele) {t, v});
			chk(&d::begin, &d::pop_front, 0, 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}


```

**一**
作者：张浩宇
耗时：440ms

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
const int MXN = 1e6 + 10;
const int left_bracket = 0, right_bracket = 1, sugar = 2; 
struct Element {
	int type;
	lld sweet;
};
typedef deque<Element> d;
d q;

int type[MXN];//仅用于读入初始数据
lld answer = 0;

template <typename iterator>
void update(iterator (d::*get_front) (), void (d::*pop_front) (), /*指向成员函数的指针*/
		int front_bracket, int back_bracket) {//合并后，更新答案
	while (q.size() > 1) {//这个每次最多执行两轮，即合并括号1次，两个糖合并1次
		iterator front = (q.*get_front)();
		if (front->type == sugar && (front + 1)->type == sugar  // 两个糖合并
		|| front->type == front_bracket && (front + 1)->type == back_bracket) {	 //或 相邻括号合并
			*(front + 1) = (Element) {sugar, front->sweet + (front + 1)->sweet};
			(q.*pop_front)();
	 	} else
		if (q.size() > 2 
		&& front->type == front_bracket 
		&& (front + 1)->type == sugar 
		&& (front + 2)->type == back_bracket) {// 括号 糖 括号  合并
			*(front + 2) = (Element) {sugar, front->sweet + (front + 1)->sweet + (front + 2)->sweet};
			(q.*pop_front)();
			(q.*pop_front)();
		} else {
			break;
		}
	}
	if ((q.*get_front)()->type == sugar) {
		answer = max(answer, (q.*get_front)()->sweet);//答案单调不降，没有被修改的不需要访问
	}
}
void inline right_push(int type, lld sweet) { //右侧加入
	q.push_back((Element) {type, sweet});
	update(&d::rbegin, &d::pop_back, right_bracket, left_bracket); //取出成员函数指针时的 & 不能省, 如果有重载需要显式说明参数列表
}
void inline left_push(int type, lld sweet) { //左侧加入
	q.push_front((Element) {type, sweet});
	update(&d::begin, &d::pop_front, left_bracket, right_bracket);
}
template <typename Type>
    void read(Type &a) {//读入优化
        int t;
        while (!isdigit(t = getchar()));
        a = t - '0';
        while ( isdigit(t = getchar())) {
            a *= 10; a += t - '0';
        }
    }
int main() {
	int n, m;
	read(n); read(m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &type[i]);
	}
	lld sweet;
	for (int i = 1; i <= n; ++i) {
        read(sweet);
		right_push(type[i], sweet);
	}
	printf("%lld\n", answer);
	for (int i = 1, type, position; i <= m; ++i) {
        read(position); read(type); read(sweet);
		if (position == 1) {
			right_push(type, sweet);
		} else {
			left_push(type, sweet);
		}
		printf("%lld\n", answer);
	}
	return 0;
}




```




**二**
作者：李杨彬
耗时：259ms
```C++
#include <bits/stdc++.h>
using namespace std;

template <typename Type>
void read(Type &a) {
    int t;
    while (!isdigit(t = getchar()));
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
}

deque<long long> vals{0};
deque<long long> r_vals;
deque<long long> l_vals;

long long mxn = 0;

inline void auto_push_front (int type, long long val) {
    switch (type) {
        case 2:
            vals.front() += val;
            if (vals.front() > mxn) mxn = vals.front();
            break;
        case 1:
            vals.push_front(0);
            l_vals.push_front(val);
            break;
        case 0:
            if (l_vals.empty()) {
                r_vals.push_front(val);
                vals.push_front(0);
                break;
            } else {
                long long num = l_vals.front() + vals.front() + val;
                l_vals.pop_front(), vals.pop_front();
                vals.front() += num;
                if (vals.front() > mxn) mxn = vals.front();
            }
            break;
    }
}

inline void auto_push_back (int type, long long val) {
    switch (type) {
        case 2:
            vals.back() += val;
            if (vals.back() > mxn) mxn = vals.back();
            break;
        case 0:
            vals.push_back(0);
            r_vals.push_back(val);
            break;
        case 1:
            if (r_vals.empty()) {
                l_vals.push_back(val);
                vals.push_back(0);
                break;
            } else {
                long long num = r_vals.back() + vals.back() + val;
                r_vals.pop_back(), vals.pop_back();
                vals.back() += num;
                if (vals.back() > mxn) mxn = vals.back();
            }            
            break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N, M;
    vector<int> types;
    read(N), read(M);
    types.resize(N);
    for (int i = 0; i < N; i++)
        read(types[i]);

    int pos, type;
    long long value;
    for (int i = 0; i < N; i++) {
        read(value);
        auto_push_back(types[i], value);
    }
    cout << mxn << "\n";
    
    while (M--) {
        read(pos), read(type), read(value);
        if (pos) auto_push_back(type, value);
        else auto_push_front(type, value);
        cout << mxn << "\n";
    }
    return 0;

}
```
