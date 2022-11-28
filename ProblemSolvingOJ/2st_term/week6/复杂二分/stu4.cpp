#include <iostream>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L;
lld n, m, cnt = 0;
lld a[maxn];
lld same = 1;
lld sum = 0;
bool flag=0;
lld get_random()
{
    return A = C + (A * B) % MOD;
}
int part(lld left, lld right, lld mid)
{

    long long pivotvalue = a[mid];
    swap(a[mid], a[right]);
    int lindex = left;
    int rindex = left;
    for (int i = left; i < right; i++)
    {

        if (a[i] < pivotvalue)
        {
            sum += a[i];
            flag=1;
            swap(a[lindex], a[i]);
            if (lindex != rindex)
                swap(a[rindex], a[i]);
            rindex++;
            lindex++;
        }
        else if (a[i] == pivotvalue)
        {
            swap(a[rindex], a[i]);
            same++;
            rindex++;
        }
    }

    swap(a[rindex], a[right]);
    return lindex;
}

void selectfrom(lld left, lld right)
{
    same = 1;
    sum = 0;
    flag = 0;
    if (left > right)
    {
        cout << cnt;
        return;
    }

    if (right == left)
    {
        if (a[left] <= L)
        {
            cout << cnt + 1;
            return;
        }
        else
        {
            cout << cnt;
            return;
        }
    }
    lld mid = (rand() & 32767) % (right - left) + left;
    mid = part(left, right, mid);
    if(flag==0)
    {
        if(L>0&&a[mid]>0)
        {
            if (sum + same * a[mid] < L)
            {
                L -= sum + same * a[mid];
                cnt += mid - left + same;
                selectfrom(mid + same, right);
            }
            else if (sum + same * a[mid] >= L)
            {
                cout<<cnt+L/a[mid];
                return ;
            }
        }
        else if(L>0&&a[mid]<=0)
        {
            L -= sum + same * a[mid];
            cnt += mid - left + same;
            selectfrom(mid + same, right);
        }
        else if(L<=0&&a[mid]>0)
        {
            cout<<cnt;
            return ;
        }
        else if(L<=0&&a[mid]<=0)
        {
            if(same * a[mid] <= L)
            {
                L -= sum + same * a[mid];
                cnt += mid - left + same;
                selectfrom(mid + same, right);
            }
            else
            {
                cout<<cnt;
                return ;
            }
        }
    }
    else
    {
        if(sum + same * a[mid] <= L)
        {
            L -= sum + same * a[mid];
            cnt += mid - left + same;
            selectfrom(mid + same, right);
        }
        else
        {
            if(sum<=L)
            {
                    while(L-sum>=a[mid])
                    {
                        cnt++;
                        L-=a[mid];
                    }
                    cnt += mid - left ;
                cout<<cnt;
                    return;
            }
            else
            {
                selectfrom(left, mid-1);
            }
        }
    }
    
    
    
    
    
    
//    if (sum < L || flag==0)
//    {
//
//        if (sum + same * a[mid] < L)
//        {
//            L -= sum + same * a[mid];
//            cnt += mid - left + same;
//            selectfrom(mid + same, right);
//        }
//        else if (sum + same * a[mid] > L)
//        {
//            while(L-sum>=a[mid])
//            {
//                cnt++;
//                L-=a[mid];
//            }
//            cout << cnt + mid - left ;
//            return;
//        }
//        else
//        {
//            cout << cnt + mid - left + same;
//            return;
//        }
//    }
//    else if (sum == L)
//    {
//        cnt += mid - left;
//        L=0;
//        selectfrom(mid+1,right);
//    }
//    else
//    {
//        selectfrom(left, mid - 1);
//    }
}

int main()
{
    cin >> n >> A >> B >> C >> MOD >> L;
    srand((unsigned)time(0));
    for (int i = 1; i <= n; ++i)
        a[i] = get_random();
    selectfrom(1, n);
    //    18000000 1000000000 1000000000 1000000000 1000000000
    //  1000000000000000000

    //    for (int i = 1; i <= n; ++i) cout<<a[i]<<endl;
    //    sort(a+1,a+n+1);
    //
    //    i=1;
    //    while(1)
    //    {
    //        if(L<0)
    //        {
    //            cout<<cnt-1;
    //            return 0;
    //        }
    //        L-=a[i];
    //        i++;
    //        if(i>n&&L>=0)
    //        {
    //            cout<<n;
    //            return 0;
    //        }
    //
    //        cnt++;
    //    }
    //    while(1)
    //       {
    //
    //           temp=selectsmall(1,n,k);
    //           if(temp>L)
    //           {
    //               cout<<cnt;
    //               return 0;
    //           }
    //           L-=temp;
    //           cnt++;
    //           cout<<L<<endl;
    //           k++;
    //       }
    //    while(1)
    //    {
    //
    //        temp=selectsmall(1,n,k);
    //        if(temp*same>=L)
    //        {
    //            cout<<cnt+L/temp;
    //            return 0;
    //        }
    //        else
    //        {
    //            L-=temp*same;
    //            cnt+=same;
    //        }
    //        k++;
    //    }
    //

    return 0;
}

