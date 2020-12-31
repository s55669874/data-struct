#include<stdio.h>
#include<math.h>
double distance(int a, int b)
{
    double new_a = a * 1.0, new_b = b * 1.0;
    double  calculus = (new_a * new_a) + (new_b * new_b);
    return calculus;
}
int main()
{
    int x, y;
    while(scanf("%d", &x) == 1 && scanf("%d", &y) == 1)
    {
        double dis = distance(x, y);
        if( dis < 100.0 * 100.0 ||  dis - 100.0*100.0 < 1e-6)
            printf("inside\n");
        else
            printf("outside\n");
    }
    return 0;
}
