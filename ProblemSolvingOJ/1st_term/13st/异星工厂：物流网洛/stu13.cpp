#include <stdio.h>
#include <string.h>
int top, bottom;//表示格的上界和下界 
bool status;//记录是否为格 
int a[55][55];//记录关系
int b[55];//记录是否有两元素完全相等,相等元素在之后的计算不再考虑 
void init()
{
	top = bottom = 0;
	status = true;
	memset(b, 0, sizeof(b));
}
void check(int n)
{
	for(int i = 1; i <= n; i++)//自反性判断 
	{
		if(a[i][i] != 1)
		{
			status = false;
			return;	
		}	
	}
	for(int i = 1; i <= n; i++)//传递性检测 
	{
		for(int j = 1; j <= n; j++)
		{
			if(i == j) continue;
			if(a[i][j] == 1)
			{
				for(int k = 1; k <= n; k++)
				{
					if(a[j][k] == 1 && a[i][k] == 0)
					{
						status = false;
						return;
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)//等价元素转化 
	{
		for(int j = i + 1; j <= n; j++)
		{
				if(a[i][j] != 1 || a[j][i] != 1) continue;
				int count1 = 0, count2 = 0;
				int k = 1;
				while(k <= n)//对应的n个关系均相等，count == n
				{
					if(a[i][k] == a[j][k]) count1++;
					k++;
				}
				k = 1;
				while(k <= n)//对应的n个关系均相等，count == n
				{
					if(a[k][i] == a[k][j]) count2++;
					k++;
				}
				if(count1 == n && count2 == n)
				{
					if(i > j)
					{
						b[i] = 1;
					} 
					if(j > i)
					{
						b[j] = 1;
					}
				}
		}
	} 
	for(int i = 1; i <= n; i++)//无关元素上下唯一确界检测 
	{
		if(b[i] == 1) continue;
		else
		{
			for(int j = i + 1; j <= n; j++)
			{
				if(b[j] == 1) continue;
				else if(a[i][j] == 0 && a[j][i] == 0)//无关的两个元素,检测他们是否处于某两个及以上元素的共同上或下界 
				{
					bool status1 = false, status2 = false;
					//status1记录他们是否有下界，status2记录是否有上界 
					int sup = 1, inf = 1;
//记录上一个找到的上界或下界，对比是否存在偏序关系，不存在则上下界不唯一,存在取较近的作为新的上下界 
					for(int k = 1; k <= n; k++)
					{
						if(k == i || k == j || b[k] == 1) continue;
						else
						{
							if(a[i][k] == 1 && a[j][k] == 1)//找到了一个共同下界k 
							{
								if(status1 == false)
								{
									inf = k;
									status1 = true; 
								}
								else if(a[inf][k] == 0 && a[k][inf] == 0)//两下界无关，不成立 
								{
									status = false;
									return;
								}
								else if(a[k][inf] == 1 && a[inf][k] == 0) inf = k;//k比inf更靠近最小下界 
							}
							if(a[k][i] == 1 && a[k][j] == 1)//找到了一个共同上界k 
							{
								if(status2 == false)
								{
									sup = k;
									status2 = true;
								}
								else if(a[inf][k] == 0 && a[k][inf] == 0)//
								{
									status = false;
									return;
								}
								else if(a[inf][k] == 1 && a[k][inf] == 0) inf = k;//k比inf更靠近最小上界 
							}
						}
					}
					if(status1 == false || status2 == false)//无上下界 
					{
						status = false;
						return; 
					}
				}	
			}		
		}				
	}			 
} 
int main()
{
	int T;
	scanf("%d", &T);
	for(int k = 0; k < T; k++)
	{
		init();
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				int x;
				scanf("%d", &x);
				a[i][j] = x;
			}
		}
		check(n);
		if(status == true) printf("Y\n");
		else printf("N\n");
	}
}
