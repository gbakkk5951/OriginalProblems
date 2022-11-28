#include <bits/stdc++.h>
using namespace std;
const int MaxN = 505;                    
const int MaxC = 1003;                   
const int MaxM = 5e5 + 5;                
const int PoolSize = MaxN * MaxC + MaxM; 
struct ListItem;
typedef ListItem Li;
const int inf = -1e9 - 5;
int Index = 0;
Li *Head[MaxN], *Tail[MaxN]; 

struct ListItem
{
    int mark;
    Li *front;
    Li *back;
    int subNumber;
} Pool[PoolSize];

void GetNewListItem(int c, int subNum)
{
    if (c != 0)
    {
        Head[subNum] = &Pool[++Index];
        Pool[Index].mark = Index;
        Pool[Index].front = NULL;
        Pool[Index].back = &Pool[Index + 1];
        Pool[Index].subNumber = subNum;
        for (int i = 1; i < c; i++)
        {
            Pool[Index + i].mark = Index + i;
            Pool[Index + i].front = &Pool[Index + i - 1];
            Pool[Index + i].back = &Pool[Index + i + 1];
            Pool[Index + i].subNumber = subNum;
        }
        Index += c - 1;
        Pool[Index].back = NULL;
        Tail[subNum] = &Pool[Index];
    }
//	return NULL;
}

int main()
{
    int n, m, c, op, id, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c);
        GetNewListItem(c, i);
    }
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &op, &id);
        if (op == 1)
        {
            if (id > Index || id <= 0)
                printf("NULL NULL NULL\n");
            else
            {
                if (Pool[id].front == NULL)
                    printf("NULL ");
                else
                    printf("%d ", (*Pool[id].front).mark);
                if (Pool[id].mark == inf)
                    printf("NULL ");
                else
                    printf("%d ", Pool[id].mark);
                if (Pool[id].back == NULL)
                    printf("NULL\n");
                else
                    printf("%d\n", Pool[id].back->mark);
            }
        }
        else if (op == 2)
        {
            if (0 < id && Index >= id)
            {
                if (Pool[id].mark != inf)
                {
                    Pool[id].mark = inf;
                    if (Head[Pool[id].subNumber] == &Pool[id])
                        Head[Pool[id].subNumber] = Pool[id].back;
                    if (Tail[Pool[id].subNumber] == &Pool[id])
                        Tail[Pool[id].subNumber] = Pool[id].front;

                    if (Pool[id].front != NULL)
                        Pool[id].front->back = Pool[id].back;
                    if (Pool[id].back != NULL)
                        Pool[id].back->front = Pool[id].front;
                    Pool[id].front = Pool[id].back = NULL;
                }
            }
        }
        else if (op == 3)
        {
            Index++;
            Pool[Index].mark = Index;
            Pool[Index].front = NULL;
            Pool[Index].subNumber = id;
            Pool[Index].back = Head[id];
            if (Head[id] != NULL)
                Head[id]->front = &Pool[Index];
            if (Tail[id] == NULL)
                Tail[id] = &Pool[Index];
            Head[id] = &Pool[Index];
        }
        else if (op == 4)
        {
            Index++;
            Pool[Index].mark = Index;
            Pool[Index].back = NULL;
            Pool[Index].subNumber = id;
            Pool[Index].front = Tail[id];
            if (Tail[id] != NULL)
                Tail[id]->back = &Pool[Index];
            if (Head[id] == NULL)
                Head[id] = &Pool[Index];
            Tail[id] = &Pool[Index];
        }
        else if (op == 5)
        {
            scanf("%d", &x);
            if (0 < id && Index >= id)
                if (Pool[id].mark != inf)
                    Pool[id].mark = x;
        }
    }
    return 0;
}
