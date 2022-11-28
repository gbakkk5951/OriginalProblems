#include <bits/stdc++.h>
using namespace std;
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;
struct ListItem;
typedef ListItem Li; 

Li *Head[MaxN], *Tail[MaxN];
long long Index = 0;

struct ListItem {
    Li *pre;
    Li *nxt;
    int value = 0;
    int flag = 0;
    bool Tail, Head;
    int nIndex = 0;//标记是哪一个子程序.
}Pool[PoolSize];
void inite(int c, int nid)
{
    Pool[Index + 1].pre = NULL;
    for (int i = 1; i < c; ++i)
    {
        Pool[Index + i].nxt = &Pool[Index + i + 1];
        Pool[Index + i].nIndex = nid;
        Pool[Index + i].value = Index + i;
        Pool[Index + i + 1].pre = &Pool[Index + i];
    }
    Index += c;
    Pool[Index].nIndex = nid;
    Pool[Index].value = Index;
    Pool[Index].nxt = NULL;
}
void check(int id)
{
    if (Pool[id].pre != NULL && Pool[id].pre->flag != 1)
        printf("%d ", Pool[id].pre->value);
    else
        printf("NULL ");
        printf("%d ", Pool[id].value);
    if (Pool[id].nxt != NULL && Pool[id].nxt->flag != 1)
        printf("%d\n", Pool[id].nxt->value);
    else
        printf("NULL\n");
}
void del(int id)
{
    if (Pool[id].pre != NULL)
        Pool[id].pre->nxt = Pool[id].nxt;
    if (Pool[id].nxt != NULL)
        Pool[id].nxt->pre = Pool[id].pre;
    Pool[id].flag = 1;
    if (Pool[id].Head == true)
    {
        if (Pool[id].nxt != NULL)
        {
            Pool[id].nxt->Head = true;
            Head[Pool[id].nIndex] = Pool[id].nxt;
        }
        else
            Head[Pool[id].nIndex] = NULL;
    }
    if (Pool[id].Tail == true)
    {
        if (Pool[id].pre != NULL)
        {
            Pool[id].pre->Tail = true;
            Tail[Pool[id].nIndex] = Pool[id].pre;
        }
        else
            Tail[Pool[id].nIndex] = NULL;
    }
}
void insertH(int nid)
{
    Index++;
    if (Head[nid] != NULL)
    {
        Head[nid]->pre = &Pool[Index];
        Pool[Index].pre = NULL;
        Pool[Index].nxt = Head[nid];
        Head[nid]->Head = false;
        Head[nid] = &Pool[Index];
        Pool[Index].value = Index;
        Pool[Index].Head = true;
        Pool[Index].nIndex = nid;
    }
    else
    {
        Head[nid] = &Pool[Index];
        Tail[nid] = &Pool[Index];
        Pool[Index].value = Index;
        Pool[Index].Head = Pool[Index].Tail = true;
        Pool[Index].pre = Pool[Index].nxt = NULL;
    }
}
void insertT(int nid)
{
    Index++;
    if(Tail[nid] != NULL)
    {
        Tail[nid]->nxt = &Pool[Index];
        Pool[Index].pre = Tail[nid];
        Pool[Index].nxt = NULL;
        Tail[nid]->Tail = false;
        Tail[nid] = &Pool[Index];
        Pool[Index].value = Index;
        Pool[Index].Tail = true;
        Pool[Index].nIndex = nid;
    }
    else
    {
        Head[nid] = &Pool[Index];
        Tail[nid] = &Pool[Index];
        Pool[Index].value = Index;
        Pool[Index].Head = Pool[Index].Tail = true;
        Pool[Index].pre = Pool[Index].nxt = NULL;
    }
}
void change(int id, int x)
{
    Pool[id].value = x;
}

int main() {
    int n = 0, c = 0, m = 0, opt, id, nid, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c);
        if (c != 0)
        {
            Head[i] = &Pool[Index + 1];
            Pool[Index + 1].Head = true;
            inite(c, i);
            Tail[i] = &Pool[Index];
            Pool[Index].Tail = true;
        }
        else
        {
            Head[i] = NULL;
            Tail[i] = NULL;
        }
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &opt);
        switch(opt)
        {
            case 1:
            scanf("%d", &id);
            if (id > 0 && id <= Index && Pool[id].flag != 1)
                check(id);
            else
                printf("NULL NULL NULL\n");
            break;
            case 2:
            scanf("%d", &id);
            if (id > 0 && id <= Index && Pool[id].flag != 1)
                del(id);
            break;
            case 3:
            scanf("%d", &nid);
            insertH(nid);
            break;
            case 4:
            scanf("%d", &nid);
            insertT(nid);
            break;
            case 5:
            scanf("%d%d", &id, &x);
            if (id > 0 && id <= Index && Pool[id].flag != 1)
                change(id, x);
            break;
        }
    }
	return 0;
}
