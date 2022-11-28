#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <queue>
using namespace std;
int op[4000000 + 2];
int main() 
{
	int n, m;
	queue <int> q;//真实的入队情况(分别存2，4两种push进来的可能)
	scanf("%d%d", &n, &m);
	int empty_num = n, push_num = 0;
	getchar();
	for (int i = 1; i <= m; i++)
	{
		char temp = getchar();
		op[i] = temp - '0';
		if (op[i] == 0)
			push_num++;
	}

	int sta = 1;//处理前面是1的情况
	while (op[sta] == 1)
		sta++;
	int end = m;//处理后面是push的操作
	while (op[end] == 0)	
		end--;

	int push_now = 0;
	//记录有多少个不需要push进来的情况
	for (int i = sta; i <= end; i++)
	{
		if (op[i] == 0)
			push_now++;
		else
		{
			if (push_now == 0)
				continue;//这个属于无效pop	
			else
				push_now--;
		}
		//处理不需要push进来的情况		
	}
	int should_push = push_num - (m - end) - push_now;
	long long ans = 0;//表示最高的那个栈的元素个数
	for (int i = sta; i <= end; i++)
	{
		if (op[i] == 0)
		{			
			if (should_push == 0)
				continue;
			should_push--;
			//这一部分不需要push了，反正也不pop出来
			//push（看此时是否有空栈，若有直接弹进去，否则堆在一起）
			if (empty_num)
			{
				q.push(2);
				empty_num--;
				//printf("+2操作是：%d\n", i);
				ans += 2;
			}
			else
			{
				q.push(4);
				ans += 4;
				//printf("+4操作是：%d\n", i);
			}
		}
		else
		{
			if (q.size() == 0)
			{
				continue;
			}			
			//无效pop
			int temp = q.front();
			q.pop();
			if (temp == 2 && (q.size() == 0 || q.front() == 2))
			{
				//说明此时弹出来后空栈数加1
				empty_num++;
			}
			else if (temp == 2 && q.front() == 4)
			{
				//说明它的上面还有元素，空栈数量不变
			}
			else if (temp == 4 && (q.size() == 0 || q.front() == 2))
			{
				//说明弹出了累计元素的最后一个
				empty_num++;
			}
			else if (temp == 4 && q.front() == 4)
			{
				//说明不变
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
