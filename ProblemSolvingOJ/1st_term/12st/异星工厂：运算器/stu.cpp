#include <stdio.h>
#include <string.h>
const int Maxsize = 2e5 + 5;
bool Runtime = false;
bool tell = false;//区分是加减号还是正负号 true时为减号 
int option[Maxsize];
int number[Maxsize];
int value[Maxsize];	
//优先级2:%5=1	正：11	负：16  ~:21
//优先级3:%5=2	*:12	/:17	%:22
//优先级4:%5=3	+:13	-:18
//优先级5:%5=4	>:14	<:19
int top1 = 0, top2 = 0, top3 = 0;
void init();
void push(char x);
int change(char c);
void init()
{
    top1 = top2 = top3 = 0;
    memset(option, 0, sizeof(option));
    memset(number, 0, sizeof(number));
    memset(value, 0, sizeof(value));
    Runtime = false;
	tell = false;	
}
void push(char x)
{
    if(x >= '0' && x <= '9')
		{
        	number[top2] = change(x);
        	top2++;
        	tell = true;
		}
	else if(x == '(')  
	{
		option[top1] = -1;
		top1++;
		tell = false;
	}
	else if(x == ')')
			{
			while(option[top1 - 1] != -1)//不断弹出符号栈元素直到左括号 
				{
					number[top2] = option[top1 - 1];
					option[top1 - 1] = 0;
					top2++;
					top1--;	
				}
				option[top1 - 1] = 0;//清除左括号 
				top1--;	
				tell = true;
			}
	else
	{
		if(x == '\n')//到最后，全部弹出 
		{
			while(top1 != 0)
			{
				number[top2] = option[top1 - 1];
				option[top1 - 1] = 0;
				top2++;
				top1--;	
			}
			return;
		}
		int t = change(x);
			while(top1 != 0) //弹出符号直到左括号或优先级小于它
			{	
				if(option[top1 - 1] == -1 || t % 5 < option[top1 - 1] % 5 || (t % 5 == 1 && option[top1 - 1] % 5 == 1)) break;
				number[top2] = option[top1 - 1];
				option[top1 - 1] = 0;
				top2++;
				top1--;	
			}
		option[top1] = t;
		top1++; 
		tell = false;
	} 
}
int change(char c)//将符号转为数字编码
{
	if(c == '+')
	{
		if(tell == true)//加号 
		{
			tell = false;
			return	13; 
		}
		else	return 11;
	}
	else if(c == '-')
	{
		if(tell == true)//减号 
		{
			tell = false;
			return	18; 
		}
		else	return 16;
	}
	else switch(c)
	{
//优先级2:%5=1	正：11	负：16  ~:21
//优先级3:%5=2	*:12	/:17	%:22
//优先级4:%5=3	+:13	-:18
//优先级5:%5=4	>:14	<:19
		case '~': return 21;
					break;
		case '*': return 12;
					break;
		case '/': return 17;
					break;
		case '%': return 22;
					break;
		case '>': return 14;
					break;
		case '<': return 19;
					break;
		default : return c - '0';
					break;	
	}
} 
void calculate()
{
	for(int i = 0; i < top2 && Runtime == false; i++)
	{
		if(number[i] <= 9)
		{
			value[top3] = number[i];
			top3++;	
		}  
		else switch(number[i])
		{
//优先级2:%5=1	正：11	负：16  ~:21
//优先级3:%5=2	*:12	/:17	%:22
//优先级4:%5=3	+:13	-:18
//优先级5:%5=4	>:14	<:19
			case 11:	break;
			case 16:	value[top3 - 1] = value[top3 - 1] * (-1);
						break;
			case 21:	value[top3 - 1] = ~value[top3 - 1];
						break;
			case 12:	value[top3 - 2] = value[top3 - 2] * value[top3 - 1];
						top3--;
						break;
			case 17: 	if(value[top3 - 1] == 0)
						{
							Runtime = true;
							printf("Runtime Error\n");
							break;
						}
						else
						{
							value[top3 - 2] = value[top3 - 2] / value[top3 - 1];
							top3--;	
							break;	
						}
			case 22:	if(value[top3 - 1] == 0)
						{
							Runtime = true;
							printf("Runtime Error\n");
							break;
						}
						else
						{
							value[top3 - 2] = value[top3 - 2] % value[top3 - 1];
							top3--;	
							break;	
						}		
			case 13:	value[top3 - 2] += value[top3 - 1];
						top3--;
						break;
			case 18:	value[top3 - 2] -= value[top3 - 1];
						top3--;
						break;
			case 14:	if(value[top3 - 2] > value[top3 - 1])
						{
							value[top3 - 2] = 1;
							top3--;
							break;
						}	
						else
						{
							value[top3 - 2] = 0;
							top3--;
							break;
						}	
			case 19:	if(value[top3 - 2] < value[top3 - 1])
						{
							value[top3 - 2] = 1;
							top3--;
							break;
						}	
						else
						{
							value[top3 - 2] = 0;
							top3--;
							break;
						}	
			default:	break;
		}
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	getchar();
	for(int i = 0; i < T; i++)
	{
		init();
		char c;
		do
		{
			c = getchar();
			push(c);	
		}while(c != '\n');
		calculate();
		if(Runtime == false) printf("%d\n", value[0]);
	};	
	return 0;
}
