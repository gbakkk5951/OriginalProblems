#include <stdio.h>

int main ()
{
    int T;
    double a,t;
    scanf("%d",&T);
    for (int i = 1;i <= T;i ++){
        scanf("%lf%lf",&a,&t);
        long double d;
        d = a * t * t / 2.0;
        if(d < -0.3)
            d = 0 - d;
        printf("%.1Lf\n",d);
    }
    return 0;
}
