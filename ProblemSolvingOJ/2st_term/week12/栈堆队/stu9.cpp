/*
首先，通过特判得到有效的01序列。
(1)push:
若此时整个栈堆中存在空栈，则输入元素为2；
若此时整个栈堆中没有空栈，则输入元素为4；
同时，对所有元素标记一下：其是否位于栈底。 
(2)pop:
若这个元素上面没有元素了，位于栈底，则答案以2记录，同时空栈的数目++
若这个元素上面还有元素，则考察空栈数目的变化：
若此时空栈的数目为n-1，则表示非空栈只有当前一个，空栈数目不变
若此时空栈的数目小于n-1，则表示非空栈有许多，空栈数目++ 

*/





#include <cstdio>
#include <iostream>
#include <queue>
#define ll long long
using namespace std;
const int MAXN = 4e6 + 2;//最多 
ll ans;
int n, m, PUSH[MAXN], POP[MAXN],  output = 1, tot, s;//tot记录有效元素的下标
bool isbottom[MAXN], istop[MAXN];
queue<int> q;
int e, ne;
/*
empty表示空栈的数目，notempty为非空栈的数目，isbottom[x]表示序号为x的有效入栈元素是否在栈底
对于push(x):
若notempty < n,即还有空栈，则ANS++, notempty++, empty--, isbottom[x] = true;
若notempty = n,ANS++, isbottom[x] = false; 相当于加在上一个数上面
*/
int getTop(int st)//获得栈顶的元素 
{
	while(st <= tot && (!isbottom[st]))
		{
			st++;
		}
	return st - 1;
}
void push(int x)
{
	if(ne < n)//表示还有空栈
		{
			e--;ne++;
			ans += 1ll * 2;
			isbottom[x] = true;//标记元素x是位于栈底的。其上有元素，当且仅当x+1不是栈底元素 
		}
	else //表示没有空栈
		ans += 1ll * 4;
}
void pop()//弹出元素 
{
	if(output == tot)//此时，应当只有一个元素了
	{
		e++;ne--;
	//	ans += 1ll * q.front();
		q.pop();
		return;
	 } 
	 if(!isbottom[output])//如果output不是栈底元素，则为栈顶元素，直接输出即可，不会影响栈的
	 //数目
	{
	//	ans += 1ll * q.front();
		q.pop();
		return;	 	
	} 
	//如果为栈底元素 
	if(isbottom[output] == true && isbottom[output + 1] == true)//如果output是单独一个的栈底元素，直接弹出！空栈++  
		{
			e++;ne--;
	//		ans += 1ll * q.front();
			q.pop();
			return;
		} 
	//否则，就表示其上面有元素，只需考虑空栈的变化情况即可。
	if(isbottom[output] == true && isbottom[output + 1] == false)//此时，output是栈底的情况，且上面有堆叠的元素 
		{
			if(ne > 1)//说明有多于两个的情况，此时output+1不是栈底了，而是栈顶！		
				{
					e++;ne--;
				//	ans += 1ll * q.front();
					q.pop();
					return;
				}
			//否则，就是只有一个的情况，不会增加e的数目。但是，需要更新栈底！ 
			else
				{
					isbottom[tot] = true;//标记当前栈顶，作为新的栈底。 
			//		ans += 1ll * q.front();
					q.pop();
					return;	
				} 
		} 
}
int main()
{
	char ch;
	scanf("%d%d", &n, &m);	
	e = n;//初始化empty为n个，ne为0个 
	ne = 0;
	int val;
	for (int i = 1 ; i <= m ; i++)
		{
			cin >> ch;
			val = ch - '0';
			//当出栈的时候，才把最开始入栈的步数算上即可。
			POP[i] = val;
		}
	for (int i = m ; i >= 1 ; i--)
		{
			POP[i] += POP[i + 1];//这样POP[i]存储的就是i~n的pop操作的个数了	
		}
	for (int i = 1 ; i <= m; i++)
		{
			
			int op = POP[i] - POP[i + 1];
			if(s >= POP[i] && op == 0)//当前栈中总元素个数超过i往后的所有pop次数了，不必再push! 
				continue;
			if(s == 0 && op == 1)//栈为空，则pop为无效操作
				continue;
			if(op == 0)
			{
				s++;
				tot++;
				push(tot);
			}
			else
			{
				pop();
				output++;
				s--;
			}
		}
	printf("%lld\n", ans);
	return 0;
}
