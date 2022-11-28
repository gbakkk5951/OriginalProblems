#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef long long lld;
const int maxn = 1.8e7 + 15;
const lld Error = __LONG_LONG_MAX__; //用这个最大数来表示已经选择过了这个当时的最值
lld A, B, C, MOD, Now_Adding = 0, Ans = 0, L = 0, n = 0, m = 0;
lld get_random()
{
    return A = C + (A * B) % MOD;
}
lld tmp_chose[maxn];
int Partion_lower_higher(lld *thisone, int start, int end)
{
	printf("P end - start %d\n", end - start);
	fflush(stdout);
    int Rand_index = start + rand() % (end - start);
    int tmp_refer = thisone[Rand_index];
    thisone[Rand_index] = thisone[start]; //随机获取参考值
    while (start < end)
    {
        while (start < end && thisone[end] > tmp_refer)
            --end; // don't be afraid of changing it
        if (start < end)
            thisone[start++] = thisone[end]; //从右边选取第一个小于tmp的值复制到thisone[start]
        while (start < end && thisone[start] < tmp_refer)
            ++start;
        if (start < end)
            thisone[end--] = thisone[start]; //从左边选取第一个大于tmp的值复制到thisone[end]
    }
    thisone[start] = tmp_refer; //将保存在tmp里面的thisone[start]存到最终的位置
	printf("ret %d\n", start);
    return start;
}
lld Find_No_k(lld *thisone, int start, int end, int k)
{
	printf("FNK  end - start %d\n", end - start);
    assert(k > 0 && k <= end - start + 1);                     // Not bad(())
    int tmp_index = Partion_lower_higher(thisone, start, end); //随机拆分成左小右大的2部分
    int nlower = tmp_index - start + 1;                        //左边小元素的个数
    if (k == nlower)                                           //若左边小元素个数恰好为k，则返回
        return thisone[tmp_index];
    else if (nlower < k) //左边元素个数比k少，则在右边继续寻找剩下的k-nlower
        return Find_No_k(thisone, tmp_index + 1, end, k - nlower);
    else
        return Find_No_k(thisone, start, tmp_index - 1, k); //继续在左边部分寻找第k大
}
lld Cal_all_lower_sum(lld *thisone, lld this_value, int No_number, int start, int end)
{
	printf("CAL  end - start %d\n", end - start);
    lld tmp_ans = 0, tmp_count = 0;
    for (int i = start; i <= end; i++)
        if (thisone[i] < this_value)
        {
            tmp_ans += thisone[i];
            ++tmp_count;
        }
    return this_value * (No_number - tmp_count) + tmp_ans; //将相等的数加上
}
lld Find_acc_max_k(lld *thisone, lld Now_sum, int start, int end, int count)
{
	printf("FAM  end - start %d\n", end - start);
    if (start == end)
        return (Now_sum + thisone[start] > L ? count : count + 1);
    else if (start == end - 1)
    {
        if (Now_sum + thisone[start] + thisone[end] > L)
        {
            if (Now_sum + thisone[start] <= L || Now_sum + thisone[start] <= L)
                return count + 1;
            else
                return count;
        }
        else
            return count + 2;
    }
    else
    {
        int Rand_index = Partion_lower_higher(thisone, start, end);
        lld tmp_ans = Now_sum;
		printf("(S %d, End %d, Rind %d)\n", start, end, Rand_index);
        for (int i = start; i <= Rand_index; i++)
            tmp_ans += thisone[i];
        if (tmp_ans > L)
            return Find_acc_max_k(thisone, Now_sum, start, Rand_index, count);
        else if (tmp_ans < L)
            return Find_acc_max_k(thisone, tmp_ans, Rand_index + 1, end, count + Rand_index - start + 1);
        else
            return count + Rand_index - start + 1;
    }
} //两个快排是吧（好小子
int main()
{
    scanf("%lld %lld %lld %lld %lld %lld", &n, &A, &B, &C, &MOD, &L);
    lld temop = 0, neg_sum = 0, post_index = 0;
    for (int i = 1; i <= n; ++i)
    {
        temop = get_random();
        if (temop <= 0)
        {
            neg_sum += temop;
            ++Ans;
        }
        else
            tmp_chose[++post_index] = temop;
    }
    L -= neg_sum;
    if (L < 0)
        Ans = 0;
    else if (L == 0)
        Ans += 0;
    else if (post_index > 0)
        Ans += Find_acc_max_k(tmp_chose, 0, 1, post_index, 0);
    printf("%lld", Ans);
    return 0;
}
