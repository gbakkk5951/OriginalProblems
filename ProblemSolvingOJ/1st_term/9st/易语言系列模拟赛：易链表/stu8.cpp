#include <bits/stdc++.h>
#define ffor(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
int n, m, c[1010], total = 0;
struct Mynode
{
    int id;
    int value;
    int num;
    struct Mynode *prev;
    struct Mynode *next;
};
struct Mynode *Map[50000010];
struct Mylist
{
    struct Mynode *head;
    struct Mynode *tail;
} liist[1005];
struct Mynode *init(int Id)
{
    struct Mynode *node = (struct Mynode *)malloc(sizeof(struct Mynode));
    Map[++total] = node;
    node->num=Id;
    node->id = total;
    node->value = total;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
void insert1(int nid)
{
    if (nid < 0 || nid > n)
        return;
    struct Mynode *node = init(nid);
    if (liist[nid].head == NULL)
        liist[nid].head = liist[nid].tail = node;
    else
    {
        node->next = liist[nid].head;
        liist[nid].head->prev=node;
        liist[nid].head = node;
    }
}
void insert2(int nid)
{
    if (nid < 0 || nid > n)
        return;
    struct Mynode *node = init(nid);
    if (liist[nid].tail == NULL)
        liist[nid].head = liist[nid].tail = node;
    else
    {
        node->prev = liist[nid].tail;
        liist[nid].tail->next=node;
        liist[nid].tail = node;
    }
    return;
}
void printout(struct Mynode *node, bool end = true)
{
    if (node != NULL )
        cout << node->value << "";
    else cout<<"NULL";
	if (end) cout << " ";
    return;
}
void printnode(int id)
{
    if ( (id < 1) || (id > total)|| Map[id] == NULL)
        cout << "NULL NULL NULL";
    else
    {
        struct Mynode *now = Map[id];
        struct Mynode *prev = now->prev;
        struct Mynode *next = now->next;
        printout(prev);
        printout(now);
        printout(next, false);
        
    }cout << endl;
}
void deleteit(int id)
{
    if (  (id > total)|| (id < 1) ||Map[id] == NULL)return;

    struct Mynode *node=Map[id];
    Map[id]=NULL;
    
    if(node->prev!=NULL)node->prev->next=node->next;
    if(node->next!=NULL)node->next->prev=node->prev;
    if(node==liist[node->num].head)liist[node->num].head=node->next;
    if(node==liist[node->num].tail)liist[node->num].tail=node->prev;
    free(node);
}
void upnode(int op1,int op2)
{
    if(op1<=0||op1>total)return;
    if (Map[op1] != NULL)
    Map[op1]->value = op2;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    ffor(i, 1, n)
    {
        cin >> c[i];
        ffor(j, 1, c[i])insert2(i);
    }
    cin >> m;
    ffor(i, 1, m)
    {
        int op, op1, op2;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> op1;
            printnode(op1);
            break;
        case 2:
            cin >> op1;
            deleteit(op1);
            break;
        case 3:
            cin >> op1;
            insert1(op1);
            break;
        case 4:
            cin >> op1;
            insert2(op1);
            break;
        case 5:
            cin >> op1 >> op2;
            upnode(op1,op2);
            break;

        default:
            break;
        }
    }
}
