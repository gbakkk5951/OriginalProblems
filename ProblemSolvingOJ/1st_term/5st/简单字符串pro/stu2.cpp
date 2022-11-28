#include <iostream>

int main()
{
    int n, i, cnt = 0, overflowFlag;
    int A[1000001] = {0};
    int B[1000001] = {0};
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    B[0] = -1;
    for (i = 0; i < n; i++)
    {
        overflowFlag = 1;
        for (; i < n; i++)
        {
            if (A[i] == 0)
            {
                cnt++;
                B[cnt] = i;
                overflowFlag = 0;
                break;
            }
        }

        if (overflowFlag == 1)
        {
            if (cnt == 0 && n != 1)
                i = 1;
            else
            {
                if(cnt ==0 && n == 1)
                    i = 0;
                else
                    i = B[cnt] + 1;
            }

            while (n - i)
            {
                printf("overflow\n");
                i++;
            }
        }
        else
        {
            for (i = B[cnt - 1] + 1; i <= B[cnt]; i++)
                printf("%d\n", B[cnt] - i);
            i--;
        }
    }
    return 0;
}
