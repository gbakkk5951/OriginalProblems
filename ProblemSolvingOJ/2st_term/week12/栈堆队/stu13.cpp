#include <cstdio>
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <queue>
#include <utility>
const int maxm = 4e6 + 10;
std::vector<std::pair<int, int>> Change;
std::pair<int, int> now_need(0, 0), rev(0, 0);
std::queue<std::pair<int, int>> Now_in;

int n = 0, m = 0, i = 0, All_count = 0;
int pop_num = 0, Limit = -1; //来看看我们最多需要维护到哪里，只要在范围内的就必须要维护
int nownum = 0, now_push = 0, now_pop = 0;
int blank_stack = 0;
int _4_Num = 0, _2_Num = 0;
//一下四个int变量用来记录当前的栈堆情况，不同的栈根据分类这样就可以简单地表达出来
char tmp[maxm];

int main(void)
{
    scanf("%d %d", &n, &m);
    blank_stack = n;
    scanf("%s", tmp);
    nownum = i = 0;
    while (i < m)
    {
        now_push = 0;
        while (i < m && tmp[i] == '0')
        {
            now_push++;
            i++;
        }
        now_pop = 0;
        while (i < m && tmp[i] == '1')
        {
            now_pop++;
            i++;
        }
        nownum += now_push;
        int Need_pop = std::min(nownum, now_pop);
        if (now_push)
        {
            now_need.first = now_push;
            now_need.second = Need_pop;
            Change.push_back(now_need);
        }
        pop_num += Need_pop;
        nownum -= Need_pop;

    } // check_ok
    nownum = 0;
    for (auto j = Change.begin(); j != Change.end();)
    {
        if (nownum >= pop_num)
        {
            (j - 1)->second += j->second;
            j = Change.erase(j);
        }
        else
        {
            nownum += j->first;
            if (nownum > pop_num)
                j->first -= nownum - pop_num;
            j++;
        }
    } // check_ok
    for (auto j = Change.begin(); j != Change.end(); j++)
    {
        //printf("%d %d\n", j->first, j->second);
        if (j->first > blank_stack)
        {
            if (blank_stack)
            {
                rev.first = blank_stack;
                rev.second = 2;
                Now_in.push(rev);
            }
            rev.first = j->first - blank_stack;
            rev.second = 4;
            Now_in.push(rev);
            blank_stack = 0;
        }
        else
        {
            rev.first = j->first;
            rev.second = 2;
            Now_in.push(rev);
            blank_stack -= rev.first;
        } // in
        //printf("After this round of push we now have %d blank stacks.\n", blank_stack);
        int now_need_pop = j->second;
        while (now_need_pop)
        {
            assert(!Now_in.empty());
            std::pair<int, int> tmp_out = Now_in.front();
            if (tmp_out.first > now_need_pop)
            {
                Now_in.front().first -= now_need_pop;
                if (tmp_out.second > 3) // 4
                {
                    _4_Num += now_need_pop;
                    if (blank_stack > n - 1 && tmp_out.second < 5)
                    {
                        blank_stack--;
                        Now_in.front().second = 5; //>4
                    }
                }
                else
                {
                    _2_Num += now_need_pop;
                    blank_stack += now_need_pop;
                }
                now_need_pop = 0;
            }
            else
            {
                now_need_pop -= tmp_out.first;
                Now_in.pop();
                if (tmp_out.second > 3) // 4
                {
                    if (tmp_out.second > 4)
                        blank_stack++;
                    _4_Num += tmp_out.first;
                }
                else
                {
                    _2_Num += tmp_out.first;
                    blank_stack += tmp_out.first;
                }
                if (!Now_in.empty())
                    if (Now_in.front().second > 3)
                    {
                        if (blank_stack > n - 1)
                        {
                            Now_in.front().second = 5;
                            blank_stack--;
                        }
                    }
            }
        }
        //printf("After this round of pop we now have %d blank stacks.\n", blank_stack);
    }
    All_count = _4_Num * 4 + _2_Num * 2;
    printf("%d\n", All_count);
    return 0;
}
