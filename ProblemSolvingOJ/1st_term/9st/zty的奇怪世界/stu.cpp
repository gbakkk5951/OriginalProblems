#include <iostream>
#include <stdlib.h>
const int maxN = 500 + 5;
int n, T;
struct position
{
    int x;
    int y;
};
struct cell
{
    int x;
    int y;
    cell *up, *down, *left, *right;
};	
position *zty = (position *)malloc(sizeof(position));
cell world[maxN][maxN];
struct List
{
    void create(cell *p, int i, int j, int n)
    {
    	p->x = i;
    	p->y = j;
        if (j < n)
            p->up = &world[i][j + 1];
        else
            p->up = NULL;
        if (j > 1)
            p->down = &world[i][j - 1];
        else
            p->down = NULL;
        if (i < n)
            p->right = &world[i + 1][j];
        else
            p->right = NULL;
        if (i > 1)
            p->left = &world[i - 1][j];
        else
            p->left = NULL;
    }
    void init(int n)
    {
        zty->x = 1;
        zty->y = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                create(&world[i][j], i, j, n);
            }
        }
    }
    void move(char dir)
    {	printf("MOVE");
        if (dir == 'W')
        {
            if (world[zty->x][zty->y].up != NULL)
            {
                int tmp = zty->x;
                zty->x = world[zty->x][zty->y].up->x;
                zty->y = world[tmp][zty->y].up->y;
            }
        }
        else if (dir == 'A')
        {
            if (world[zty->x][zty->y].left != NULL)
            {
                int tmp = zty->x;
                zty->x = world[zty->x][zty->y].left->x;
                zty->y = world[tmp][zty->y].left->y;
            }
        }
        else if (dir == 'S')
        {
            if (world[zty->x][zty->y].down != NULL)
            {
                int tmp = zty->x;
                zty->x = world[zty->x][zty->y].down->x;
                zty->y = world[tmp][zty->y].down->y;
            }
        }
        else
        {
            if (world[zty->x][zty->y].right != NULL)
            {
                int tmp = zty->x;
                zty->x = world[zty->x][zty->y].right->x;
                zty->y = world[tmp][zty->y].right->y;
            }
        }
    }
    void del()
    {
        world[zty->x][zty->y].up->down = world[zty->x][zty->y].down;
        world[zty->x][zty->y].down->up = world[zty->x][zty->y].up;
        world[zty->x][zty->y].left->right = world[zty->x][zty->y].right;
        world[zty->x][zty->y].right->left = world[zty->x][zty->y].left;
    }
    void query()
    {
        printf("(%d, %d)\n", zty->x, zty->y);
    }
};
List strangeWorld;
int main()
{
    scanf("%d", &n);
    strangeWorld.init(n);
    scanf("%d", &T);
	char tmp;
    while (tmp = getchar())
    {
		printf("\ngot %c(%d)\n", tmp, tmp);
    }
	char opt;
	while (T--) {
		scanf("%c", &opt);
	}
    return 0;
}
