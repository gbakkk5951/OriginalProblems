#include <cstdio>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int MaxN = 505;
const int MaxC = 1003;
const int MaxM = 5e5 + 5;
const int PoolSize = MaxN * MaxC + MaxM;


struct ListItem {
    int Index;
    int Nid;
    ListItem* next;
    ListItem* prev;
    bool liveStatus;
    /*To Do*/
    /*增加更多的数据成员以实现题目要求*/
    /*你必须用指针来实现链表的连接*/
}Pool[PoolSize];

typedef ListItem Li; //给ListItem起了一个别名Li

Li *Head[MaxN], *Tail[MaxN];//

int Index = 0;
Li* GetNewListItem() {
    ++Index;
    Li* NewOne = &Pool[Index];
    NewOne -> liveStatus = true;
    NewOne->Index = Index;//这里的编号和池的下标是同步的，可以直接通过Pool[i]来得到第i号表项, &Pool[i] 或 (Pool + i) 表示指向第i号表项的指针
    NewOne->next = NULL;
    return NewOne;
}
/*To Do*/

void TailIns(int nid)
{
    Li* newNode = GetNewListItem();
    newNode -> Nid = nid;
    if (Tail[nid] == NULL)
    {
        Tail[nid] = newNode;
        Head[nid] = newNode;
    }
    else
    {
        Tail[nid] -> next = newNode;
        newNode -> prev = Tail[nid];
        Tail[nid] = newNode;
        
    }
    
}

void HeadIns(int nid)
{
    Li* newNode = GetNewListItem();
    newNode -> Nid = nid;
    if (Head[nid] == NULL){
        Head[nid] = newNode;
        Tail[nid] = newNode;
    }
    else
    {
        Head[nid] -> prev = newNode;
        newNode -> next = Head[nid];
        Head[nid] = newNode;
    }
}

void Delete(int id){
    if ((id <= 0)||(id > Index)||(Pool[id].liveStatus == false)){
        return;
    }
    else{
        int nid = Pool[id].Nid;
        
        if (Head[nid] == NULL){
            return;
        }
        else if (Head[nid] == Tail[nid]){
            //cout << "a" << endl;
            Head[nid] = NULL;
            Tail[nid] = NULL;
            Pool[id].liveStatus = false;
        }
        else{
            Pool[id].liveStatus = false;
            Li* last = Pool[id].prev;
            Li* later = Pool[id].next;
            if (last == NULL){
                Head[nid] = Pool[id].next;
                 if (Tail[nid] == &Pool[id]) Tail[nid] = NULL;
            }
            else if (later == NULL){
                Tail[nid] = Pool[id].prev;
                if (Head[nid] == &Pool[id]) Head[nid] = NULL;
            }
            else{
                last -> next = Pool[id].next;
                later -> prev = Pool[id].prev;
            }
        }
    }
}


void changeId(int id, int x){
    if ((id <= 0)||(id > Index)||(Pool[id].liveStatus == false)){
        return;
    }
    else{
        int nid = Pool[id].Nid;
        if ((Head[nid] == NULL)&&(Tail[nid] == NULL)){
            assert(0);
            return;
        }
        else{
            Pool[id].Index = x;
        }
    }
}

void output(int id){
        if ((id <= 0)||(id > Index)||(Pool[id].liveStatus == false)){
            cout << "NULL " << "NULL " << "NULL" << endl;
        }
        else{
            Li* last = Pool[id].prev;
            Li* later = Pool[id].next;
            if (last == NULL){
                cout << "NULL ";
            }
            else{
                if (last -> liveStatus == false){
                    cout << "NULL ";
                }
                else{
                    cout << last -> Index << " ";
                }
            }
            cout << Pool[id].Index << " ";
            if (later == NULL){
                cout << "NULL ";
            }
            else{
                if (later -> liveStatus == false){
                    cout << "NULL ";
                }
                else{
                    cout << later -> Index << " ";
                }
            }
            cout << endl;
        }
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){
        int c;
        cin >> c;
        for (int j = 1; j <= c; j++){
            TailIns(i);
        }
    }
    int m;
    cin >> m;
    while(m--){
        int k;
        cin >> k;
        if (k == 1){
            int id;
            cin >> id;
            output(id);
        }
        if (k == 2){
            int id;
            cin >> id;
            Delete(id);
        }
        if (k == 3){
            int id;
            cin >> id;
            HeadIns(id);
        }
        if (k == 4){
            int id;
            cin >> id;
            TailIns(id);
        }
        if (k == 5){
            int id, x;
            cin >> id >> x;
            changeId(id, x);
        }
    }
    /*To Do*
    /*书写更多代码以实现本题的要求*/
    
    return 0;
}
