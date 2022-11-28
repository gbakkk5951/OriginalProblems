
### 1. 考察知识：
一个最朴素的思路，对于每次移动，判断每个起点是否仍然合法。

一个简单优化：删掉不合法的起点

如何实现，可以先做标记，然后移动完一轮之后再执行删除，这样整体进行移动，单次复杂度
O(剩余的起点数)

另一个优化，假设当前坐标和到达了一个之前已经到达过的位置，那么本次移动不会造成点被删除

用一个数组标记访问

如何处理负数下标？ 加一个偏移量即可

另外，要特判移动越界，此时不要访问数组，以免运行错误

由于只考虑有效的移动，故最多有n^2次

一个不太严谨的证明，表明了这样做的总体复杂度为O(n^3)



### 2. 优秀代码
**一**
作者：张浩宇


```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 405;
char v[maxn * 2][maxn * 2];
char del[maxn * maxn];
int point[maxn * maxn];
int pn;
char s[maxn][maxn];
const int vx = 401, vy = 401;
int nx = 0, ny = 0;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == '1') {
				point[++pn] = (i << 10) | j; //压缩信息，不必要，可用pair<int, int>表示
			}
		}
	}
	v[vx + nx][vy + ny] = 1;
	printf("%d\n", pn);
	for (int i = 1; i <= m; ++i) {
		int d;
		scanf("%d", &d);
		nx += dx[d], ny += dy[d];
		if (pn && !v[vx + nx][vy + ny]) {//防止越界，因为越界前必然清空
			v[vx + nx][vy + ny] = 1;
			for (int i = 1; i <= pn; ++i) {
				int x = (point[i] >> 10) + nx, y = (point[i] & 1023) + ny;
				del[i] = s[x][y] != '1';
			}
			int l = 0;
			for (int i = 1; i <= pn; ++i) {//本轮删除标记处理完后，再移动
				if (!del[i]) {
					point[++l] = point[i];
				}
			}
			pn = l;
		}
		printf("%d\n", pn);//不是在上面的括号里
	}
	return 0;
}


```

**二**
作者：郑九铭
敏捷

```C++
#include<iostream>
#include<cmath>
using namespace std;
const int N = 400 + 3 , M = 1e6 + 5;
int leave = 0 , Leave[N*N];
bool array[N][N] , Up[N*N] , Down[N*N] , Left[N*N] , Right[N*N] , map[2*N][2*N];
enum{
    UP , DOWN , LEFT , RIGHT
};
void work(int n , int m)
{
    if(leave == 0)
    {
        while(m--)
            printf("0\n");
        return;
    }
    int num , i = 1 , j , op , x = 400 , y = 400 , move = 0;
    map[x][y] = 1;
    for(i ; i <= m ; i++)
    {
        scanf("%d" , &op);
        num = 0;
        switch(op)
        {
            case UP:
            x--;
            if(map[x][y])
            {
                printf("%d\n" , leave);
                move -= n;
                continue;
            }
            for(j = 1 ; j <= leave ; j++)
            {
                Leave[j] += move;
                if(Up[Leave[j]])
                    Leave[++num] = Leave[j] - n;
            }
            break;
            case DOWN:
            x++;
            if(map[x][y])
            {
                printf("%d\n" , leave);
                move += n;
                continue;
            }
            for(j = 1 ; j <= leave ; j++)
            {
                Leave[j] += move;
                if(Down[Leave[j]])
                    Leave[++num] = Leave[j] + n;
            }
            break;
            case LEFT:
            y--;
            if(map[x][y])
            {
                printf("%d\n" , leave);
                move--;
                continue;
            }
            for(j = 1 ; j <= leave ; j++)
            {
                Leave[j] += move;
                if(Left[Leave[j]])
                    Leave[++num] = Leave[j] - 1;
            }
            break;
            case RIGHT:
            y++;
            if(map[x][y])
            {
                printf("%d\n" , leave);
                move++;
                continue;
            }
            for(j = 1 ; j <= leave ; j++)
            {
                Leave[j] += move;
                if(Right[Leave[j]])
                    Leave[++num] = Leave[j] + 1;
            }
            break;
        }
        move = 0;
        map[x][y] = 1;
        leave = num;
        printf("%d\n" , leave);
        if(leave == 0)
            break;
    }
    while(i < m)
    {
        printf("0\n");
        i++;
    }
    return;
}
int main()
{
    int n , m , q = 1;
    char x;
    scanf("%d %d" , &n , &m);
    for(int i = 1 ; i <= n ; i++)
    {
        x = getchar();
        for(int j = 1 ; j <= n ; j++)
        {
            x = getchar() - '0';
            if(x)
            {
                array[i][j] = 1;
                Leave[++leave] = q;
            }
            q++;
        }
    }
    q = 0;
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
        {
            q++;
            if(array[i][j] == 0)
                continue;
            if(j+1 <= n && array[i][j+1])
                Right[q] = 1;
            if(j-1 >= 1 && array[i][j-1])
                Left[q] = 1;
            if(i+1 <= n && array[i+1][j])
                Down[q] = 1;
            if(i-1 >= 1 && array[i-1][j])
                Up[q] = 1;
        }
    printf("%d\n" , leave);
    work(n , m);
    return 0;    
}
```