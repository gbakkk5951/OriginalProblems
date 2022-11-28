#include <bits/stdc++.h>
using namespace std;

bool flag = false;
typedef long long lld;
const int maxn = 1.8e7 + 10;
lld A, B, C, MOD;
lld L;
int n, m;
lld get_random()
{
    return A = C + (A * B) % MOD;
}
int a[maxn];

int partion(int *a, int start, int end)
{
    int rnd = start + rand() % (end - start + 1);
    int tmp = a[rnd];
    a[rnd] = a[start]; //随机获取参考值
    while (start < end)
    {
        for (; start < end && a[end] > tmp; end--)
            ;
        if (start < end)
        {
            a[start++] = a[end];
        } //从右边选取第一个小于tmp的值复制到a[start]
        for (; start < end && a[start] < tmp; start++)
            ;
        if (start < end)
        {
            a[end--] = a[start];
        } //从左边选取第一个大于tmp的值复制到a[end]
    }
    a[start] = tmp; //将保存在tmp里面的a[start]存到最终的位置
    return start;
}

int findk(int *a, int start, int end, lld goal)
{
    int pivot = partion(a, start, end); //随机拆分成左小右大的2部分
    lld temp_sum = 0;                   //左边小元素的和
    for (int i = start; i <= pivot; i++)
    {
        temp_sum += a[i];
    }
    if ((temp_sum > goal) && a[pivot] > 0)
    {
        if (pivot == start)
            return 0;
        return findk(a, start, pivot - 1, goal);
    }
    else
    {
        if (pivot == end)
        {
            if (temp_sum > goal)
                return 0;
            else
                return pivot - start + 1;
        }
        return pivot - start + 1 + findk(a, pivot + 1, end, goal - temp_sum);
    }
}

int main()
{
    cin >> n >> A >> B >> C >> MOD >> L;
    for (int i = 1; i <= n; ++i)
        a[i] = get_random();
    cout << findk(a, 1, n, L);
    return 0;
}

