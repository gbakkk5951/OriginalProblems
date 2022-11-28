#include <bits/stdc++.h>
long long int max = 0;
long long int count_ = 0;
long long int count_2 = 0;
void read(long long int &a) 
{
    char t, f = 1;
    while (!isdigit(t = getchar())) {
        if (t == '-') f = -1;
    }
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
    a *= f;
}
struct Candy
{
	long long int value;
	Candy *next = NULL;
	bool connect = false; 
};
Candy *stack1[2000006];//存指针 
Candy *stack2[2000006];
int top1 = 1000002, top2 = 1000002, bottom1 = 1000002, bottom2 = 1000002;//top使用时需减一，bottom - 1 
Candy head, tail;//tail的next特殊，指向最后一个元素 
void insert(int position, int type, long long int value)
{
	if(!head.next)
	{
		tail.next = head.next = new Candy;
		head.next -> value = value;
		if(type == 0)
		{
			stack1[top1] = head.next;
			top1++;
		}
		else if(type == 1)
		{
			stack2[top2] = head.next;
			top2++;
		}
		else if(type == 2)
		{
			head.next -> connect = true;
			max = value;	
		} 
	}
	else if(position == 0)//左添加 
	{
		Candy *p = new Candy;
		p -> next = head.next;
		head.next = p;
		p -> value = value;
		if(type == 0)//添加的是左括号 
		{
			if(top2 > bottom2)//新入的左括号应与栈顶的右括号匹配 
			{
				while(p -> next != stack2[top2 - 1])
				{
					p -> value += p -> next -> value;
					++count_;
					p -> next = p -> next -> next;//吞并匹配的括号中间的串，让他们相连 
				}
				p -> value += p -> next -> value;
				p -> next = p -> next -> next;//吞并右括号 
				top2--;
				p -> connect = true;
				while(p -> next)
				{
					if(p -> next -> connect == false) break;
					while(p -> next -> connect == true)
					{
						
						++count_;
						p -> value += p -> next -> value;
						p -> next = p -> next -> next;//将后续可合并项合并 
						if(!p -> next) break;
					}
				}
				if(p -> next == NULL) tail.next = p;//吞并了最后一项，修改尾指针 
				if(p -> value > max) max = p -> value;
			}
			else//栈中右括号不足，左括号入栈底 
			{
				stack1[bottom1 - 1] = p;
				bottom1--;
			}
		}
		else if(type == 1)//添加的是右括号，直接入栈顶
		{
			stack2[top2] = p;
			top2++;
		}
		else if(type == 2)//添加的是糖
		{
			p -> connect = true;
			while(p -> next)
				{
					if(p -> next -> connect == false) break;
					while(p -> next -> connect == true)
					{
						++count_;
						p -> value += p -> next -> value;
						p -> next = p -> next -> next;//将后续可合并项合并 
						if(!p -> next) break;
					}
				}
			if(p -> value > max) max = p -> value;	
		} 
	}
	else if(position == 1)//右添加 
	{
		Candy *p = new Candy;
		if(type == 2)
		{
			if(tail.next -> connect == true)
			{
				tail.next -> value += value;
				if(tail.next -> value > max) max = tail.next -> value;
			} 
			else
			{
				p -> connect = true;
				tail.next = tail.next -> next = p;
				p -> value = value;
				if(p -> value > max) max = p -> value;
			}
			return;
		}
		tail.next = tail.next -> next = p;
		p -> value = value;
		if(type == 1)//添加的是右括号 
		{
			if(top1 > bottom1)//新入的右括号应与栈顶的左括号匹配 
			{
				while(stack1[top1 - 1] -> next != p)
				{
					stack1[top1 - 1] -> value += stack1[top1 - 1] -> next -> value;
					++count_;
					stack1[top1 - 1] -> next = stack1[top1 - 1] -> next -> next;//吞并匹配的括号中间的串，让他们相连 
				}
				stack1[top1 - 1] -> value += stack1[top1 - 1] -> next -> value;
				stack1[top1 - 1] -> next = stack1[top1 - 1] -> next -> next;//吞并新添加的右括号
				tail.next = stack1[top1 - 1]; 
				while(stack1[top1 - 1] -> next)
				{
					if(stack1[top1 - 1] -> next -> connect == false) break;
					while(stack1[top1 - 1] -> next -> connect == true)
					{
						stack1[top1 - 1] -> value += stack1[top1 - 1] -> next -> value;
						++count_;
						stack1[top1 - 1] -> next = stack1[top1 - 1] -> next -> next;//将后续可合并项合并 
						if(!stack1[top1 - 1] -> next) break;
					}
				}
				stack1[top1 - 1] -> connect = true;
				if(head.next != stack1[top1 - 1])
				{
					Candy *q = head.next;
					while(q -> next != stack1[top1 - 1])
					{
						q = q -> next;	
					++count_2;
					}
					if(q -> connect == true)//用q吞并刚匹配的括号串 
					{
						q -> value += stack1[top1 - 1] -> value;
						q -> next = stack1[top1 - 1] -> next;
						if(tail.next == stack1[top1 - 1]) tail.next = q;
						if(q -> value > max) max = q -> value;
						top1--;
						return;	
					}	
				}
				if(stack1[top1 - 1] -> value > max) max = stack1[top1 - 1] -> value;
				top1--;
			}
			else//栈中左括号不足，右括号入栈底 
			{
				stack2[bottom2 - 1] = p;
				bottom2--;
			}
		}
		else if(type == 0)//添加的是左括号，直接入栈顶
		{
			stack1[top1] = p;
			top1++;
		}
	}
}
int main()
{
	long long int N, M;
	read(N);
	read(M);
	head.value = tail.value = 0;
	head.next = tail.next = NULL;
	long long int Type[N];
	for(int i = 0; i < N; i++)
	{
		read(Type[i]);
	}
	for(int i = 0; i < N; i++)
	{
		long long int value;
		read(value);
		insert(1, Type[i], value);
	}
	printf("%lld\n", max);
	for(int i = 0; i < M; i++)
	{
		long long position, type;
		long long value;
		read(position);
		read(type);
		read(value);
		insert(position, type, value);
		printf("%lld\n", max);
	}
using namespace std;
	cerr << count_ << endl << count_2 << endl;
}
