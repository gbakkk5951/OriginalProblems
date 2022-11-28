#include <bits/stdc++.h>
using namespace std;
int maxn, maxn1, minx, minx1, a[1000002], b[1000002], minn[1000002];
template<class T>void read(T &x)
{
    x=0;int f=0;char ch=getchar();
    while(ch<'0'||ch>'9'){f|=(ch=='-');ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return;
}
int main()
{
    int n, k;
    read(n);
	read(k);
    minx = minx1 = n + 1;
    a[minx] = 2147483647;
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        if (a[i] > a[maxn1])
        {
            maxn1 = i;
            if (a[i] > a[maxn])
            {
                maxn1 = maxn;
                maxn = i;
            }
        }
        if (a[i] < a[minx1])
        {
            minx1 = i;
            if (a[i] < a[minx])
            {
                minx1 = minx;
                minx = i;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        b[i] = a[i];
	}
    if (a[maxn1] + a[maxn] < k)
    {
        printf("%d ", a[1] + a[2]);
        for (int i = 3; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
    else
    {
        maxn = 0;
        maxn1 = 0;
        int flag = 0;
        for (int i = n; i >= 1; i--)
        {
            if (flag)
                break;
            if (a[i] > a[maxn1])
            {
                maxn1 = i;
                if (a[i] > a[maxn])
                {
                    maxn1 = maxn;
                    maxn = i;
                }
                if (a[maxn] + a[maxn1] >= k)
                {
                    if (a[max(maxn, maxn1)] == k - 1)
                        for (int j = i - 1; j >= 1; j--)
                        {
                            if (a[j] == 1)
                            {
                                b[max(maxn, maxn1)] = 0;
                                flag = 1;
                                break;
                            }
                        }
                    if (flag)
                    	break;
                    for (int j = n; j > i; j--)
                        if (a[j] + a[i] >= k)
                        {
                            b[i] = 1;
                            b[j] = a[i] + a[j] - k;
                            flag = 1;
                            break;
                        }
                    
                }
            }
        }
        for (int i = 1; i <= n; i++)
            printf("%d ", b[i]);
        printf("\n");
    }
    for (int i = 1; i <= n; i++)
    {
        b[i] = a[i];
	}
    if (a[minx] + a[minx1] >= k)
    {
    	printf("1 %d ", a[1] + a[2] - k);
    	for (int i = 3; i <= n; i++)
    		printf("%d ", a[i]);
    	printf("\n");
	}
	else
	{
		int flag = 0;
		minn[n] = a[n];
		for (int i = n - 1; i >= 1; i--)
			minn[i] = min(a[i], minn[i + 1]);
		for (int i = 1; i <= n - 1; i++)
		{
			if (flag)
				break;
			if (a[i] > a[i + 1] && a[i] + minn[i + 2] < k)
			{
				for (int j = n; j > i + 1; j--)
					if (a[i] + a[j] < k)
					{
						b[i] = -1;
						b[j] = a[i] + a[j];
						flag = 1;
						break;	
					}
			}
		}
		if (!flag)
		{
			minx = minx1 = 0;
			a[0] = 2147483647;
			for (int i = n; i >= 1; i--)
        	{
            	if (flag)
                	break;
            	if (a[i] < a[minx1])
            	{
                	minx1 = i;
                	if (a[i] < a[minx])
                	{
                    	minx1 = minx;
                    	minx = i;
                	}
                    for (int j = n; j > i; j--)
                        if (a[j] + a[i] < k)
                        {
                            b[i] = -1;
                            b[j] = a[i] + a[j];
                            flag = 1;
                            break;
                        }
            	}	
			}
		}
		int i = 1;
		while (b[i] == 0 || b[i] == -1)
			i++;
		for (i; i <= n; i++)
			if (b[i] != -1)
				printf("%d ", b[i]);
	}
	return 0;
}
