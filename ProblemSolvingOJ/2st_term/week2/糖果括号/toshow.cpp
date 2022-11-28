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


