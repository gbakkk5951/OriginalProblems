#include <bits/stdc++.h>
using namespace std;

int a[1000000 + 5];
long long v[1000000 + 5];
int x[1000000 + 5];
long long Maxans;

struct MyList
{
    int type;
    int pos;
    long long val;
    struct MyList *next, *prev;
};
MyList *head;
MyList *tail;

void HeadInsert(int sym, long long value)
{
    MyList *temp = (MyList *)malloc(sizeof(MyList));
    temp->type = sym;
    temp->val = value;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        tail->next = NULL;
        tail->prev = NULL;
        head->next = NULL;
        head->prev = NULL;
        return;
    }
    temp->prev = NULL;
    temp->next = head;
    head->prev = temp;
    head = temp;
}

void TailInsert(int sym, long long value)
{
    MyList *temp = (MyList *)malloc(sizeof(MyList));
    temp->type = sym;
    temp->val = value;
    if (tail == NULL)
    {
        head = temp;
        tail = temp;
        tail->next = NULL;
        tail->prev = NULL;
        head->next = NULL;
        head->prev = NULL;
        return;
    }
    tail->next = temp;
    temp->prev = tail;
    temp->next = NULL;
    tail = temp;
}
long long Check()
{
    long long Max = 0;
    for (MyList *now = head; now != NULL; now = now->next)
    {
        if (now->type != 2)
        {
            continue;
        }
        Max = max(Max, now->val);
    }
    return Max;
}

void Print()
{
    MyList *cur = head;
    while (cur)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
}
int main()
{
    int n, m, positions, types;
    long long values;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &v[i]);
    }
    int id = 0;
    if (n != 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == 0)
            {
                x[++id] = i;
            }
            else if (a[i] == 1 && a[x[id]] == 0 && id != 0)
            {
                id--;
            }
            else if (a[i] == 1)
            {
                x[++id] = i;
            }
        }
        if (id == 0)
        {
            long long add = 0;
            for (int i = 0; i < n; i++)
            {
                add += v[i];
            }
            HeadInsert(2, add);
        }
        else
        {
            for (int i = 0; i < id; i++)
            {
                long long add = 0;
                for (int j = x[i] + 1; j < x[i + 1]; j++)
                {
                    add += v[j];
                }
                if (i == 0)
                {
                    add += v[0];
                    HeadInsert(a[0], add);
                    if (x[1] != 0)
                        TailInsert(a[x[i + 1]], v[x[i + 1]]);
                }
                else
                {
                    if (add)
                        TailInsert(2, add);
                    TailInsert(a[x[i + 1]], v[x[i + 1]]);
                }
            }
            long long add = 0;
            for (int i = x[id] + 1; i < n; i++)
            {
                add += v[i];
            }
            if (add)
                TailInsert(2, add);
        }
        Maxans = Check();
    }
    // Print();
    printf("%lld\n", Maxans);
    while (m--)
    {
        scanf("%d %d %lld", &positions, &types, &values);
        if (positions == 0)
        {
            long long add = values;
            MyList *nowloc = head;
            if (types == 0)
            {
                bool ex = 0;
                for (MyList *cur = head; cur != NULL && ex == 0; cur = cur->next)
                {
                    // cout << "h" << cur->val << endl;
                    add += cur->val;
                    if (cur->type == 1)
                    {
                        ex = 1;
                        cur->val = add;
                        cur->type = 2;
                        cur->prev = NULL;
                        // cout << "hi" << cur->val << endl;

                        if (cur->next != NULL && cur->next->type == 2)
                        {
                            if (cur->next == tail)
                            {
                                tail = cur;
                            }
                            // cout << "here" << endl;

                            add += cur->next->val;
                            cur->val += cur->next->val;
                            cur->next = cur->next->next;
                            if (cur->next)
                                cur->next->prev = cur;
                        }
                        if (cur->next != NULL)
                        {
                            cur->next->prev = cur;
                        }
                        if (cur == tail)
                        {
                            tail = cur;
                            // cout << "istail" << endl;
                        }
                        head = cur;
                        // cout << "HEADDDD" <<  head->val << endl;
                        if (Maxans < add)
                        {
                            Maxans = add;
                        }
                    }
                }
                if (ex == 0)
                {
                    HeadInsert(0, values);
                    // Print();
                    // cout << endl;
                }
            }
            else if (types == 1)
            {
                HeadInsert(1, values);
            }
            else if (types == 2 && nowloc != NULL && nowloc->type == 2)
            {
                // cout << "inthe2" << endl;
                // cout << nowloc->val;
                nowloc->val += values;
                if (Maxans < nowloc->val)
                {
                    Maxans = nowloc->val;
                }
            }
            else if (types == 2)
            {
                // cout << "intheother2" << endl;
                HeadInsert(2, values);
                if (Maxans < values)
                {
                    Maxans = values;
                }
            }
            // cout << "hhh" ;
            // Print();
            // cout << endl;
        }
        else if (positions == 1)
        {
            long long add = values;
            if (types == 1)
            {
                bool ex = 0;
                for (MyList *cur = tail; cur != NULL && ex == 0; cur = cur->prev)
                {
                    // cout << "tail" << tail->val << endl;
                    // cout << "inn\n";
                    add += cur->val;
                    if (cur->type == 0)
                    {
                        ex = 1;
                        cur->val = add;
                        cur->type = 2;
                        cur->next = NULL;

                        if (cur->prev != NULL && cur->prev->type == 2)
                        {
                            // cout << "Yes" << endl;
                            if (cur->prev == head)
                            {
                                head = cur;
                            }

                            add += cur->prev->val;
                            cur->val += cur->prev->val;
                            cur->prev = cur->prev->prev;
                        }
                        if (cur->prev != NULL)
                        {
                            // cout <<  "yes" << cur->prev->val << endl;

                            cur->prev->next = cur;
                        }
                        // cout << "head" << head->val << head->next->val << endl;
                        if (cur == head)
                        {
                            // cout << "yess" << endl;
                            head = cur;
                        }
                        tail = cur;
                        if (Maxans < add)
                        {
                            Maxans = add;
                        }
                    }
                }
                if (ex == 0)
                {

                    TailInsert(1, values);
                    // cout << "nowtailid" << tail->val << endl;
                }
            }
            else if (types == 0)
            {
                TailInsert(0, values);
            }
            else if (types == 2 && (tail != NULL) && tail->type == 2)
            {
                tail->val += values;
                if (Maxans < tail->val)
                {
                    Maxans = tail->val;
                }
            }
            else if (types == 2)
            {
                TailInsert(2, values);
                if (Maxans < values)
                {
                    Maxans = values;
                }
            }
            // cout << "hh";
            // Print();
            // cout << endl;
        }
        printf("%lld\n", Maxans);
    }
    return 0;
}

