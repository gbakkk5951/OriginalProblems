#include <stdio.h>
#include <math.h>
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        double a, t, s;
        scanf("%lf %lf", &a, &t);
        s = fabs(a) * pow(t, 2) / 2.0;
        printf("%.1lf\n", s);
    }
    return 0;
}

