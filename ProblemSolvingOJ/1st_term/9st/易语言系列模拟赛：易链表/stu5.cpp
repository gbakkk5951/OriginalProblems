#include <iostream>
using namespace std;
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;
int Totalid = 1;
//
int Pool[PoolSize] = {};
int sub[MaxN] = {};
int n;
int c[MaxN];

int deletedNode[MaxM];
int m; //操作次数

struct Node
{
    int id;
    int x;
    int nid;
    struct Node *prev;
    struct Node *next;
};
struct Node *Pool1[PoolSize] = {};
//
struct LinkedList
{
    int nid;
    struct Node *Head;
    struct Node *Tail;
};
struct LinkedList list[MaxN] = {};

//操作
struct Node *createNode()
{
    struct Node *NewNode = new struct Node; //FIXME:shall I delete it?
    NewNode->id = NewNode->x = Totalid;
    Pool1[Totalid] = NewNode;
    Totalid++;
    NewNode->prev = NewNode->next = NULL;
    return NewNode;
}

void AddHead(int nid)
{
    struct Node *HeadNode = createNode();
    HeadNode->nid = nid;
    if (list[nid].Head == NULL)
    {
        list[nid].Head = list[nid].Tail = HeadNode;
    }
    else
    {
        list[nid].Head->prev = HeadNode;
        HeadNode->next = list[nid].Head;
        HeadNode->prev = NULL;
        list[nid].Head = HeadNode;
    }
}

void AddTail(int nid)
{
    struct Node *TailNode = createNode();
    TailNode->nid = nid;
    if (list[nid].Tail == NULL)
    {
        list[nid].Tail = list[nid].Head = TailNode;
    }
    else
    {
        list[nid].Tail->next = TailNode;
        TailNode->prev = list[nid].Tail;
        TailNode->next = NULL;
        list[nid].Tail = TailNode;
    }
}
void changeX(int id, int newx)
{
    if (id <= 0 || id > Totalid)
    {
        return;
    }
    if (Pool1[id] == NULL)
    {
        return;
    }
    Pool1[id]->x = newx;
}
void deleteNode(int id)
{

    if (id <= 0 || id > Totalid)
    {
        return;
    }
    if (Pool1[id] == NULL)
    {
        return;
    }

    if (Pool1[id]->prev != NULL)
    {
        Pool1[id]->prev->next = Pool1[id]->next;
    }
    if (Pool1[id]->next != NULL)
    {
        Pool1[id]->next->prev = Pool1[id]->prev;
    }
    if (Pool1[id] == list[Pool1[id]->nid].Head)
    {
        list[Pool1[id]->nid].Head = Pool1[id]->next;
    }
    if (Pool1[id] == list[Pool1[id]->nid].Tail)
    {
        list[Pool1[id]->nid].Tail = Pool1[id]->prev;
    }

    Pool1[id] = NULL;
    //

    //cout << "Deleted." << endl;
}
void outputNodeX(struct Node *node, bool space = true)
{
    if (node != NULL)
    {
        cout << node->x;
    }
    else
    {
        cout << "NULL";
    }
	if (space) cout << " ";
}
void OutputNodeX(int id)
{
    if (id <= 0 || id > Totalid)
    {
        return;
    }

    if (Pool1[id] == NULL)
    {
        cout << "NULL NULL NULL";
    }
    else
    {
        struct Node *now = Pool1[id];
        struct Node *prev = now->prev;
        struct Node *next = now->next;
        outputNodeX(prev);
        outputNodeX(now);
        outputNodeX(next, false);
    }
    cout << endl;
}

//
int main()
{
    int op;
    int nid, id, newx;
    cin >> n;                    //输入n，即子程序数目
    for (int i = 1; i <= n; i++) //创建n个LinkedList
    {
        list[i].nid = i;
        //testline
        //cout << "The nid of subroutine " << i << "is " << list[i].nid << endl;
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    //testline
    //cout << "All the Cs have been inputed. " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c[i]; j++)
        {
            AddTail(i);
        }
        //cout << "Initalized subroutine" << i << endl;
    }
    //cout << "All Initialized." << endl;

    cin >> m;
    //int i = 1;
    while (m--)
    {
        //testline
        //cout << "Now m is " << m << endl;
        cin >> op;
        //OP1
        if (op == 1)
        {
            cin >> id;
            //cout << "Output No." << i << endl;
            OutputNodeX(id);
            //i++;
        }

        //OP2
        else if (op == 2)
        {
            cin >> id;
            deleteNode(id);
        }

        //OP3
        else if (op == 3)
        {
            cin >> nid;
            AddHead(nid);
        }

        //OP4
        else if (op == 4)
        {
            cin >> nid;
            AddTail(nid);
        }

        //OP5
        else if (op == 5)
        {
            cin >> id >> newx;
            changeX(id, newx);
        }
    }
    return 0;
}

