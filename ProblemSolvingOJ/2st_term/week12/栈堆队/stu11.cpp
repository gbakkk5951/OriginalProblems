#include<iostream>
using namespace std;
const int N = 4e6 + 5;
int array[2][N] , step[N] , prefix , total = 0 , popnum = 0 , acc = 0;
enum{
    num , order
};//order为0时为顺序，为1时为逆序
void work(int n , int m)
{
    if(n >= m>>1)
        printf("%d" , m);
    else
    {
        int head = 1 , tail = 0 , ans = 0;
        for(int i = 1 ; i <= m ; i++)
        {
            if(step[i] == 0)
            {
                if(array[num][(tail+1)%n])
                {
                    array[num][tail]++;
                    array[order][tail]=1;
                    ans += 4;
                }
                else
                {
                    tail = (tail+1)%n;
                    array[num][tail]++;
                    ans += 2;
                }
            }
            else
            {
                if(array[order][head])
                {
                    if(acc > 0)
                    {
                        array[num][head]--;
                        acc--;
                        if(array[num][head] == 1)
                            array[order][head] = 0;
                    }
                    else
                    {
                        array[num][(head+1)%n] += acc = array[num][head] - 1;
                        array[num][head] = 0;
                        array[order][head] = 0;
                        head = (head+1)%n;
                        tail = head;
                        if(array[num][head] > 1)
                            array[order][head] = 1;
                        else
                            acc = 0;
                    }
                }
                else
                {
                    array[num][head]--;
                    head = (head+1)%n;
                }
            }
        }
        printf("%d" , ans);
    }
    return;
}
int main()
{
    int n , m , tmp;
    scanf("%d %d" , &n , &m);
    getchar();
    for(int i = 1 ; i <= m ; i++)
    {
        tmp = getchar() - '0';
        if(tmp == 0)
        {
            step[++total] = tmp;
            prefix++;
        }
        else if(prefix > 0)
        {
            step[++total] = tmp;
            prefix--;
            popnum++;
        }
    }
    m = total;
    total = 0;
    for(int i = 1 ; i <= m ; i++)
    {
        if(step[i])
            step[++total] = step[i];
        else if(popnum)
        {
            step[++total] = step[i];
            popnum--;
        }
    }
    work(n , total);
}


