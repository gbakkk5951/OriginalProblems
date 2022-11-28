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
	int flag = 0;//表示有元素倒过来了
	for (int i = sta; i <= end; i++)
	{
		if (op[i] == 0)
		{
			if (should_push == 0)
				break;
			should_push--;
			//这一部分不需要push了，反正也不pop出来
			//push（看此时是否有空栈，若有直接弹进去，否则堆在一起）
			if (empty_num)
			{
				q.push(2);
				empty_num--;
				//printf("加2的元素是%d\n", i);
				ans += 2;
			}
			else
			{
				q.push(4);
				//printf("加4的元素是%d\n", i);
				ans += 4;
			}
		}
		else
		{
			if (q.size() == 0)
				continue;
			int temp = q.front();
			q.pop();
			if (temp == 2)
			{
				if (q.size() == 0 || q.front() == 2)
				{
					//printf("%d 此时空栈元素增加\n", i);
					empty_num++;
				}					
				else if (q.front() == 4)
				{
					if(empty_num > 0 && n - empty_num - 1 > 0)
						empty_num++;
					else if (empty_num == n - 1)
					{
						//说明有空栈
						//printf("%d 有元素倒过来了\n", i);
						continue;
					}					
					else if (empty_num == 0)
					{
						//没有空栈
						//printf("%d 没有空栈\n", i);
						flag = 1;//标记有一列元素倒过来,并倒在其他元素上面
						empty_num++;
					}
				}
			}
			else if (temp == 4)
			{
				if (q.size() == 0)
				{
					//printf("%d 栈为空\n", i);
					if (flag == 1)
						flag = 0;
					empty_num++;
				}					
				else if (q.front() == 4)
				{
					//printf("%d 一直在pop\n", i);
					continue;
				}					
				else if (q.front() == 2)
				{
					if (flag == 1)
					{
						flag = 0;
						continue;
					}
					else
						empty_num++;
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
