#include <stdio.h>

int main()
{
    int T;
    char n;
    scanf("%d",&T);
    for(int i = 0;i<T;i++)
    {
        scanf("\n%c",&n);
        printf("%c%c%c    %c%c%c\n %c%c%c  %c%c%c\n  %c%c%c%c%c%c\n   %c%c%c%c\n   %c%c%c%c\n  %c%c%c%c%c%c\n %c%c%c  %c%c%c\n%c%c%c    %c%c%c\n",n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n);
    }
    return 0;
}
